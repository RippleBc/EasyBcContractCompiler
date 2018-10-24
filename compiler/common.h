#ifndef _COMMON_H_
#define _COMMON_H_

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "error.h"
#include "ops.h"

#define KEYWORD		-1 /* 表示关键字 */
#define _PC_VER_    "0.1.5" /* 编译器版本 */

#define FILE_NAME_LEN	(64)

#ifdef WIN32
#define YY_NO_UNISTD_H
#endif

#define MAX_LINE_LENGTH		(20480) /* 词法分析错误追踪时，可以追踪的行的最长字符个数 */
#define STACK_SEG_SIZE		(2048)

#define LABEL_LEN			(32)
#define LAST_ENTRY			(65536 * 1024)

#define NAME_LEN			(32) /* 变量名称可占用的最大字节数 */
#define SIZE_CHAR			(1) /* char类型变量占用1字节 */
#define SIZE_INTEGER		(4) /* integer类型变量占用4字节 */
#define SIZE_REAL			(4) /* real类型变量占用4字节 */
#define SIZE_BOOLEAN		SIZE_INTEGER /* boolean类型变量占用4字节 */
#define SIZE_POINTER		(4) /* pointer类型变量占用4字节 */

/* 对应_symbol_结构体中的defn属性，表示symbol的类型 */
#define DEF_UNKNOWN			(0)
#define DEF_CONST			(1)
#define DEF_VAR				(2)
#define DEF_TYPE			(3)
#define DEF_FIELD			(4)
#define DEF_VALPARA			(5) /* value */
#define DEF_VARPARA			(6) /* variable */
#define DEF_PROC			(7)
#define DEF_FUNCT			(8)
#define DEF_PROG			(9)
#define DEF_TEMPVAR			(10)
#define DEF_ELEMENT			(11)
#define DEF_LABEL			(12)

typedef int					boolean;

#define false 				0
#define true 				1
#define new_index(m)        ++m##_index
#define size(x)             SIZE_##x

/* 记录汇编期间的信息 */
extern	FILE 	*codfp;
extern	FILE	*datfp;
/* 记录编译期间的错误信息 */
extern  FILE 	*errfp;

typedef struct
{
    /* 名称 */
    char name[NAME_LEN];
    /* 关键字 */
    int key;
    /* 属性 */
    int attr;
    /* 返回值类型 */
    int ret_type;
    /* 参数类型 */
    int arg_type;
}
KEYENTRY;

/* memory allocation arenas. */
enum { PERM=0, FUNC, STMT, TREE, DAG, LASTARENA };

/* position of file. */
typedef struct coord
{
    char *file;
    unsigned x, y;
}
Coordinate;

void *allocate(unsigned long n, unsigned a);

/* memory allocation */
#define NEW(p,a) ((p) = allocate(sizeof *(p), (a)))
#define NEW0(p,a) memset(NEW((p),(a)), 0, sizeof *(p))

#define NELEMS(a) ((int)(sizeof (a)/sizeof ((a)[0])))
#undef roundup
#define roundup(x,n) (((x)+((n)-1))&(~((n)-1)))


/* 对应_type_结构体中的type_id属性，表示TYPE的类型 */
enum {
    TYPE_UNKNOWN = 0,
    TYPE_INTEGER = 1,
    TYPE_CHAR = 2,
    TYPE_REAL = 3,
    TYPE_BOOLEAN = 4,
    TYPE_ARRAY = 5,
    TYPE_ENUM = 6,
    TYPE_SUBRANGE = 7,
    TYPE_RECORD = 8,
    TYPE_VOID = 9,
    TYPE_STRING = 10,
    TYPE_POINTER = 11,
    TYPE_DOUBLE = 12,
    TYPE_FUNCTION = 13,
    TYPE_LONG = 14,
    TYPE_CONST = 15
};

enum {
    F=TYPE_REAL,
    I=TYPE_INTEGER,
    P=TYPE_POINTER,
    V=TYPE_VOID,
    B=TYPE_RECORD
};

/* for operations. */
#include "ops.h"

#define generic(op)  ((op)&0x3F0)
#define opindex(op) (((op)>>4)&0x3F)

/* symbol and type definition. */
#include "symtab.h"

typedef struct list *List;
struct list
{
    void *x; /* 头部LIST节点中的x指向LIST链表的末尾节点，非头部LIST节点中的x指向AST节点或者DAG节点 */
    List link; /* 指向下一个LIST节点 */
};

List list_append(List list, void *x);
int list_length(List list);
void **list_ltov(List list, unsigned arena);
void list_clear(List list);


typedef struct
{
    union {
        /* 程序入口 */
        struct
        {
            int argc; /* 参数个数 */
            char **argv; /* 具体参数 */
            Symtab tab; /* 对应的符号表 */
        }
        program;

        /* 子程序 */
        struct
        {
            Symtab tab; /* 对应的符号表 */
        }
        main;
    }u;
}
Env;

extern Env global_env; /* 全局 */
extern Env main_env; /* 主程序 */

/* trees */
#include "tree.h"

/* nodes and dags. */
#include "./optimize/dag.h"

/* target interface */
#include "config.h"

/* 类型度量 */
typedef struct metrics
{
    unsigned char size, align; /* 大小，对其方式 */
}
Metrics;

typedef struct blockcontext
{
    unsigned char size;
}
BlockContext;

typedef struct interface
    {
        /* type interface */
        Metrics charmetric;
        Metrics shortmetric;
        Metrics intmetric;
        Metrics floatmetric;
        Metrics doublemetric;
        Metrics pointermetric;
        Metrics structmetric;
    }
Interface;

typedef struct binding
{
    char *name;
    Interface *ir;
}
Binding;

extern Binding bindings[];
extern Interface *IR;

int get_keytable_size();
void *allocate(unsigned long n, unsigned a);
void deallocate(unsigned a);
void *newarray(unsigned long m, unsigned long n, unsigned a);
void const_folding(Node n);

#endif

