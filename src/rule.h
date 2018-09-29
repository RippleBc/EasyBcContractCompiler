/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
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
/* Tokens.  */
#define kAND 258
#define kARRAY 259
#define kBEGIN 260
#define kCASE 261
#define kCONST 262
#define kDIV 263
#define kDO 264
#define kDOWNTO 265
#define kELSE 266
#define kEND 267
#define kFILE 268
#define kFOR 269
#define kFUNCTION 270
#define kGOTO 271
#define kIF 272
#define kIN 273
#define kLABEL 274
#define kMOD 275
#define kNIL 276
#define kNOT 277
#define kOF 278
#define kOR 279
#define kPACKED 280
#define kPROCEDURE 281
#define kPROGRAM 282
#define kRECORD 283
#define kREPEAT 284
#define kSET 285
#define kTHEN 286
#define kTO 287
#define kTYPE 288
#define kUNTIL 289
#define kVAR 290
#define kWHILE 291
#define kWITH 292
#define SYS_CON 293
#define cFALSE 294
#define cTRUE 295
#define cMAXINT 296
#define cSTRING 297
#define cINTEGER 298
#define cREAL 299
#define cCHAR 300
#define cBOOLEAN 301
#define SYS_TYPE 302
#define tINTEGER 303
#define tCHAR 304
#define tREAL 305
#define tBOOLEAN 306
#define tTEXT 307
#define SYS_FUNCT 308
#define fABS 309
#define fCHR 310
#define fODD 311
#define fORD 312
#define fPRED 313
#define fSQR 314
#define fSQRT 315
#define fSUCC 316
#define SYS_PROC 317
#define pREAD 318
#define pREADLN 319
#define pWRITE 320
#define pWRITELN 321
#define oPLUS 322
#define oMINUS 323
#define oMUL 324
#define oDIV 325
#define oEQUAL 326
#define oASSIGN 327
#define oUNEQU 328
#define oLT 329
#define oLE 330
#define oGT 331
#define oGE 332
#define oCOMMA 333
#define oSEMI 334
#define oCOLON 335
#define oQUOTE 336
#define oDOT 337
#define oDOTDOT 338
#define oARROW 339
#define oLP 340
#define oRP 341
#define oLB 342
#define oRB 343
#define oLC 344
#define oRC 345
#define yNAME 346




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 106 "spl.y"
{
	char 		p_char[NAME_LEN];
	int 		num;
	int 		ascii;
	Symbol 		p_symbol;
	Type		p_type;
	KEYENTRY	*p_lex;
	Tree 		p_tree;
}
/* Line 1489 of yacc.c.  */
#line 241 "rule.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

