#include "common.h"

/* alloc memory from tree arena. */
static int where = TREE;
static int print_level = 0;

/* new tree or node */
Tree new_tree(int op, Type type, Tree left, Tree right)
{

    Tree p;

    NEW0(p, where);
    p->op = op;
    p->result_type = type;
    p->kids[0] = left;
    p->kids[1] = right;
    return p;
}

/* new header tree. */
Tree header_tree(symtab *ptab)
{
    Tree t;

    t = new_tree(HEADER, ptab->type, NULL, NULL);
    t->u.generic.symtab = ptab;
    return t;
}

/* type conversion tree. */
Tree conversion_tree(Symbol source, Type target)
{
    Tree t;

    switch (target->type_id)
    {
    case TYPE_INTEGER:
        t = new_tree(CVI, target, NULL, NULL);
        break;
    case TYPE_REAL:
        t = new_tree(CVF, target, NULL, NULL);
        break;
    case TYPE_POINTER:
        t = new_tree(CVP, target, NULL, NULL);
        break;
    case TYPE_BOOLEAN:
        t = new_tree(CVB, target, NULL, NULL);
        break;
    }

    t->u.generic.sym = source;
    return t;
}

/* get value of id tree. */
Tree id_factor_tree(Tree source, Symbol sym)
{
    Tree t;

    if (source)
        t = new_tree(LOAD, source->result_type, source, NULL);
    else
        t = new_tree(LOAD, sym->type, NULL, NULL);
    t->u.generic.sym = sym;
    return t;
}

/* get address tree */
Tree address_tree(Tree source, Symbol sym)
{
    Tree t;

    if (source)
        t = new_tree(ADDRG, source->result_type, source, NULL);
    else
        t = new_tree(ADDRG, sym->type, NULL, NULL);
    t->u.generic.sym = sym;
    return t;
}

/* negative tree */
Tree neg_tree(Tree source)
{
    Tree t;

    t = new_tree(NEG, source->result_type, source, NULL);
    return t;
}

/* not operation tree. */
Tree not_tree(Tree source)
{
    Tree t;

    t = new_tree(NOT, source->result_type, source, NULL);
    return t;
}


/* Right tree.
 * holding arguments, comma operations.
 */
Tree right_tree(Tree *root, Tree newrightpart)
{
    Tree right;

    if (*root == NULL)
    {
        *root = new_tree(RIGHT, newrightpart->result_type, newrightpart, NULL);
        return *root;
    }

    /* right = (*root)->kids[1]; */
    right = (*root);

    while(right->kids[1] != NULL)
        right = right->kids[1];

    right->kids[1] = new_tree(RIGHT, newrightpart->result_type, newrightpart, NULL);

    return right->kids[1];
}


/* arguments tree.
 * set argtree to NULL when first called.
 */
Tree arg_tree(Tree argtree, Symtab function, Symbol arg, Tree expr)
{
    Tree t, right;

    if (arg != NULL && arg->type->type_id != expr->result_type->type_id)
    {
        /* do conversions, left for excises. */
        parse_error("type miss match.", "");
    }

    if (argtree == NULL)
    {
        if (arg != NULL) 
            t = new_tree(ARG, arg->type, expr, NULL);
        else
            t = new_tree(ARG, expr->result_type, expr, NULL);
        t->u.arg.sym = arg;
        t->u.arg.symtab = function;
        return t;
    }

    /* append to right tree. */
    right = right_tree(&(argtree->kids[1]), expr);
    right->u.arg.sym = arg;
    right->u.arg.symtab = function;

    return argtree;
}

/* get value of a field of record. */
Tree field_tree(Symbol record, Symbol field)
{
    Tree t;

    t = new_tree(FIELD, field->type, NULL, NULL);
    t->u.field.record = record;
    t->u.field.field = field;
    return t;

}

/* get value of an item of array. */
Tree array_factor_tree(Symbol array, Tree expr)
{
    Tree t;

    t = new_tree(ARRAY, array->type->last->type, expr, NULL);
    t->u.generic.sym = array;
    return t;
}

/*  const value */
Tree const_tree(Symbol constval)
{
    Tree t;

    t = new_tree(CNST, constval->type, NULL, NULL);
    t->u.generic.sym = constval;
    return t;
}

/*  function call */
Tree call_tree(Symtab routine, Tree argstree)
{
    Tree t;

    t = new_tree(CALL, routine->type, argstree, NULL);
    t->u.call.symtab = routine;
    return t;
}

/*  system call */
Tree sys_tree(int sys_id, Tree argstree)
{
    Tree t;
    Symtab ptab;

    ptab = find_sys_routine(sys_id);
    if (ptab)
        t = new_tree(SYS, ptab->type, argstree, NULL);
    else
        t = new_tree(SYS, find_type_by_id(TYPE_VOID), argstree, NULL);

    t->u.sys.sys_id = sys_id;
    return t;
}

/* 
 * binary operation.
 */
Tree binary_expr_tree(int op, Tree left, Tree right)
{
    Tree t;

    t = new_tree(op, left->result_type, left, right);
    t->result_type = left->result_type;
    return t;
}

/* 
 * comparision operation.
 */
Tree compare_expr_tree(int op, Tree left, Tree right)
{
    Tree t;

    t = new_tree(op, find_type_by_id(TYPE_BOOLEAN), left, right);
    return t;
}

/* 
 * assignment tree.
 */
Tree assign_tree(Tree id, Tree expr)
{
    Tree t;

    t = new_tree(ASGN, id->result_type, id, expr);
    return t;
}

/* 
 * label tree.
 */
Tree label_tree(Symbol label)
{
    Tree t;

    t = new_tree(LABEL, label->type, NULL, NULL);
    t->u.label.label = label;
    return t;
}

/* 
 * jump without condition.
 */
Tree jump_tree(Symbol label)
{
    Tree t;

    t = new_tree(JUMP, label->type, NULL, NULL);
    t->u.generic.sym = label;
    return t;
}

/* 
 * conditional condition.
 */
Tree cond_jump_tree(Tree cond, int trueorfalse, Symbol label)
{
    Tree t;

    t = new_tree(COND, label->type, cond, NULL);
    t->u.cond_jump.label = label;
    t->u.cond_jump.true_or_false = trueorfalse;
    return t;
}

/*
 * increment.
 */
Tree incr_one_tree(Tree source)
{
    Tree t;

    t = new_tree(INCR, source->result_type, source, NULL);
    return t;
}

/*
 * decrement.
 */
Tree decr_one_tree(Tree source)
{
    Tree t;

    t = new_tree(DECR, source->result_type, source, NULL);
    return t;
}

static void print_tree(Tree tp)
{
    int i;

    if (tp == NULL)
        return;

    printf("+");
    for (i = 0; i < print_level; i++)
    {
        printf("-");
    }

    switch(generic(tp->op))
    {
    case LOAD:
        printf("%s (%s)\n", get_op_name(generic(tp->op)), tp->u.generic.sym->name);
        break;
    case LABEL:
        printf("LABEL (%s)\n", tp->u.label.label->name);
        break;
    case JUMP:
        printf("JUMP (%s)\n", tp->u.generic.sym->name);
        break;
    default:
        printf("%s\n", get_op_name(generic(tp->op)));
        break;
    }

    print_level++;

    if (tp->kids[0])
        print_tree(tp->kids[0]);

    if (tp->kids[1])
        print_tree(tp->kids[1]);

    print_level--;
}


void print_forest(List ast_forest)
{
    int n, i;
    Tree *forest;

    n = list_length(ast_forest);
    forest = (Tree *)list_ltov(ast_forest, STMT);

    printf("\n---------------------forest-----------------------------------\n");
    for (i = 0; i < n ; i++)
    {
        printf("\n\n");
        print_level = 0;
        print_tree(forest[i]);
    }
}

