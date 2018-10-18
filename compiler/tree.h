#ifndef _TREE_H_
#define _TREE_H_

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "common.h"
#include "symtab.h"

struct _node;

/* DAG节点定义 */
struct _node
{
    short op; /* 操作码 */
#ifdef DEBUG

    char *op_name; /* 操作名称 */
#endif

    short count; /* 被引用的次数 */
    Symbol syms[3]; /* 相关联的symbol */
    Symtab symtab; /* 相关联的symtab */
    union {
        int		sys_id; /* 系统调用ID */
        struct
        {
            Symbol label; /* 标签符号 */
            int true_or_false; /* 当跳转到指定标签符号时条件语句是真还是假 */
        }
        cond;
    }u;
    Type type; /* 节点类型 */
    struct _node* kids[2]; /* 左节点和右节点 */
    struct _node* link; /* 连接下一片节点森林 */
};

typedef struct _node * Node;

/* AST节点 */
struct _tree;
typedef struct _tree
{
    int op; /* 操作码 */
    Type result_type; /* 节类型 */
    struct _tree *kids[2]; /* 代表左子树和右子树 */
    Node dag_node; /* 对应的DAG节点 */
    union {

        /* for general nodes. */
        struct
        {
            Value val; /* 值 */
            Symbol sym; /* 相关联的symbol（变量或者参数） */
            Symtab symtab; /* 相关联的符号表 */
        }
        generic;

        /* for arg nodes. */
        struct
        {
            Symbol sym; /* 相关联的symbol（参数） */
            Symtab symtab; /* 相关联的符号表 */
        }
        arg;

        /* for field operation node. */
        struct
        {
            Symbol record; /* 相关联的symbol（record） */
            Symbol field; /* 相关联的symbol（record中的字段） */
        }
        field;

        /* for function/routine call */
        struct
        {
            /* routine/function symtab，函数和过程拥有一个symtab对象，
             其中定义了函数中的局部变量（参数以及变量）、自定义类型、返回值类型等信息。
             因此只需要提供函数或者过程的symtab即可对其进行调用。 */
            Symtab symtab;
        }
        call; /* 调用函数 */

        /* for function/routine header. */
        struct
        {
            List para;					/* parameter list. */
            Symtab symtab;				/* symtab of the function/routine */
        }
        header; /* 函数头，需要提供参数列表以及对应的symtab */

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
Tree arg_tree(Tree argtree, Symtab function, Symbol arg, Tree expr);
Tree record_field_tree(Symbol record, Symbol field);
Tree array_index_tree(Symbol array, Tree expr);
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

