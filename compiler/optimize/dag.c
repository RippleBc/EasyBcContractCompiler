#include "../common.h"

#include _YTAB_H_

static int where = DAG; /* 定义DAG所在内存区域 */

static struct dag
{
    struct _node node; /* DAG节点 */
    struct dag *hlink; /* 链接下一个DAG节点 */
}*buckets[16]; /* 存放DAG node */


int nodecount;
static int depth = 0;
static struct dag *dag_node(int, Node, Node, Symbol);
static void kill_nodes(Symbol);
static void reset(void);
static Node node(int, Node, Node, Symbol);

static int print_level = 0; /* 输出层次 */

#ifdef DEBUG
static int travel_level = 0; /* 遍历层次 */
#endif

extern int dump_ast; /* 是否输出ast信息 */
extern int dump_dag; /* 是否输出dag信息 */
extern int dump_asm; /* 是否输出sam信息 */

/* 哈希函数 */
#define available_node_hash(op, left, right, sym) (opindex(op)^((unsigned long)sym>>2))&(NELEMS(buckets)-1)

static struct dag *dag_node(int op, Node l, Node r, Symbol sym)
{
    struct dag *p;

    NEW0(p, where);

    /* 对应的指令*/
    p->node.op = op;

    /* 初始化左右节点，引用次数 */
    if ((p->node.kids[0] = l) != NULL)
        ++l->count;
    if ((p->node.kids[1] = r) != NULL)
        ++r->count;

    /* 对应的符号 */
    p->node.syms[0] = sym;
#if DEBUG & COMMON_EXPR_DEBUG

    if (sym)
        printf("node %s (%s) created.\n", get_op_name(generic(op)), sym->name);
    else
        printf("node %s created.\n", get_op_name(generic(op)));
#endif

    return p;
}

static Node node(int op, Node l, Node r, Symbol sym)
{
    int i;
    struct dag *p;

    /* DAG节点哈希值 */
    i = available_node_hash(op, l, r, sym);

    /* 检查是否有相同的DAG节点 */
    for (p = buckets[i]; p; p = p->hlink)
    {
        if (p->node.op == op && p->node.syms[0] == sym &&  p->node.kids[0] == l  && p->node.kids[1] == r)
        {
            /* 相同的DAG节点，刷新引用次数 */
            p->node.count ++;
#if DEBUG & CONST_FOLDING_DEBUG

            printf("common expr found %s (%s).\n",
                   get_op_name(generic(p->node.op)),
                   p->node.syms[0]->name);
#endif
            return &p->node;
        }
    }

    /* 初始化DAG节点 */
    p = dag_node(op, l, r, sym);

    /* 插入DAG链表头部 */
    p->hlink = buckets[i];
    buckets[i] = p;

    /* 刷新DAG节点数量 */
    ++nodecount;

    return &p->node;
}

Node new_node(int op, Node l, Node r, Symbol sym)
{
    /* 返回DAG节点地址 */
    return &dag_node(op, l, r, sym)->node;
}

static void kill_nodes(Symbol p)
{
    int i;
    struct dag **q;

    for (i = 0; i < NELEMS(buckets); i++)
    {
        for (q = &buckets[i]; *q; )
        {
            /* 清楚与符号p相关联的节点 */
            if (generic((*q)->node.op) == LOAD &&
                    ((*q)->node.syms[0] == p))
            {
#if DEBUG & COMMON_EXPR_DEBUG
                printf("node %s killed.\n", p->name);
#endif
                /* 清除当前DAG节点 */
                *q = (*q)->hlink;
                --nodecount;
            }
            else
            {
                q = &(*q)->hlink;
            }
        }
    }
}

static void reset(void)
{
    if (nodecount > 0)
        memset(buckets, 0, sizeof buckets);
    nodecount = 0;
}

Node travel(Tree tp)
{
    Node p = NULL, l = NULL, r = NULL;
    int op;

    if (tp == NULL)
        return NULL;

    if (tp->dag_node)
        return tp->dag_node;

    travel_level++;

    op = tp->op;
    switch (generic(tp->op))
    {
    case ARRAY:
        
        /* tp->kids[0]表示数组的下标（表达式） */
        l = travel(tp->kids[0]);
        
        /* tp->u.generic.sym表示数组对应的符号 */
        p = node(op, l, NULL, tp->u.generic.sym);
        break;
    case AND:
    case OR:
        if (depth++ == 0)
            reset();

        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        depth--;
        p = node(op, l, r, NULL);

        /* 常量合并 */
        const_folding(p);
        break;
    case NOT:
        depth++;
        l = travel(tp->kids[0]);
        depth--;
        p = node(op, l, NULL, NULL);

        /* 常量合并 */
        const_folding(p);
        break;
    case COND:
        /* tp->kids[0]表示判断条件（表达式） */
        l = travel(tp->kids[0]);
        reset();
        p = new_node(op, l, NULL, tp->u.cond_jump.label);

        /* 跳转标签符号 */
        p->u.cond.label = tp->u.cond_jump.label;

        /* 跳转条件（为真跳转还是为假跳转） */
        p->u.cond.true_or_false = tp->u.cond_jump.true_or_false;
        break;
    case CNST:
        p = new_node(op, NULL, NULL, tp->u.generic.sym);
        break;
    case RIGHT:
        /* 参数AST节点的子节点，表示实参 */
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        p = node(op, l, r, NULL);
        break;
    case JUMP:
        p = new_node(op, NULL, NULL, tp->u.generic.sym);
        reset();
        break;
    case CALL:
        l = travel(tp->kids[0]);
        p = new_node(op, l, NULL, NULL);

        /* 自定义函数或者过程调用对应的符号表 */
        p->symtab = tp->u.generic.symtab;
        break;
    case SYS:
        l = travel(tp->kids[0]);
        p = new_node(op, l, NULL, NULL);

        /* 对应系统函数或者系统过程的ID */
        p->u.sys_id = tp->u.sys.sys_id;

        /* 读取字符或者读取字符串操作 */
        if (p->u.sys_id == pREAD || p->u.sys_id == pREADLN)
        {
            /* 地址AST树的第一个子节点为空，变量类型不是数组或者记录 */
            if (tp->kids[0]->kids[0] == NULL)
                kill_nodes(tp->kids[0]->u.generic.sym);
            else
                reset();
        }
        break;
    case ARG:
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);

        /* tp->u.arg.sym表示参数对应的符号 */
        p = new_node(op, l, r, tp->u.generic.sym);

        /* tp->u.arg.symtab表示对应的符号表 */
        p->symtab = tp->u.generic.symtab;
        break;
    case EQ:
    case NE:
    case GT:
    case GE:
    case LE:
    case LT:
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        p = node(op, l, r, NULL);

        /* 常量合并 */
        const_folding(p);
        break;
    case ASGN:
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        p = node(op, l, r, NULL);

        /* 地址AST节点的第一个子节点为空，变量类型不是数组和记录 */
        if (tp->kids[0]->kids[0] == NULL)
            /* 清除相同的变量 */
            kill_nodes(tp->kids[0]->u.generic.sym);
        else
            reset();
        break;
    case BOR: /* 二进制或 */
    case BAND: /* 二进制与 */
    case BXOR: /* 二进制异或 */
    case ADD:
    case SUB:
    case RSH: /* 右移 */
    case LSH: /* 左移 */
    case DIV:
    case MUL:
    case MOD:
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        p = node(op, l, r, NULL);

        /* 常量合并 */
        const_folding(p);
        break;
    case CVF:
    case CVI:
    case CVP:
        l = travel(tp->kids[0]);
        p = node(op, l, NULL, NULL);
        break;
    case BCOM: /* 二进制比较 */
    case NEG:
        l = travel(tp->kids[0]);
        p = node(op, l, NULL, NULL);

        /* 常量合并 */
        const_folding(p);
        break;
    case LOAD:
    case INDIR:

        if (tp->kids[0])
            l = travel(tp->kids[0]);

        if (tp->kids[0] && (generic(tp->kids[0]->op) == FIELD))
        {
            p = node(op, l, NULL, tp->kids[0]->u.field.field);
        }
        else if (tp->kids[0] && (generic(tp->kids[0]->op) == ARRAY))
        {
            p = node(op, l, NULL, tp->kids[0]->u.generic.sym);
        }
        else
        {
            p = node(op, l, NULL, tp->u.generic.sym);
        }
        break;
    case FIELD:
        /* tp->u.field.record表示记录符号 */
        p = node(op, NULL, NULL, tp->u.field.record);

        if (p->syms[1] != tp->u.field.field)
            p = new_node(op, NULL, NULL, tp->u.field.record);

        /* tp->u.field.field表示属性符号 */
        p->syms[1] = tp->u.field.field;
        break;
    case ADDRG:
        l = travel(tp->kids[0]);
        p = node(op, l, NULL, tp->u.generic.sym);
        break;
    case HEADER:
        p = new_node(tp->op, NULL, NULL, NULL);
        p->symtab = tp->u.header.symtab;
        break;
    case TAIL:
        p = new_node(tp->op, NULL, NULL, NULL);
        p->symtab = tp->u.generic.symtab;
        break;
    case BLOCKBEG:
    case BLOCKEND:
        p = new_node(tp->op, NULL, NULL, NULL);
        break;
    case LABEL:
        p = new_node(tp->op, NULL, NULL, tp->u.generic.sym);
        break;
    case INCR:
    case DECR:
        l = travel(tp->kids[0]);
        p = new_node(tp->op, l, NULL, NULL);
        break;
    default:
        assert(0);
    }


    travel_level--;
#if DEBUG & DAG_DEBUG

    p->op_name = get_op_name(p->op);
#endif

    /* DAG节点类型 */
    p->type = tp->result_type;

    /* DAG节点与AST节点相关联 */
    tp->dag_node = p;
    return p;
}

int gen_dag(List ast_forest, List dag_forest)
{
    int n, i, dag_count;
    Tree *forest;

    if (dump_ast)
        print_forest(ast_forest);

    n = list_length(ast_forest);

    /* AST节点链表转化为数组 */
    forest = (Tree *)list_ltov(ast_forest, STMT);

    reset();

    for (i = 0, dag_count = 0; i < n ; i++)
    {
        Tree ast = forest[i];

        /* 生成DAG节点 */
        Node dag = travel(ast);
        if (dag)
        {
            /* 添加到DAG森林 */
            list_append(dag_forest, dag);
            dag_count++;
        }
    }

    /* clean temporary memory. */
    deallocate(STMT);
    return dag_count;
}

static int mark(Node cp)
{
    /* mark children first. */
    if (cp->kids[0])
        mark(cp->kids[0]);
    if (cp->kids[1])
        mark(cp->kids[1]);
    if (cp->kids[2])
        mark(cp->kids[2]);

    /* mark node itself. */
    return (*IR->mark_node)(cp);
}

int emit_code(List dags)
{
    // int should_stop = 0;
    // List cp;

    // if (dump_dag)
    // {
    //     print_dags(dags);
    // }
    
    // for (cp = dags->link; cp; cp = cp->link)
    // {
    //     if ((should_stop = mark((Node)cp->x)) < 0)
    //     {
    //         return should_stop;
    //     }
    // }

    // (*IR->function_process)(dags);

    // return should_stop;
    return 0;
}

static void print_node(Node n)
{
    int i;

    if (n == NULL)
        return;

    printf("+");
    for (i = 0; i < print_level; i++)
    {
        printf("-");
    }

    if (generic(n->op) == CNST)
        printf("%s(%d)\n", get_op_name(generic(n->op)), n->syms[0]->v.i);
    else
        printf("%s\n", get_op_name(generic(n->op)));

    print_level++;

    if (n->kids[0])
        print_node(n->kids[0]);

    if (n->kids[1])
        print_node(n->kids[1]);

    print_level--;
}


void print_dags(List dags)
{
    List cp;

    printf("\n--------------dags---------------------------\n");

    cp = dags->link;
    for (; cp; cp = cp->link)
    {
        printf("\n\n");
        print_level = 0;
        print_node((Node)cp->x);
    }
}

