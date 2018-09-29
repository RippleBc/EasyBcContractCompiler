#ifndef _X86_H
#define _X86_H

#include "config.h"

#define LABEL_SLINK		"static_link"
#define LABEL_RETVAL	"retval_addr"
#define LABEL_HIRETVAL	"retval_addr_hi"

#define STACK_SEG		512

#ifdef GENERATE_AST
#define STATIC static
#else
#undef STATIC
#endif

void push_call_stack(symtab *);
symtab *top_call_stack();
symtab *pop_call_stack();
symbol *top_call_symbol();
void set_call_stack_top(symbol *);

#ifndef GENERATE_AST

void emit_write1(int arg_type);
void emit_sqrt(int arg_type);
void emit_odd(int arg_type);
void emit_abs(int arg_type);
void emit_sqr(int arg_type);
void emit_read1(int arg_type);
void emit_writeln(int arg_type);

symbol *do_function_call(symtab *);
void emit_program_head();
void emit_program_prologue(symtab *);
void emit_program_epilogue(symtab *);
void emit_main_prologue(symtab *);
void emit_main_epilogue(symtab *);
void emit_routine_prologue(symtab *);
void emit_routine_epilogue(symtab *);
void emit_local_args(symtab *);
void emit_push_op(int);
void emit_load_value(symbol *);
void do_function_assign(symtab *,int);
void do_procedure_call(symtab *);
void do_assign(symbol *, int);
void do_if_test();
void do_if_caluse();
void do_if_exit();
void do_repeat_start();
void do_repeat_exit();
void do_while_start();
void do_while_expr();
void do_while_exit();
void do_for_start(symbol *);
void do_for_test(int);
void do_for_exit();
void do_expression(symbol *, int);
void do_negate(symbol *);
void do_expr(symbol *, int);
void do_term(symbol *, int);
void do_factor(symbol *);
void do_no_factor(symbol *);
void do_array_factor(symbol *);
void do_record_factor(symbol *, symbol *);
void do_first_arg(int);
void reset_args(symtab *);
void push_stmt_stack(int);
int pop_stmt_stack();
int top_stmt_stack();
void emit_load_address(symbol *p);
void do_sys_routine(int routine_id, int arg_type);
void do_if_clause();
void do_if_exit();
void do_repeat_start();
void do_case_start();
void do_case_test();
void add_case_const(symbol *p);
void do_case_jump();
void do_args(int ptype);
void do_not_factor(symbol *p);
void emit_load_field(symbol*p);

#endif

#endif
