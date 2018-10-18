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
    /* AST节点的类型 */
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

    /* 节点对应的symbol */
    t->u.generic.sym = source;
    return t;
}

/* 获取变量值 */
Tree id_factor_tree(Tree source, Symbol sym)
{
    Tree t;

    if (source)
        /* 通过AST树取值（数组） */
        t = new_tree(LOAD, source->result_type, source, NULL);
    else
        /* 通过符号取值 */
        t = new_tree(LOAD, sym->type, NULL, NULL);

    /* 节点对应的symbol */
    t->u.generic.sym = sym;
    return t;
}

Tree address_tree(Tree source, Symbol sym)
{
    Tree t;

    /* 当变量类型为数组或者记录时，source（ARRAY AST节点或者FIELD AST节点）用来定位变量中的元素 */
    if (source)
        t = new_tree(ADDRG, source->result_type, source, NULL);
    else
        t = new_tree(ADDRG, sym->type, NULL, NULL);
    
    /* 变量对应的符号 */
    t->u.generic.sym = sym;
    
    return t;
}

Tree neg_tree(Tree source)
{
    Tree t;

    t = new_tree(NEG, source->result_type, source, NULL);
    return t;
}

Tree not_tree(Tree source)
{
    Tree t;

    t = new_tree(NOT, source->result_type, source, NULL);
    return t;
}


/* Right tree.
 * holding arguments, comma operations.
 * root表示参数AST树的左子树，newrightpart表示表达式AST树。
 */
Tree right_tree(Tree *root, Tree newrightpart)
{
    
}


/* arguments tree.
 * set argtree to NULL when first called.
 * argtree表示可以参数AST树、function表示函数对应的符号表、arg指向符号表中的参数链表的头部、expr表示实参
 */
Tree arg_tree(Tree argtree, Symtab function, Symbol arg, Tree expr)
{
    Tree t, right;

    /* 检查arg类型是否与expr类型相同 */
    if (arg != NULL && arg->type->type_id != expr->result_type->type_id)
    {
        /* do conversions, left for excises. */
        parse_error("type miss match.", "");
    }

    if (argtree == NULL)
    {
        /* 函数参数树没有进行初始化 */
        if (arg != NULL) 
            /* 符号表中的参数符号类型 */
            t = new_tree(ARG, arg->type, expr, NULL);
        else
            /* expr中的类型 */
            t = new_tree(ARG, expr->result_type, expr, NULL);

        t->u.arg.sym = arg; /* 参数符号 */
        t->u.arg.symtab = function; /* 函数符号表 */
        return t;
    }

    /* 函数参数树已经初始化 */
    if (argtree->kids[1] == NULL)
    {
        argtree->kids[1] = new_tree(RIGHT, expr->result_type, expr, NULL);
        right = argtree->kids[1];
    }
    else
    {
        right = argtree->kids[1];

        /* 移动到参数AST树最右端 */
        while(right->kids[1] != NULL)
            right = right->kids[1];

        /* 初始化一个最右AST树 */
        right->kids[1] = new_tree(RIGHT, expr->result_type, expr, NULL);

        right = right->kids[1];
    }

    right->u.arg.sym = arg; /* 参数符号 */
    right->u.arg.symtab = function; /* 函数符号表 */

    return argtree;
}

/* 通常与id_factor_tree一起使用（通过field_tree获取属性，通过id_factor_tree获取属性值） */
Tree record_field_tree(Symbol record, Symbol field)
{
    Tree t;
    /* record表示记录类型的自定义变量符号，
     field表示记录类型中的属性符号（record类型拥有多个属性，需要指定属性）。 */
    t = new_tree(FIELD, field->type, NULL, NULL);
    t->u.field.record = record;
    t->u.field.field = field;
    return t;

}

/* 通常与id_factor_tree一起使用（通过array_factor_tree获取数组项，通过id_factor_tree获取数组项的值） */
Tree array_index_tree(Symbol array, Tree expr)
{
    Tree t;
    /* expr用于表示array的下标 */
    t = new_tree(ARRAY, array->type->first->type, expr, NULL);
    /* 对应的array符号 */
    t->u.generic.sym = array;
    return t;
}

/*  常量树 */
Tree const_tree(Symbol constval)
{
    Tree t;

    t = new_tree(CNST, constval->type, NULL, NULL);
    t->u.generic.sym = constval;
    return t;
}

/*  自定义函数或过程调用 */
Tree call_tree(Symtab routine, Tree argstree)
{
    Tree t;

    t = new_tree(CALL, routine->type, argstree, NULL);
    t->u.call.symtab = routine;
    return t;
}

/*  系统函数或过程调用 */
Tree sys_tree(int sys_id, Tree argstree)
{
    Tree t;
    Symtab ptab;

    ptab = find_sys_routine(sys_id);
    if (ptab)
        t = new_tree(SYS, ptab->type, argstree, NULL);
    else
        /* 对应的系统函数或过程没有进行初始化，初始化一个空的AST树 */
        t = new_tree(SYS, find_type_by_id(TYPE_VOID), argstree, NULL);

    /* 初始化系统函数或过程的id */
    t->u.sys.sys_id = sys_id;
    return t;
}

Tree binary_expr_tree(int op, Tree left, Tree right)
{
    Tree t;

    /* AST树的类型等于左AST树类型 */
    t = new_tree(op, left->result_type, left, right);
    t->result_type = left->result_type;
    return t;
}

Tree compare_expr_tree(int op, Tree left, Tree right)
{
    Tree t;

    /* AST树类型为布尔型 */
    t = new_tree(op, find_type_by_id(TYPE_BOOLEAN), left, right);
    return t;
}


Tree assign_tree(Tree id, Tree expr)
{
    Tree t;

    /* id表示一棵地址树，expr表示赋值内容 */
    t = new_tree(ASGN, id->result_type, id, expr);

    return t;
}

/* 
 * 标签.
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
 * 条件跳转
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

