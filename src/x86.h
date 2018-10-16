#ifndef _X86_H
#define _X86_H

#include "config.h"

#define LABEL_SLINK		"static_link"
#define LABEL_RETVAL	"retval_addr"
#define LABEL_HIRETVAL	"retval_addr_hi"

#define STACK_SEG		512


#define STATIC static

void push_call_stack(symtab *);
symtab *top_call_stack();
symtab *pop_call_stack();
symbol *top_call_symbol();
void set_call_stack_top(symbol *);

#endif
