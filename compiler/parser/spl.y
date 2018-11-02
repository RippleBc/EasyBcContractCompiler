%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../common.h"
#include "../ast/symtab.h"
#include "error.h"
#include "../ast/tree.h"

extern char *yytext; /* flex用于记录匹配到的字符串 */
Symtab rtn = NULL; /* 表示system routine */
symtab *ptab;
symbol *p, *q;
type *pt, *qt;
Tree t;

Env global_env;
Env main_env;

/* 记录term上下文 */
symbol* pop_term_stack();
symbol* top_term_stack();
void push_term_stack(symbol * p);


/* 记录AST上下文 */
Tree pop_ast_stack();
Tree top_ast_stack();
void push_ast_stack(Tree t);

/* 记录条件跳转语句的层级 */
int pop_lbl_stack();
int top_lbl_stack();
void push_lbl_stack(int id);

/*  */
int pop_case_stack();
int top_case_stack();
void push_case_stack(int id);

/*  */
List pop_case_ast_stack();
List top_case_ast_stack();
void push_case_ast_stack(List newlist);

/*  */
symtab *top_call_stack();
symtab *pop_call_stack();
void push_call_stack(symtab *p);

/*  */
List top_ast_forest_stack();
List pop_ast_forest_stack();
void push_ast_forest_stack(List l);

/* CASE结构使用 */
List case_list = NULL;  

/* 参数AST树 */
Tree args;
Symbol arg = NULL;

/*  */
struct list routine_forest;
/*  */
struct list *ast_forest;
/*  */
struct list dag_forest;

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

int parser_init();

Symbol install_temporary_symbol(char *name, int deftype, int typeid);
Type install_temporary_type(char *name, int deftype, int typeid);

void trap_in_debug();

#ifdef DEBUG
#define DEBUG_POINT	trap_in_debug();
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

%type  <p_tree>routine_stmt assign_stmt
%type  <p_tree>expression
%type  <p_tree>factor term expr

%start  program

%%

program
:first_act_at_prog program_head sub_program oDOT
{
	/* 弹出无效的symtab */
	pop_symtab_stack();

	if (!err_occur())
	{
		/* 清空dag_forest */
		list_clear(&dag_forest);

		/* 该树节点的操作类型为TAIL，表示该树节点实现的是程序结束的操作。 */
		t = new_tree(TAIL, NULL, NULL, NULL);

		/* 初始化当前命名空间下的符号表 */
		t->u.generic.symtab = top_symtab_stack();
		
		/* 将AST节点挂到ast_forest后面 */
		list_append(top_ast_forest_stack(), t);

		/* generate dag forest. */
		gen_dag(top_ast_forest_stack(), &dag_forest);

		pop_ast_forest_stack();

		/*  */
		interpret(&routine_forest, &dag_forest);
	}

	return 0;
}
;

first_act_at_prog
:%empty  
{
	/* 初始化解析器 */
	parser_init();
	/* 创建全局符号表 */
	make_global_symtab();
	/* 创建系统符号表 */
	make_system_symtab();
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
	/*  */
	global_env.u.program.tab = Global_symtab;

	/* 将全局符号表压入符号表栈中 */
	push_symtab_stack(Global_symtab);

	/*  */
	NEW0(ast_forest, TREE);
	push_ast_forest_stack(ast_forest);
}
|error oSEMI
;

sub_program
:routine_head
{
	main_env.u.main.tab = Global_symtab;
}
routine_body {}
;

name_list
:name_list oCOMMA yNAME 
{
	/* 匹配 oCOMMA yNAME */
	p = new_symbol($3, DEF_UNKNOWN, TYPE_UNKNOWN);

	/* 移动到链表末尾 */
	q = $1;
	while(q->next) {
		q = q->next;
	}

	/* 与新创建的symbol进行链接 */
	q->next = p;

	/* 永远指向头部 */
	$$ = $1;
}
|yNAME
{
	/* 匹配 yNAME */
	p = new_symbol($1, DEF_UNKNOWN, TYPE_UNKNOWN);
	$$ = p;
}
|yNAME error oSEMI {}
|yNAME error oCOMMA {}
;

sub_routine
:routine_head routine_body
;

routine_head
:const_part type_part var_part routine_part {/* 依次定义常量、自定义类型、变量以及自定义函数和过程（函数和过程不分先后顺序） */}
;

const_part
:%empty {}
|kCONST const_expr_list {}
;

const_expr_list
:const_expr_list yNAME oEQUAL const_value oSEMI
{
	/* 命名 */
	strncpy($4->name, $2, NAME_LEN);
	/* 放入符号表 */
	add_symbol_to_table(top_symtab_stack(), $4);
}
|yNAME oEQUAL const_value oSEMI
{
	/* 命名 */
	strncpy($3->name, $1, NAME_LEN);
	/* 放入符号表 */
	add_symbol_to_table(top_symtab_stack(), $3);
}
;

const_value
:cINTEGER
{
	/* 符号 */
	p = new_symbol("$$$", DEF_CONST, TYPE_INTEGER);

	/* 符号值 */
	p->v.i = $1;

	$$ = p;
}
|cREAL
{
	p = new_symbol("$$$",DEF_CONST, TYPE_REAL);

	/* 字符串转化为浮点数 */
	p->v.f = atof($1);

	$$ = p;
}
|cCHAR
{
	p = new_symbol("$$$", DEF_CONST, TYPE_CHAR);

	p->v.c= $1[1];

	$$ = p;
}
|cSTRING
{
	p = new_symbol("$$$", DEF_CONST,
		TYPE_STRING);

	p->v.s = strdup($1);

	$$ = p;
}
|SYS_CON
{
	/* 系统常量符号 */
	p = new_symbol("$$$", DEF_CONST, TYPE_UNKNOWN);

	switch($1)
	{
	case cMAXINT:
		strcpy(p->rname, "maxint");
		/* 符号值（最大整型） */
		p->v.i = (1 << (IR->intmetric.size * 8)) - 1;
		/* 符号类型 */
		p->type = find_type_by_id(TYPE_INTEGER);
		break;

	case cFALSE:
		strcpy(p->rname, "0");
		p->v.b = 0;
		p->type = find_type_by_id(TYPE_BOOLEAN);
		break;
		  
	case cTRUE:
		strcpy(p->rname, "1");
		p->v.b = 1;
		p->type = find_type_by_id(TYPE_BOOLEAN);
		break; 

	default:
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
		/* 全新的自定义类型符号 */
		$$ = $3;
		/* 命名 */
		strncpy($$->name, $1, NAME_LEN);
	}
	else
	{
		/* 已有的自定义类型符号创建自定义类型 */
		$$ = clone_type($3);
		/* 命名 */
		strncpy($$->name, $1, NAME_LEN);
		/* 添加到符号表 */
		add_type_to_table(top_symtab_stack(), $$);
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
	add_type_to_table(top_symtab_stack(), $$);
}
;

record_type_decl
:kRECORD field_decl_list kEND
{
	$$ = new_record_type("$$$", $2);
 	add_type_to_table(top_symtab_stack(), $$);
}
;

field_decl_list
:field_decl_list field_decl
{
	/* 指向属性符号链表的末尾 */
	for(p = $1; p->next; p = p->next);

	/* 添加到属性符号链表末尾 */
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
	/* 遍历名称符号表 */
	for(p = $1; p; p = p->next) {
		/* 定义符号小类 */
		if($3->type_id == TYPE_SUBRANGE || $3->type_id == TYPE_ENUM)
			/* 变量（子范围或枚举类型）的类型由其类型的成员（子范围或枚举类型中的成员）的类型定义 */
			p->type = $3->first->type;
		else
			p->type = find_type_by_id($3->type_id);

		/* 检查子范围和枚举类型的符号值是否合法 */
		p->type_link = $3;

		/* 定义符号大类 */
		p->defn = DEF_FIELD;
	}
	$$ = $1;
}
;

simple_type_decl
:SYS_TYPE
{
	/* char，integer，boolean，real */
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
	/* 枚举类型 */
	$$ = new_enum_type("$$$");

	/* 枚举类型的符号链表 */
	add_enum_elements($$, $2);

	/* 枚举类型放入符号表 */
	add_type_to_table(top_symtab_stack(), $$);
}
|const_value oDOTDOT const_value
{
  /* 子范围类型的前后常量类型必须一致 */
	if($1->type->type_id != $3->type->type_id)
	{
		parse_error("type mismatch","");
		return 0;
	}
	
	/* 子范围类型 */
	$$ = new_subrange_type("$$$", $1->type->type_id);

	/* 子范围类型放入符号表 */
	add_type_to_table(top_symtab_stack(), $$);

	/* 子范围类型的上下界 */
	if($1->type->type_id == TYPE_INTEGER)
		set_subrange_bound($$, (int)$1->v.i, (int)$3->v.i);
	else if ($1->type->type_id == TYPE_BOOLEAN)
		set_subrange_bound($$, (int)$1->v.b, (int)$3->v.b);
	else if ($1->type->type_id == TYPE_CHAR)
		set_subrange_bound($$, (int)$1->v.c, (int)$3->v.c);
	else
		parse_error("invalid element type of subrange","");
}
|oMINUS const_value oDOTDOT const_value
{
	if($2->type->type_id != $4->type->type_id){
		parse_error("type mismatch","");
		return 0;
	}

	$$ = new_subrange_type("$$$", $2->type->type_id);
		
	add_type_to_table(top_symtab_stack(), $$);

	if($2->type->type_id == TYPE_INTEGER){
		/* 转化为负数 */
		$2->v.i = -$2->v.i;
		set_subrange_bound($$, (int)$2->v.i, (int)$4->v.i);
	}
	else if ($2->type->type_id == TYPE_BOOLEAN){
		/* 1转化为0，0转化为1 */
		$2->v.b ^= 1;
		set_subrange_bound($$, (int)$2->v.b,(int)$4->v.b);
	}
	else if ($2->type->type_id == TYPE_CHAR)
		parse_error("invalid operator", "");
	else
   		parse_error("invalid element type of subrange", "");
}
|oMINUS const_value oDOTDOT oMINUS const_value
{
	if($2->type->type_id != $5->type->type_id) {
		parse_error("type mismatch", "");
		return  0;
	}
	
	$$ = new_subrange_type("$$$", $2->type->type_id);

	add_type_to_table(top_symtab_stack(), $$);

	if($2->type->type_id == TYPE_INTEGER){
		$2->v.i = -$2->v.i;
		$5->v.i = -$5->v.i;
	
		set_subrange_bound($$, (int)$2->v.i, (int)$5->v.i);
	}
	else if ($2->type->type_id == TYPE_BOOLEAN){
		$2->v.b ^= 1;
		$5->v.b ^= 1;

		set_subrange_bound($$, (int)$2->v.b, (int)$5->v.b);
	}
	else if ($2->type->type_id == TYPE_CHAR)
		parse_error("invalid operator", "");
	else
		parse_error("invalid element type of subrange", "");
}
|yNAME oDOTDOT yNAME
{
	
	/* 符号（枚举） */
	p = find_symbol(top_symtab_stack(), $1);
	if(!p){
		parse_error("Undeclared identifier", $1);
		install_temporary_symbol($1, DEF_ENUM_ELEMENT, TYPE_INTEGER);
	}
	if(p->defn != DEF_ENUM_ELEMENT){
		parse_error("not an element identifier", $1);
	}
	
	/* 符号（枚举） */
	q = find_symbol(top_symtab_stack(), $3);
	if(!q){
		parse_error("Undeclared identifier", $3);
		install_temporary_symbol($3, DEF_ENUM_ELEMENT, TYPE_INTEGER);
	}
	if(q->defn != DEF_ENUM_ELEMENT){
		parse_error("Not an element identifier", $3);
	}
	
	/* 子范围类型 */
	$$ = new_subrange_type("$$$", TYPE_INTEGER);
	/* 添加到符号表 */
	add_type_to_table(top_symtab_stack(), $$);
	/* 子范围类型的上下界 */
	set_subrange_bound($$, p->v.i, q->v.i);
}
;

var_part
:%empty {}
|kVAR var_decl_list {}
;

var_decl_list
:var_decl_list var_decl {}
|var_decl {}
;

var_decl
:name_list oCOLON type_decl oSEMI
{
	/* 对应的符号表 */
	ptab = top_symtab_stack();
	
	/* 遍历名称符号链表 */
	for(p = $1; p;){
		if($3->type_id == TYPE_SUBRANGE || $3->type_id == TYPE_ENUM)
		{
			/* 变量（子范围以及枚举类型）的类型是由其类型中的成员（子范围或者枚举类型的成员）的类型定义 */
			p->type = find_type_by_id($3->first->type->type_id);
		}
		else
		{
			p->type = find_type_by_id($3->type_id);
		}

		p->type_link = $3;

		/* 定义符号大类 */
		p->defn = DEF_VAR;

		q = p; 
		p = p->next;
		q->next = NULL;

		/* 添加到符号表中 */
		add_symbol_to_table(ptab, q);
	}
}
;

routine_part
:%empty
|routine_part function_decl { }
|routine_part procedure_decl { }
|function_decl {}
|procedure_decl {}
;

function_decl
:function_head oSEMI sub_routine oSEMI 
{
	if (!err_occur())
	{
		/* 清楚DAG森林 */
		list_clear(&dag_forest);

		/* 终点AST节点 */
		t = new_tree(TAIL, NULL, NULL, NULL);
		/* 对应的符号表 */
		t->u.generic.symtab = top_symtab_stack();
		/* 放入AST森林 */
		list_append(top_ast_forest_stack(), t);

		/* 生成AST森林 */
		gen_dag(top_ast_forest_stack(), &dag_forest);

		/*  */
		pop_ast_forest_stack();

		/*  */
		list_append(&routine_forest, dag_forest.link);
	}

	/* 弹出函数对应的符号表 */
	pop_symtab_stack();
}
;

function_head
:kFUNCTION
{
	/* AST森林 */
	NEW0(ast_forest, TREE);
	push_ast_forest_stack(ast_forest);

	/* 创建符号表 */
	ptab = new_symtab(top_symtab_stack());

	/* 记录自定义函数 */
	add_routine_to_table(top_symtab_stack(), ptab);

	/* 符号表压栈 */
	push_symtab_stack(ptab);
}
yNAME parameters oCOLON simple_type_decl
{
	/* 对应的符号表 */
	ptab = top_symtab_stack();

	/* 符号表命名 */
	strncpy(ptab->name, $3, NAME_LEN);

	/* 符号表的汇编名称命名 */
	sprintf(ptab->rname, "rtn%03d", ptab->id);

	/* 符号表大类 */
	ptab->defn = DEF_FUNCT;
	
	/* 符号表小类 */
	if($6->type_id == TYPE_SUBRANGE || $6->type_id == TYPE_ENUM)
		ptab->type = find_type_by_id(TYPE_INTEGER);
	else
		ptab->type = find_type_by_id($6->type_id);

	/* 函数符号 */
	p = new_symbol($3, DEF_FUNCT, ptab->type->type_id);
	/* 当函数返回值为子范围或枚举时，需要检查返回值是否合法 */
	p->type_link = $6;
	/* 添加到符号表中 */
	add_symbol_to_table(ptab, p);
	/* 符号表中的参数符号链表反转 */
	reverse_parameters(ptab);

	/* 生成一颗AST树 */
	Tree header;
	/* 头部AST节点 */
	header = new_tree(HEADER, ptab->type, NULL, NULL);
	/* 头部AST节点对应的符号表 */
	header->u.generic.symtab = ptab;
	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), header);
}
;

procedure_decl
:procedure_head oSEMI sub_routine oSEMI
{

	if (!err_occur())
	{
		list_clear(&dag_forest);

		t = new_tree(TAIL, NULL, NULL, NULL);
		t->u.generic.symtab = top_symtab_stack();
		list_append(top_ast_forest_stack(), t);

		gen_dag(top_ast_forest_stack(), &dag_forest);

		pop_ast_forest_stack();;

		list_append(&routine_forest, dag_forest.link);
	}
	pop_symtab_stack();
}
;

procedure_head
:kPROCEDURE
{
	NEW0(ast_forest, TREE);
	push_ast_forest_stack(ast_forest);

	ptab = new_symtab(top_symtab_stack());

	add_routine_to_table(top_symtab_stack(), ptab);

	push_symtab_stack(ptab);
}
yNAME parameters
{
	ptab = top_symtab_stack();
	strncpy(ptab->name, $3, NAME_LEN);
	sprintf(ptab->rname, "rtn%03d", ptab->id);
	ptab->defn = DEF_PROC;

	p = new_symbol($3, DEF_PROC, TYPE_VOID);
	add_symbol_to_table(ptab, p);
	reverse_parameters(ptab);

	Tree header;
	header = new_tree(HEADER, find_type_by_id(TYPE_VOID), NULL, NULL);
	list_append(top_ast_forest_stack(), header);
}
;

parameters
:%empty {/* 参数部分可以为空 */}
|oLP para_decl_list oRP
{
	/* 对应的符号表 */
	ptab = top_symtab_stack();
	/* 符号表大小 */
	ptab->local_size = 0;
}
;

para_decl_list
:para_decl_list oSEMI para_type_list {/* 不同类型的参数之间使用符号';'进行分割 */}
|para_type_list {}
;

para_type_list
:val_para_list oCOLON simple_type_decl
{
	/* 对应的符号表 */
	ptab = top_symtab_stack();

	/* 遍历名称符号链表 */
	for(p = $1; p;)
	{
		if($3->type_id == TYPE_SUBRANGE || $3->type_id == TYPE_ENUM)
			p->type = $3->first->type;
		else
			p->type = find_type_by_id($3->type_id);
		p->type_link = $3;
		p->defn = DEF_VALPARA;

		q = p; 
		p = p->next;
		q->next = NULL;

		/* 放入符号表中 */
		add_symbol_to_table(ptab, q);
	}
}
|var_para_list oCOLON simple_type_decl
{
	/* 对应的符号表 */
	ptab = top_symtab_stack();

	/* 遍历名称符号链表 */
	for(p = $1; p;)
	{
		if($3->type_id == TYPE_SUBRANGE || $3->type_id == TYPE_ENUM)
			p->type = $3->first->type;
		else
			p->type = find_type_by_id($3->type_id);
		p->type_link = $3;
		p->defn = DEF_VARPARA;

		q = p; p = p->next;
		q->next=NULL;

		/* 放入符号表中 */
		add_symbol_to_table(ptab, q);
	}
}
;

val_para_list
:name_list 
{ 
	$$ = $1;
}
;

var_para_list
:kVAR name_list
{
	$$ = $2;
}
;

routine_body
:compound_stmt {}
;

stmt_list
:%empty {/* 可以是空函数 */}
|stmt_list stmt oSEMI {}
|stmt_list error oSEMI {/* 错误处理 */}

;

stmt
:%empty {}
|assign_stmt {}
|routine_stmt {}
|compound_stmt {}
|if_stmt {}
|repeat_stmt {}
|while_stmt {}
|for_stmt {}
|case_stmt {}
;

assign_stmt
:yNAME oASSIGN expression
{
	/* 对应的符号 */
	p = find_symbol(top_symtab_stack(), $1);
	if (p == NULL)
	{
		parse_error("undeclared identifier.", $1);
		install_temporary_symbol($1, DEF_VAR, $3->result_type->type_id);
	}

	/* 检查赋值是否合法 */
	if(p->type->type_id == TYPE_RECORD)
	{
		parse_error("lvalue expected", "");
	}
	if(p->type->type_id == TYPE_ARRAY)
	{
		if($3->result_type->type_id != TYPE_STRING)
		{
			parse_error("lvalue expected", "");
		}
	}

	/* 类型检查 */
	if((p->type->type_id != $3->result_type->type_id) &&
	(p->type->type_id != TYPE_ARRAY || p->type->last->type->type_id != TYPE_CHAR || $3->result_type->type_id != TYPE_STRING))
	{
		parse_error("type mismatch", "");
		return 0;  
	}


	/* 地址AST树 */
	t = address_tree(p);
	/* 赋值AST树 */
	$$ = assign_tree(t, $3);
	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), $$);
}
|yNAME oLB
{
	/* 对应的符号 */
	p = find_symbol(top_symtab_stack(), $1);
	if(p == NULL)
	{
		parse_error("undefined identifier", $1);
		return 0;
	}
	
	/* 检查赋值是否合法 */
	if(p->type->type_id != TYPE_ARRAY)
	{
		parse_error("var type mismatch", $1);
		return 0;
	}
	
	push_term_stack(p);
}
expression oRB
{
	/* 获取符号 */
	p = top_term_stack();
	
	/* 数组AST节点 */
	t = array_index_tree(p, $4);

	push_ast_stack(t);
}
oASSIGN expression
{
	t = pop_ast_stack();

	/* 赋值AST节点 */
	$$ = assign_tree(t, $8);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), $$);
}
|yNAME oDOT yNAME
{
	/* 对应的符号 */
	p = find_symbol(top_symtab_stack(), $1);
	if(!p || p->type->type_id != TYPE_RECORD){
		parse_error("Undeclared record vaiable", $1);
		return 0;
	}

	/* 对应的属性 */
	q = find_field(p, $3);
	if(!q || q->defn != DEF_FIELD){
		parse_error("Undeclared field", $3);
		return 0;
	}


	/* 属性AST节点 */
	t = record_field_tree(p, q);

	push_ast_stack(t);
}
oASSIGN expression
{
	t = pop_ast_stack();

	/* 赋值AST节点 */
	$$ = assign_tree(t, $6);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), $$);
}
;

routine_stmt
:yNAME
{
	/* 寻找自定义函数或者过程 */
	if((ptab = find_routine(top_symtab_stack(), $1)))
	{
		push_call_stack(ptab);
	}
  		
	else
	{
		parse_error("Undeclared funtion", $1);
		return  0;
	}
}
oLP args_list oRP
{
	/* 函数或过程调用AST节点 */
	$$ = call_tree(top_call_stack(), args);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), $$);

	pop_call_stack();
}
|SYS_FUNCT
{
	/* 系统函数或者系统过程调用AST节点 */
	$$ = sys_tree($1->attr, NULL);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), $$);
}
|SYS_PROC
{
	$$ = sys_tree($1->attr, NULL);

	list_append(top_ast_forest_stack(), $$);
}
|SYS_FUNCT 
{
	/* 对应的系统函数或者系统过程的符号表 */
	rtn = find_sys_routine($1->attr);

	push_call_stack(rtn);
}
oLP args_list oRP 
{
	/* 系统函数或者系统过程调用AST节点 */
	$$ = sys_tree($1->attr, args);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), $$);

	pop_call_stack();
}
|SYS_PROC 
{
	rtn = find_sys_routine($1->attr);

	push_call_stack(rtn);
}
oLP args_list oRP 
{
	$$ = sys_tree($1->attr, args);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), $$);

	pop_call_stack();
}
|pREAD oLP factor oRP
{
	if($3 == NULL){
		parse_error("too few parameters in call to", "read");
		return 0;
	}
	
	if (generic($3->op) == LOAD)
	{
		if($3->kids[0]) /* 数组或者记录 */
		{
			t = $3->kids[0];
		}
		else
		{
			t = address_tree($3->u.generic.sym);
		}
	}
	else
	{
		parse_error("pread need a variable argument", "");
		return 0;
	}

	/* 系统函数或者系统过程调用AST节点 */
	$$ = sys_tree(pREAD, t);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), $$);
}
;

compound_stmt
:kBEGIN
{
	/* 开始块AST节点 */
	t = new_tree(BLOCKBEG, NULL, NULL, NULL);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), t);
}
stmt_list
kEND
{
	/* 结束块AST节点 */
	t = new_tree(BLOCKEND, NULL, NULL, NULL);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), t);
}
;

if_stmt
:kIF 
{
	/* 记录标签层级 */
	push_lbl_stack(if_label_count++);
}
expression kTHEN
{
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_false_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（ELSE子句的入口） */
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 条件跳转AST节点（条件为假时跳转到ELSE标签的入口） */
	t = cond_jump_tree($3, false, new_label);
	list_append(top_ast_forest_stack(), t);
}
stmt
{
  /* 初始化符号（ELSE子句的入口） */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_false_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 标签AST节点（ELSE子句的入口） */
	t = label_tree(new_label);
	/* 记录AST节点 */
	push_ast_stack(t);

	/* 初始化符号（IF结构出口） */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 条件跳转AST节点（IF子句执行完毕后，跳转到IF结构的出口） */
	t = jump_tree(exit_label);
	list_append(top_ast_forest_stack(), t);

	/* 获取标签AST节点（ELSE子句的入口） */
	t = pop_ast_stack();
	list_append(top_ast_forest_stack(), t);
}
else_clause
{
	/* 初始化符号（IF结构出口） */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 标签AST节点（IF结构出口） */
	t = label_tree(exit_label);
	list_append(top_ast_forest_stack(), t);
	pop_lbl_stack();
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
:%empty {}
|kELSE stmt {}
;

repeat_stmt
:kREPEAT
{
	push_lbl_stack(repeat_label_count++);
	snprintf(mini_buf, sizeof(mini_buf) - 1, "repeat_%d", repeat_label_count - 1);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（REPEAT结构的入口） */
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 标签AST节点（REPEAT结构的入口） */
	t = label_tree(new_label);
	list_append(top_ast_forest_stack(), t);
}
stmt kUNTIL expression
{
	snprintf(mini_buf, sizeof(mini_buf) - 1, "repeat_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（REPEAT结构的入口） */
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 条件跳转AST节点（条件为真时，跳转到REPEAT结构的入口） */
	t = cond_jump_tree($5, false, new_label);
	list_append(top_ast_forest_stack(), t);

	pop_lbl_stack();
}
;

while_stmt
:kWHILE
{
	push_lbl_stack(while_label_count++);
	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_test_%d", while_label_count - 1);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（WHILE结构的入口） */
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 标签AST节点（WHILE结构的入口） */
	t = label_tree(test_label);

	list_append(top_ast_forest_stack(), t);
}
expression kDO
{
	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（WHILE结构的出口） */
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 条件跳转AST节点（条件为假时，跳转到WHILE结构的出口） */
	t = cond_jump_tree($3, false, exit_label);

	list_append(top_ast_forest_stack(), t);
}
stmt
{
	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（WHILE结构的出口） */
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 标签AST节点（WHILE结构的出口） */
	t = label_tree(exit_label);
	push_ast_stack(t);

	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_test_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（WHILE结构的入口） */
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 跳转AST节点（跳转到WHILE结构的入口） */
	t = jump_tree(test_label);
	list_append(top_ast_forest_stack(), t);

	/* 获取标签AST节点（WHILE结构的出口） */
	t = pop_ast_stack();
	list_append(top_ast_forest_stack(), t);
	pop_lbl_stack();
}
;

for_stmt
:kFOR yNAME oASSIGN expression
{
	/* 变量对应的符号 */
	p = find_symbol(top_symtab_stack(), $2);
	if(!p || p->defn != DEF_VAR)
	{
		parse_error("lvalue expected","");
		return 0;
	}

	/* 检查变量取值格式 */
	if(p->type->type_id == TYPE_ARRAY
		||p->type->type_id == TYPE_RECORD)
	{
		parse_error("lvalue expected","");
		return 0;
	}
	
	/* 地址AST节点 */
	t = address_tree(p);
	/* 保存地址AST节点（FOR中条件判断相关的变量） */
	push_ast_stack(t);
	/* 赋值AST节点 */
	list_append(top_ast_forest_stack(), assign_tree(t, $4));

	push_lbl_stack(for_label_count++);
	snprintf(mini_buf, sizeof(mini_buf) - 1, "for_test_%d", for_label_count - 1);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（FOR结构的入口） */
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 标签AST节点（FOR结构的入口） */
	t = label_tree(test_label);
	list_append(top_ast_forest_stack(), t);
}
direction expression kDO
{
	snprintf(mini_buf, sizeof(mini_buf) - 1, "for_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（FOR结构的出口） */
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 变量对应的符号 */
	p = find_symbol(top_symtab_stack(), $2);
	/* 取值AST节点（获取变量的值） */
	t = id_factor_tree(NULL, p);

	if ($6 == kTO)
	{
		/* 比较AST节点 */
		t = compare_expr_tree(LE, t, $7);
	}
	else
	{
		t = compare_expr_tree(GE, t, $7);
	}

	/* 条件跳转AST节点（条件为假时，跳转到FOR结构的出口） */
	t = cond_jump_tree(t, false, exit_label);
	list_append(top_ast_forest_stack(), t);
}
stmt
{
	/* 获取地址AST节点（FOR中条件判断相关的变量） */
	t = pop_ast_stack();

	if ($6 == kTO)
	{
		/* 递增AST节点（FOR中条件判断相关的变量递增） */
		t = incr_one_tree(t);
	}
	else
	{
		t = decr_one_tree(t);
	}
	list_append(top_ast_forest_stack(), t);

	snprintf(mini_buf, sizeof(mini_buf) - 1, "for_test_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（FOR结构的出口） */
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 跳转AST节点（跳转到FOR结构的入口） */
	t = jump_tree(test_label);
	list_append(top_ast_forest_stack(), t);

	snprintf(mini_buf, sizeof(mini_buf) - 1, "for_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;

	/* 标签符号（FOR结构的出口） */
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 标签AST符号（FOR结构的出口） */
	t = label_tree(exit_label);
	list_append(top_ast_forest_stack(), t);

	pop_lbl_stack();
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
	push_lbl_stack(switch_label_count++);
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_test_%d", switch_label_count - 1);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号 */
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 跳转AST节点（条件测试的入口） */
	t = jump_tree(test_label);
	list_append(top_ast_forest_stack(), t);

	/* 在STMT区域为case_list分配内存 */
	NEW0(case_list, STMT);
	push_case_ast_stack(case_list);
	case_label_count = 0;
	push_case_stack(case_label_count++);
}
expression kOF case_expr_list
{
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_test_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（条件测试的入口） */
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 标签AST节点（条件测试的入口） */
	t = label_tree(test_label);
	list_append(top_ast_forest_stack(), t);
	case_list = pop_case_ast_stack();

	/* 将CASE子句从链表结构转化为数组结构 */
	int n = list_length(case_list);
	Tree *cases = (Tree *)list_ltov(case_list, PERM);
	int i;

	/* 遍历CASE子句数组（用来产生条件测试的内容） */
	for (i = 0; i < n; i += 2)
	{
		/* 获取标签符号（CASE子句的入口） */
		new_label = cases[i]->u.generic.sym;
		/* 比较AST节点（CASE子句判断条件） */
		t = compare_expr_tree(EQ, $3, cases[i + 1]);
		/* 条件跳转AST节点（条件为真时跳转到指定的CASE子句） */
		t = cond_jump_tree(t, true, new_label);
		list_append(top_ast_forest_stack(), t);
	}

	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（CASE结构的出口） */
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 标签AST节点（CASE结构的出口） */
	t = label_tree(exit_label);
	list_append(top_ast_forest_stack(), t);
	pop_lbl_stack();
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
	case_label_count = pop_case_stack();
	snprintf(mini_buf, sizeof(mini_buf) - 1, "case_%d_%d", top_lbl_stack(), case_label_count++);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	push_case_stack(case_label_count);

	/* 标签符号（CASE子句的入口） */
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 标签AST节点（CASE子句的入口） */
	t = label_tree(new_label);
	list_append(top_ast_forest_stack(), t);

	/* 获取CASE子句链表 */
	case_list = top_case_ast_stack();
	/* 将标签AST节点（CASE子句的入口）放入CASE子句链表 */
	list_append(case_list, t);

	/* 常数AST节点（CASE子句判断条件） */
	t = const_tree($1);
	/* 将常数AST节点（CASE子句判断条件）放入CASE子句链表 */
	list_append(case_list, t);
}
oCOLON stmt
{
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（CASE结构的出口） */
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 跳转AST节点（CASE结构的出口） */
	t = jump_tree(exit_label);
	list_append(top_ast_forest_stack(), t);
}
oSEMI
|yNAME
{
	/* 变量对应的符号 */
	p = find_symbol(top_symtab_stack(),$1);
	if(!p){
			parse_error("Undeclared identifier",$1);
			install_temporary_symbol($1, DEF_CONST, TYPE_INTEGER);
			/* return 0; */
	}
	/* 检查变量类型（CASE子句中的判断条件只能是枚举或者常量类型） */
	if(p->defn != DEF_ENUM_ELEMENT && p->defn != DEF_CONST){
			parse_error("Element name expected","");
			return 0;
	}
	case_label_count = top_case_stack();
	snprintf(mini_buf, sizeof(mini_buf) - 1, "case_%d_%d", top_lbl_stack(), case_label_count++);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	push_case_stack(case_label_count);

	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = label_tree(new_label);
	list_append(top_ast_forest_stack(), t);

	case_list = top_case_ast_stack();
	list_append(case_list, t);

	t = id_factor_tree(NULL, p);
	list_append(case_list, t);
}
oCOLON stmt
{
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = jump_tree(exit_label);
	list_append(top_ast_forest_stack(), t);
}
oSEMI
;

expression
:expression oGE expr
{
	/* 比较运算AST树（>=），由于优先级问题，放在expr表达式中（expression表达式中的运算优先级比expr中的要低），仅支持左结合 */
	$$ = compare_expr_tree(GE, $1, $3);
}
|expression oGT expr
{
	/* 比较运算AST树（>） */
	$$ = compare_expr_tree(GT, $1, $3);
}
|expression oLE expr
{
	/* 比较运算AST树（<=） */
	$$ = compare_expr_tree(LE, $1, $3);
}
|expression oLT expr
{
	/* 比较运算AST树（<） */
	$$ = compare_expr_tree(LT, $1, $3);
}
|expression oEQUAL expr
{
	/* 比较运算AST树（=） */
	$$ = compare_expr_tree(EQ, $1, $3);
}
|expression oUNEQU  expr
{
	/* 比较运算AST树（<>，不相等） */
	$$ = compare_expr_tree(NE, $1, $3);
}
|expr
{
	$$ = $1;
}
;

expr
:expr oPLUS term
{
	/* 二元运算AST树（+），由于优先级问题，放在expr表达式中（expr表达式中的运算优先级比term中的要低），仅支持左结合 */
	$$ = binary_expr_tree(ADD, $1, $3);
}
|expr oMINUS term
{
	/* 二元运算AST树（-） */
	$$ = binary_expr_tree(SUB, $1, $3);
}
|expr kOR term
{
	/* 二元运算AST树（or）  */
	$$ = binary_expr_tree(OR, $1, $3);
}
|term
{
	$$ = $1;
}
;

term
:term oMUL factor
{
	/* 二元运算AST树（*），由于优先级问题，放在expr表达式中（运算符优先级最高），仅支持左结合。 */
	$$ = binary_expr_tree(MUL, $1, $3);
}
|term oDIV factor
{
	/* 二元运算AST树（/） */
	$$ = binary_expr_tree(DIV, $1, $3);
}
|term kDIV factor
{
	/* 二元运算AST树（div） */
	$$ = binary_expr_tree(DIV, $1, $3);
}
|term kMOD factor
{
	/* 二元运算AST树（mod） */
	$$ = binary_expr_tree(MOD, $1, $3);
}
|term kAND factor
{
	/* 二元运算AST树（and） */
	$$ = binary_expr_tree(AND, $1, $3);
}
|factor
{
	$$ = $1;
}
;

factor
:yNAME
{
	/* 对应的符号 */
	p = find_symbol(top_symtab_stack(), $1);
	if(p)
	{
		/* 类型检查 */
		if(p->type->type_id == TYPE_ARRAY || p->type->type_id == TYPE_RECORD)
		{
			parse_error("rvalue expected", "");
			return 0;
		}
	}
	else
	{
		parse_error("Undeclard identificr", $1);
		p = install_temporary_symbol($1, DEF_VAR, TYPE_INTEGER);
	}

	/* 取值AST节点 */
	$$ = id_factor_tree(NULL, p);
}
|yNAME
{
	/* 寻找自定义函数或者过程 */
	if((ptab = find_routine(top_symtab_stack(), $1)))
  		push_call_stack(ptab);
	else
	{
		parse_error("Undeclared funtion or procedure", $1);
		return  0;
	}
}
oLP args_list oRP
{
	/* 自定义函数或者过程调用AST节点 */
	$$ = call_tree(top_call_stack(), args);

	pop_call_stack();
}
|SYS_FUNCT
{
	ptab = find_sys_routine($1->attr);

	/* 系统函数或者过程调用AST节点 */
	$$ = sys_tree($1->attr, NULL);
}
|SYS_FUNCT
{
	ptab = find_sys_routine($1->attr);
	push_call_stack(ptab);
}
oLP args_list oRP
{
	/* 获取当前需要调用的函数或者过程对应的符号表 */
	ptab = top_call_stack();

	/* 系统函数或者过程调用（有参调用） */
	$$ = sys_tree($1->attr, args);
}
|const_value
{
	/* 常量（term中const_value由于只在表达式中使用一次，不需要对name字段进行命名），比如表达式 1+2+3 中的 1 */
	switch($1->type->type_id){
		case TYPE_REAL:
		case TYPE_STRING:
			/* 通过全局符号表记录常量 */
			add_symbol_to_table(Global_symtab, $1);
			break;
		case TYPE_BOOLEAN:
			/* 通过汇编名称记录常量 */
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

	/* 常量AST树 */
	$$ = const_tree($1);
}
|oLP expression oRP
{
 	/* AST树（提高expression的优先级） */
	$$ = $2;
}
|kNOT factor
{
	/* 一元操作符（not） */
	$$ = not_tree($2);
}
|oMINUS factor
{
	/* 一元操作符（-） */
	$$ = neg_tree($2);
}
|yNAME oLB
{
	/* 寻找对应的符号 */
	p = find_symbol(top_symtab_stack(), $1);
	
	/* 检查符号类型是否是数组 */
	if(!p || p->type->type_id != TYPE_ARRAY){
		parse_error("Undeclared array name",$1);
		return  0;
	}

	/* 数组符号入栈（保存上下文） */
	push_term_stack(p);
}
expression oRB
{
	/* 数组符号出栈（获取上下文） */
	p = pop_term_stack(p);
	/* 数组AST树 */
	t = array_index_tree(p, $4);
	/* 数组取值AST树 */
	$$ = id_factor_tree(t, NULL);
}
|yNAME oDOT yNAME
{
	/* 寻找对应的符号 */
	p = find_symbol(top_symtab_stack(), $1);

	/* 检查符号类型是否是记录 */
	if(!p || p->type->type_id != TYPE_RECORD) {
		parse_error("Undeclared record variable",$1);
		return  0;
	}

	/* 寻找记录类型变量对应的symbol */
	q = find_field(p, $3);

	/* 检查符号类型 */
	if(!q || q->defn != DEF_FIELD){
		parse_error("Undeclared field ",$3);
		return 0;
	}

	/* field的AST树 */
	t = record_field_tree(p, q);
	/* field取值AST树 */
	$$ = id_factor_tree(t, NULL);
}
;

args_list
:%empty 
{
	/**/
	args = NULL; 
}
|args_list  oCOMMA  expression 
{
	/* 获取函数或者过程调用上下文 */
	rtn = top_call_stack();

	/* 从符号表的参数链表中获取下一个参数 */
	if (arg)
	{
		arg = arg->next;
	}

	/* 将参数放入参数AST树中 */
	args = arg_tree(args, rtn, arg, $3); 
}
|expression 
{
	args = NULL;

	/* 获取上下文环境（函数或者过程对应的符号表） */
	rtn = top_call_stack();

	/* 从符号表的参数链表中获取第一个参数 */
	if(rtn)
		arg = rtn->args;
	else
	{
		parse_error("parse argument list.", "");
		return 0;
	}

	/* 初始化参数AST树 */
	args = arg_tree(args, rtn, arg, $1);
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
	memset(&case_list, 0, sizeof(case_list));
	if_label_count = repeat_label_count = 
		do_label_count = while_label_count = 
			case_label_count = switch_label_count = 
				for_label_count = 0;
	return 0;
}

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

Symbol install_temporary_symbol(char *name, int deftype, int typeid)
{
	Symbol p = new_symbol(name, deftype, typeid);
	add_local_to_table(top_symtab_stack(), p);
	return p;
}

void trap_in_debug(){
	printf("trap_in_debug()\n");
}

#define MAX_CALL_LEVEL 16

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

    return call_stk[call_tos];
}

void push_call_stack(symtab *p)
{
    call_stk[call_tos] = p;

    call_tos--;
    if (call_tos == -1)
        internal_error("call stack overflow.");
}


static List ast_forest_stk[MAX_CALL_LEVEL];

static int ast_forest_tos = MAX_CALL_LEVEL - 1;

List top_ast_forest_stack( )
{
    return ast_forest_stk[ast_forest_tos + 1];
}

List pop_ast_forest_stack()
{
    ast_forest_tos++;

    if (ast_forest_tos == MAX_CALL_LEVEL)
        internal_error("ast forest stack underflow.");

    return ast_forest_stk[ast_forest_tos];
}

void push_ast_forest_stack(List l)
{
    ast_forest_stk[ast_forest_tos] = l;

    ast_forest_tos--;

    if (ast_forest_tos == -1)
        internal_error("ast forest stack overflow.");
}