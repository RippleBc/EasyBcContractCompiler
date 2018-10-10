%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"
#include "symtab.h"
#include "error.h"
#include "tree.h"

#ifdef _MSDOS_
#include "debug.h"
#include "type.h"
#endif

#include "x86.h"

extern char *yytext; /* flex用于记录匹配到的字符串 */
symtab *ptab; /* 符号表表头 */
symbol *p, *q;
tree   *t;
type *pt, *qt;
int temp;

/* 对token的操作 */
symbol* pop_term_stack();
symbol* top_term_stack();
void push_term_stack(symbol * p);

Env global_env;
Env main_env;

Symtab	rtn = NULL; /* 表示system routine */
Symbol	arg = NULL;

#ifdef GENERATE_AST

Tree pop_ast_stack();
Tree top_ast_stack();
void push_ast_stack(Tree t);

int pop_lbl_stack();
int top_lbl_stack();
void push_lbl_stack(int id);

int pop_case_stack();
int top_case_stack();
void push_case_stack(int id);

List pop_case_ast_stack();
List top_case_ast_stack();
void push_case_ast_stack(List newlist);

struct list ast_forest;
struct list para_list;				/* for parameter list. */
List  case_list = NULL;
struct list dag_forest;				/* for dags. */
Tree args;
Tree now_function;
Tree t;
Symbol	new_label = NULL;
Symbol	test_label = NULL;
Symbol  exit_label = NULL;
char 	mini_buf[NAME_LEN];			/* buffer for generated name. */
int		if_label_count;				/* count for label of if. */
int		repeat_label_count;			/* count for label of repeat. */
int		case_label_count;			/* count for label of case. */
int		switch_label_count;			/* count for label of switch. */
int		do_label_count;				/* count for label of do. */
int		while_label_count;			/* count for label of while. */
int		for_label_count;			/* count for label of for. */

#endif

int parser_init();

Symbol install_temporary_symbol(char *name, int deftype, int typeid);
Type install_temporary_type(char *name, int deftype, int typeid);

void trap_in_debug();

#ifdef DEBUG
#define DEBUG_POINT	trap_in_debug();
#endif

#if 0

#ifndef GENERATE_AST

%type  <num>proc_stmt assign_stmt
%type  <num>expression expression_list
%type  <p_symbol>factor term expr

#else

%type  <p_tree>proc_stmt assign_stmt
%type  <p_tree>factor term expr
%type  <p_tree>expression expression_list

#endif

#endif

%}

%union {
	char 		p_char[NAME_LEN];
	int 		num;
	int 		ascii;
	Symbol 		p_symbol; /* 符号 */
	Type		p_type; /* 类型 */
	KEYENTRY	*p_lex; /* 关键字 */
	Tree 		p_tree;
}

%error-verbose

%term kAND
%term kARRAY
%term kBEGIN
%term kCASE
%term kCONST
%term kDIV
%term kDO
%term kDOWNTO
%term kELSE
%term kEND
%term kFILE
%term kFOR
%term kFUNCTION
%term kGOTO
%term kIF
%term kIN
%term kLABEL
%term kMOD
%term kNIL
%term kNOT
%term kOF
%term kOR
%term kPACKED
%term kPROCEDURE
%term kPROGRAM
%term kRECORD
%term kREPEAT
%term kSET
%term kTHEN
%term kTO
%term kTYPE
%term kUNTIL
%term kVAR
%term kWHILE
%term kWITH
%term <num>SYS_CON
%term cFALSE
%term cTRUE
%term cMAXINT
%term <p_char>cSTRING
%term <num>cINTEGER
%term <p_char>cREAL
%term <p_char>cCHAR
%term <p_char>cBOOLEAN
%term <p_char>SYS_TYPE
%term tINTEGER
%term tCHAR
%term tREAL
%term tBOOLEAN
%term tTEXT
%term <p_lex>SYS_FUNCT
%term fABS
%term fCHR
%term fODD
%term fORD
%term fPRED
%term fSQR
%term fSQRT
%term fSUCC
%term <p_lex>SYS_PROC
%term pREAD
%term pREADLN

%term  pWRITE
%term  pWRITELN
%term  oPLUS
%term  oMINUS
%term  oMUL
%term  oDIV
%term  oEQUAL
%term  oASSIGN
%term  oUNEQU
%term  oLT
%term  oLE
%term  oGT
%term  oGE
%term  oCOMMA
%term  oSEMI
%term  oCOLON
%term  oQUOTE
%term  oDOT
%term  oDOTDOT
%term  oARROW
%term  oLP
%term  oRP
%term  oLB
%term  oRB
%term  <p_char>yNAME

%type  <p_symbol>const_value
%type  <p_symbol>name_list
%type  <p_symbol>val_para_list var_para_list
%type  <num>direction
%type  <p_type>type_decl_list type_definition
%type  <p_type>type_decl simple_type_decl
%type  <p_type>array_type_decl record_type_decl
%type  <p_symbol>field_decl field_decl_list

%type  <p_tree>proc_stmt assign_stmt
%type  <p_tree>factor term expr
%type  <p_tree>expression expression_list

%start  program

%%

program
:first_act_at_prog program_head sub_program oDOT
{
	/* 弹出无效的symtab */
	pop_symtab_stack();
#ifdef GENERATE_AST
	if (!err_occur())
	{
		/* 清空dag_forest */
		list_clear(&dag_forest);

		/* 该树节点的操作类型为TAIL，表示该树节点实现的是程序结束的操作。 */
		t = new_tree(TAIL, NULL, NULL, NULL);

		/* 初始化当前命名空间下的符号表 */
		t->u.generic.symtab = top_symtab_stack();
		
		/* 将AST节点挂到ast_forest后面 */
		list_append(&ast_forest, t);

		/* generate dag forest. */
		gen_dag(&ast_forest, &dag_forest);

		/* emit asm code. */
		emit_code(&dag_forest);

		(*(IR->main_end))(&main_env);

		/* call end interface. */
		(*(IR->program_end))(&global_env);
	}
#else
	emit_main_epilogue(Global_symtab);
	emit_program_epilogue(Global_symtab);
#endif
	return 0;
}
;

first_act_at_prog
:   
{
	/* 初始化解析器 */
	parser_init();
	/* 创建全局符号表 */
	make_global_symtab();
	/* 创建系统符号表 */
	make_system_symtab();
	/* 将全局符号表压入符号表栈中 */
	push_symtab_stack(Global_symtab);
};

program_head
:kPROGRAM yNAME oSEMI 
{
	/* 初始化全局符号表的名称 */
	strcpy(Global_symtab->name, $2);
	/* 初始化全局符号表的汇编名称 */
	snprintf(Global_symtab->rname, sizeof(Global_symtab->rname), "main");
	/* 初始化大类 */
	Global_symtab->defn = DEF_PROG;
#ifdef GENERATE_AST
	global_env.u.program.tab = Global_symtab;
	/* call initialization interface. */
	(*(IR->program_begin))(&global_env);
#else
	emit_program_prologue(Global_symtab);
#endif

}
|error oSEMI
;

sub_program
:routine_head
{
#ifdef GENERATE_AST
	main_env.u.main.tab = Global_symtab;
	(*(IR->main_begin))(&main_env);
	list_clear(&ast_forest);
	list_clear(&para_list);
	
	push_symtab_stack(Global_symtab);
	/*
	ptab = top_symtab_stack();
	strncpy(ptab->name, $3, NAME_LEN);
	sprintf(ptab->rname, "rtn%03d",ptab->id);
	ptab->defn = DEF_PROC;
	p = new_symbol($3, DEF_PROC, TYPE_VOID);
	add_symbol_to_table(ptab,p);
	reverse_parameters(ptab);
	{
		Tree header;
		
		header = new_tree(HEADER, find_type_by_id(TYPE_VOID), NULL, NULL); 
		header->u.header.para = &para_list;
		list_append(&ast_forest, header);
		now_function = new_tree(ROUTINE, find_type_by_id(TYPE_VOID), header, NULL);
	}

	ptab = new_symtab(top_symtab_stack());
	push_symtab_stack(ptab);
	*/

#else
	emit_main_prologue(Global_symtab);
#endif

}
routine_body
{
}
;

name_list
:name_list oCOMMA yNAME 
{
	p = new_symbol($3, DEF_UNKNOWN, TYPE_UNKNOWN);
	for(q = $1; q->next; q = q->next);
	q->next = p; p ->next = NULL;
	$$ = $1;
}
|yNAME
{
	p = new_symbol($1, DEF_UNKNOWN, TYPE_UNKNOWN);
	$$ = p;
}
|yNAME error oSEMI
|yNAME error oCOMMA
;

sub_routine
:routine_head routine_body
;

routine_head
:const_part type_part var_part routine_part
{
#ifdef GENERATE_AST
#else
	emit_routine_prologue(top_symtab_stack());
#endif
}
;

const_part
:%empty {}
|kCONST const_expr_list {}
;

const_expr_list
:const_expr_list yNAME oEQUAL const_value oSEMI
{
	/* 给const_value命名 */
	strncpy($4->name, $2, NAME_LEN);
	/* 将const类型symbol放入符号表中 */
	add_symbol_to_table(top_symtab_stack(), $4);
}
|yNAME oEQUAL const_value oSEMI
{
	/* 给const_value命名 */
	strncpy($3->name, $1, NAME_LEN);
	/* 将const类型symbol放入符号表中 */
	add_symbol_to_table(top_symtab_stack(), $3);
}
;

const_value
:cINTEGER
{
	/* 先采用默认命名，随后会被正确命名 */
	p = new_symbol("$$$", DEF_CONST,
		TYPE_INTEGER);

	/* 给symbol赋值 */
	p->v.i = $1;
	$$ = p;
}
|cREAL
{
	p = new_symbol("$$$",DEF_CONST,
		TYPE_REAL);

	/* 给symbol赋值，将字符串转化为浮点数 */
	p->v.f = atof($1);
	$$ = p;
}
|cCHAR
{
	p = new_symbol("$$$", DEF_CONST,
		TYPE_CHAR);

	/* 给symbol赋值 */
	p->v.c= $1[1];
	$$ = p;
}
|cSTRING
{
	p = new_symbol("$$$", DEF_CONST,
		TYPE_STRING);

	/* 给symbol赋值，字符串 */
	p->v.s = strdup($1);
	$$ = p;
}
|SYS_CON
{
	p = new_symbol("$$$", DEF_CONST,
		TYPE_UNKNOWN);

	switch($1)
	{
	case cMAXINT:
		strcpy(p->rname, "maxint");
		/* 定义symbol值 */
		p->v.i = (1 << (IR->intmetric.size * 8)) - 1;
		/* 定义symbol类型 */
		p->type = find_type_by_id(TYPE_INTEGER);
		break;

	case cFALSE:
		strcpy(p->rname, "0");
		/* 定义symbol值 */
		p->v.b = 0;
		/* 定义symbol类型 */
		p->type = find_type_by_id(TYPE_BOOLEAN);
		break;
		  
	case cTRUE:
		strcpy(p->rname, "1");
		/* 定义symbol值 */
		p->v.b = 1;
		/* 定义symbol类型 */
		p->type = find_type_by_id(TYPE_BOOLEAN);
		break; 

	default:
		/* 不是上述七大类型，默认为空 */
		p->type = find_type_by_id(TYPE_VOID);
		break;
	}

	$$ = p;
}
;

type_part
:%empty {}
|kTYPE type_decl_list {}
;

type_decl_list
:type_decl_list type_definition {}
|type_definition {}
;

type_definition
:yNAME oEQUAL type_decl oSEMI
{
	if($3->name[0] == '$')
	{
		/* 全新的类型 */
		$$ = $3;
		/* 类型命名 */
		strncpy($$->name, $1, NAME_LEN);
	}
	else{
		/* 支持类型重定义。 */
		$$ = clone_type($3);
		/* 类型命名 */
		strncpy($$->name, $1, NAME_LEN);
		/* 将类型添加到符号表中 */
		add_type_to_table(
			top_symtab_stack(), $$);
	}
}
;

type_decl
:simple_type_decl {}
|array_type_decl {}
|record_type_decl {}
;

array_type_decl
:kARRAY oLB simple_type_decl oRB kOF type_decl
{
	$$ = new_array_type("$$$", $3, $6);
	add_type_to_table(
		top_symtab_stack(),$$);
} 
;

record_type_decl
:kRECORD field_decl_list kEND
{ 
	pt = new_record_type("$$$", $2);
 	add_type_to_table(top_symtab_stack(), pt);
	$$ = pt;
}
;

field_decl_list
:field_decl_list field_decl
{
    for(p = $1; p->next; p = p->next);
	p->next = $2;
	$$ = $1;  
}
|field_decl
{
	$$ = $1;
}
;

field_decl
:name_list oCOLON type_decl oSEMI
{    
	for(p = $1; p; p = p->next) {
		if($3->type_id == TYPE_SUBRANGE)
			p->type = $3->first->type;
		else if($3->type_id == TYPE_ENUM)
			p->type = find_type_by_id(TYPE_INTEGER);
		else
			p->type = find_type_by_id($3->type_id);

		p->type_link = $3;
		p->defn = DEF_FIELD;
	}
	$$ = $1;
}
;

simple_type_decl
:SYS_TYPE
{
	/* 系统类型（char，integer，boolean，real） */
	pt = find_type_by_name($1);

	if(!pt)
		parse_error("Undeclared type name",$1);

	$$ = pt;
}
|yNAME
{
  /* 用户自定义类型 */
	pt = find_type_by_name($1);

	if (!pt)
	{
		parse_error("Undeclared type name", $1);
		return 0;
	}

	$$ = pt;
}
|oLP name_list oRP
{
	/* 初始化一个枚举类型 */
	$$ = new_enum_type("$$$");
	/* 初始化枚举类型的符号链表 */
	add_enum_elements($$, $2);
	/* 将枚举类型放入 */
	add_type_to_table(
		top_symtab_stack(),$$);
}
|const_value oDOTDOT const_value
{
  /* 类似于1..7或者1..8，subrange类型 */
	if($1->type->type_id != $3->type->type_id){
		parse_error("type mismatch","");
		return 0;
	}
	$$ = new_subrange_type("$$$", $1->type->type_id);
	add_type_to_table(
		top_symtab_stack(), $$);

	if($1->type->type_id == TYPE_INTEGER)
		set_subrange_bound($$,
			(int)$1->v.i,(int)$3->v.i);
	else if ($1->type->type_id == TYPE_BOOLEAN)
		set_subrange_bound($$,
			(int)$1->v.b,(int)$3->v.b);
	else if ($1->type->type_id == TYPE_CHAR)
		set_subrange_bound($$,
			(int)$1->v.c,(int)$3->v.c);
	else
		parse_error("invalid element type of subrange","");
}
|oMINUS const_value oDOTDOT const_value
{
	if($2->type->type_id != $4->type->type_id){
		parse_error("type mismatch","");
		/* return 0; */
	}

	$$ = new_subrange_type("$$$",
		$2->type->type_id);
		
	add_type_to_table(
		top_symtab_stack(),$$);

	if($2->type->type_id == TYPE_INTEGER){
		$2->v.i= -$2->v.i;
		set_subrange_bound($$,
			(int)$2->v.i,(int)$4->v.i);
	}
	else if ($2->type->type_id == TYPE_BOOLEAN){
		$2->v.b ^= 1;
		set_subrange_bound($$,
			(int)$2->v.b,(int)$4->v.b);
	}
	else if ($2->type->type_id == TYPE_CHAR)
		parse_error("invalid operator","");
	else
   		parse_error("invalid element type of subrange","");
}
|oMINUS const_value oDOTDOT oMINUS const_value
{
	if($2->type->type_id != $5->type->type_id) {
		parse_error("type mismatch.","");
		return  0;
	}
	
	$$ = new_subrange_type("$$$", $2->type->type_id);

	add_type_to_table(
		top_symtab_stack(),$$);

	if($2->type->type_id == TYPE_INTEGER){
		$2->v.i = -$2->v.i;
		$5->v.i = -$5->v.i;
	
		set_subrange_bound($$,(int)$2->v.i,
			(int)$5->v.i);
	}
	else if ($2->type->type_id == TYPE_BOOLEAN){
		$2->v.b ^= 1;
		$5->v.b ^= 1;
		set_subrange_bound($$,(int)$2->v.b,
		(int)$5->v.b);
	}
	else if ($2->type->type_id == TYPE_CHAR)
		parse_error("invalid operator","");
	else
		parse_error("invalid element type of subrange","");
}
|yNAME oDOTDOT yNAME
{
	p = find_element(top_symtab_stack(), $1);

	if(!p){
		parse_error("Undeclared identifier", $1);
		install_temporary_symbol($1, DEF_ELEMENT, TYPE_INTEGER);
		/* return 0; */
	}
	
	if(p->defn != DEF_ELEMENT){
		parse_error("not an element identifier", $1);
		/* return 0; */
	}
	
	q = find_element(top_symtab_stack(), $3);
	if(!q){
		parse_error("Undeclared identifier", $3);
		install_temporary_symbol($3, DEF_ELEMENT, TYPE_INTEGER);
		/* return 0; */
	}
	if(q->defn != DEF_ELEMENT){
		parse_error("Not an element identifier", $3);
		/* return 0; */
	}
	
	if(p && q){
		$$ = new_subrange_type("$$$", TYPE_INTEGER);
		add_type_to_table(
			top_symtab_stack(),$$);
		set_subrange_bound($$, p->v.i, q->v.i);
	}
	else
		$$ = NULL;
}
;

var_part
:kVAR var_decl_list
|
;

var_decl_list
:var_decl_list var_decl
|var_decl
;

var_decl
:name_list oCOLON type_decl oSEMI
{    
	ptab = top_symtab_stack();
	
	for(p = $1; p ;){
		if($3->type_id == TYPE_SUBRANGE)
			p->type = find_type_by_id($3->first->type->type_id);
		else if($3->type_id == TYPE_ENUM)
			p->type = find_type_by_id(TYPE_INTEGER);
		else
			p->type = find_type_by_id($3->type_id);

		p->type_link = $3;
		p->defn = DEF_VAR;

		q = p; p = p->next;
		q->next = NULL;
		add_symbol_to_table(ptab, q);
	}
	$1 = NULL;
}
;

routine_part
:routine_part function_decl
|routine_part procedure_decl
|function_decl
|procedure_decl
|
;

function_decl
:function_head oSEMI sub_routine oSEMI 
{
#ifdef GENERATE_AST
	if (!err_occur())
	{
		
		list_clear(&dag_forest);
		t = new_tree(TAIL, NULL, NULL, NULL);
		t->u.generic.symtab = top_symtab_stack();
		list_append(&ast_forest, t);

		/* generate dag forest. */
		gen_dag(&ast_forest, &dag_forest);

		/* emit asm code. */
		emit_code(&dag_forest);
	}
#else
	emit_routine_epilogue(top_symtab_stack());
#endif

	pop_symtab_stack();
}
;

function_head
:kFUNCTION
{
#ifdef GENERATE_AST
	list_clear(&ast_forest);
	list_clear(&para_list);
#endif

	ptab = new_symtab(top_symtab_stack());
	push_symtab_stack(ptab);
}
yNAME parameters oCOLON
simple_type_decl
{
	ptab = top_symtab_stack();
	strncpy(ptab->name, $3, NAME_LEN);
	sprintf(ptab->rname, "rtn%03d",ptab->id);
	ptab->defn = DEF_FUNCT;
	
	if($6->type_id == TYPE_SUBRANGE)
		ptab->type = $6->first->type;
	else if($6->type_id == TYPE_ENUM)
		ptab->type = find_type_by_id(TYPE_INTEGER);
	else
		ptab->type = find_type_by_id($6->type_id);

	p = new_symbol($3, DEF_FUNCT, ptab->type->type_id);
	p->type_link = $6;
	add_symbol_to_table(ptab, p);
	reverse_parameters(ptab);
#ifdef GENERATE_AST
	{
		Tree header;
		
		header = new_tree(HEADER, ptab->type, NULL, NULL);
		header->u.header.para = &para_list;
		header->u.header.symtab = ptab;
		list_append(&ast_forest, header);
		now_function = new_tree(FUNCTION, ptab->type, header, NULL);
	}
#endif	
}
;

procedure_decl
:procedure_head oSEMI sub_routine oSEMI
{
#ifdef GENERATE_AST
	{
		list_clear(&dag_forest);
		t = new_tree(TAIL, NULL, NULL, NULL);
		list_append(&ast_forest, t);

		/* generate dag forest. */
		gen_dag(&ast_forest, &dag_forest);

		/* emit asm code. */
		emit_code(&dag_forest);
	}
#else
	emit_routine_epilogue(top_symtab_stack());
#endif

	pop_symtab_stack();
}
;

procedure_head
:kPROCEDURE
{
#ifdef GENERATE_AST
	list_clear(&ast_forest);
	list_clear(&para_list);
#endif

	ptab = new_symtab(top_symtab_stack());
	push_symtab_stack(ptab);
}
yNAME parameters
{
	ptab = top_symtab_stack();
	strncpy(ptab->name, $3, NAME_LEN);
	sprintf(ptab->rname, "rtn%03d",ptab->id);
	ptab->defn = DEF_PROC;
	p = new_symbol($3, DEF_PROC, TYPE_VOID);
	add_symbol_to_table(ptab,p);
	reverse_parameters(ptab);

#ifdef GENERATE_AST
	{
		Tree header;
		
		header = new_tree(HEADER, find_type_by_id(TYPE_VOID), NULL, NULL);
		header->u.header.para = &para_list;
		list_append(&ast_forest, header);
		now_function = new_tree(ROUTINE, find_type_by_id(TYPE_VOID), header, NULL);
	}
#endif	
}
;

parameters
:oLP para_decl_list oRP
{
	ptab = top_symtab_stack();
	ptab->local_size = 0;
}
|
;

para_decl_list
:para_decl_list oSEMI para_type_list
|para_type_list
;

para_type_list
: val_para_list oCOLON simple_type_decl
{
	ptab = top_symtab_stack();
	for(p = $1; p ;){
		if($3->type_id
			== TYPE_SUBRANGE)
			p->type = $3->first->type;
		else if ($3->type_id == TYPE_ENUM)
			p->type = find_type_by_id(TYPE_INTEGER);
		else
			p->type = find_type_by_id($3->type_id);
		p->type_link = $3;
		p->defn = DEF_VALPARA;

		q = p; p = p->next;
		q->next = NULL;
		add_symbol_to_table(ptab,q);
#ifdef GENERATE_AST
		/* append to paralist. */
		list_append(&para_list, q);
#endif
	}

	$1 = NULL;
}
| var_para_list oCOLON simple_type_decl
{
	ptab = top_symtab_stack();
	for(p = $1; p;){
		if($3->type_id == TYPE_SUBRANGE)
			p->type = $3->first->type;
		else if($3->type_id == TYPE_ENUM)
			p->type = find_type_by_id(TYPE_INTEGER);
		else
			p->type = find_type_by_id($3->type_id);
		p->type_link = $3;
		p->defn = DEF_VARPARA;
		q = p; p = p->next;
		q->next=NULL;
		add_symbol_to_table(ptab,q);
#ifdef GENERATE_AST
		/* append to para_list. */
		list_append(&para_list, q);
#endif
	}
	$1 = NULL;
}
;

val_para_list
:name_list
;

var_para_list
:kVAR name_list
{
	$$ = $2;
}
;

routine_body
:compound_stmt
;

stmt_list
:stmt_list stmt oSEMI
|stmt_list error oSEMI
|
;

stmt
:cINTEGER oCOLON non_label_stmt
| non_label_stmt
;

non_label_stmt
:assign_stmt
| proc_stmt
| compound_stmt
| if_stmt
| repeat_stmt
| while_stmt
| for_stmt
| case_stmt
| goto_stmt
|
;

assign_stmt
:yNAME oASSIGN expression
{
	p = find_symbol(top_symtab_stack(), $1);
	if (p == NULL)
	{
		parse_error("Undefined identifier", $1);
		p = install_temporary_symbol($1, DEF_VAR, TYPE_INTEGER);
	}
	if(p->type->type_id == TYPE_ARRAY
		||p->type->type_id == TYPE_RECORD)
	{
		parse_error("lvalue expected","");
		/* return 0; */
	}

	if (p && p->defn != DEF_FUNCT)
	{
	#ifdef GENERATE_AST
		if(p->type->type_id != $3->result_type->type_id)
	#else
		if(p->type->type_id != $3)
	#endif
		{
			parse_error("type mismatch","");
			/* return 0; */
		}
	}
	else
	{
		ptab = find_routine($1);
		if(ptab)
		{
		#ifdef GENERATE_AST
			if(ptab->type->type_id != $3->result_type->type_id)
		#else
			if(ptab->type->type_id != $3)
		#endif
			{
				parse_error("type mismatch","");
				/* return 0; */
			}
		}
		else{
			parse_error("Undeclared identifier.",$1);
		#ifdef GENERATE_AST
			install_temporary_symbol($1, DEF_VAR, $3->result_type->type_id);
		#else
			install_temporary_symbol($1, DEF_VAR, $3);
		#endif
			/* return 0; */
		}
	}

#ifdef GENERATE_AST
	t = address_tree(NULL, p);
	$$ = assign_tree(t, $3);
	
	/* append to forest. */
	list_append(&ast_forest, $$);
	
#else
	
	if (p && p->defn != DEF_FUNCT)
	{
		do_assign(p, $3);
	}
	else
	{
		do_function_assign(ptab, $3);
	}
#endif
}
|yNAME oLB
{
	p = find_symbol(top_symtab_stack(), $1);
	if(!p || p->type->type_id != TYPE_ARRAY){
		parse_error("Undeclared array name",$1);
		return 0;
	}
	
	push_term_stack(p);
#ifdef GENERATE_AST
#else
	emit_load_address(p);
	emit_push_op(TYPE_INTEGER);
#endif
}
expression oRB
{
	p = top_term_stack();
#ifdef GENERATE_AST
	p = find_symbol(top_symtab_stack(), $1);
	if(!p || p->type->type_id != TYPE_ARRAY){
		parse_error("Undeclared array name",$1);
		return 0;
	}
	
	t = array_factor_tree(p, $4);
	t = address_tree(t, p);
	push_ast_stack(t);
#else
	do_array_factor(p);
#endif
}
oASSIGN expression
{
#ifdef GENERATE_AST
	t = pop_ast_stack();
	$$ = assign_tree(t, $8);
	list_append(&ast_forest, $$);
#else
	p = pop_term_stack();
	do_assign(p, $8);
#endif
}
|yNAME oDOT yNAME
{
	p = find_symbol(top_symtab_stack(),$1);
	if(!p || p->type->type_id != TYPE_RECORD){
		parse_error("Undeclared record vaiable",$1);
		return 0;
	}

	q = find_field(p,$3);
	if(!q || q->defn != DEF_FIELD){
		parse_error("Undeclared field",$3);
		return 0;
	}

#ifdef GENERATE_AST
	t = field_tree(p, q);
	t = address_tree(t, q);
	push_ast_stack(t);
#else
	emit_load_address(p);
	emit_push_op(TYPE_INTEGER);
	do_record_factor(p,q);
	push_term_stack(p);
	push_term_stack(q);
#endif
}
oASSIGN expression
{
#ifdef GENERATE_AST
	t = pop_ast_stack();
	$$ = assign_tree(t, $6);
	list_append(&ast_forest, $$);
#else
	q = pop_term_stack();
	p = pop_term_stack();
	do_assign(q, $6);
#endif
}
;

proc_stmt
:yNAME
{
	ptab = find_routine($1);
	if(!ptab || ptab->defn != DEF_PROC){
		parse_error("Undeclared procedure",$1);
		return 0;
	}

#ifdef GENERATE_AST
	$$ = call_tree(ptab, NULL);
	list_append(&ast_forest, $$);
#else
	do_procedure_call(ptab);
#endif
}
|yNAME
{
	ptab = find_routine($1);
	if(!ptab || ptab->defn != DEF_PROC){
			parse_error("Undeclared procedure",$1);
			return 0;
	}
	push_call_stack(ptab);
}
oLP args_list oRP
{
#ifdef GENERATE_AST
	$$ = call_tree(top_call_stack(), args);
	list_append(&ast_forest, $$);
#else
	do_procedure_call(top_call_stack());
#endif
	pop_call_stack();
}
|SYS_PROC
{
#ifdef GENERATE_AST
	$$ = sys_tree($1->attr, NULL);
	list_append(&ast_forest, $$);
#else
	do_sys_routine($1->attr, 0);
#endif
}
|SYS_PROC 
{
	rtn = find_sys_routine($1->attr);

	if(rtn)
		arg = rtn->args;
	else
	{
		arg = NULL;
	}

	push_call_stack(rtn);
}
oLP expression_list oRP 
{
#ifdef GENERATE_AST
	$$ = sys_tree($1->attr, $4);
	list_append(&ast_forest, $$);
#else
	do_sys_routine($1->attr, $4);
#endif
	
	pop_call_stack();
}
|pREAD oLP factor oRP
{
	if(!$3){
		parse_error("too few parameters in call to", "read");
		return 0;
	}
#ifdef GENERATE_AST
	if (generic($3->op) == LOAD)
		t = address_tree(NULL, $3->u.generic.sym);
	else
		t = address_tree($3, $3->u.generic.sym);
	$$ = sys_tree(pREAD, t);
	list_append(&ast_forest, $$);
#else
	emit_load_address($3);
	do_sys_routine(pREAD, $3->type->type_id);
#endif
}
;

compound_stmt
:kBEGIN
{
#ifdef GENERATE_AST
	/* block begin. */
	t = new_tree(BLOCKBEG, NULL, NULL, NULL);
	list_append(&ast_forest, t);
#endif
}
stmt_list
kEND
{
#ifdef GENERATE_AST
	/* block end. */
	t = new_tree(BLOCKEND, NULL, NULL, NULL);
	list_append(&ast_forest, t);
#endif
}
;

if_stmt
:kIF 
{
#ifdef GENERATE_AST
	push_lbl_stack(if_label_count++);
#endif
}
expression kTHEN
{
#ifdef GENERATE_AST
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_false_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	t = cond_jump_tree($3, false, new_label);
	list_append(&ast_forest, t);
#else
	do_if_test();
#endif
}
stmt
{
#ifdef GENERATE_AST
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_false_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	t = label_tree(new_label);
	push_ast_stack(t);

	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	/* append jump tree. */
	t = jump_tree(exit_label);
	list_append(&ast_forest, t);
	
	/* append label tree. */
	t = pop_ast_stack();
	list_append(&ast_forest, t);
#else
	do_if_clause();
#endif
}
else_clause
{
#ifdef GENERATE_AST
	/* append exit label. */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	t = label_tree(exit_label);
	list_append(&ast_forest, t);
	pop_lbl_stack();

#else
	do_if_exit();
#endif
}
|kIF error 
{
	printf("expression expected.\n");
}
kTHEN 
{
	printf("then matched.\n");
}
stmt else_clause
;

else_clause
:kELSE stmt
|
;

repeat_stmt
:kREPEAT
{
#ifdef GENERATE_AST
	push_lbl_stack(repeat_label_count++);
	snprintf(mini_buf, sizeof(mini_buf) - 1, "repeat_%d", repeat_label_count - 1);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = label_tree(new_label);
	list_append(&ast_forest, t);
#else
	do_repeat_start();
#endif
}
stmt_list kUNTIL expression
{
#ifdef GENERATE_AST
	snprintf(mini_buf, sizeof(mini_buf) - 1, "repeat_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = cond_jump_tree($5, false, new_label);
	list_append(&ast_forest, t);
	pop_lbl_stack();
#else
	do_repeat_exit();
#endif
}
;

while_stmt
:kWHILE
{
#ifdef GENERATE_AST
	push_lbl_stack(while_label_count++);
	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_test_%d", while_label_count - 1);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = label_tree(test_label);
	list_append(&ast_forest, t);
#else
	do_while_start();
#endif
}
expression kDO
{
#ifdef GENERATE_AST
	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = cond_jump_tree($3, false, exit_label);
	list_append(&ast_forest, t);
#else
	do_while_expr();
#endif
}
stmt
{
#ifdef GENERATE_AST

	/* generate while_exit_%d label tree and push. */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = label_tree(exit_label);
	push_ast_stack(t);

	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_test_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* jump to test tree. */
	t = jump_tree(test_label);
	list_append(&ast_forest, t);

	/* pop while_exit_%d label tree and append. */
	t = pop_ast_stack();
	list_append(&ast_forest, t);
	pop_lbl_stack();
#else
	do_while_exit();
#endif
}
;

for_stmt
:kFOR yNAME oASSIGN expression
{
	p = find_symbol(top_symtab_stack(),$2);
	if(!p || p->defn != DEF_VAR)
	{
		parse_error("lvalue expected","");
		return 0;
	}

	if(p->type->type_id == TYPE_ARRAY
		||p->type->type_id == TYPE_RECORD)
	{
		parse_error("lvalue expected","");
		return 0;
	}
#ifdef GENERATE_AST
	
	/* assign tree */
	t = address_tree(NULL, p);
	push_ast_stack(t);
	list_append(&ast_forest, assign_tree(t, $4));

	/* label tree. */
	push_lbl_stack(for_label_count++);
	snprintf(mini_buf, sizeof(mini_buf) - 1, "for_test_%d", for_label_count - 1);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	t = label_tree(test_label);
	list_append(&ast_forest, t);

#else
	do_for_start(p);
#endif
}
direction expression kDO
{
#ifdef GENERATE_AST

	snprintf(mini_buf, sizeof(mini_buf) - 1, "for_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);


	p = find_symbol(top_symtab_stack(),$2);
	t = id_factor_tree(NULL, p);

	if ($6 == kTO)
	{
		t = compare_expr_tree(LE, t, $7);
	}
	else
	{
		t = compare_expr_tree(GE, t, $7);
	}

	t = cond_jump_tree(t, false, exit_label);
	list_append(&ast_forest, t);
#else
	do_for_test($6);
#endif
}
stmt
{
#ifdef GENERATE_AST
	t = pop_ast_stack();

	if ($6 == kTO)
	{
		t = incr_one_tree(t);
	}
	else
	{
		t = decr_one_tree(t);
	}

	list_append(&ast_forest, t);

	/* jump ast. */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "for_test_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = jump_tree(test_label);
	list_append(&ast_forest, t);

	/* add label ast. */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "for_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = label_tree(exit_label);
	list_append(&ast_forest, t);
	pop_lbl_stack();

#else
	do_for_exit();
#endif
}
;

direction
:kTO
{
	$$ = kTO;
}
|kDOWNTO
{
	$$ = kDOWNTO;
}
;

case_stmt
:kCASE 
{
#ifdef GENERATE_AST
	push_lbl_stack(switch_label_count++);
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_test_%d", switch_label_count - 1);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	case_label_count = 0;
	t = jump_tree(test_label);
	list_append(&ast_forest, t);
	NEW0(case_list, STMT);
	push_case_ast_stack(case_list);
	case_label_count = 0;
	push_case_stack(case_label_count++);
	/* list_clear(&case_list); */
#endif
}
expression kOF
{
#ifdef GENERATE_AST
#else
	do_case_start();
#endif
}
case_expr_list
{
#ifdef GENERATE_AST
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_test_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	t = label_tree(test_label);
	list_append(&ast_forest, t);
	case_list = pop_case_ast_stack();
	{
		int n = list_length(case_list);
		Tree *cases = (Tree *)list_ltov(case_list, PERM);
		int i;

		for (i = 0; i < n; i += 2)
		{
			new_label = cases[i]->u.label.label;
			
			t = compare_expr_tree(EQ, $3, cases[i + 1]);
			t = cond_jump_tree(t, true, new_label);
			list_append(&ast_forest, t);
		}
	}

	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	
	t = label_tree(exit_label);
	list_append(&ast_forest, t);
	pop_lbl_stack();

#else
	do_case_test();
#endif
}
kEND
;

case_expr_list
:case_expr_list case_expr
|case_expr
;

case_expr
:const_value
{
#ifdef GENERATE_AST
	
	case_label_count = pop_case_stack();
	snprintf(mini_buf, sizeof(mini_buf) - 1, "case_%d_%d", top_lbl_stack(), case_label_count++);
	mini_buf[sizeof(mini_buf) - 1] = 0;

	push_case_stack(case_label_count);

	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = label_tree(new_label);
	list_append(&ast_forest, t);

	case_list = top_case_ast_stack();
	list_append(case_list, t);

	t = const_tree($1);
	list_append(case_list, t);
#else
	add_case_const($1);
#endif
}
oCOLON stmt
{
#ifdef GENERATE_AST
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	t = jump_tree(exit_label);
	list_append(&ast_forest, t);
#else
	do_case_jump();
#endif
}
oSEMI
|yNAME
{
	p = find_symbol(
		top_symtab_stack(),$1);
	if(!p){
			parse_error("Undeclared identifier",$1);
			install_temporary_symbol($1, DEF_CONST, TYPE_INTEGER);
			/* return 0; */
	}
	if(p->defn != DEF_ELEMENT
		&&p->defn != DEF_CONST){
			parse_error("Element name expected","");
			return 0;
	}
#ifdef GENERATE_AST
	case_label_count = top_case_stack();
	snprintf(mini_buf, sizeof(mini_buf) - 1, "case_%d_%d", top_lbl_stack(), case_label_count++);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	push_case_stack(case_label_count);

	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = label_tree(new_label);
	list_append(&ast_forest, t);

	case_list = top_case_ast_stack();
	list_append(case_list, t);

	t = id_factor_tree(NULL, p);
	list_append(case_list, t);
#else
	emit_load_value(p);
	add_case_const(p);
#endif
}
oCOLON stmt
{
#ifdef GENERATE_AST
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = jump_tree(exit_label);
	list_append(&ast_forest, t);
#else
	do_case_jump();
#endif
}
oSEMI
;

goto_stmt
:kGOTO cINTEGER
;

expression_list
:expression_list  oCOMMA  expression
{
#ifdef GENERATE_AST

	rtn = top_call_stack();

	/* next argument. */
	if (arg)
	{
		arg = arg->next;
	}

	/* append to right tree of args. */
	args = arg_tree(args, rtn, arg, $3);
	$$ = args;

#endif
}
|expression
{
#ifdef GENERATE_AST

	args = NULL;

	/* first argument. set rtn to symtab of current function call. */
	rtn = top_call_stack();

	if(rtn)
		arg = rtn->args;
	else
	{
		parse_error("error parse sys call list.", "");
		return 0;
	}

	args = arg_tree(args, rtn, arg, $1);

	$$ = args;

#endif
}
;

expression
:expression
{
#ifdef GENERATE_AST
#else
    emit_push_op($1);
#endif
}
oGE expr
{
#ifdef GENERATE_AST
	$$ = compare_expr_tree(GE, $1, $4);
#else
	do_expression($4, oGE);
	$$ = TYPE_BOOLEAN;
#endif
}
|expression
{
#ifdef GENERATE_AST
#else
   	emit_push_op($1);
#endif
}
oGT expr
{
#ifdef GENERATE_AST
	$$ = compare_expr_tree(GT, $1, $4);
#else
	do_expression($4, oGT);
	$$ = TYPE_BOOLEAN;
#endif
}
|expression
{
#ifdef GENERATE_AST
#else
   emit_push_op($1);
#endif
}
oLE expr
{
#ifdef GENERATE_AST
	$$ = compare_expr_tree(LE, $1, $4);
#else

	do_expression($4,oLE);
	$$ = TYPE_BOOLEAN;
#endif
}
|expression
{
#ifdef GENERATE_AST
#else
	emit_push_op($1);
#endif
}
oLT expr
{
#ifdef GENERATE_AST
	$$ = compare_expr_tree(LT, $1, $4);
#else
	do_expression($4,oLT);
	$$ = TYPE_BOOLEAN;
#endif
}
|expression
{
#ifdef GENERATE_AST
#else
	emit_push_op($1);
#endif
}
oEQUAL expr
{
#ifdef GENERATE_AST
	$$ = compare_expr_tree(EQ, $1, $4);
#else
	do_expression($4,oEQUAL);
	$$ = TYPE_BOOLEAN;
#endif
}
|expression
{
#ifdef GENERATE_AST
#else
	emit_push_op($1);
#endif
}
oUNEQU  expr
{
#ifdef GENERATE_AST
	$$ = compare_expr_tree(NE, $1, $4);
#else
	do_expression($4,oUNEQU);
	$$ = TYPE_BOOLEAN;
#endif
}
|expr
{
#ifdef GENERATE_AST
	$$ = $1;
#else
	$$ = $1->type->type_id;
#endif
}
;

expr:expr
{
#ifdef GENERATE_AST
#else
	emit_push_op($1->type->type_id);
#endif
}
oPLUS term
{
#ifdef GENERATE_AST
	$$ = binary_expr_tree(ADD, $1, $4);
#else
	do_expr($4,oPLUS);
#endif
}
|expr
{
#ifdef GENERATE_AST
#else
	emit_push_op($1->type->type_id);
#endif
}
oMINUS  term
{
#ifdef GENERATE_AST
	$$ = binary_expr_tree(SUB, $1, $4);
#else
	do_expr($4 ,oMINUS);
#endif
}
|expr
{
#ifdef GENERATE_AST
#else
	emit_push_op($1->type->type_id);
#endif
}
kOR term
{
#ifdef GENERATE_AST
	$$ = binary_expr_tree(OR, $1, $4);
#else
	do_expression($4,kOR);
#endif
}
|term
{
#ifdef GENERATE_AST
	$$ = $1;
#endif
}
;

term    :term
{
#ifdef GENERATE_AST
#else
        emit_push_op($1->type->type_id);
#endif
}
oMUL  factor
{
#ifdef GENERATE_AST
	$$ = binary_expr_tree(MUL, $1, $4);
#else
	do_term($4,oMUL);
#endif
}
|  term
{
#ifdef GENERATE_AST
#else
	emit_push_op($1->type->type_id);
#endif
}
oDIV factor
{
#ifdef GENERATE_AST
	$$ = binary_expr_tree(DIV, $1, $4);
#else
	do_term($4,kDIV);
#endif
}
|term
{
#ifdef GENERATE_AST
#else
	emit_push_op($1->type->type_id);
#endif

}
kDIV factor
{
#ifdef GENERATE_AST
	$$ = binary_expr_tree(DIV, $1, $4);
#else
	do_term($4, kDIV);
#endif
}
|term
{
#ifdef GENERATE_AST
#else
	emit_push_op($1->type->type_id);
#endif

}
kMOD factor
{
#ifdef GENERATE_AST
	$$ = binary_expr_tree(MOD, $1, $4);
#else
	do_term($4, kMOD);
#endif
}
|term
{
#ifdef GENERATE_AST
#else
	emit_push_op($1->type->type_id);
#endif
}
kAND factor
{
#ifdef GENERATE_AST
	$$ = binary_expr_tree(AND, $1, $4);
#else
	do_term($4,kAND);
#endif
}
|factor
{
	$$ = $1;
}
;

factor: yNAME
{ 
	p = NULL;

	if((p = find_symbol(
		top_symtab_stack(),$1)))
	{
		if(p->type->type_id == TYPE_ARRAY
			||p->type->type_id == TYPE_RECORD)
		{
			parse_error("rvalue expected",  "");
			return 0;
		}
	}
	else if ((ptab = find_routine($1)) == NULL)
	{
		parse_error("Undeclard identificr",$1);
		p = install_temporary_symbol($1, DEF_VAR, TYPE_INTEGER);
		/* return  0; */
	}
#ifdef GENERATE_AST
	if (p)
	{
		$$ = id_factor_tree(NULL, p);
	}
	else
	{
		/* call functions with no arguments. */
		$$ = call_tree(ptab, NULL);
	}
#else
	if(p)
	{
		$$ = p;
		do_factor(p);
	}
	else 
	{
		$$ = do_function_call(ptab);
	}
#endif
}
|yNAME
{
	if((ptab = find_routine($1)))
  		push_call_stack(ptab);
	else
	{
		parse_error("Undeclared funtion",$1);
		return  0;
	}
}
oLP args_list oRP
{
#ifdef GENERATE_AST
	$$ = call_tree(ptab, args);
#else
	$$ = do_function_call(top_call_stack());
#endif
	pop_call_stack();
}
|SYS_FUNCT
{
	ptab = find_sys_routine($1->attr);
#ifdef GENERATE_AST
	$$ = sys_tree($1->attr, NULL);
#else
	do_sys_routine(ptab->id, ptab->type->type_id);
	$$ = ptab->locals;
#endif
}
|SYS_FUNCT
{
	ptab = find_sys_routine($1->attr);
	push_call_stack(ptab);
}
oLP args_list oRP
{
	ptab = top_call_stack();
#ifdef GENERATE_AST
	$$ = sys_tree($1->attr, args);
#else
	ptab = top_call_stack();
	do_sys_routine(-ptab->id, ptab->type->type_id);
	ptab = pop_call_stack();
	$$ = ptab->locals;
#endif
}
|const_value
{
	switch($1->type->type_id){
		case TYPE_REAL:
		case TYPE_STRING:
			add_symbol_to_table(Global_symtab, $1);
			break;
		case TYPE_BOOLEAN:
			sprintf($1->rname, "%d", (int)($1->v.b));
			break;
		case TYPE_INTEGER:
			if($1->v.i > 0)
				sprintf($1->rname,"0%xh", $1->v.i);
			else
				sprintf($1->rname, "-0%xh", -($1->v.i));
			break;
		case TYPE_CHAR:
			sprintf($1->rname, "'%c'", $1->v.c);
			break;
		default:
			break;
	}
#ifdef GENERATE_AST
	$$ = const_tree($1);
#else
	do_factor($1);
#endif
}
|oLP expression oRP
{
#ifdef GENERATE_AST
	$$ = $2;
#else
	$$ = find_symbol(NULL, "");
	$$->type = find_type_by_id($2);
#endif
}
|kNOT factor
{
#ifdef GENERATE_AST
	$$ = not_tree($2);
#else
	do_not_factor($2);
	$$ = $2;
#endif
}
|oMINUS factor
{
#ifdef GENERATE_AST
	$$ = neg_tree($2);
#else
	do_negate($2);
	$$ = $2;
#endif
}
|yNAME  oLB
{
	p = find_symbol(
		top_symtab_stack(), $1);
		   
	if(!p || p->type->type_id != TYPE_ARRAY){
		parse_error("Undeclared array  name",$1);
		return  0;
	}

	push_term_stack(p);

#ifdef GENERATE_AST
#else
	emit_load_address(p);
  	emit_push_op(TYPE_INTEGER);
#endif
}
expression oRB
{
#ifdef GENERATE_AST
	p = pop_term_stack(p);
	t = array_factor_tree(p, $4);
	$$ = id_factor_tree(t, p);
#else
	p = pop_term_stack(p);
	do_array_factor(p);
	emit_load_value(p);
	$$ = p->type_link->last;
#endif
}
|yNAME oDOT yNAME
{
	p = find_symbol(top_symtab_stack(), $1);
	if(!p || p->type->type_id != TYPE_RECORD) {
		parse_error("Undeclared record variable",$1);
		return  0;
	}
	q = find_field(p, $3);
	if(!q || q->defn != DEF_FIELD){
		parse_error("Undeclared field ",$3);
		return 0;
	}
	
#ifdef GENERATE_AST
	t = field_tree(p, q);
	$$ = id_factor_tree(t, q);
#else
	emit_load_address(p);
	emit_push_op(TYPE_INTEGER);
	do_record_factor(p,q);
	emit_load_field(q);
	$$ = q;
#endif
}
;

args_list
:args_list  oCOMMA  expression 
{
#ifdef GENERATE_AST

	rtn = top_call_stack();

	/* next argument. */
	if (arg)
	{
		arg = arg->next;
	}

	/* append to right tree of args. */
	args = arg_tree(args, rtn, arg, $3);
#else
	do_args($3);
#endif
}
|expression 
{
#ifdef GENERATE_AST

	args = NULL;

	/* first argument. set rtn to symtab of current function call. */
	rtn = top_call_stack();

	if(rtn)
		arg = rtn->args;
	else
	{
		parse_error("parse argument list.", "");
		return 0;
	}

	if(arg)
	{
		args = arg_tree(args, rtn, arg, $1);
	}

#else
	do_first_arg($1);
#endif
}
;

%%

#define MAX_TERM  64
symbol *term_stk[MAX_TERM];
int term_stk_tos = MAX_TERM - 1;

void push_term_stack(symbol * p)
{
	if(term_stk_tos == 0)
		internal_error("teminal stak overtlow");
	else
   		term_stk[term_stk_tos--] = p;
 }

symbol * pop_term_stack()
{
	if (term_stk_tos == MAX_TERM - 1)
	{
  		internal_error("terminal stack underflow");
  		return NULL;
	}
    else
		return term_stk[++term_stk_tos];
}

symbol* top_term_stack()
{
	if(term_stk_tos == MAX_TERM - 1){
		internal_error("terminal stack underflow");
		return NULL;
	}
	else
		return term_stk[term_stk_tos + 1];
}

/* 初始化语法解析器 */
int parser_init()
{
#ifdef GENERATE_AST
	memset(&ast_forest, 0, sizeof(ast_forest));
	memset(&para_list, 0, sizeof(para_list));
	memset(&case_list, 0, sizeof(case_list));
	if_label_count = repeat_label_count = 
		do_label_count = while_label_count = 
			case_label_count = switch_label_count = 
				for_label_count = 0;
#endif
	return 0;
}

#ifdef GENERATE_AST
Tree ast_stk[MAX_TERM];
int ast_stk_tos = MAX_TERM - 1;

void push_ast_stack(Tree t)
{
	if(ast_stk_tos == 0)
		internal_error("ast tree stak overtlow");
	else
   		ast_stk[ast_stk_tos--] = t;
}

Tree pop_ast_stack()
{
	if (ast_stk_tos == MAX_TERM - 1)
	{
  		internal_error("ast tree stack underflow");
  		return NULL;
	}
    else
		return ast_stk[++ast_stk_tos];
}

Tree top_ast_stack()
{
	if(ast_stk_tos == MAX_TERM - 1){
		internal_error("ast stack underflow");
		return NULL;
	}
	else
		return ast_stk[ast_stk_tos + 1];
}

int lbl_stk[MAX_TERM];
int lbl_stk_tos = MAX_TERM - 1;

void push_lbl_stack(int id)
{
	if(lbl_stk_tos == 0)
		internal_error("ast tree stak overtlow");
	else
   		lbl_stk[lbl_stk_tos--] = id;
}

int pop_lbl_stack()
{
	if (lbl_stk_tos == MAX_TERM - 1)
	{
  		internal_error("ast tree stack underflow");
  		return 0;
	}
    else
		return lbl_stk[++lbl_stk_tos];
}

int top_lbl_stack()
{
	if(lbl_stk_tos == MAX_TERM - 1){
		internal_error("ast stack underflow");
		return 0;
	}
	else
		return lbl_stk[lbl_stk_tos + 1];
}

int case_stk[MAX_TERM];
int case_stk_tos = MAX_TERM - 1;

void push_case_stack(int id)
{
	if(case_stk_tos == 0)
		internal_error("ast tree stak overtlow");
	else
   		case_stk[case_stk_tos--] = id;
}

int pop_case_stack()
{
	if (case_stk_tos == MAX_TERM - 1)
	{
  		internal_error("ast tree stack underflow");
  		return 0;
	}
    else
		return case_stk[++case_stk_tos];
}

int top_case_stack()
{
	if(case_stk_tos == MAX_TERM - 1){
		internal_error("ast stack underflow");
		return 0;
	}
	else
		return case_stk[case_stk_tos + 1];
}

List case_ast_stk[MAX_TERM];
int case_ast_stk_tos = MAX_TERM - 1;

void push_case_ast_stack(List newlist)
{
	if(case_ast_stk_tos == 0)
		internal_error("ast tree stak overtlow");
	else
   		case_ast_stk[case_ast_stk_tos--] = newlist;
}

List pop_case_ast_stack()
{
	if (case_ast_stk_tos == MAX_TERM - 1)
	{
  		internal_error("ast tree stack underflow");
  		return NULL;
	}
    else
		return case_ast_stk[++case_ast_stk_tos];
}

List top_case_ast_stack()
{
	if(case_ast_stk_tos == MAX_TERM - 1){
		internal_error("ast stack underflow");
		return NULL;
	}
	else
		return case_ast_stk[case_ast_stk_tos + 1];
}
#endif

/* add a temporary symbol when encounted a not defined symbol */
Symbol install_temporary_symbol(char *name, int deftype, int typeid)
{
	Symbol p = new_symbol(name, deftype, typeid);
	add_local_to_table(top_symtab_stack(), p);
	return p;
}

void trap_in_debug(){
	printf("trap_in_debug()\n");
}
