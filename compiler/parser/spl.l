%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../common.h"

#include "rule.h"

int Keytable_size = 0;

/* number of line. */
extern int line_no;
/* position of line. */
extern int line_pos;
/* buffer of current line. */
extern char line_buf[];

extern YYSTYPE yylval;
/* 是否把匹配到的文本输出 */
extern int dump_source;
/* 是否把匹配的TOKEN输出 */
extern int dump_token;

/* 判断是标识符还是关键字 */
static int id_or_keyword(char *lex);

/* 拷贝匹配到的内容到line_buf（结束标记'\0'），
 重新计算line_pos时需要删除结束标记'\0' */
#define DUMP_SOURCE if(dump_source) ECHO; \
						if (line_pos + strlen(yytext) < MAX_LINE_LENGTH) \
							memmove(line_buf + line_pos, yytext, strlen(yytext) + 1); \
						line_pos += strlen(yytext);

static char tmp[NAME_LEN];
%}

letter	[_a-zA-Z]
alnum	[_a-zA-Z0-9]
dec		[0-9]
hex		[0-9a-fA-F]
oct		[0-7]

%s star_slash_comment slash_slash_comment
%%
"{" {
	int c;
	
	/* 检查块结果 */
	while ((c = input()))
	{
		if (c == '}')
		{
			break;
		}
		else if (c == '\n')
		{
			line_no ++;
		}
	}

	if (c == EOF)
		parse_error("Unexpected EOF.","");
}

[1-9]+{dec}* {
	DUMP_SOURCE

	/* 将字符串转化成十进制数字 */
	yylval.num = stoi(yytext, 10);

	if (dump_token)
	{
		printf("token: cINTEGER, yylval.num = %d.\n", yylval.num);
	}
	return cINTEGER;
}
					
0{oct}* {
	DUMP_SOURCE

	/* 将字符串转化成十进制数字 */
	yylval.num = stoi(yytext, 8);

	if (dump_token)
	{
		printf("token: cINTEGER, yylval.num = %d.\n", yylval.num);
	}
	return cINTEGER;
}
					
0(x|X){hex}+ {
	DUMP_SOURCE

	/* 将字符串转化成十进制数字 */
	yylval.num = stoi(yytext, 16);

	if (dump_token)
	{
		printf("token: cINTEGER, yylval.num = %d.\n", yylval.num);
	}
	return cINTEGER;
}

{dec}+(\.{dec}+)?([E|e][+\-]?{dec}+)? {
	/* 1.1E+1 or 1.1E-1*/
	DUMP_SOURCE

	/* 函数原型char *strncpy(char *dest, char *src, int size_t n);
	 复制字符串src中的内容到字符串dest中，复制多少由size_t n的值决定。
	 如果src的前n个字符不含NULL字符，则结果不会以NULL字符结束。
	 如果n < src的长度，只是将src的前n个字符复制到dest的前n个字符，不自动添加'\0'，也就是结果dest不包括'\0'，需要再手动添加一个'\0'。
	 如果src的长度小于n个字节，则以NULL填充dest直到复制完n个字节。
	 src和dest所指内存区域不可以重叠且dest必须有足够的空间来容纳src的字符长度+'\0'。 */
	strncpy(yylval.p_char, yytext, NAME_LEN);

	if (dump_token)
	{
		printf("token: cREAL, yylval.p_char = %s.\n", yylval.p_char);
	}
	return cREAL;
}
					
'([^']|\\')' {
	/* Note that inside of a character class, all regular expression operators lose their special meaning 
	 except escape '\' and the character class operators, '-', '[', ']', and, at the beginning of the class '^'.
	 int this case, 起始和结束字符串必须是'，中间可以出现除了字符'之外的所有字符。 */

	DUMP_SOURCE

	strncpy(yylval.p_char, yytext, NAME_LEN);

	if (dump_token)
	{
		printf("token: cCHAR, yylval.p_char = %s.\n", yylval.p_char);
	}
	return cCHAR;
}
					
'([^']|\\')+' {
	DUMP_SOURCE

	int i;
	for(i = 1; i < strlen(yytext) - 1; i++)
	{
		tmp[i - 1] = yytext[i];
	}
	tmp[i - 1] = '\0';

	strncpy(yylval.p_char, tmp, NAME_LEN);

	if (dump_token)
	{
		printf("token: cSTRING, yylval.p_char = %s.\n", yylval.p_char);
	}
	return cSTRING;
}
					
"(" { 
	DUMP_SOURCE 

	if (dump_token)
	{
		printf("token: oLP.\n");
	}
	return oLP; 
}

")" { 
	DUMP_SOURCE 

	if (dump_token)
	{
		printf("token: oRP.\n");
	}
	return oRP; 
}


"[" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oLB.\n");
	}
	return oLB; 
}

"]" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oRB.\n");
	}
	return oRB; 
}

"+" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oPLUS.\n");
	}
	return oPLUS; 
}

"-" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oMINUS.\n");
	}
	return oMINUS; 
}

"*" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oMUL.\n");
	}
	return oMUL; 
}

"/" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oDIV.\n");
	}
	return oDIV; 
}

"%" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oMOD.\n");
	}
	return oMOD; 
}

":=" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oASSIGN.\n");
	}
	return oASSIGN; 
}

"=" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oEQUAL.\n");
	}
	return oEQUAL; 
}

"<" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oLT.\n");
	}
	return oLT; 
}

">" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oGT.\n");
	}
	return oGT; 
}

"<=" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oLE.\n");
	}
	return oLE; 
}

">=" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oGE.\n");
	}
	return oGE; 
}

"!=" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oUNEQU.\n");
	}
	return oUNEQU; 
}

"," { 
	DUMP_SOURCE 
	if (dump_token)
	{
		printf("token: oCOMMA.\n");
	}
	return oCOMMA; 
}
 

"&&" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oAND.\n");
	}
	return oAND; 
}

"||" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oOR.\n");
	}
	return oOR; 
}

"!" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oNOT.\n");
	}
	return oNOT; 
}

"&" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oBAND.\n");
	}
	return oBAND; 
}

"|" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oBOR.\n");
	}
	return oBOR; 
}

"^" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oBXOR.\n");
	}
	return oBXOR; 
}

"~" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oBCOM.\n");
	}
	return oBCOM; 
}

">>" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oRSH.\n");
	}
	return oRSH; 
}

"<<" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oLSH.\n");
	}
	return oLSH; 
}

";" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oSEMI.\n");
	}
	return oSEMI; 
}

":" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oCOLON.\n");
	}
	return oCOLON; 
}

".." { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oDOTDOT.\n");
	}
	return oDOTDOT; 
}

"." { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oDOT.\n");
	}
	return oDOT; 
}

"'" { 
	DUMP_SOURCE 
	
	if (dump_token)
	{
		printf("token: oQUOTE.\n");
	}
	return oQUOTE; 
}

{letter}{alnum}* {
	DUMP_SOURCE

	strncpy(yylval.p_char, yytext, NAME_LEN);
	return id_or_keyword(yytext);
}

<INITIAL,star_slash_comment>"\n" {
	line_no++;
	line_pos = 0;
	line_buf[line_pos] = 0;
}

"/*" {
	BEGIN(star_slash_comment);
}

<star_slash_comment>[^*]* {
	/* eat anything that's not a '*' */
}

<star_slash_comment>"*"+[^/]* {
	/* eat up '*' not followed by '/'s */
}

<star_slash_comment>"*/" {
	BEGIN(INITIAL);
}

"//" {
	BEGIN(slash_slash_comment);
}

<slash_slash_comment>[^\n]* {
	/* eat anything that's not a '//' */
}

<slash_slash_comment>"\n" {
	line_no++;
	line_pos = 0;
	line_buf[line_pos] = 0;
	BEGIN(INITIAL);
}

. {
	/* 匹配除了换行符之外的所有字符 */
	DUMP_SOURCE
}
%%

/*
	type 用于自定义类型
	var 用于声明变量
	const 用于申明常量

	function 用于申明函数
	procedure 用于申明过程

	div 取整
	mod 取余

	repeat util 用于循环语句
	for to/downto do 用于循环语句
	while do 用于循环语句
	case of 条件跳转
	if then else if then else 条件跳转
	label goto 跳转
	begin 用于程序块或者流程控制语句，一般与end联合使用（for，function，while）
	end 主程序的end后面加'.'，函数，过程，和其他的加'；'（record定义、case of语句末尾），如果end后面有else，就什么都不加
*/


/* 匹配字符，对应的Token，Token类型*/
KEYENTRY Keytable[] = {
{"abs",		SYS_FUNCT,	fABS},
{"and",		kAND,		KEYWORD},
{"array",	kARRAY, 	KEYWORD},
{"begin",	kBEGIN, 	KEYWORD},
{"boolean", SYS_TYPE,	tBOOLEAN},
{"case",	kCASE, 		KEYWORD},
{"char",	SYS_TYPE,	tCHAR},
{"const",	kCONST,		KEYWORD},
{"cvb", TYPE_CONVERT, cvBOOLEAN},
{"cvc",	TYPE_CONVERT, cvCHAR},
{"cvf",	TYPE_CONVERT,	cvREAL},
{"cvi",	TYPE_CONVERT, cvINT},
{"cvuc",	TYPE_CONVERT, cvUCHAR},
{"cvui",	TYPE_CONVERT,	cvUINT},
{"div", 	kDIV,		KEYWORD},
{"do",		kDO, 		KEYWORD},
{"downto",	kDOWNTO,	KEYWORD},
{"else",	kELSE,		KEYWORD},
{"end", 	kEND, 		KEYWORD},
{"false",	SYS_CON,	cFALSE},
{"for",		kFOR,		KEYWORD},
{"function", kFUNCTION, KEYWORD},
{"if",		kIF, 		KEYWORD},
{"in", 		kIN,		KEYWORD},
{"integer", SYS_TYPE,	tINTEGER},
{"label",	kLABEL,		KEYWORD},
{"maxint", 	SYS_CON,	cMAXINT},
{"mod",		kMOD,		KEYWORD},
{"not", 	kNOT,		KEYWORD},
{"of",		kOF,		KEYWORD},
{"or",		kOR,		KEYWORD},
{"procedure", 	kPROCEDURE,	KEYWORD},
{"program", 	kPROGRAM, KEYWORD},
{"read",	SYS_READ,	pREAD},
{"readln", 	SYS_READ,	pREADLN},
{"real",	SYS_TYPE,	tREAL},
{"record", 	kRECORD,	KEYWORD},
{"repeat",	kREPEAT,	KEYWORD},
{"sqr",		SYS_FUNCT,	fSQR},
{"sqrt",	SYS_FUNCT,	fSQRT},
{"then",	kTHEN,		KEYWORD},
{"to",		kTO,		KEYWORD},
{"true",	SYS_CON,	cTRUE},
{"type",	kTYPE,		KEYWORD},
{"uchar",	SYS_TYPE,	tUCHAR},
{"uinteger",	SYS_TYPE,	tUINTEGER},
{"until",	kUNTIL,	KEYWORD},
{"var",		kVAR,		KEYWORD},
{"while",	kWHILE,		KEYWORD},
{"write",	SYS_PROC,	pWRITE},
{"writeln",	SYS_PROC,	pWRITELN},
{"----",	LAST_ENTRY,	KEYWORD}
};

struct {
	char *name;
	int key;
}key_to_name[] = {
	{"TYPE_CONVERT", TYPE_CONVERT },
	{"SYS_FUNCT",	SYS_FUNCT },
	{"kAND",		kAND },
	{"kARRAY",		kARRAY },
	{"kBEGIN",		kBEGIN },
	{"SYS_TYPE", 	SYS_TYPE },
	{"kCASE",		kCASE },
	{"kCONST",		kCONST },
	{"kDIV", 		kDIV },
	{"kDO",			kDO },
	{"kDOWNTO",		kDOWNTO },
	{"kELSE",		kELSE },
	{"kEND", 		kEND },
	{"SYS_CON",		SYS_CON },
	{"kFOR",		kFOR },
	{"kFUNCTION", 	kFUNCTION },
	{"kIF",			kIF },
	{"kIN", 		kIN },
	{"kLABEL",		kLABEL },
	{"kMOD",		kMOD },
	{"kNOT", 		kNOT },
	{"kOF",			kOF },
	{"kOR",			kOR },
	{"kPROCEDURE", 	kPROCEDURE },
	{"kPROGRAM", 	kPROGRAM },
	{"SYS_READ",		SYS_READ },
	{"kRECORD", 	kRECORD },
	{"kREPEAT",		kREPEAT },
	{"kTHEN",		kTHEN },
	{"kTO",			kTO },
	{"kTYPE",		kTYPE },
	{"kUNTIL",		kUNTIL },
	{"kVAR",		kVAR },
	{"kWHILE",		kWHILE },
	{"SYS_PROC",	SYS_PROC },
	{"LAST_ENTRY",	LAST_ENTRY }
};

static char *get_name_by_key(int key)
{
	int i;

	for (i = 0; i < sizeof(key_to_name) / sizeof(key_to_name[0]); i++)
	{
		if (key_to_name[i].key == key)
			return key_to_name[i].name;
	}
	return "bad key";
}

static int id_or_keyword(char *lex)
{
	int left = 0, right = Keytable_size;
	int mid = (left + right) / 2;
	char *p;

	if (!Keytable_size)
	{
		internal_error("Key table size not known.\n");
		exit(0);
	}
	
	/* 转化为小写（pascal语言的token是忽略大小写的） */
	for (p = lex; *p; p++)
		*p = tolower(*p);

	/* 二分法查找 */
	while (mid != left && mid != right)
	{
		if (!strcmp(Keytable[mid].name, lex))
		{
			if (dump_token)
			{
				printf("token: %s ", get_name_by_key(Keytable[mid].key));
			}

			if (Keytable[mid].key == SYS_FUNCT
				|| Keytable[mid].key == SYS_PROC)
			{
				/* 系统函数或者系统调用 */
				yylval.p_lex = &Keytable[mid];

				if (dump_token)
				{
					printf(",yylval.p_lex = &Keytable[%d]", mid);
				}
			}
			else if(Keytable[mid].key == SYS_READ)
			{
				/* read function */
				yylval.p_lex = &Keytable[mid];

				if (dump_token)
				{
					printf(",yylval.p_lex = &Keytable[%d]", mid);
				}
			}
			else if(Keytable[mid].key == TYPE_CONVERT)
			{
				/* type conversion */
				yylval.p_lex = &Keytable[mid];
				if (dump_token)
				{
					printf(",yylval.p_lex = &Keytable[%d]", mid);
				}
			}
			else if (Keytable[mid].key == SYS_CON)
			{
				/* true、false或者maxint */
				yylval.num = Keytable[mid].attr;

				if (dump_token)
				{
					printf(",yylval.p_num = Keytable[%d].atrr = %d", mid, Keytable[mid].attr);
				}
			}
			else if (Keytable[mid].key == SYS_TYPE)
			{
				/* real、integer、char、boolean */
				strncpy(yylval.p_char, yytext, NAME_LEN);

				if (dump_token)
				{
					printf(",yylval.p_char = %s", yylval.p_char);
				}
			}

			if (dump_token)
				printf(".\n");

			return Keytable[mid].key;
		}
		else if (strcmp(Keytable[mid].name, lex) < 0)
			left = mid;
		else if (strcmp(Keytable[mid].name, lex) > 0)
			right = mid;

		mid = (left + right) / 2;
	}

	if (dump_token)
	{
		printf("token: yNAME, yylval.p_char = %s.\n", yylval.p_char);
	}

	/* 变量名称 */
	return yNAME;
}

int get_keytable_size()
{
	int i;

	Keytable_size = 0;

	for (i = 0; ; Keytable_size++, i++)
	{
		if (Keytable[i].key == LAST_ENTRY)
			break;
	}

	return 0;
}

int yywrap() 
{
	return 1;
}

