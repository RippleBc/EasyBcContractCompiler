#include "../common.h"
#include "../parser/rule.h"

static int where = DAG; /* 定义DAG所在内存区域 */

static struct dag
{
    struct _node node; /* DAG节点 */
    struct dag *hlink; /* 链接下一个DAG节点 */
}*buckets[16]; /* 存放DAG node */


int nodecount;
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

#define available_node_hash(op, sym) (opindex(op)^((unsigned long)sym>>2))&(NELEMS(buckets)-1)

static struct dag *dag_node(int op, Node l, Node r, Symbol sym)
{
    struct dag *p;

    NEW0(p, where);

    /* 指令*/
    p->node.op = op;

    /* 引用次数 */
    if ((p->node.kids[0] = l) != NULL)
        ++l->count;
    if ((p->node.kids[1] = r) != NULL)
        ++r->count;

    /* 符号 */
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

    i = available_node_hash(op, sym);

    for (p = buckets[i]; p; p = p->hlink)
    {
        /* 检查节点是否存在 */
        if (p->node.op == op && p->node.syms[0] == sym &&  p->node.kids[0] == l  && p->node.kids[1] == r)
        {
            /* 公共表达式存在，刷新引用次数 */
            p->node.count ++;

#if DEBUG & COMMON_EXPR_DEBUG
            printf("common expr found %s (%s).\n", get_op_name(generic(p->node.op)), p->node.syms[0]->name);
#endif
            /* 返回已经存在的公共表达式 */
            return &p->node;
        }
    }

    /* 创建新节点 */
    p = dag_node(op, l, r, sym);

    /* 插入 */
    p->hlink = buckets[i];
    buckets[i] = p;

    /* 刷新数量 */
    ++nodecount;

    return &p->node;
}

Node new_node(int op, Node l, Node r, Symbol sym)
{
    return &(dag_node(op, l, r, sym)->node);
}

static void kill_nodes(Symbol p)
{
    int i;
    struct dag *q;

    for (i = 0; i < NELEMS(buckets); i++)
    {
        q = buckets[i];
        while(q != NULL)
        {
            /* 引用变量p的值的节点 */
            if (generic(q->node.op) == LOAD && (q->node.syms[0] == p))
            {
#if DEBUG & COMMON_EXPR_DEBUG
                printf("node %s killed.\n", p->name);
#endif
                /* 删除节点（变量的值已经发生改变，无法被重复指定） */
                q = q->hlink;
                --nodecount;
            }
            else
            {
                q = q->hlink;
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
    case CVF:
    case CVI:
    case CVP:
        l = travel(tp->kids[0]);
        /* 变量 */
        p = node(op, l, NULL, NULL);
        break;
    }

    switch (generic(tp->op))
    {
    case CNST:
        /* 常量 */
        p = new_node(op, NULL, NULL, tp->u.generic.sym);
        break;
    case ARRAY:
        l = travel(tp->kids[0]);
        
        /* 数组下标，数组变量 */
        p = node(op, l, NULL, tp->u.generic.sym);
        break;
    case FIELD:
        /* tp->u.field.record表示记录符号 */
        p = node(op, NULL, NULL, tp->u.field.record);

        /*  */
        if (p->syms[1] != tp->u.field.field)
        {
            p = new_node(op, NULL, NULL, tp->u.field.record);
        }

        /* tp->u.field.field表示属性符号 */
        p->syms[1] = tp->u.field.field;
        break;
    case ASGN:
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);

        /* 变量，赋值表达式 */
        p = node(op, l, r, NULL);

        /*  */
        kill_nodes(tp->kids[0]->u.generic.sym);
        
        break;
    case ADDRG:
        l = travel(tp->kids[0]);

        /*  */
        p = node(op, l, NULL, tp->u.generic.sym);
        break;
    case LOAD:
        if(tp->u.generic.sym)
        {
            p = node(op, l, NULL, tp->u.generic.sym);
        }
        else
        {
            l = travel(tp->kids[0]);
            /*  */
            p = node(op, l, NULL, NULL);
        }
        break;
    }

    switch (generic(tp->op))
    {
    case LABEL:
        p = new_node(tp->op, NULL, NULL, tp->u.generic.sym);
        break;
    case ARG:
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);

        /* tp->u.arg.sym表示参数对应的符号 */
        p = new_node(op, l, r, tp->u.generic.sym);

        /* tp->u.arg.symtab表示对应的符号表 */
        p->symtab = tp->u.generic.symtab;
        break;
    case RIGHT:
        /* 参数AST节点的子节点，表示实参 */
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        p = node(op, l, r, tp->u.generic.sym);
        break;
    case COND:
        /* tp->kids[0]表示判断条件（表达式） */
        l = travel(tp->kids[0]);
        p = new_node(op, l, NULL, tp->u.cond_jump.label);

        /* 跳转标签符号 */
        p->u.cond.label = tp->u.cond_jump.label;

        /* 跳转条件（为真跳转还是为假跳转） */
        p->u.cond.true_or_false = tp->u.cond_jump.true_or_false;
        break;
    case JUMP:
        p = new_node(op, NULL, NULL, tp->u.generic.sym);
        break;
    case CALL:
        l = travel(tp->kids[0]);
        p = new_node(op, l, NULL, NULL);

        /* 自定义函数或者过程调用对应的符号表 */
        p->symtab = tp->u.generic.symtab;
        break;
    case SYS:
        l = travel(tp->kids[0]);

        /* address tree or array field tree */
        p = new_node(op, l, NULL, NULL);

        /* 对应系统函数或者系统过程的ID */
        p->u.sys_id = tp->u.sys.sys_id;

        /* 读取字符或者读取字符串操作 */
        if (p->u.sys_id == pREAD || p->u.sys_id == pREADLN)
        {
            kill_nodes(tp->kids[0]->u.generic.sym);
        }
        break;
    }

    switch (generic(tp->op))
    {
    case INCR:
    case DECR:
        l = travel(tp->kids[0]);
        p = new_node(tp->op, l, NULL, NULL);
        break;
    }

    switch (generic(tp->op))
    {
    case NOT:
    case NEG:
        l = travel(tp->kids[0]);
        p = node(op, l, NULL, NULL);

        /* 常量合并 */
        const_folding(p);
        break;
    case AND:
    case OR:
    case BOR: /* 二进制或 */
    case BAND: /* 二进制与 */
    case BXOR: /* 二进制异或 */
    case LSH: /* 左移 */
    case RSH: /* 右移 */
    case EQ:
    case NE:
    case GT:
    case GE:
    case LE:
    case LT:
    case ADD:
    case SUB:
    case DIV:
    case MUL:
    case MOD:
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        p = node(op, l, r, NULL);

        /* 常量合并 */
        const_folding(p);
        break;
    }

    switch (generic(tp->op))
    {
    case HEADER:
    case TAIL:
        p = new_node(tp->op, NULL, NULL, NULL);
        p->symtab = tp->u.generic.symtab;
        break;
    case BLOCKBEG:
    case BLOCKEND:
        p = new_node(tp->op, NULL, NULL, NULL);
        break;
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

    /*  */
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

