/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_RULE_H_INCLUDED
# define YY_YY_PARSER_RULE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    kAND = 258,
    kARRAY = 259,
    kBEGIN = 260,
    kCASE = 261,
    kCONST = 262,
    kDIV = 263,
    kDO = 264,
    kDOWNTO = 265,
    kELSE = 266,
    kEND = 267,
    kFILE = 268,
    kFOR = 269,
    kFUNCTION = 270,
    kIF = 271,
    kIN = 272,
    kLABEL = 273,
    kMOD = 274,
    kNIL = 275,
    kNOT = 276,
    kOF = 277,
    kOR = 278,
    kPACKED = 279,
    kPROCEDURE = 280,
    kPROGRAM = 281,
    kRECORD = 282,
    kREPEAT = 283,
    kSET = 284,
    kTHEN = 285,
    kTO = 286,
    kTYPE = 287,
    kUNTIL = 288,
    kVAR = 289,
    kWHILE = 290,
    kWITH = 291,
    SYS_CON = 292,
    cFALSE = 293,
    cTRUE = 294,
    cMAXINT = 295,
    cSTRING = 296,
    cINTEGER = 297,
    cREAL = 298,
    cCHAR = 299,
    cBOOLEAN = 300,
    SYS_TYPE = 301,
    tINTEGER = 302,
    tCHAR = 303,
    tREAL = 304,
    tBOOLEAN = 305,
    tTEXT = 306,
    SYS_FUNCT = 307,
    fABS = 308,
    fCHR = 309,
    fODD = 310,
    fORD = 311,
    fPRED = 312,
    fSQR = 313,
    fSQRT = 314,
    fSUCC = 315,
    SYS_PROC = 316,
    pREAD = 317,
    pREADLN = 318,
    pWRITE = 319,
    pWRITELN = 320,
    oPLUS = 321,
    oMINUS = 322,
    oMUL = 323,
    oDIV = 324,
    oEQUAL = 325,
    oASSIGN = 326,
    oUNEQU = 327,
    oLT = 328,
    oLE = 329,
    oGT = 330,
    oGE = 331,
    oCOMMA = 332,
    oSEMI = 333,
    oCOLON = 334,
    oQUOTE = 335,
    oDOT = 336,
    oDOTDOT = 337,
    oARROW = 338,
    oLP = 339,
    oRP = 340,
    oLB = 341,
    oRB = 342,
    yNAME = 343
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 92 "parser/spl.y" /* yacc.c:1909  */

	char 		p_char[NAME_LEN];
	int 		num;
	int 		ascii;
	Symbol 		p_symbol; /* 符号 */
	Type		p_type; /* 类型 */
	KEYENTRY	*p_lex; /* 关键字 */
	Tree 		p_tree;

#line 153 "parser/rule.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_RULE_H_INCLUDED  */
