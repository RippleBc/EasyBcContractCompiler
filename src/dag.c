#include "common.h"

#include _YTAB_H_

#define iscall(op) (generic(op) == CALL || IR->mulops_calls \
				&& (generic(op)==DIV || generic(op)==MOD || generic(op)==MUL) \
				&& (optype(op)==U || optype(op)==I))
/* static Node forest; */

static int where = DAG;

static struct dag
{
    struct _node node;
    struct dag *hlink;
}
*buckets[16];


int nodecount;
static int depth = 0;
static struct dag *dag_node(int, Node, Node, Symbol);
static void kill_nodes(Symbol);
static void reset(void);
static Node node(int, Node, Node, Symbol);

static int print_level = 0;

#ifdef DEBUG
static int travel_level = 0;
#endif

extern int dump_ast;
extern int dump_dag;
extern int dump_asm;

/* hash function. */
#define available_node_hash(op, left, right, sym)	(opindex(op)^((unsigned long)sym>>2))&(NELEMS(buckets)-1)

static struct dag *dag_node(int op, Node l, Node r, Symbol sym)
{
    struct dag *p;

    NEW0(p, where);
    p->node.op = op;
    if ((p->node.kids[0] = l) != NULL)
        ++l->count;
    if ((p->node.kids[1] = r) != NULL)
        ++r->count;
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

    i = available_node_hash(op, l, r, sym);
    /* (opindex(op)^((unsigned long)sym>>2))&(NELEMS(buckets)-1); */
    for (p = buckets[i]; p; p = p->hlink)
        if (p->node.op == op && p->node.syms[0] == sym
                &&  p->node.kids[0] == l  && p->node.kids[1] == r)
        {
            p->node.count ++;
            /* match. */
#if DEBUG & CONST_FOLDING_DEBUG

            printf("common expr found %s (%s).\n",
                   get_op_name(generic(p->node.op)),
                   p->node.syms[0]->name);
#endif

            return &p->node;
        }
    p = dag_node(op, l, r, sym);
    p->hlink = buckets[i];
    buckets[i] = p;
    ++nodecount;
    return &p->node;
}

Node new_node(int op, Node l, Node r, Symbol sym)
{
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
            /*
            if (generic((*q)->node.op) == LOAD &&
            	(!isaddrop((*q)->node.kids[0]->op)
            	 || (*q)->node.kids[0]->syms[0] == p)) 
            */
            if (generic((*q)->node.op) == LOAD &&
                    ((*q)->node.syms[0] == p))
            {
#if DEBUG & COMMON_EXPR_DEBUG
                printf("node %s killed.\n", p->name);
#endif

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
    Node p = NULL, l, r;
    int op;

    if (tp == NULL)
        return NULL;

    l = r = NULL;

    if (tp->dag_node)
        return tp->dag_node;

    travel_level++;

    op = tp->op;
    switch (generic(tp->op))
    {
    case AND:
        if (depth++ == 0)
            reset();
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        depth--;
        p = node(op, l, r, NULL);
        const_folding(p);
        break;
    case ARRAY:
        l = travel(tp->kids[0]);
        p = node(op, l, NULL, tp->u.generic.sym);
        break;
    case OR:
        if (depth++ == 0)
            reset();
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        depth--;
        p = node(op, l, r, NULL);
        const_folding(p);
        break;
    case NOT:
        depth++;
        l = travel(tp->kids[0]);
        depth--;
        p = node(op, l, NULL, NULL);
        const_folding(p);
        break;
    case COND:
        l = travel(tp->kids[0]);
        reset();
        p = new_node(op, l, NULL, tp->u.cond_jump.label);
        p->u.cond.label = tp->u.cond_jump.label;
        p->u.cond.true_or_false = tp->u.cond_jump.true_or_false;
        break;
    case CNST:
        p = new_node(op, NULL, NULL, tp->u.generic.sym);
        break;
    case RIGHT:
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
        p->symtab = tp->u.call.symtab;
        break;
    case SYS:
        l = travel(tp->kids[0]);
        p = new_node(op, l, NULL, NULL);
        p->u.sys_id = tp->u.sys.sys_id;
        if (p->u.sys_id == pREAD ||
                p->u.sys_id == pREADLN)
        {
            /* kill nodes. */
            if (tp->kids[0]->kids[0] == NULL)
                kill_nodes(tp->kids[0]->u.generic.sym);
            else
                reset();
        }
        break;
    case ARG:
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        p = new_node(op, l, r, tp->u.arg.sym);
        p->symtab = tp->u.arg.symtab;
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
        const_folding(p);
        break;
    case ASGN:
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        p = node(op, l, r, NULL);
        /* kill nodes. */
        if (tp->kids[0]->kids[0] == NULL)
            kill_nodes(tp->kids[0]->u.generic.sym);
        else
            reset();
        break;
    case BOR:
    case BAND:
    case BXOR:
    case ADD:
    case SUB:
    case RSH:
    case LSH:
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        p = node(op, l, r, NULL);
        const_folding(p);
        break;
    case DIV:
    case MUL:
    case MOD:
        l = travel(tp->kids[0]);
        r = travel(tp->kids[1]);
        p = node(op, l, r, NULL);
        const_folding(p);
        break;
    case RET:
        /* not used in SPL. */
        break;
    case CVF:
    case CVI:
    case CVP:
        l = travel(tp->kids[0]);
        p = node(op, l, NULL, NULL);
        break;
    case BCOM:
    case NEG:
        l = travel(tp->kids[0]);
        p = node(op, l, NULL, NULL);
        /* const_folding(p); */
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
        p = node(op, NULL, NULL, tp->u.field.record);
        if (p->syms[1] != tp->u.field.field)
            p = new_node(op, NULL, NULL, tp->u.field.record);
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
        p = new_node(tp->op, NULL, NULL, tp->u.label.label);
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

    p->type = tp->result_type;
    tp->dag_node = p;
    return p;
}


/**
 * generate dag from ast.
 * return number of generated dag.
 */
int gen_dag(List ast_forest, List dag_forest)
{
    int n, i, dag_count;
    Tree *forest;

    if (dump_ast)
        print_forest(ast_forest);

    n = list_length(ast_forest);
    forest = (Tree *)list_ltov(ast_forest, STMT);

    /* reset available nodes table. */
    reset();

    for (i = 0, dag_count = 0; i < n ; i++)
    {
        Tree ast = forest[i];

        Node dag = travel(ast);
        if (dag)
        {
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

/*
 * emit asm code.
 **/
int emit_code(List dags)
{
    int should_stop = 0;
    List cp;

    if (dump_dag)
        print_dags(dags);

    /* chance for back end to select instructions and regisgers. */
    cp = dags->link;
    for (; cp; cp = cp->link)
    {
        if ((should_stop = mark((Node)cp->x)) < 0)
            return should_stop;
    }

    /* call back end to generate asm code. */
    (*IR->function_process)(dags);

    return should_stop;
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

