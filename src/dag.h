#ifndef _DAG_H_
#define _DAG_H_

/* This file is included in common.h */
/* node is defined in tree.h. */

#if 0
typedef struct _node *Node;

/* node for dag. */
struct _node
{
    short op;
    short count;
    Symbol syms[3];
    Node kids[2];
    Node link;
    Xnode x;
};
#endif

enum { CODE=1, BSS, DATA, LIT };

typedef struct table *Table;
struct table
{
    int level;
    Table previous;
    struct entry
    {
        symbol sym;
        struct entry *link;
    }
    *buckets[256];
    Symbol all;
};

typedef struct code *Code;

struct code
{
    enum { Blockbeg, Blockend, Local, Address, Defpoint,
           Label,    Start,    Gen,   Jump,    Switch
         } kind;
    Code prev, next;
    union {
        struct
        {
            int level;
            Symbol *locals;
            Table identifiers, types;
            /* Env x; */
        }
        block;
        Code begin;
        Symbol var;

        struct
        {
            Symbol sym;
            Symbol base;
            long offset;
        }
        addr;
        struct
        {
            Coordinate src;
            int point;
        }
        point;
        Node forest;
        struct
        {
            Symbol sym;
            Symbol table;
            Symbol deflab;
            int size;
            long *values;
            Symbol *labels;
        }
        swtch;

    } u;
};

void print_dags(List dags);
int gen_dag(List ast_forest, List dag_forest);
int emit_code(List dags);

#endif

