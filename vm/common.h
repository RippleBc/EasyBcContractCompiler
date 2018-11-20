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

#define TYPE_BYTE_DEBUG (0)
#define VM_STACK_DEBUG (0)
#define GLOBAL_AREA_DEBUG (0)

#define VM_STACK_DEEP 256

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

Interface *IR;

int g_is_big_endian;

enum {
    TYPE_UNKNOWN = 0,
    TYPE_INTEGER = 1,
    TYPE_UINTEGER = 2,
    TYPE_CHAR = 3,
    TYPE_UCHAR = 4,
    TYPE_REAL = 5,
    TYPE_BOOLEAN = 6,
};

typedef union _value_* Value;
typedef union _value_ value;
union _value_
{
    int i;
    unsigned int ui;
    float f;
    boolean b;
    char c;
    unsigned char uc;
};

struct _op_code_ {
    int code;
    char name[NAME_LEN];
    int in;
    int out;
};

/* byte sequence */
extern int byte_sequence_size;
extern unsigned char byte_sequence[];
extern int byte_sequence_index;

extern void assign_with_byte_unit(int type, unsigned char *array, Value v);
extern void load_with_byte_unit(int type, unsigned char *array, Value v);

/* function stack */
extern void push_call();
extern void pop_call();
extern void assign_call(int align);
extern void load_call(int align);
extern int top_call();

/* vm stack */
extern int vm_stack_deep;
extern unsigned char vm_stack[];
extern void push_vm_stack_from_byte_sequence(int align);
extern void push_vm_stack_from_compute(int type, Value v);
extern void pop_vm_stack(int align);
extern int get_int_from_vm_stack();
extern unsigned int get_uint_from_vm_stack();
extern float get_real_from_vm_stack();
extern boolean get_boolean_from_vm_stack();
extern char get_char_from_vm_stack();
extern unsigned char get_uchar_from_vm_stack();
