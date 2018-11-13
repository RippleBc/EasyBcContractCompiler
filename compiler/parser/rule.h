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
    kPROCEDURE = 279,
    kPROGRAM = 280,
    kRECORD = 281,
    kREPEAT = 282,
    kTHEN = 283,
    kTO = 284,
    kTYPE = 285,
    kUNTIL = 286,
    kVAR = 287,
    kWHILE = 288,
    SYS_CON = 289,
    cFALSE = 290,
    cTRUE = 291,
    cMAXINT = 292,
    cSTRING = 293,
    cINTEGER = 294,
    cREAL = 295,
    cCHAR = 296,
    cBOOLEAN = 297,
    SYS_TYPE = 298,
    tINTEGER = 299,
    tCHAR = 300,
    tREAL = 301,
    tBOOLEAN = 302,
    tUCHAR = 303,
    tUINTEGER = 304,
    SYS_FUNCT = 305,
    fABS = 306,
    fSQR = 307,
    fSQRT = 308,
    SYS_PROC = 309,
    SYS_READ = 310,
    TYPE_CONVERT = 311,
    cvBOOLEAN = 312,
    cvINT = 313,
    cvREAL = 314,
    cvUCHAR = 315,
    cvCHAR = 316,
    cvUINT = 317,
    pWRITE = 318,
    pWRITELN = 319,
    pREAD = 320,
    pREADLN = 321,
    oPLUS = 322,
    oMINUS = 323,
    oMUL = 324,
    oDIV = 325,
    oEQUAL = 326,
    oASSIGN = 327,
    oUNEQU = 328,
    oAND = 329,
    oOR = 330,
    oNOT = 331,
    oBAND = 332,
    oBOR = 333,
    oBXOR = 334,
    oBCOM = 335,
    oRSH = 336,
    oLSH = 337,
    oMOD = 338,
    oLT = 339,
    oLE = 340,
    oGT = 341,
    oGE = 342,
    oCOMMA = 343,
    oSEMI = 344,
    oCOLON = 345,
    oQUOTE = 346,
    oDOT = 347,
    oDOTDOT = 348,
    oLP = 349,
    oRP = 350,
    oLB = 351,
    oRB = 352,
    yNAME = 353
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 98 "parser/spl.y" /* yacc.c:1909  */

	char 		p_char[NAME_LEN];
	int 		num;
	int 		ascii;
	Symbol 		p_symbol; /* 符号 */
	Type		p_type; /* 类型 */
	KEYENTRY	*p_lex; /* 关键字 */
	Tree 		p_tree;

#line 163 "parser/rule.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_RULE_H_INCLUDED  */
