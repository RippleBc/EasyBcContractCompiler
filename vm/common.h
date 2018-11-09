#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define _PC_VER_    "0.1.5" /* 编译器版本 */

#define NELEMS(a) ((int)(sizeof (a)/sizeof ((a)[0])))
#undef roundup
#define roundup(x,n) (((x)+((n)-1))&(~((n)-1)))

#define NEW(p,a) ((p) = allocate(sizeof *(p), (a)))
#define NEW0(p,a) memset(NEW((p),(a)), 0, sizeof *(p))

#define NAME_LEN 218
#define FILE_NAME_LEN 218

#define true 1
#define false 0

typedef int boolean;

/* memory allocation arenas. */
enum { PERM=0, FUNC, LASTARENA };

typedef struct metrics
{
    unsigned char size, align; /*  */
}
Metrics;

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

extern Interface *IR;

int g_is_big_endian;