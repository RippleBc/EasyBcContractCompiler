#ifndef _TREE_H_TPC_
#define _TREE_H_TPC_

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "common.h"
#include "symtab.h"

enum { CONSTANTS=1, LABELS, GLOBAL, PARAM, LOCAL };

struct _node;

/* DAG节点 */
struct _node
{
    short op; /* 操作码 */
#ifdef DEBUG

    char *op_name;
#endif

    short count;
    Symbol syms[3];
    Symtab symtab; /* 符号表 */
    union {
        int		sys_id;
        struct
        {
            Symbol label;
            int true_or_false;
        }
        cond;
    }u; /* 跳转相关 */
    Type type;
    /* 三元操作符 */
    struct _node* kids[2];
    struct _node* link;
};

typedef struct _node * Node;

/* AST节点 */
struct _tree;
typedef struct _tree
{
    int op;
    Type result_type;
    struct _tree *kids[2];
    Node dag_node;
    union {

        /* for general nodes. */
        struct
        {
            Value val;
            Symbol sym;
            Symtab symtab;
        }
        generic;

        /* for arg nodes. */
        struct
        {
            Symbol sym;
            Symtab symtab;
        }
        arg;

        /* for field operation node. */
        struct
        {
            Symbol record;
            Symbol field;
        }
        field;

        /* for function/routine call */
        struct
        {
            Symtab symtab;				/* routine/function symtab */
        }
        call;

        /* for function/routine header. */
        struct
        {
            List para;					/* parameter list. */
            Symtab symtab;				/* symtab of the function/routine */
        }
        header;

        /* for system function/routine. */
        struct
        {
            int sys_id;					/* call id. */
        }
        sys;

        /* for conditional jump. */
        struct
        {
            Symbol label;
            int true_or_false;
        }
        cond_jump;

        /* for label. */
        struct
        {
            Symbol label;
        }
        label;

    } u;
}
tree;

typedef tree * Tree;

Tree new_tree(int op, Type type, Tree left, Tree right);
Tree header_tree(symtab *ptab);
Tree conversion_tree(Symbol source, Type target);
Tree id_factor_tree(Tree source, Symbol sym);
Tree address_tree(Tree source, Symbol sym);
Tree not_tree(Tree source);
Tree neg_tree(Tree source);
Tree right_tree(Tree *root, Tree newrightpart);
Tree arg_tree(Tree argtree, Symtab function, Symbol arg, Tree expr);
Tree field_tree(Symbol record, Symbol field);
Tree array_factor_tree(Symbol array, Tree expr);
Tree const_tree(Symbol constval);
Tree call_tree(Symtab routine, Tree argstree);
Tree sys_tree(int sys_id, Tree argstree);
Tree binary_expr_tree(int op, Tree left, Tree right);
Tree compare_expr_tree(int op, Tree left, Tree right);
Tree assign_tree(Tree id, Tree expr);
Tree label_tree(Symbol label);
Tree jump_tree(Symbol label);
Tree cond_jump_tree(Tree cond, int trueorfalse, Symbol label);
Tree incr_one_tree(Tree source);
Tree decr_one_tree(Tree source);
void print_forest(List forest);

#endif

