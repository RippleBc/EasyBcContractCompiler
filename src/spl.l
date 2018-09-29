%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common.h"

#include _YTAB_H_

int Keytable_size = 0;
extern int line_no;					/* line no. */
extern int line_pos;				/* position of line. */
extern char line_buf[];				/* buffer of current line. */

extern YYSTYPE	yylval;
extern int dump_source;
extern int dump_token;

static int id_or_keyword(char *lex);

#define DUMP_SOURCE		if(dump_source) ECHO; \
						if (line_pos + strlen(yytext) < MAX_LINE_LENGTH) \
							memmove(line_buf + line_pos, yytext, strlen(yytext) + 1); \
						line_pos += strlen(yytext);

%}

letter	[_a-zA-Z]
alnum	[_a-zA-Z0-9]
dec		[0-9]
hex		[0-9a-fA-F]
oct		[0-7]

%%
"{"		{
			int c;
			
			/* DUMP_SOURCE */

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

[1-9]+{dec}*		{
						DUMP_SOURCE
						yylval.num = stoi(yytext, 10);
						if (dump_token)
						{
							printf("token: cINTEGER, yylval.num = %d.\n", yylval.num);
						}
						return cINTEGER;
					}
					
0{oct}*				{
						DUMP_SOURCE
						yylval.num = stoi(yytext, 8);
						if (dump_token)
						{
							printf("token: cINTEGER, yylval.num = %d.\n", yylval.num);
						}
						return cINTEGER;
					}
					
0(x|X){hex}+		{
						DUMP_SOURCE
						yylval.num = stoi(yytext, 16);
						if (dump_token)
						{
							printf("token: cINTEGER, yylval.num = %d.\n", yylval.num);
						}
						return cINTEGER;
					}

{dec}+(\.{dec}+)?([E|e][+\-]?{dec}+)?	{
						DUMP_SOURCE
						strncpy(yylval.p_char, yytext, NAME_LEN);
						if (dump_token)
						{
							printf("token: cREAL, yylval.p_char = %s.\n", yylval.p_char);
						}
						return cREAL;
					}
					
'([^']|\")'			{
						DUMP_SOURCE
						strncpy(yylval.p_char, yytext, NAME_LEN);
						if (dump_token)
						{
							printf("token: cCHAR, yylval.p_char = %s.\n", yylval.p_char);
						}
						return cCHAR;
					}
					
\'(\\.|[^\'])(\\.|[^\'])+\'		{
						DUMP_SOURCE
						strncpy(yylval.p_char, yytext, NAME_LEN);
						if (dump_token)
						{
							printf("token: cSTRING, yylval.p_char = %s.\n", yylval.p_char);
						}
						return cSTRING;
					}
					
"("					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oLP.\n");
						}
						return oLP; }
")"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oRP.\n");
						}
						return oRP; }
"["					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oLB.\n");
						}
						return oLB; }
"]"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oRB.\n");
						}
						return oRB; }
"+"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oPLUS.\n");
						}
						return oPLUS; }
"-"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oMINUS.\n");
						}
						return oMINUS; }
"*"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oMUL.\n");
						}
						return oMUL; }
"/"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oDIV.\n");
						}
						return oDIV; }
":="				{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oASSIGN.\n");
						}
						return oASSIGN; }
"="					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oEQUAL.\n");
						}
						return oEQUAL; }
"<"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oLT.\n");
						}
						return oLT; }
">"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oGT.\n");
						}
						return oGT; }
"<="				{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oLE.\n");
						}
						return oLE; }
">="				{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oGE.\n");
						}
						return oGE; }
"<>"				{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oUNEQU.\n");
						}
						return oUNEQU; }
","					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oCOMMA.\n");
						}
						return oCOMMA; }
";"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oSEMI.\n");
						}
						return oSEMI; }
":"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oCOLON.\n");
						}
						return oCOLON; }
"'"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oQUOTE.\n");
						}
						return oQUOTE; }
".."				{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oDOTDOT.\n");
						}
						return oDOTDOT; }
"."					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oDOT.\n");
						}
						return oDOT; }
"^"					{ DUMP_SOURCE 
						if (dump_token)
						{
							printf("token: oARROW.\n");
						}
						return oARROW; }
{letter}{alnum}*	{
						DUMP_SOURCE
						strncpy(yylval.p_char, yytext, NAME_LEN);
						return id_or_keyword(yytext);
					}
"\n"				{
						line_no++;
						line_pos = 0;
						line_buf[line_pos] = 0;
					}
.					{
						DUMP_SOURCE
					}
%%

KEYENTRY Keytable[] = {
{"abs",		SYS_FUNCT,	fABS, TYPE_INTEGER, TYPE_INTEGER },
{"and",		kAND,		KEYWORD, 0, 0 },
{"array",	kARRAY, 	KEYWORD, 0, 0 },
{"begin",	kBEGIN, 	KEYWORD, 0, 0 },
{"boolean", SYS_TYPE,	tBOOLEAN, 0, 0 },
{"case",	kCASE, 		KEYWORD, 0, 0 },
{"char",	SYS_TYPE,	tCHAR,	0, 0 },
{"chr",		SYS_FUNCT, 	fCHR, TYPE_CHAR, TYPE_CHAR },
{"const",	kCONST,		KEYWORD, 0, 0 },
{"div", 	kDIV,		KEYWORD, 0, 0 },
{"do",		kDO, 		KEYWORD, 0, 0 },
{"downto",	kDOWNTO,	KEYWORD, 0, 0 },
{"else",	kELSE,		KEYWORD, 0, 0 },
{"end", 	kEND, 		KEYWORD, 0, 0 },
{"false",	SYS_CON,	cFALSE, 0, 0 },
{"for",		kFOR,		KEYWORD, 0, 0 },
{"function", kFUNCTION, KEYWORD, 0, 0 },
{"goto",	kGOTO,	KEYWORD, 0, 0 },
{"if",		kIF, 		KEYWORD, 0, 0 },
{"in", 		kIN,		KEYWORD, 0, 0 },
{"integer", SYS_TYPE,	tINTEGER,	0, 0 },
{"label",	kLABEL,		KEYWORD, 0, 0 },
{"maxint", 	SYS_CON,	cMAXINT, 0, 0 },
{"mod",		kMOD,		KEYWORD, 0, 0 },
{"not", 	kNOT,		KEYWORD, 0, 0 },
{"odd",		SYS_FUNCT,	fODD, TYPE_INTEGER, TYPE_BOOLEAN },
{"of",		kOF,		KEYWORD, 0, 0 },
{"or",		kOR,		KEYWORD, 0, 0 },
{"ord",		SYS_FUNCT,	fORD, TYPE_INTEGER, TYPE_INTEGER },
{"packed",	kPACKED,	KEYWORD, 0, 0 },
{"pred",	SYS_FUNCT,	fPRED, TYPE_INTEGER, TYPE_INTEGER },
{"procedure", 	kPROCEDURE,	KEYWORD, 0, 0 },
{"program", 	kPROGRAM, KEYWORD, 0, 0 },
{"read",	pREAD,	pREAD, 0, 0 },
{"readln", 	pREAD,	pREADLN, 0, 0 },
{"real",	SYS_TYPE,	KEYWORD, 0, 0 },
{"record", 	kRECORD,	KEYWORD, 0, 0 },
{"repeat",	kREPEAT,	KEYWORD, 0, 0 },
{"set", 	kSET, 		KEYWORD, 0, 0 },
{"sqr",		SYS_FUNCT,	fSQR,	TYPE_INTEGER, TYPE_INTEGER },
{"sqrt",	SYS_FUNCT,	fSQRT,	TYPE_INTEGER, TYPE_INTEGER },
{"succ",	SYS_FUNCT,	fSUCC,	TYPE_INTEGER, TYPE_INTEGER },
{"then",	kTHEN,		KEYWORD, 0, 0 },
{"to",		kTO,		KEYWORD, 0, 0 },
{"true",	SYS_CON,	cTRUE,	0, 0 },
{"type",	kTYPE,		KEYWORD, 0, 0 },
{"until",	kUNTIL,		KEYWORD, 0, 0 },
{"var",		kVAR,		KEYWORD, 0, 0 },
{"while",	kWHILE,		KEYWORD, 0, 0 },
{"with",	kWITH, 		KEYWORD, 0, 0 },
{"write",	SYS_PROC,	pWRITE, 0, 0 },
{"writeln",	SYS_PROC,	pWRITELN, 0, 0 },
{"----",	LAST_ENTRY,	KEYWORD, 0, 0 },
};

struct {
	char *name;
	int key;
}key_to_name[] = {
	{"SYS_FUNCT",	SYS_FUNCT },
	{"kAND",		kAND },
	{"kARRAY",		kARRAY },
	{"kBEGIN",		kBEGIN },
	{"SYS_TYPE", 	SYS_TYPE },
	{"kCASE",		kCASE },
	{"SYS_TYPE",	SYS_TYPE },
	{"kCONST",		kCONST },
	{"kDIV", 		kDIV },
	{"kDO",			kDO },
	{"kDOWNTO",		kDOWNTO },
	{"kELSE",		kELSE },
	{"kEND", 		kEND },
	{"SYS_CON",		SYS_CON },
	{"kFOR",		kFOR },
	{"kFUNCTION", 	kFUNCTION },
	{"kGOTO",		kGOTO },
	{"kIF",			kIF },
	{"kIN", 		kIN },
	{"kLABEL",		kLABEL },
	{"kMOD",		kMOD },
	{"kNOT", 		kNOT },
	{"kOF",			kOF },
	{"kOR",			kOR },
	{"kPACKED",		kPACKED },
	{"kPROCEDURE", 	kPROCEDURE },
	{"kPROGRAM", 	kPROGRAM },
	{"pREAD",		pREAD },
	{"kRECORD", 	kRECORD },
	{"kREPEAT",		kREPEAT },
	{"kSET", 		kSET },
	{"kTHEN",		kTHEN },
	{"kTO",			kTO },
	{"kTYPE",		kTYPE },
	{"kUNTIL",		kUNTIL },
	{"kVAR",		kVAR },
	{"kWHILE",		kWHILE },
	{"kWITH",		kWITH },
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
	
	for (p = lex; *p; p++)
		*p = tolower(*p);

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
				yylval.p_lex = &Keytable[mid];

				if (dump_token)
				{
					printf(",yylval.p_lex = &Keytable[%d]", mid);
				}
			}
			else if (Keytable[mid].key == SYS_CON)
			{
				yylval.num = Keytable[mid].attr;
				if (dump_token)
				{
					printf(",yylval.p_num = Keytable[%d].atrr = %d", 
						mid, Keytable[mid].attr);
				}
			}
			else if (Keytable[mid].key == SYS_TYPE)
			{
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

