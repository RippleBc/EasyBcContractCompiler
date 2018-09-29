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

#ifndef YY_YY_RULE_H_INCLUDED
# define YY_YY_RULE_H_INCLUDED
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
    kGOTO = 271,
    kIF = 272,
    kIN = 273,
    kLABEL = 274,
    kMOD = 275,
    kNIL = 276,
    kNOT = 277,
    kOF = 278,
    kOR = 279,
    kPACKED = 280,
    kPROCEDURE = 281,
    kPROGRAM = 282,
    kRECORD = 283,
    kREPEAT = 284,
    kSET = 285,
    kTHEN = 286,
    kTO = 287,
    kTYPE = 288,
    kUNTIL = 289,
    kVAR = 290,
    kWHILE = 291,
    kWITH = 292,
    SYS_CON = 293,
    cFALSE = 294,
    cTRUE = 295,
    cMAXINT = 296,
    cSTRING = 297,
    cINTEGER = 298,
    cREAL = 299,
    cCHAR = 300,
    cBOOLEAN = 301,
    SYS_TYPE = 302,
    tINTEGER = 303,
    tCHAR = 304,
    tREAL = 305,
    tBOOLEAN = 306,
    tTEXT = 307,
    SYS_FUNCT = 308,
    fABS = 309,
    fCHR = 310,
    fODD = 311,
    fORD = 312,
    fPRED = 313,
    fSQR = 314,
    fSQRT = 315,
    fSUCC = 316,
    SYS_PROC = 317,
    pREAD = 318,
    pREADLN = 319,
    pWRITE = 320,
    pWRITELN = 321,
    oPLUS = 322,
    oMINUS = 323,
    oMUL = 324,
    oDIV = 325,
    oEQUAL = 326,
    oASSIGN = 327,
    oUNEQU = 328,
    oLT = 329,
    oLE = 330,
    oGT = 331,
    oGE = 332,
    oCOMMA = 333,
    oSEMI = 334,
    oCOLON = 335,
    oQUOTE = 336,
    oDOT = 337,
    oDOTDOT = 338,
    oARROW = 339,
    oLP = 340,
    oRP = 341,
    oLB = 342,
    oRB = 343,
    oLC = 344,
    oRC = 345,
    yNAME = 346
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 106 "spl.y" /* yacc.c:1909  */

	char 		p_char[NAME_LEN];
	int 		num;
	int 		ascii;
	Symbol 		p_symbol;
	Type		p_type;
	KEYENTRY	*p_lex;
	Tree 		p_tree;

#line 156 "rule.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_RULE_H_INCLUDED  */
