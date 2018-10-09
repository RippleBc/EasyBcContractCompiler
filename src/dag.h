#ifndef _DAG_H_
#define _DAG_H_

/*  */
typedef struct table *Table;
struct table
{
    int level; /* 层级 */
    Table previous;
    struct entry
    {
        symbol sym;
        struct entry *link;
    }
    *buckets[256];
    Symbol all;
};

/* */
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
/* 将AST森林转化为DAG森林 */
int gen_dag(List ast_forest, List dag_forest);
int emit_code(List dags);

#endif

