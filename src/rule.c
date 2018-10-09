/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "spl.y" /* yacc.c:339  */


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


#line 172 "rule.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "rule.h".  */
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
#line 107 "spl.y" /* yacc.c:355  */

	char 		p_char[NAME_LEN];
	int 		num;
	int 		ascii;
	Symbol 		p_symbol; /* 符号 */
	Type		p_type; /* 类型 */
	KEYENTRY	*p_lex; /* 关键字 */
	Tree 		p_tree;

#line 314 "rule.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_RULE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 331 "rule.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   366

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  92
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  100
/* YYNRULES -- Number of rules.  */
#define YYNRULES  178
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  318

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   346

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   228,   228,   261,   269,   283,   288,   287,   328,   335,
     340,   341,   345,   349,   358,   363,   364,   368,   375,   385,
     393,   401,   409,   417,   452,   453,   457,   458,   462,   481,
     482,   483,   487,   496,   505,   511,   518,   536,   543,   553,
     560,   582,   610,   640,   678,   679,   683,   684,   688,   712,
     713,   714,   715,   716,   720,   747,   746,   790,   814,   813,
     847,   852,   856,   857,   861,   886,   911,   915,   922,   926,
     927,   928,   932,   933,   937,   938,   939,   940,   941,   942,
     943,   944,   945,   946,   950,  1023,  1038,  1022,  1066,  1065,
    1106,  1122,  1121,  1140,  1150,  1149,  1173,  1195,  1194,  1215,
    1221,  1234,  1214,  1275,  1279,  1274,  1286,  1287,  1292,  1291,
    1321,  1334,  1320,  1375,  1410,  1374,  1474,  1478,  1486,  1504,
    1511,  1485,  1551,  1552,  1557,  1580,  1556,  1594,  1628,  1593,
    1643,  1647,  1665,  1692,  1691,  1708,  1707,  1724,  1723,  1741,
    1740,  1757,  1756,  1773,  1772,  1788,  1799,  1798,  1814,  1813,
    1829,  1828,  1843,  1852,  1851,  1867,  1866,  1882,  1881,  1898,
    1897,  1914,  1913,  1928,  1934,  1977,  1976,  1995,  2006,  2005,
    2022,  2050,  2059,  2068,  2078,  2077,  2108,  2135,  2153
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "kAND", "kARRAY", "kBEGIN", "kCASE",
  "kCONST", "kDIV", "kDO", "kDOWNTO", "kELSE", "kEND", "kFILE", "kFOR",
  "kFUNCTION", "kGOTO", "kIF", "kIN", "kLABEL", "kMOD", "kNIL", "kNOT",
  "kOF", "kOR", "kPACKED", "kPROCEDURE", "kPROGRAM", "kRECORD", "kREPEAT",
  "kSET", "kTHEN", "kTO", "kTYPE", "kUNTIL", "kVAR", "kWHILE", "kWITH",
  "SYS_CON", "cFALSE", "cTRUE", "cMAXINT", "cSTRING", "cINTEGER", "cREAL",
  "cCHAR", "cBOOLEAN", "SYS_TYPE", "tINTEGER", "tCHAR", "tREAL",
  "tBOOLEAN", "tTEXT", "SYS_FUNCT", "fABS", "fCHR", "fODD", "fORD",
  "fPRED", "fSQR", "fSQRT", "fSUCC", "SYS_PROC", "pREAD", "pREADLN",
  "pWRITE", "pWRITELN", "oPLUS", "oMINUS", "oMUL", "oDIV", "oEQUAL",
  "oASSIGN", "oUNEQU", "oLT", "oLE", "oGT", "oGE", "oCOMMA", "oSEMI",
  "oCOLON", "oQUOTE", "oDOT", "oDOTDOT", "oARROW", "oLP", "oRP", "oLB",
  "oRB", "oLC", "oRC", "yNAME", "$accept", "program", "first_act_at_prog",
  "program_head", "sub_program", "$@1", "name_list", "sub_routine",
  "routine_head", "label_part", "const_part", "const_expr_list",
  "const_value", "type_part", "type_decl_list", "type_definition",
  "type_decl", "array_type_decl", "record_type_decl", "field_decl_list",
  "field_decl", "simple_type_decl", "var_part", "var_decl_list",
  "var_decl", "routine_part", "function_decl", "function_head", "$@2",
  "procedure_decl", "procedure_head", "$@3", "parameters",
  "para_decl_list", "para_type_list", "val_para_list", "var_para_list",
  "routine_body", "stmt_list", "stmt", "non_label_stmt", "assign_stmt",
  "$@4", "$@5", "$@6", "proc_stmt", "$@7", "$@8", "compound_stmt", "$@9",
  "if_stmt", "$@10", "$@11", "$@12", "$@13", "$@14", "else_clause",
  "repeat_stmt", "$@15", "while_stmt", "$@16", "$@17", "for_stmt", "$@18",
  "$@19", "direction", "case_stmt", "$@20", "$@21", "$@22",
  "case_expr_list", "case_expr", "$@23", "$@24", "$@25", "$@26",
  "goto_stmt", "expression_list", "expression", "$@27", "$@28", "$@29",
  "$@30", "$@31", "$@32", "expr", "$@33", "$@34", "$@35", "term", "$@36",
  "$@37", "$@38", "$@39", "$@40", "factor", "$@41", "$@42", "$@43",
  "args_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346
};
# endif

#define YYPACT_NINF -178

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-178)))

#define YYTABLE_NINF -169

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -178,    65,    19,  -178,    -9,   -13,  -178,  -178,    15,    29,
    -178,    93,  -178,  -178,   111,    26,    86,  -178,  -178,  -178,
      50,    33,    45,   102,  -178,   284,    68,    69,    45,  -178,
      52,     6,    11,  -178,  -178,  -178,  -178,  -178,    62,   284,
     121,  -178,     7,   -56,    52,  -178,  -178,  -178,     6,  -178,
      66,  -178,    71,    72,  -178,  -178,    61,   110,    70,  -178,
    -178,    76,    75,    77,   126,    78,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,    88,    83,    52,
    -178,   284,    52,   100,   101,   107,  -178,  -178,  -178,   -26,
     104,   121,  -178,   108,   119,  -178,  -178,  -178,  -178,  -178,
     204,   129,  -178,  -178,   204,  -178,   204,   188,   106,   204,
     204,   124,  -178,   140,  -178,  -178,   222,    21,    -3,  -178,
     144,   -28,   139,   284,  -178,  -178,  -178,  -178,   152,   147,
     147,   156,   111,   158,   204,   154,   204,   204,   -18,  -178,
     200,    -6,   189,  -178,   204,   210,   207,    43,    98,  -178,
     204,   157,   259,  -178,   204,   204,   164,   121,  -178,  -178,
     249,  -178,  -178,  -178,  -178,   -16,   174,  -178,  -178,  -178,
    -178,  -178,   170,  -178,   245,   165,  -178,   176,  -178,   186,
     192,   195,   203,   213,   212,   219,   220,   272,   229,   233,
     296,   285,   309,   259,  -178,  -178,   204,  -178,    -2,   259,
    -178,   243,   226,   259,    17,   301,   246,   284,  -178,    52,
     265,   -53,  -178,   264,   266,   222,   204,  -178,  -178,   204,
     204,    -8,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,    31,   171,   171,   259,
     171,   204,  -178,   204,  -178,   204,  -178,   121,  -178,  -178,
     265,   -16,  -178,   222,   222,  -178,    18,   235,    32,  -178,
    -178,    -8,  -178,    -6,    -6,    -6,    -6,    -6,    -6,   189,
     189,   189,  -178,  -178,  -178,  -178,  -178,  -178,  -178,   204,
     334,  -178,  -178,   259,   259,   275,   259,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,   268,   269,   338,  -178,   145,   171,
    -178,   334,   204,   171,   171,  -178,  -178,  -178,  -178,   259,
    -178,  -178,   171,   273,   274,  -178,  -178,  -178
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,    14,     5,     0,     0,
       6,    16,     4,     2,     0,     0,    25,    97,     7,    68,
       0,    15,     0,    45,    71,     0,     0,     0,    24,    27,
       0,    53,     0,    23,    22,    19,    20,    21,     0,     0,
       0,    26,     0,     0,    44,    47,    55,    58,    13,    51,
       0,    52,     0,     0,   118,    98,     0,     0,     0,   108,
     110,     0,    93,     0,    90,     0,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    18,     0,     0,     0,
      37,     0,     0,    38,     0,     0,    30,    31,    29,     0,
       0,     0,    46,     0,     0,    49,    50,    14,    14,    70,
       0,     0,   130,   103,     0,    71,     0,    83,     0,     0,
       0,     0,    85,     0,    69,    17,     0,     0,     0,    35,
       0,     0,     0,     0,    28,    11,    10,     8,     0,    61,
      61,     0,     0,     0,     0,   167,     0,     0,   164,   170,
     133,   145,   152,   163,     0,     0,   133,     0,   133,    72,
       0,     0,    84,    88,     0,     0,     0,     0,    33,    34,
       0,    39,    43,    40,    48,     0,     0,    59,    54,    12,
      57,   172,     0,   173,   133,     0,   174,     0,   119,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,   104,   100,     0,   111,     0,   132,
      96,     0,   133,   178,     0,     0,     0,     0,    41,     0,
      66,     0,    63,     0,     0,     0,     0,   171,   176,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,    83,   109,
      83,     0,    95,     0,    86,     0,    92,     0,    36,    42,
      67,     0,    60,     0,     0,    56,     0,   133,     0,   127,
     124,   120,   123,   134,   136,   138,   140,   142,   144,   147,
     149,   151,   154,   156,   158,   160,   162,   117,   116,     0,
     107,   101,   112,   131,    89,     0,   177,    32,    62,    64,
      65,   169,   175,   166,     0,     0,     0,   122,   133,    83,
     105,   107,     0,    83,    83,   121,   114,   106,   102,    87,
     128,   125,    83,     0,     0,   115,   129,   126
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -178,  -178,  -178,  -178,  -178,  -178,   -76,   253,   348,  -178,
    -178,  -178,   -25,  -178,  -178,   327,   -89,  -178,  -178,  -178,
     238,  -106,  -178,  -178,   313,  -178,   310,  -178,  -178,   311,
    -178,  -178,   230,  -178,   112,  -178,  -178,   232,   256,   -59,
     255,  -178,  -178,  -178,  -178,  -178,  -178,  -178,    -1,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,    64,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,   105,  -178,  -178,  -178,  -178,  -178,  -178,   -99,  -178,
    -178,  -178,  -178,  -178,  -178,   115,  -178,  -178,  -178,  -148,
    -178,  -178,  -178,  -178,  -178,  -105,  -178,  -178,  -178,  -177
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,     9,    14,    43,   131,   132,    11,
      16,    21,   139,    23,    28,    29,    85,    86,    87,   118,
     119,    88,    31,    44,    45,    48,    49,    50,    93,    51,
      52,    94,   166,   211,   212,   213,   214,    18,    32,    65,
      66,    67,   154,   285,   201,    68,   113,   108,    69,    24,
      70,   104,   238,   301,   145,   237,   300,    71,   105,    72,
     106,   240,    73,   236,   312,   279,    74,   100,   221,   296,
     261,   262,   295,   314,   294,   313,    75,   198,   203,   179,
     180,   181,   182,   183,   184,   141,   185,   186,   187,   142,
     188,   189,   190,   191,   192,   143,   177,   172,   219,   204
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      38,   140,   128,   117,   151,   146,   121,   148,    89,   158,
     156,   152,    53,    19,    77,    84,    17,    54,  -150,   209,
       4,    46,    90,    55,    91,    56,   251,    57,    58,   171,
      33,   173,    47,   252,    34,    35,    36,    37,   174,   256,
      59,   277,   117,   258,    53,   193,     5,    60,    17,    54,
      90,   199,   125,   126,    61,   202,   120,    56,   161,    57,
      58,  -146,  -148,   278,   175,     3,    84,  -165,   206,   176,
       7,   103,    59,    62,    63,    42,   241,   196,     8,    60,
     269,   270,   271,   259,   242,    -9,    61,    -9,    42,   210,
     -83,    84,   -99,    -9,    12,   245,   245,   239,   163,    90,
      15,   157,    64,   246,   291,    62,    63,   197,   -99,   255,
     245,    13,   -99,   -99,   -99,   -99,    17,    20,   293,    22,
     257,    25,   -83,   -99,    26,    78,   272,   273,   274,   275,
     276,    19,    84,   250,    64,   208,    27,    30,   -99,    39,
      40,    76,   283,    42,   284,    97,   286,   289,   290,    79,
      98,    99,   101,   102,   306,   -99,   107,   114,   287,    33,
     -94,   -99,   109,    34,    35,    36,    37,   115,    80,  -141,
     116,  -143,  -139,  -137,  -135,   210,    17,    54,   280,   281,
     298,   282,   249,   122,   123,    56,   124,    57,    58,    81,
      84,   150,  -161,    17,    54,   127,   260,  -157,   110,   129,
      59,   144,    56,   309,    57,    58,    82,    60,   111,  -159,
     130,   -91,    83,   112,    61,   153,  -141,    59,  -143,  -139,
    -137,  -135,    84,   178,    60,   155,   134,   160,    84,    84,
     162,   164,   165,    62,    63,   168,   260,   170,   195,  -168,
     307,   194,    33,   200,   310,   311,    34,    35,    36,    37,
      62,    63,   205,   315,   215,   216,   218,   135,  -153,  -155,
      33,   220,    64,   222,    34,    35,    36,    37,   223,    80,
     224,  -141,   136,  -143,  -139,  -137,  -135,   225,  -141,    64,
    -143,  -139,  -137,  -135,   226,   227,   228,    33,   229,   137,
      81,    34,    35,    36,    37,   138,   230,  -141,   231,  -143,
    -139,  -137,  -135,   232,   233,   234,  -141,    82,  -143,  -139,
    -137,  -135,   235,    83,   244,   243,  -141,   207,  -143,  -139,
    -137,  -135,    33,   292,   247,   248,    34,    35,    36,    37,
    -141,   217,  -143,  -139,  -137,  -135,  -133,   263,   264,   265,
     266,   267,   268,    90,   253,   299,   254,   302,   303,   304,
     305,   133,   316,   317,    10,    41,   159,    92,    95,    96,
     167,   147,   149,   288,   169,   308,   297
};

static const yytype_uint16 yycheck[] =
{
      25,   100,    91,    79,   109,   104,    82,   106,     1,    12,
     116,   110,     1,    14,    39,    40,     5,     6,    24,    35,
       1,    15,    78,    12,    80,    14,    79,    16,    17,   134,
      38,   136,    26,    86,    42,    43,    44,    45,   137,   216,
      29,    10,   118,   220,     1,   144,    27,    36,     5,     6,
      78,   150,    78,    79,    43,   154,    81,    14,    86,    16,
      17,    67,    68,    32,    82,     0,    91,    85,   157,    87,
      79,     1,    29,    62,    63,    91,    78,    34,    91,    36,
     228,   229,   230,    91,    86,    78,    43,    80,    91,   165,
      79,   116,    22,    86,    79,    78,    78,   196,   123,    78,
       7,    80,    91,    86,    86,    62,    63,     9,    38,   215,
      78,    82,    42,    43,    44,    45,     5,    91,    86,    33,
     219,    71,    79,    53,    91,     4,   231,   232,   233,   234,
     235,   132,   157,   209,    91,   160,    91,    35,    68,    71,
      71,    79,   241,    91,   243,    79,   245,   253,   254,    28,
      79,    79,    91,    43,     9,    85,    80,    79,   247,    38,
      85,    91,    85,    42,    43,    44,    45,    79,    47,    71,
      87,    73,    74,    75,    76,   251,     5,     6,   237,   238,
     279,   240,   207,    83,    83,    14,    79,    16,    17,    68,
     215,    85,     3,     5,     6,    91,   221,     8,    72,    91,
      29,    72,    14,   302,    16,    17,    85,    36,    82,    20,
      91,    85,    91,    87,    43,    91,    71,    29,    73,    74,
      75,    76,   247,    23,    36,    85,    22,    83,   253,   254,
      91,    79,    85,    62,    63,    79,   261,    79,    31,    85,
     299,    31,    38,    86,   303,   304,    42,    43,    44,    45,
      62,    63,    88,   312,    80,    85,    91,    53,    69,    70,
      38,    85,    91,    77,    42,    43,    44,    45,    76,    47,
      75,    71,    68,    73,    74,    75,    76,    74,    71,    91,
      73,    74,    75,    76,    71,    73,    67,    38,    68,    85,
      68,    42,    43,    44,    45,    91,    24,    71,    69,    73,
      74,    75,    76,    70,     8,    20,    71,    85,    73,    74,
      75,    76,     3,    91,    88,    72,    71,    68,    73,    74,
      75,    76,    38,    88,    23,    79,    42,    43,    44,    45,
      71,    86,    73,    74,    75,    76,    77,   222,   223,   224,
     225,   226,   227,    78,    80,    11,    80,    72,    80,    80,
      12,    98,    79,    79,     6,    28,   118,    44,    48,    48,
     130,   105,   107,   251,   132,   301,   261
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    93,    94,     0,     1,    27,    95,    79,    91,    96,
     100,   101,    79,    82,    97,     7,   102,     5,   129,   140,
      91,   103,    33,   105,   141,    71,    91,    91,   106,   107,
      35,   114,   130,    38,    42,    43,    44,    45,   104,    71,
      71,   107,    91,    98,   115,   116,    15,    26,   117,   118,
     119,   121,   122,     1,     6,    12,    14,    16,    17,    29,
      36,    43,    62,    63,    91,   131,   132,   133,   137,   140,
     142,   149,   151,   154,   158,   168,    79,   104,     4,    28,
      47,    68,    85,    91,   104,   108,   109,   110,   113,     1,
      78,    80,   116,   120,   123,   118,   121,    79,    79,    79,
     159,    91,    43,     1,   143,   150,   152,    80,   139,    85,
      72,    82,    87,   138,    79,    79,    87,    98,   111,   112,
     104,    98,    83,    83,    79,    78,    79,    91,   108,    91,
      91,    99,   100,    99,    22,    53,    68,    85,    91,   104,
     170,   177,   181,   187,    72,   146,   170,   130,   170,   132,
      85,   187,   170,    91,   134,    85,   113,    80,    12,   112,
      83,    86,    91,   104,    79,    85,   124,   124,    79,   129,
      79,   187,   189,   187,   170,    82,    87,   188,    23,   171,
     172,   173,   174,   175,   176,   178,   179,   180,   182,   183,
     184,   185,   186,   170,    31,    31,    34,     9,   169,   170,
      86,   136,   170,   170,   191,    88,   108,    68,   104,    35,
      98,   125,   126,   127,   128,    80,    85,    86,    91,   190,
      85,   160,    77,    76,    75,    74,    71,    73,    67,    68,
      24,    69,    70,     8,    20,     3,   155,   147,   144,   170,
     153,    78,    86,    72,    88,    78,    86,    23,    79,   104,
      98,    79,    86,    80,    80,   113,   191,   170,   191,    91,
     104,   162,   163,   177,   177,   177,   177,   177,   177,   181,
     181,   181,   187,   187,   187,   187,   187,    10,    32,   157,
     131,   131,   131,   170,   170,   135,   170,   108,   126,   113,
     113,    86,    88,    86,   166,   164,   161,   163,   170,    11,
     148,   145,    72,    80,    80,    12,     9,   131,   148,   170,
     131,   131,   156,   167,   165,   131,    79,    79
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    92,    93,    94,    95,    95,    97,    96,    98,    98,
      98,    98,    99,   100,   101,   102,   102,   103,   103,   104,
     104,   104,   104,   104,   105,   105,   106,   106,   107,   108,
     108,   108,   109,   110,   111,   111,   112,   113,   113,   113,
     113,   113,   113,   113,   114,   114,   115,   115,   116,   117,
     117,   117,   117,   117,   118,   120,   119,   121,   123,   122,
     124,   124,   125,   125,   126,   126,   127,   128,   129,   130,
     130,   130,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   133,   134,   135,   133,   136,   133,
     137,   138,   137,   137,   139,   137,   137,   141,   140,   143,
     144,   145,   142,   146,   147,   142,   148,   148,   150,   149,
     152,   153,   151,   155,   156,   154,   157,   157,   159,   160,
     161,   158,   162,   162,   164,   165,   163,   166,   167,   163,
     168,   169,   169,   171,   170,   172,   170,   173,   170,   174,
     170,   175,   170,   176,   170,   170,   178,   177,   179,   177,
     180,   177,   177,   182,   181,   183,   181,   184,   181,   185,
     181,   186,   181,   181,   187,   188,   187,   187,   189,   187,
     187,   187,   187,   187,   190,   187,   187,   191,   191
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     0,     3,     2,     0,     3,     3,     1,
       3,     3,     2,     5,     0,     2,     0,     5,     4,     1,
       1,     1,     1,     1,     2,     0,     2,     1,     4,     1,
       1,     1,     6,     3,     2,     1,     4,     1,     1,     3,
       3,     4,     5,     3,     2,     0,     2,     1,     4,     2,
       2,     1,     1,     0,     4,     0,     6,     4,     0,     4,
       3,     0,     3,     1,     3,     3,     1,     2,     1,     3,
       3,     0,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     3,     0,     0,     8,     0,     6,
       1,     0,     5,     1,     0,     5,     4,     0,     4,     0,
       0,     0,     8,     0,     0,     7,     2,     0,     0,     5,
       0,     0,     6,     0,     0,    10,     1,     1,     0,     0,
       0,     8,     2,     1,     0,     0,     6,     0,     0,     6,
       2,     3,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     0,     5,     1,     0,     5,
       1,     3,     2,     2,     0,     5,     3,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 229 "spl.y" /* yacc.c:1646  */
    {
	//dump_symtab(Global_symtab);
	pop_symtab_stack();
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
#line 1704 "rule.c" /* yacc.c:1646  */
    break;

  case 3:
#line 261 "spl.y" /* yacc.c:1646  */
    {
	parser_init();
	make_global_symtab();
	make_system_symtab();
	push_symtab_stack(Global_symtab);
}
#line 1715 "rule.c" /* yacc.c:1646  */
    break;

  case 4:
#line 270 "spl.y" /* yacc.c:1646  */
    {
	strcpy(Global_symtab->name, (yyvsp[-1].p_char));
	snprintf(Global_symtab->rname, sizeof(Global_symtab->rname), "main");
	Global_symtab->defn = DEF_PROG;
#ifdef GENERATE_AST
	global_env.u.program.tab = Global_symtab;
	/* call initialization interface. */
	(*(IR->program_begin))(&global_env);
#else
	emit_program_prologue(Global_symtab);
#endif

}
#line 1733 "rule.c" /* yacc.c:1646  */
    break;

  case 6:
#line 288 "spl.y" /* yacc.c:1646  */
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
#line 1772 "rule.c" /* yacc.c:1646  */
    break;

  case 7:
#line 323 "spl.y" /* yacc.c:1646  */
    {
}
#line 1779 "rule.c" /* yacc.c:1646  */
    break;

  case 8:
#line 329 "spl.y" /* yacc.c:1646  */
    {
	p = new_symbol((yyvsp[0].p_char), DEF_UNKNOWN, TYPE_UNKNOWN);
	for(q = (yyvsp[-2].p_symbol); q->next; q = q->next);
	q->next = p; p ->next = NULL;
	(yyval.p_symbol) = (yyvsp[-2].p_symbol);
}
#line 1790 "rule.c" /* yacc.c:1646  */
    break;

  case 9:
#line 336 "spl.y" /* yacc.c:1646  */
    {
	p = new_symbol((yyvsp[0].p_char), DEF_UNKNOWN, TYPE_UNKNOWN);
	(yyval.p_symbol) = p;
}
#line 1799 "rule.c" /* yacc.c:1646  */
    break;

  case 13:
#line 350 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	emit_routine_prologue(top_symtab_stack());
#endif
}
#line 1810 "rule.c" /* yacc.c:1646  */
    break;

  case 17:
#line 369 "spl.y" /* yacc.c:1646  */
    {
	/* change name of symbol const_value to yNAME */
	strncpy((yyvsp[-1].p_symbol)->name, (yyvsp[-3].p_char), NAME_LEN);
	add_symbol_to_table(
		top_symtab_stack(), (yyvsp[-1].p_symbol));
}
#line 1821 "rule.c" /* yacc.c:1646  */
    break;

  case 18:
#line 376 "spl.y" /* yacc.c:1646  */
    {
	/* change name of symbol const_value to yNAME */
	strncpy((yyvsp[-1].p_symbol)->name, (yyvsp[-3].p_char), NAME_LEN);
	add_symbol_to_table(
		top_symtab_stack(),(yyvsp[-1].p_symbol));
}
#line 1832 "rule.c" /* yacc.c:1646  */
    break;

  case 19:
#line 386 "spl.y" /* yacc.c:1646  */
    {
	/* integer const, temperary named $$$, will change later. */
	p = new_symbol("$$$", DEF_CONST,
		TYPE_INTEGER);
	p->v.i = (yyvsp[0].num);
	(yyval.p_symbol) = p;
}
#line 1844 "rule.c" /* yacc.c:1646  */
    break;

  case 20:
#line 394 "spl.y" /* yacc.c:1646  */
    {
	p = new_symbol("$$$",DEF_CONST,
		TYPE_REAL);

	p->v.f = atof((yyvsp[0].p_char));
	(yyval.p_symbol) = p;
}
#line 1856 "rule.c" /* yacc.c:1646  */
    break;

  case 21:
#line 402 "spl.y" /* yacc.c:1646  */
    {
	p = new_symbol("$$$", DEF_CONST,
		TYPE_CHAR);

	p->v.c= (yyvsp[0].p_char)[1];
	(yyval.p_symbol) = p;
}
#line 1868 "rule.c" /* yacc.c:1646  */
    break;

  case 22:
#line 410 "spl.y" /* yacc.c:1646  */
    {
	p = new_symbol("$$$",DEF_CONST,
		TYPE_STRING);

	p->v.s = strdup((yyvsp[0].p_char));
	(yyval.p_symbol) = p;
}
#line 1880 "rule.c" /* yacc.c:1646  */
    break;

  case 23:
#line 418 "spl.y" /* yacc.c:1646  */
    {
	p = new_symbol("$$$", DEF_CONST,
		TYPE_UNKNOWN);

	switch((yyvsp[0].num))
	{
	case cMAXINT:
		strcpy(p->rname, "maxint");
		p->v.i = (1 << (IR->intmetric.size * 8)) - 1;
		p->type = find_type_by_id(TYPE_INTEGER);
		break;

	case cFALSE  :
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

	(yyval.p_symbol) = p;
}
#line 1916 "rule.c" /* yacc.c:1646  */
    break;

  case 28:
#line 463 "spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-1].p_type)->name[0] == '$')
	{
		/* a new type. */
		(yyval.p_type) = (yyvsp[-1].p_type);
		strncpy((yyval.p_type)->name, (yyvsp[-3].p_char), NAME_LEN);
	}
	else{
		/* an existed type. */
		(yyval.p_type) = clone_type((yyvsp[-1].p_type));
		strncpy((yyval.p_type)->name, (yyvsp[-3].p_char), NAME_LEN);
		add_type_to_table(
			top_symtab_stack(), (yyval.p_type));
	}
}
#line 1936 "rule.c" /* yacc.c:1646  */
    break;

  case 32:
#line 488 "spl.y" /* yacc.c:1646  */
    {
	(yyval.p_type) = new_array_type("$$$", (yyvsp[-3].p_type), (yyvsp[0].p_type));
	add_type_to_table(
		top_symtab_stack(),(yyval.p_type));
}
#line 1946 "rule.c" /* yacc.c:1646  */
    break;

  case 33:
#line 497 "spl.y" /* yacc.c:1646  */
    { 
	pt = new_record_type("$$$", (yyvsp[-1].p_symbol));
 	add_type_to_table(top_symtab_stack(), pt);
	(yyval.p_type) = pt;
}
#line 1956 "rule.c" /* yacc.c:1646  */
    break;

  case 34:
#line 506 "spl.y" /* yacc.c:1646  */
    {
    for(p = (yyvsp[-1].p_symbol); p->next; p = p->next);
	p->next = (yyvsp[0].p_symbol);
	(yyval.p_symbol) = (yyvsp[-1].p_symbol);  
}
#line 1966 "rule.c" /* yacc.c:1646  */
    break;

  case 35:
#line 512 "spl.y" /* yacc.c:1646  */
    {
	(yyval.p_symbol) = (yyvsp[0].p_symbol);
}
#line 1974 "rule.c" /* yacc.c:1646  */
    break;

  case 36:
#line 519 "spl.y" /* yacc.c:1646  */
    {    
	for(p = (yyvsp[-3].p_symbol); p; p = p->next) {
		if((yyvsp[-1].p_type)->type_id == TYPE_SUBRANGE)
			p->type = (yyvsp[-1].p_type)->first->type;
		else if((yyvsp[-1].p_type)->type_id == TYPE_ENUM)
			p->type = find_type_by_id(TYPE_INTEGER);
		else
			p->type = find_type_by_id((yyvsp[-1].p_type)->type_id);

		p->type_link = (yyvsp[-1].p_type);
		p->defn = DEF_FIELD;
	}
	(yyval.p_symbol) = (yyvsp[-3].p_symbol);
}
#line 1993 "rule.c" /* yacc.c:1646  */
    break;

  case 37:
#line 537 "spl.y" /* yacc.c:1646  */
    {
	pt = find_type_by_name((yyvsp[0].p_char));
	if(!pt)
		parse_error("Undeclared type name",(yyvsp[0].p_char));
	(yyval.p_type) = pt;
}
#line 2004 "rule.c" /* yacc.c:1646  */
    break;

  case 38:
#line 544 "spl.y" /* yacc.c:1646  */
    {
	pt = find_type_by_name((yyvsp[0].p_char));
	if (!pt)
	{
		parse_error("Undeclared type name", (yyvsp[0].p_char));
		return 0;
	}
	(yyval.p_type) = pt;
}
#line 2018 "rule.c" /* yacc.c:1646  */
    break;

  case 39:
#line 554 "spl.y" /* yacc.c:1646  */
    {
	(yyval.p_type) = new_enum_type("$$$");
	add_enum_elements((yyval.p_type), (yyvsp[-1].p_symbol));
	add_type_to_table(
		top_symtab_stack(),(yyval.p_type));
}
#line 2029 "rule.c" /* yacc.c:1646  */
    break;

  case 40:
#line 561 "spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-2].p_symbol)->type->type_id != (yyvsp[0].p_symbol)->type->type_id){
		parse_error("type mismatch","");
		return 0;
	}
	(yyval.p_type) = new_subrange_type("$$$", (yyvsp[-2].p_symbol)->type->type_id);
	add_type_to_table(
		top_symtab_stack(), (yyval.p_type));

	if((yyvsp[-2].p_symbol)->type->type_id == TYPE_INTEGER)
		set_subrange_bound((yyval.p_type),
			(int)(yyvsp[-2].p_symbol)->v.i,(int)(yyvsp[0].p_symbol)->v.i);
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_BOOLEAN)
		set_subrange_bound((yyval.p_type),
			(int)(yyvsp[-2].p_symbol)->v.b,(int)(yyvsp[0].p_symbol)->v.b);
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_CHAR)
		set_subrange_bound((yyval.p_type),
			(int)(yyvsp[-2].p_symbol)->v.c,(int)(yyvsp[0].p_symbol)->v.c);
	else
		parse_error("invalid element type of subrange","");
}
#line 2055 "rule.c" /* yacc.c:1646  */
    break;

  case 41:
#line 583 "spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-2].p_symbol)->type->type_id != (yyvsp[0].p_symbol)->type->type_id){
		parse_error("type mismatch","");
		/* return 0; */
	}

	(yyval.p_type) = new_subrange_type("$$$",
		(yyvsp[-2].p_symbol)->type->type_id);
		
	add_type_to_table(
		top_symtab_stack(),(yyval.p_type));

	if((yyvsp[-2].p_symbol)->type->type_id == TYPE_INTEGER){
		(yyvsp[-2].p_symbol)->v.i= -(yyvsp[-2].p_symbol)->v.i;
		set_subrange_bound((yyval.p_type),
			(int)(yyvsp[-2].p_symbol)->v.i,(int)(yyvsp[0].p_symbol)->v.i);
	}
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_BOOLEAN){
		(yyvsp[-2].p_symbol)->v.b ^= 1;
		set_subrange_bound((yyval.p_type),
			(int)(yyvsp[-2].p_symbol)->v.b,(int)(yyvsp[0].p_symbol)->v.b);
	}
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_CHAR)
		parse_error("invalid operator","");
	else
   		parse_error("invalid element type of subrange","");
}
#line 2087 "rule.c" /* yacc.c:1646  */
    break;

  case 42:
#line 611 "spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-3].p_symbol)->type->type_id != (yyvsp[0].p_symbol)->type->type_id) {
		parse_error("type mismatch.","");
		return  0;
	}
	
	(yyval.p_type) = new_subrange_type("$$$", (yyvsp[-3].p_symbol)->type->type_id);

	add_type_to_table(
		top_symtab_stack(),(yyval.p_type));

	if((yyvsp[-3].p_symbol)->type->type_id == TYPE_INTEGER){
		(yyvsp[-3].p_symbol)->v.i = -(yyvsp[-3].p_symbol)->v.i;
		(yyvsp[0].p_symbol)->v.i = -(yyvsp[0].p_symbol)->v.i;
	
		set_subrange_bound((yyval.p_type),(int)(yyvsp[-3].p_symbol)->v.i,
			(int)(yyvsp[0].p_symbol)->v.i);
	}
	else if ((yyvsp[-3].p_symbol)->type->type_id == TYPE_BOOLEAN){
		(yyvsp[-3].p_symbol)->v.b ^= 1;
		(yyvsp[0].p_symbol)->v.b ^= 1;
		set_subrange_bound((yyval.p_type),(int)(yyvsp[-3].p_symbol)->v.b,
		(int)(yyvsp[0].p_symbol)->v.b);
	}
	else if ((yyvsp[-3].p_symbol)->type->type_id == TYPE_CHAR)
		parse_error("invalid operator","");
	else
		parse_error("invalid element type of subrange","");
}
#line 2121 "rule.c" /* yacc.c:1646  */
    break;

  case 43:
#line 641 "spl.y" /* yacc.c:1646  */
    {
	p = find_element(top_symtab_stack(), (yyvsp[-2].p_char));

	if(!p){
		parse_error("Undeclared identifier", (yyvsp[-2].p_char));
		install_temporary_symbol((yyvsp[-2].p_char), DEF_ELEMENT, TYPE_INTEGER);
		/* return 0; */
	}
	
	if(p->defn != DEF_ELEMENT){
		parse_error("not an element identifier", (yyvsp[-2].p_char));
		/* return 0; */
	}
	
	q = find_element(top_symtab_stack(), (yyvsp[0].p_char));
	if(!q){
		parse_error("Undeclared identifier", (yyvsp[0].p_char));
		install_temporary_symbol((yyvsp[0].p_char), DEF_ELEMENT, TYPE_INTEGER);
		/* return 0; */
	}
	if(q->defn != DEF_ELEMENT){
		parse_error("Not an element identifier", (yyvsp[0].p_char));
		/* return 0; */
	}
	
	if(p && q){
		(yyval.p_type) = new_subrange_type("$$$", TYPE_INTEGER);
		add_type_to_table(
			top_symtab_stack(),(yyval.p_type));
		set_subrange_bound((yyval.p_type), p->v.i, q->v.i);
	}
	else
		(yyval.p_type) = NULL;
}
#line 2160 "rule.c" /* yacc.c:1646  */
    break;

  case 48:
#line 689 "spl.y" /* yacc.c:1646  */
    {    
	ptab = top_symtab_stack();
	
	for(p = (yyvsp[-3].p_symbol); p ;){
		if((yyvsp[-1].p_type)->type_id == TYPE_SUBRANGE)
			p->type = find_type_by_id((yyvsp[-1].p_type)->first->type->type_id);
		else if((yyvsp[-1].p_type)->type_id == TYPE_ENUM)
			p->type = find_type_by_id(TYPE_INTEGER);
		else
			p->type = find_type_by_id((yyvsp[-1].p_type)->type_id);

		p->type_link = (yyvsp[-1].p_type);
		p->defn = DEF_VAR;

		q = p; p = p->next;
		q->next = NULL;
		add_symbol_to_table(ptab, q);
	}
	(yyvsp[-3].p_symbol) = NULL;
}
#line 2185 "rule.c" /* yacc.c:1646  */
    break;

  case 54:
#line 721 "spl.y" /* yacc.c:1646  */
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
#line 2212 "rule.c" /* yacc.c:1646  */
    break;

  case 55:
#line 747 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	list_clear(&ast_forest);
	list_clear(&para_list);
#endif

	ptab = new_symtab(top_symtab_stack());
	push_symtab_stack(ptab);
}
#line 2226 "rule.c" /* yacc.c:1646  */
    break;

  case 56:
#line 758 "spl.y" /* yacc.c:1646  */
    {
	ptab = top_symtab_stack();
	strncpy(ptab->name, (yyvsp[-3].p_char), NAME_LEN);
	sprintf(ptab->rname, "rtn%03d",ptab->id);
	ptab->defn = DEF_FUNCT;
	
	if((yyvsp[0].p_type)->type_id == TYPE_SUBRANGE)
		ptab->type = (yyvsp[0].p_type)->first->type;
	else if((yyvsp[0].p_type)->type_id == TYPE_ENUM)
		ptab->type = find_type_by_id(TYPE_INTEGER);
	else
		ptab->type = find_type_by_id((yyvsp[0].p_type)->type_id);

	p = new_symbol((yyvsp[-3].p_char), DEF_FUNCT, ptab->type->type_id);
	p->type_link = (yyvsp[0].p_type);
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
#line 2260 "rule.c" /* yacc.c:1646  */
    break;

  case 57:
#line 791 "spl.y" /* yacc.c:1646  */
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
#line 2284 "rule.c" /* yacc.c:1646  */
    break;

  case 58:
#line 814 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	list_clear(&ast_forest);
	list_clear(&para_list);
#endif

	ptab = new_symtab(top_symtab_stack());
	push_symtab_stack(ptab);
}
#line 2298 "rule.c" /* yacc.c:1646  */
    break;

  case 59:
#line 824 "spl.y" /* yacc.c:1646  */
    {
	ptab = top_symtab_stack();
	strncpy(ptab->name, (yyvsp[-1].p_char), NAME_LEN);
	sprintf(ptab->rname, "rtn%03d",ptab->id);
	ptab->defn = DEF_PROC;
	p = new_symbol((yyvsp[-1].p_char), DEF_PROC, TYPE_VOID);
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
#line 2323 "rule.c" /* yacc.c:1646  */
    break;

  case 60:
#line 848 "spl.y" /* yacc.c:1646  */
    {
	ptab = top_symtab_stack();
	ptab->local_size = 0;
}
#line 2332 "rule.c" /* yacc.c:1646  */
    break;

  case 64:
#line 862 "spl.y" /* yacc.c:1646  */
    {
	ptab = top_symtab_stack();
	for(p = (yyvsp[-2].p_symbol); p ;){
		if((yyvsp[0].p_type)->type_id
			== TYPE_SUBRANGE)
			p->type = (yyvsp[0].p_type)->first->type;
		else if ((yyvsp[0].p_type)->type_id == TYPE_ENUM)
			p->type = find_type_by_id(TYPE_INTEGER);
		else
			p->type = find_type_by_id((yyvsp[0].p_type)->type_id);
		p->type_link = (yyvsp[0].p_type);
		p->defn = DEF_VALPARA;

		q = p; p = p->next;
		q->next = NULL;
		add_symbol_to_table(ptab,q);
#ifdef GENERATE_AST
		/* append to paralist. */
		list_append(&para_list, q);
#endif
	}

	(yyvsp[-2].p_symbol) = NULL;
}
#line 2361 "rule.c" /* yacc.c:1646  */
    break;

  case 65:
#line 887 "spl.y" /* yacc.c:1646  */
    {
	ptab = top_symtab_stack();
	for(p = (yyvsp[-2].p_symbol); p;){
		if((yyvsp[0].p_type)->type_id == TYPE_SUBRANGE)
			p->type = (yyvsp[0].p_type)->first->type;
		else if((yyvsp[0].p_type)->type_id == TYPE_ENUM)
			p->type = find_type_by_id(TYPE_INTEGER);
		else
			p->type = find_type_by_id((yyvsp[0].p_type)->type_id);
		p->type_link = (yyvsp[0].p_type);
		p->defn = DEF_VARPARA;
		q = p; p = p->next;
		q->next=NULL;
		add_symbol_to_table(ptab,q);
#ifdef GENERATE_AST
		/* append to para_list. */
		list_append(&para_list, q);
#endif
	}
	(yyvsp[-2].p_symbol) = NULL;
}
#line 2387 "rule.c" /* yacc.c:1646  */
    break;

  case 67:
#line 916 "spl.y" /* yacc.c:1646  */
    {
	(yyval.p_symbol) = (yyvsp[0].p_symbol);
}
#line 2395 "rule.c" /* yacc.c:1646  */
    break;

  case 84:
#line 951 "spl.y" /* yacc.c:1646  */
    {
	p = find_symbol(top_symtab_stack(), (yyvsp[-2].p_char));
	if (p == NULL)
	{
		parse_error("Undefined identifier", (yyvsp[-2].p_char));
		p = install_temporary_symbol((yyvsp[-2].p_char), DEF_VAR, TYPE_INTEGER);
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
		if(p->type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	#else
		if(p->type->type_id != (yyvsp[0].p_tree))
	#endif
		{
			parse_error("type mismatch","");
			/* return 0; */
		}
	}
	else
	{
		ptab = find_routine((yyvsp[-2].p_char));
		if(ptab)
		{
		#ifdef GENERATE_AST
			if(ptab->type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
		#else
			if(ptab->type->type_id != (yyvsp[0].p_tree))
		#endif
			{
				parse_error("type mismatch","");
				/* return 0; */
			}
		}
		else{
			parse_error("Undeclared identifier.",(yyvsp[-2].p_char));
		#ifdef GENERATE_AST
			install_temporary_symbol((yyvsp[-2].p_char), DEF_VAR, (yyvsp[0].p_tree)->result_type->type_id);
		#else
			install_temporary_symbol((yyvsp[-2].p_char), DEF_VAR, (yyvsp[0].p_tree));
		#endif
			/* return 0; */
		}
	}

#ifdef GENERATE_AST
	t = address_tree(NULL, p);
	(yyval.p_tree) = assign_tree(t, (yyvsp[0].p_tree));
	
	/* append to forest. */
	list_append(&ast_forest, (yyval.p_tree));
	
#else
	
	if (p && p->defn != DEF_FUNCT)
	{
		do_assign(p, (yyvsp[0].p_tree));
	}
	else
	{
		do_function_assign(ptab, (yyvsp[0].p_tree));
	}
#endif
}
#line 2471 "rule.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1023 "spl.y" /* yacc.c:1646  */
    {
	p = find_symbol(top_symtab_stack(), (yyvsp[-1].p_char));
	if(!p || p->type->type_id != TYPE_ARRAY){
		parse_error("Undeclared array name",(yyvsp[-1].p_char));
		return 0;
	}
	
	push_term_stack(p);
#ifdef GENERATE_AST
#else
	emit_load_address(p);
	emit_push_op(TYPE_INTEGER);
#endif
}
#line 2490 "rule.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1038 "spl.y" /* yacc.c:1646  */
    {
	p = top_term_stack();
#ifdef GENERATE_AST
	p = find_symbol(top_symtab_stack(), (yyvsp[-4].p_char));
	if(!p || p->type->type_id != TYPE_ARRAY){
		parse_error("Undeclared array name",(yyvsp[-4].p_char));
		return 0;
	}
	
	t = array_factor_tree(p, (yyvsp[-1].p_tree));
	t = address_tree(t, p);
	push_ast_stack(t);
#else
	do_array_factor(p);
#endif
}
#line 2511 "rule.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1055 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	t = pop_ast_stack();
	(yyval.p_tree) = assign_tree(t, (yyvsp[0].p_tree));
	list_append(&ast_forest, (yyval.p_tree));
#else
	p = pop_term_stack();
	do_assign(p, (yyvsp[0].p_tree));
#endif
}
#line 2526 "rule.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1066 "spl.y" /* yacc.c:1646  */
    {
	p = find_symbol(top_symtab_stack(),(yyvsp[-2].p_char));
	if(!p || p->type->type_id != TYPE_RECORD){
		parse_error("Undeclared record vaiable",(yyvsp[-2].p_char));
		return 0;
	}

	q = find_field(p,(yyvsp[0].p_char));
	if(!q || q->defn != DEF_FIELD){
		parse_error("Undeclared field",(yyvsp[0].p_char));
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
#line 2556 "rule.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1092 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	t = pop_ast_stack();
	(yyval.p_tree) = assign_tree(t, (yyvsp[0].p_tree));
	list_append(&ast_forest, (yyval.p_tree));
#else
	q = pop_term_stack();
	p = pop_term_stack();
	do_assign(q, (yyvsp[0].p_tree));
#endif
}
#line 2572 "rule.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1107 "spl.y" /* yacc.c:1646  */
    {
	ptab = find_routine((yyvsp[0].p_char));
	if(!ptab || ptab->defn != DEF_PROC){
		parse_error("Undeclared procedure",(yyvsp[0].p_char));
		return 0;
	}

#ifdef GENERATE_AST
	(yyval.p_tree) = call_tree(ptab, NULL);
	list_append(&ast_forest, (yyval.p_tree));
#else
	do_procedure_call(ptab);
#endif
}
#line 2591 "rule.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1122 "spl.y" /* yacc.c:1646  */
    {
	ptab = find_routine((yyvsp[0].p_char));
	if(!ptab || ptab->defn != DEF_PROC){
			parse_error("Undeclared procedure",(yyvsp[0].p_char));
			return 0;
	}
	push_call_stack(ptab);
}
#line 2604 "rule.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1131 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = call_tree(top_call_stack(), args);
	list_append(&ast_forest, (yyval.p_tree));
#else
	do_procedure_call(top_call_stack());
#endif
	pop_call_stack();
}
#line 2618 "rule.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1141 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = sys_tree((yyvsp[0].p_lex)->attr, NULL);
	list_append(&ast_forest, (yyval.p_tree));
#else
	do_sys_routine((yyvsp[0].p_lex)->attr, 0);
#endif
}
#line 2631 "rule.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1150 "spl.y" /* yacc.c:1646  */
    {
	rtn = find_sys_routine((yyvsp[0].p_lex)->attr);

	if(rtn)
		arg = rtn->args;
	else
	{
		arg = NULL;
	}

	push_call_stack(rtn);
}
#line 2648 "rule.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1163 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = sys_tree((yyvsp[-4].p_lex)->attr, (yyvsp[-1].p_tree));
	list_append(&ast_forest, (yyval.p_tree));
#else
	do_sys_routine((yyvsp[-4].p_lex)->attr, (yyvsp[-1].p_tree));
#endif
	
	pop_call_stack();
}
#line 2663 "rule.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1174 "spl.y" /* yacc.c:1646  */
    {
	if(!(yyvsp[-1].p_tree)){
		parse_error("too few parameters in call to", "read");
		return 0;
	}
#ifdef GENERATE_AST
	if (generic((yyvsp[-1].p_tree)->op) == LOAD)
		t = address_tree(NULL, (yyvsp[-1].p_tree)->u.generic.sym);
	else
		t = address_tree((yyvsp[-1].p_tree), (yyvsp[-1].p_tree)->u.generic.sym);
	(yyval.p_tree) = sys_tree(pREAD, t);
	list_append(&ast_forest, (yyval.p_tree));
#else
	emit_load_address((yyvsp[-1].p_tree));
	do_sys_routine(pREAD, (yyvsp[-1].p_tree)->type->type_id);
#endif
}
#line 2685 "rule.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1195 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	/* block begin. */
	t = new_tree(BLOCKBEG, NULL, NULL, NULL);
	list_append(&ast_forest, t);
#endif
}
#line 2697 "rule.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1204 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	/* block end. */
	t = new_tree(BLOCKEND, NULL, NULL, NULL);
	list_append(&ast_forest, t);
#endif
}
#line 2709 "rule.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1215 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	push_lbl_stack(if_label_count++);
#endif
}
#line 2719 "rule.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1221 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_false_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	t = cond_jump_tree((yyvsp[-1].p_tree), false, new_label);
	list_append(&ast_forest, t);
#else
	do_if_test();
#endif
}
#line 2736 "rule.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1234 "spl.y" /* yacc.c:1646  */
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
#line 2765 "rule.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1259 "spl.y" /* yacc.c:1646  */
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
#line 2785 "rule.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1275 "spl.y" /* yacc.c:1646  */
    {
	printf("expression expected.\n");
}
#line 2793 "rule.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1279 "spl.y" /* yacc.c:1646  */
    {
	printf("then matched.\n");
}
#line 2801 "rule.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1292 "spl.y" /* yacc.c:1646  */
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
#line 2818 "rule.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1305 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	snprintf(mini_buf, sizeof(mini_buf) - 1, "repeat_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = cond_jump_tree((yyvsp[0].p_tree), false, new_label);
	list_append(&ast_forest, t);
	pop_lbl_stack();
#else
	do_repeat_exit();
#endif
}
#line 2835 "rule.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1321 "spl.y" /* yacc.c:1646  */
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
#line 2852 "rule.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1334 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = cond_jump_tree((yyvsp[-1].p_tree), false, exit_label);
	list_append(&ast_forest, t);
#else
	do_while_expr();
#endif
}
#line 2868 "rule.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1346 "spl.y" /* yacc.c:1646  */
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
#line 2898 "rule.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1375 "spl.y" /* yacc.c:1646  */
    {
	p = find_symbol(top_symtab_stack(),(yyvsp[-2].p_char));
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
	list_append(&ast_forest, assign_tree(t, (yyvsp[0].p_tree)));

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
#line 2937 "rule.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1410 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST

	snprintf(mini_buf, sizeof(mini_buf) - 1, "for_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);


	p = find_symbol(top_symtab_stack(),(yyvsp[-6].p_char));
	t = id_factor_tree(NULL, p);

	if ((yyvsp[-2].num) == kTO)
	{
		t = compare_expr_tree(LE, t, (yyvsp[-1].p_tree));
	}
	else
	{
		t = compare_expr_tree(GE, t, (yyvsp[-1].p_tree));
	}

	t = cond_jump_tree(t, false, exit_label);
	list_append(&ast_forest, t);
#else
	do_for_test((yyvsp[-2].num));
#endif
}
#line 2968 "rule.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1437 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	t = pop_ast_stack();

	if ((yyvsp[-4].num) == kTO)
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
#line 3007 "rule.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1475 "spl.y" /* yacc.c:1646  */
    {
	(yyval.num) = kTO;
}
#line 3015 "rule.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1479 "spl.y" /* yacc.c:1646  */
    {
	(yyval.num) = kDOWNTO;
}
#line 3023 "rule.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1486 "spl.y" /* yacc.c:1646  */
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
#line 3045 "rule.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1504 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	do_case_start();
#endif
}
#line 3056 "rule.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1511 "spl.y" /* yacc.c:1646  */
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
			
			t = compare_expr_tree(EQ, (yyvsp[-3].p_tree), cases[i + 1]);
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
#line 3097 "rule.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1557 "spl.y" /* yacc.c:1646  */
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

	t = const_tree((yyvsp[0].p_symbol));
	list_append(case_list, t);
#else
	add_case_const((yyvsp[0].p_symbol));
#endif
}
#line 3124 "rule.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1580 "spl.y" /* yacc.c:1646  */
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
#line 3141 "rule.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1594 "spl.y" /* yacc.c:1646  */
    {
	p = find_symbol(
		top_symtab_stack(),(yyvsp[0].p_char));
	if(!p){
			parse_error("Undeclared identifier",(yyvsp[0].p_char));
			install_temporary_symbol((yyvsp[0].p_char), DEF_CONST, TYPE_INTEGER);
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
#line 3179 "rule.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1628 "spl.y" /* yacc.c:1646  */
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
#line 3195 "rule.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1648 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST

	rtn = top_call_stack();

	/* next argument. */
	if (arg)
	{
		arg = arg->next;
	}

	/* append to right tree of args. */
	args = arg_tree(args, rtn, arg, (yyvsp[0].p_tree));
	(yyval.p_tree) = args;

#endif
}
#line 3217 "rule.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1666 "spl.y" /* yacc.c:1646  */
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

	args = arg_tree(args, rtn, arg, (yyvsp[0].p_tree));

	(yyval.p_tree) = args;

#endif
}
#line 3244 "rule.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1692 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
    emit_push_op((yyvsp[0].p_tree));
#endif
}
#line 3255 "rule.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1699 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = compare_expr_tree(GE, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_expression((yyvsp[0].p_tree), oGE);
	(yyval.p_tree) = TYPE_BOOLEAN;
#endif
}
#line 3268 "rule.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1708 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
   	emit_push_op((yyvsp[0].p_tree));
#endif
}
#line 3279 "rule.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1715 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = compare_expr_tree(GT, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_expression((yyvsp[0].p_tree), oGT);
	(yyval.p_tree) = TYPE_BOOLEAN;
#endif
}
#line 3292 "rule.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1724 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
   emit_push_op((yyvsp[0].p_tree));
#endif
}
#line 3303 "rule.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1731 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = compare_expr_tree(LE, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else

	do_expression((yyvsp[0].p_tree),oLE);
	(yyval.p_tree) = TYPE_BOOLEAN;
#endif
}
#line 3317 "rule.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1741 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	emit_push_op((yyvsp[0].p_tree));
#endif
}
#line 3328 "rule.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1748 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = compare_expr_tree(LT, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_expression((yyvsp[0].p_tree),oLT);
	(yyval.p_tree) = TYPE_BOOLEAN;
#endif
}
#line 3341 "rule.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1757 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	emit_push_op((yyvsp[0].p_tree));
#endif
}
#line 3352 "rule.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1764 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = compare_expr_tree(EQ, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_expression((yyvsp[0].p_tree),oEQUAL);
	(yyval.p_tree) = TYPE_BOOLEAN;
#endif
}
#line 3365 "rule.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1773 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	emit_push_op((yyvsp[0].p_tree));
#endif
}
#line 3376 "rule.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1780 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = compare_expr_tree(NE, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_expression((yyvsp[0].p_tree),oUNEQU);
	(yyval.p_tree) = TYPE_BOOLEAN;
#endif
}
#line 3389 "rule.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1789 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = (yyvsp[0].p_tree);
#else
	(yyval.p_tree) = (yyvsp[0].p_tree)->type->type_id;
#endif
}
#line 3401 "rule.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1799 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	emit_push_op((yyvsp[0].p_tree)->type->type_id);
#endif
}
#line 3412 "rule.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1806 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = binary_expr_tree(ADD, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_expr((yyvsp[0].p_tree),oPLUS);
#endif
}
#line 3424 "rule.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1814 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	emit_push_op((yyvsp[0].p_tree)->type->type_id);
#endif
}
#line 3435 "rule.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1821 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = binary_expr_tree(SUB, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_expr((yyvsp[0].p_tree) ,oMINUS);
#endif
}
#line 3447 "rule.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1829 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	emit_push_op((yyvsp[0].p_tree)->type->type_id);
#endif
}
#line 3458 "rule.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1836 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = binary_expr_tree(OR, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_expression((yyvsp[0].p_tree),kOR);
#endif
}
#line 3470 "rule.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1844 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = (yyvsp[0].p_tree);
#endif
}
#line 3480 "rule.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1852 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
        emit_push_op((yyvsp[0].p_tree)->type->type_id);
#endif
}
#line 3491 "rule.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1859 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = binary_expr_tree(MUL, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_term((yyvsp[0].p_tree),oMUL);
#endif
}
#line 3503 "rule.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1867 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	emit_push_op((yyvsp[0].p_tree)->type->type_id);
#endif
}
#line 3514 "rule.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1874 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = binary_expr_tree(DIV, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_term((yyvsp[0].p_tree),kDIV);
#endif
}
#line 3526 "rule.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1882 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	emit_push_op((yyvsp[0].p_tree)->type->type_id);
#endif

}
#line 3538 "rule.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1890 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = binary_expr_tree(DIV, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_term((yyvsp[0].p_tree), kDIV);
#endif
}
#line 3550 "rule.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1898 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	emit_push_op((yyvsp[0].p_tree)->type->type_id);
#endif

}
#line 3562 "rule.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1906 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = binary_expr_tree(MOD, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_term((yyvsp[0].p_tree), kMOD);
#endif
}
#line 3574 "rule.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1914 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
#else
	emit_push_op((yyvsp[0].p_tree)->type->type_id);
#endif
}
#line 3585 "rule.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1921 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = binary_expr_tree(AND, (yyvsp[-3].p_tree), (yyvsp[0].p_tree));
#else
	do_term((yyvsp[0].p_tree),kAND);
#endif
}
#line 3597 "rule.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1929 "spl.y" /* yacc.c:1646  */
    {
	(yyval.p_tree) = (yyvsp[0].p_tree);
}
#line 3605 "rule.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1935 "spl.y" /* yacc.c:1646  */
    { 
	p = NULL;

	if((p = find_symbol(
		top_symtab_stack(),(yyvsp[0].p_char))))
	{
		if(p->type->type_id == TYPE_ARRAY
			||p->type->type_id == TYPE_RECORD)
		{
			parse_error("rvalue expected",  "");
			return 0;
		}
	}
	else if ((ptab = find_routine((yyvsp[0].p_char))) == NULL)
	{
		parse_error("Undeclard identificr",(yyvsp[0].p_char));
		p = install_temporary_symbol((yyvsp[0].p_char), DEF_VAR, TYPE_INTEGER);
		/* return  0; */
	}
#ifdef GENERATE_AST
	if (p)
	{
		(yyval.p_tree) = id_factor_tree(NULL, p);
	}
	else
	{
		/* call functions with no arguments. */
		(yyval.p_tree) = call_tree(ptab, NULL);
	}
#else
	if(p)
	{
		(yyval.p_tree) = p;
		do_factor(p);
	}
	else 
	{
		(yyval.p_tree) = do_function_call(ptab);
	}
#endif
}
#line 3651 "rule.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1977 "spl.y" /* yacc.c:1646  */
    {
	if((ptab = find_routine((yyvsp[0].p_char))))
  		push_call_stack(ptab);
	else
	{
		parse_error("Undeclared funtion",(yyvsp[0].p_char));
		return  0;
	}
}
#line 3665 "rule.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1987 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = call_tree(ptab, args);
#else
	(yyval.p_tree) = do_function_call(top_call_stack());
#endif
	pop_call_stack();
}
#line 3678 "rule.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1996 "spl.y" /* yacc.c:1646  */
    {
	ptab = find_sys_routine((yyvsp[0].p_lex)->attr);
#ifdef GENERATE_AST
	(yyval.p_tree) = sys_tree((yyvsp[0].p_lex)->attr, NULL);
#else
	do_sys_routine(ptab->id, ptab->type->type_id);
	(yyval.p_tree) = ptab->locals;
#endif
}
#line 3692 "rule.c" /* yacc.c:1646  */
    break;

  case 168:
#line 2006 "spl.y" /* yacc.c:1646  */
    {
	ptab = find_sys_routine((yyvsp[0].p_lex)->attr);
	push_call_stack(ptab);
}
#line 3701 "rule.c" /* yacc.c:1646  */
    break;

  case 169:
#line 2011 "spl.y" /* yacc.c:1646  */
    {
	ptab = top_call_stack();
#ifdef GENERATE_AST
	(yyval.p_tree) = sys_tree((yyvsp[-4].p_lex)->attr, args);
#else
	ptab = top_call_stack();
	do_sys_routine(-ptab->id, ptab->type->type_id);
	ptab = pop_call_stack();
	(yyval.p_tree) = ptab->locals;
#endif
}
#line 3717 "rule.c" /* yacc.c:1646  */
    break;

  case 170:
#line 2023 "spl.y" /* yacc.c:1646  */
    {
	switch((yyvsp[0].p_symbol)->type->type_id){
		case TYPE_REAL:
		case TYPE_STRING:
			add_symbol_to_table(Global_symtab, (yyvsp[0].p_symbol));
			break;
		case TYPE_BOOLEAN:
			sprintf((yyvsp[0].p_symbol)->rname, "%d", (int)((yyvsp[0].p_symbol)->v.b));
			break;
		case TYPE_INTEGER:
			if((yyvsp[0].p_symbol)->v.i > 0)
				sprintf((yyvsp[0].p_symbol)->rname,"0%xh", (yyvsp[0].p_symbol)->v.i);
			else
				sprintf((yyvsp[0].p_symbol)->rname, "-0%xh", -((yyvsp[0].p_symbol)->v.i));
			break;
		case TYPE_CHAR:
			sprintf((yyvsp[0].p_symbol)->rname, "'%c'", (yyvsp[0].p_symbol)->v.c);
			break;
		default:
			break;
	}
#ifdef GENERATE_AST
	(yyval.p_tree) = const_tree((yyvsp[0].p_symbol));
#else
	do_factor((yyvsp[0].p_symbol));
#endif
}
#line 3749 "rule.c" /* yacc.c:1646  */
    break;

  case 171:
#line 2051 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = (yyvsp[-1].p_tree);
#else
	(yyval.p_tree) = find_symbol(NULL, "");
	(yyval.p_tree)->type = find_type_by_id((yyvsp[-1].p_tree));
#endif
}
#line 3762 "rule.c" /* yacc.c:1646  */
    break;

  case 172:
#line 2060 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = not_tree((yyvsp[0].p_tree));
#else
	do_not_factor((yyvsp[0].p_tree));
	(yyval.p_tree) = (yyvsp[0].p_tree);
#endif
}
#line 3775 "rule.c" /* yacc.c:1646  */
    break;

  case 173:
#line 2069 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	(yyval.p_tree) = neg_tree((yyvsp[0].p_tree));
#else
	do_negate((yyvsp[0].p_tree));
	(yyval.p_tree) = (yyvsp[0].p_tree);
#endif
}
#line 3788 "rule.c" /* yacc.c:1646  */
    break;

  case 174:
#line 2078 "spl.y" /* yacc.c:1646  */
    {
	p = find_symbol(
		top_symtab_stack(), (yyvsp[-1].p_char));
		   
	if(!p || p->type->type_id != TYPE_ARRAY){
		parse_error("Undeclared array  name",(yyvsp[-1].p_char));
		return  0;
	}

	push_term_stack(p);

#ifdef GENERATE_AST
#else
	emit_load_address(p);
  	emit_push_op(TYPE_INTEGER);
#endif
}
#line 3810 "rule.c" /* yacc.c:1646  */
    break;

  case 175:
#line 2096 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST
	p = pop_term_stack(p);
	t = array_factor_tree(p, (yyvsp[-1].p_tree));
	(yyval.p_tree) = id_factor_tree(t, p);
#else
	p = pop_term_stack(p);
	do_array_factor(p);
	emit_load_value(p);
	(yyval.p_tree) = p->type_link->last;
#endif
}
#line 3827 "rule.c" /* yacc.c:1646  */
    break;

  case 176:
#line 2109 "spl.y" /* yacc.c:1646  */
    {
	p = find_symbol(top_symtab_stack(), (yyvsp[-2].p_char));
	if(!p || p->type->type_id != TYPE_RECORD) {
		parse_error("Undeclared record variable",(yyvsp[-2].p_char));
		return  0;
	}
	q = find_field(p, (yyvsp[0].p_char));
	if(!q || q->defn != DEF_FIELD){
		parse_error("Undeclared field ",(yyvsp[0].p_char));
		return 0;
	}
	
#ifdef GENERATE_AST
	t = field_tree(p, q);
	(yyval.p_tree) = id_factor_tree(t, q);
#else
	emit_load_address(p);
	emit_push_op(TYPE_INTEGER);
	do_record_factor(p,q);
	emit_load_field(q);
	(yyval.p_tree) = q;
#endif
}
#line 3855 "rule.c" /* yacc.c:1646  */
    break;

  case 177:
#line 2136 "spl.y" /* yacc.c:1646  */
    {
#ifdef GENERATE_AST

	rtn = top_call_stack();

	/* next argument. */
	if (arg)
	{
		arg = arg->next;
	}

	/* append to right tree of args. */
	args = arg_tree(args, rtn, arg, (yyvsp[0].p_tree));
#else
	do_args((yyvsp[0].p_tree));
#endif
}
#line 3877 "rule.c" /* yacc.c:1646  */
    break;

  case 178:
#line 2154 "spl.y" /* yacc.c:1646  */
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
		args = arg_tree(args, rtn, arg, (yyvsp[0].p_tree));
	}

#else
	do_first_arg((yyvsp[0].p_tree));
#endif
}
#line 3907 "rule.c" /* yacc.c:1646  */
    break;


#line 3911 "rule.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 2181 "spl.y" /* yacc.c:1906  */


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
