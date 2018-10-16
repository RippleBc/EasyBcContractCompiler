/**
 * for backend without generate ast forest.
 */
#define  X86_DOS
#include  <stdio.h>
#include  "common.h"
#include  "symtab.h"
#include  "error.h"
#include  "x86.h"
#include  _YTAB_H_
#define  MAX_CALL_LEVEL 16

static symtab *rtn = NULL;
static symbol *arg = NULL;

static symbol *call_sym[MAX_CALL_LEVEL];
static symtab *call_stk[MAX_CALL_LEVEL];

static int call_tos = MAX_CALL_LEVEL - 1;

symtab *top_call_stack( )
{
    return call_stk[call_tos + 1];
}

symtab *pop_call_stack()
{
    call_tos++;
    if (call_tos == MAX_CALL_LEVEL)
        internal_error("call stack underflow.");
    rtn = call_stk[call_tos];
    arg = call_sym[call_tos];
    return call_stk[call_tos];
}

symbol *top_call_symbol( )
{
    return call_sym[call_tos + 1];
}

void set_call_stack_top(symbol *p)
{
    call_sym[call_tos + 1] = p;
}

void push_call_stack(symtab *p)
{
    call_stk[call_tos] = p;
    call_sym[call_tos] = p->args;
    rtn = p;
    call_tos--;
    if (call_tos == -1)
        internal_error("call stack overflow.");
}