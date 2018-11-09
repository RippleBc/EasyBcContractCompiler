#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define _PC_VER_    "0.1.5" /* 编译器版本 */

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