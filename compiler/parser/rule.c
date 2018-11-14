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
#line 1 "parser/spl.y" /* yacc.c:339  */


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
struct list *dag_forest;

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

extern void ast_compile(List, List);

#line 163 "parser/rule.c" /* yacc.c:339  */

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
#line 98 "parser/spl.y" /* yacc.c:355  */

	char 		p_char[NAME_LEN];
	int 		num;
	int 		ascii;
	Symbol 		p_symbol; /* 符号 */
	Type		p_type; /* 类型 */
	KEYENTRY	*p_lex; /* 关键字 */
	Tree 		p_tree;

#line 312 "parser/rule.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_RULE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 329 "parser/rule.c" /* yacc.c:358  */

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
#define YYLAST   363

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  99
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  82
/* YYNRULES -- Number of rules.  */
#define YYNRULES  170
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  319

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   353

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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   226,   226,   255,   266,   284,   289,   288,   296,   313,
     319,   320,   324,   328,   332,   333,   337,   344,   354,   364,
     373,   381,   390,   427,   428,   432,   433,   437,   459,   460,
     461,   465,   473,   481,   491,   498,   523,   533,   546,   557,
     582,   608,   636,   669,   670,   674,   675,   679,   711,   712,
     713,   714,   715,   719,   749,   748,   814,   837,   836,   871,
     872,   876,   877,   881,   909,   939,   946,   953,   957,   958,
     959,   964,   965,   966,   967,   968,   969,   970,   971,   972,
     976,  1016,  1035,  1015,  1055,  1054,  1090,  1089,  1113,  1121,
    1128,  1127,  1145,  1144,  1159,  1193,  1192,  1213,  1218,  1228,
    1212,  1262,  1266,  1261,  1273,  1274,  1279,  1278,  1305,  1317,
    1304,  1354,  1388,  1353,  1462,  1466,  1474,  1491,  1473,  1536,
    1537,  1542,  1565,  1541,  1576,  1605,  1575,  1616,  1627,  1638,
    1649,  1660,  1671,  1682,  1689,  1700,  1711,  1720,  1729,  1736,
    1747,  1758,  1769,  1780,  1791,  1800,  1810,  1821,  1832,  1842,
    1852,  1863,  1870,  1893,  1892,  1910,  1918,  1917,  1930,  1959,
    1964,  1975,  1980,  1991,  1996,  2035,  2034,  2057,  2085,  2090,
    2104
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "kAND", "kARRAY", "kBEGIN", "kCASE",
  "kCONST", "kDIV", "kDO", "kDOWNTO", "kELSE", "kEND", "kFILE", "kFOR",
  "kFUNCTION", "kIF", "kIN", "kLABEL", "kMOD", "kNIL", "kNOT", "kOF",
  "kOR", "kPROCEDURE", "kPROGRAM", "kRECORD", "kREPEAT", "kTHEN", "kTO",
  "kTYPE", "kUNTIL", "kVAR", "kWHILE", "SYS_CON", "cFALSE", "cTRUE",
  "cMAXINT", "cSTRING", "cINTEGER", "cREAL", "cCHAR", "cBOOLEAN",
  "SYS_TYPE", "tINTEGER", "tCHAR", "tREAL", "tBOOLEAN", "tUCHAR",
  "tUINTEGER", "SYS_FUNCT", "fABS", "fSQR", "fSQRT", "SYS_PROC",
  "SYS_READ", "TYPE_CONVERT", "cvBOOLEAN", "cvINT", "cvREAL", "cvUCHAR",
  "cvCHAR", "cvUINT", "pWRITE", "pWRITELN", "pREAD", "pREADLN", "oPLUS",
  "oMINUS", "oMUL", "oDIV", "oEQUAL", "oASSIGN", "oUNEQU", "oAND", "oOR",
  "oNOT", "oBAND", "oBOR", "oBXOR", "oBCOM", "oRSH", "oLSH", "oMOD", "oLT",
  "oLE", "oGT", "oGE", "oCOMMA", "oSEMI", "oCOLON", "oQUOTE", "oDOT",
  "oDOTDOT", "oLP", "oRP", "oLB", "oRB", "yNAME", "$accept", "program",
  "first_act_at_prog", "program_head", "sub_program", "$@1", "name_list",
  "sub_routine", "routine_head", "const_part", "const_expr_list",
  "const_value", "type_part", "type_decl_list", "type_definition",
  "type_decl", "array_type_decl", "record_type_decl", "field_decl_list",
  "field_decl", "simple_type_decl", "var_part", "var_decl_list",
  "var_decl", "routine_part", "function_decl", "function_head", "$@2",
  "procedure_decl", "procedure_head", "$@3", "parameters",
  "para_decl_list", "para_type_list", "val_para_list", "var_para_list",
  "routine_body", "stmt_list", "stmt", "assign_stmt", "$@4", "$@5", "$@6",
  "routine_stmt", "$@7", "$@8", "$@9", "compound_stmt", "$@10", "if_stmt",
  "$@11", "$@12", "$@13", "$@14", "$@15", "else_clause", "repeat_stmt",
  "$@16", "while_stmt", "$@17", "$@18", "for_stmt", "$@19", "$@20",
  "direction", "case_stmt", "$@21", "$@22", "case_expr_list", "case_expr",
  "$@23", "$@24", "$@25", "$@26", "expression", "expr", "term", "factor",
  "$@27", "$@28", "$@29", "args_list", YY_NULLPTR
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
     345,   346,   347,   348,   349,   350,   351,   352,   353
};
# endif

#define YYPACT_NINF -143

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-143)))

#define YYTABLE_NINF -157

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -143,    56,    27,  -143,   -66,   -47,    62,  -143,   -14,    -3,
      -1,  -143,    73,  -143,    36,    17,  -143,   117,    38,    91,
     169,    69,  -143,  -143,  -143,    74,    38,  -143,    46,    25,
    -143,  -143,  -143,  -143,  -143,    65,   169,  -143,    94,  -143,
      26,   -42,    46,  -143,  -143,  -143,    25,  -143,    71,  -143,
      76,  -143,    77,     8,    75,    46,  -143,   169,    46,    79,
      92,    78,  -143,  -143,  -143,   -24,    86,    94,  -143,    89,
      95,  -143,  -143,    62,    62,  -143,    80,  -143,  -143,   106,
      32,  -143,  -143,    96,   112,   119,   -53,   100,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,    -9,    51,     3,  -143,
     123,   -38,   127,   169,  -143,  -143,  -143,  -143,   128,   136,
     136,   149,   117,   158,  -143,   232,   180,  -143,   232,   141,
     232,   142,   173,   232,   232,   170,  -143,   175,  -143,   177,
      94,  -143,  -143,   275,  -143,  -143,  -143,  -143,   -21,   185,
    -143,  -143,  -143,  -143,   232,   182,   232,   232,   232,   232,
     232,    35,  -143,   207,    19,   145,  -143,   232,   249,   212,
     248,   147,   232,   232,   186,   273,  -143,   232,   232,   262,
     197,   169,  -143,    46,   199,     4,  -143,   200,   205,    -9,
    -143,   195,  -143,  -143,  -143,  -143,   268,   203,  -143,   208,
      40,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   273,  -143,  -143,   232,  -143,   273,   -34,
     -28,  -143,   231,   234,    14,    94,  -143,  -143,   199,   -21,
    -143,    -9,    -9,  -143,   232,  -143,  -143,   232,   232,  -143,
    -143,    40,  -143,    19,    19,    19,    19,    19,    19,   145,
     145,   145,   145,  -143,  -143,  -143,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,     7,   141,   141,   273,   141,
     232,  -143,  -143,   232,  -143,  -143,  -143,  -143,  -143,  -143,
      23,   251,    29,   214,   216,   298,  -143,  -143,  -143,   232,
     300,  -143,  -143,   273,   273,   245,  -143,  -143,  -143,   141,
     141,  -143,   164,   141,  -143,   300,   232,  -143,  -143,  -143,
    -143,  -143,   273,   236,   238,   141,  -143,  -143,  -143
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,    14,     5,     0,     0,
       0,     6,    23,     4,     0,    15,     2,     0,     0,    43,
       0,     0,    95,     7,    67,     0,    24,    26,     0,    48,
      22,    21,    18,    19,    20,     0,     0,    68,     0,    25,
       0,     0,    44,    46,    54,    57,    13,    51,     0,    52,
       0,    17,     0,     0,     0,     0,    36,     0,     0,    37,
       0,     0,    29,    30,    28,     0,     0,     0,    45,     0,
       0,    49,    50,    14,    14,    16,     0,   116,    96,     0,
       0,   106,   108,    88,    89,     0,    86,     0,    72,    73,
      74,    75,    76,    77,    78,    79,     0,     0,     0,    34,
       0,     0,     0,     0,    27,    11,    10,     8,     0,    59,
      59,     0,     0,     0,    70,     0,     0,   101,     0,    71,
       0,     0,     0,     0,     0,     0,    81,     0,    69,     0,
       0,    32,    33,     0,    38,    42,    39,    47,     0,     0,
      58,    53,    12,    56,     0,   155,     0,     0,     0,     0,
       0,   152,   158,     0,   133,   138,   151,     0,     0,     0,
       0,     0,   168,   168,     0,    80,    84,     0,   168,     0,
       0,     0,    40,     0,    65,     0,    62,     0,     0,     0,
     160,     0,   164,   162,   161,   163,     0,     0,   165,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   111,   102,    98,     0,   109,   170,     0,
       0,    94,     0,     0,     0,     0,    35,    41,    66,     0,
      60,     0,     0,    55,   168,   159,   167,     0,   168,   124,
     121,   117,   120,   131,   132,   130,   129,   128,   127,   136,
     134,   135,   137,   144,   141,   142,   139,   140,   145,   146,
     147,   148,   149,   150,   143,     0,    71,    71,   107,    71,
       0,    91,    93,     0,    82,    87,    31,    61,    63,    64,
       0,     0,     0,     0,     0,     0,   119,   115,   114,     0,
     104,    99,   110,   169,    85,     0,   157,   166,   154,    71,
      71,   118,     0,    71,   103,   104,     0,   125,   122,   112,
     105,   100,    83,     0,     0,    71,   126,   123,   113
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -143,  -143,  -143,  -143,  -143,  -143,   -54,   254,   317,  -143,
    -143,   -20,  -143,  -143,   303,   -62,  -143,  -143,  -143,   235,
     -89,  -143,  -143,   290,  -143,   288,  -143,  -143,   294,  -143,
    -143,   237,  -143,   113,  -143,  -143,   233,  -143,  -117,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,    -7,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,    44,  -143,  -143,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,  -143,   109,
    -143,  -143,  -143,  -143,  -112,    50,   -19,    53,  -143,  -143,
    -143,  -142
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    10,    17,    41,   111,   112,    12,
      15,   152,    19,    26,    27,    61,    62,    63,    98,    99,
      64,    29,    42,    43,    46,    47,    48,    69,    49,    50,
      70,   139,   175,   176,   177,   178,    23,    53,    87,    88,
     167,   295,   222,    89,   127,   121,   122,    90,    37,    91,
     118,   267,   305,   158,   266,   304,    92,   119,    93,   120,
     269,    94,   265,   315,   289,    95,   115,   285,   241,   242,
     284,   314,   283,   313,   218,   154,   155,   156,   189,   181,
     237,   219
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,    97,   160,   153,   101,   108,   159,   129,   161,    76,
      24,   173,   165,    22,    77,   131,    52,   287,    60,   124,
      78,   220,    79,     7,    80,    30,   224,    65,     4,    31,
      32,    33,    34,   117,    56,    81,   288,   100,   186,   125,
      44,    82,   197,   126,    97,   213,    66,    60,    67,    45,
      66,     8,     5,   -97,   270,   223,     3,   134,    83,    57,
     270,   271,    84,    85,   105,   106,   -97,   272,   170,     9,
     -97,   -97,   -97,   -97,    30,    13,    60,    40,    31,    32,
      33,    34,   -97,   136,   174,    58,   198,   199,   -97,    59,
     233,    16,   280,   229,   200,    14,   282,   -71,    54,   230,
     -97,    40,   270,    18,   268,    24,    86,    20,   -97,   275,
      60,   270,   -97,   172,    -9,    21,    -9,   270,   296,   228,
      55,    -9,    22,    28,   298,   281,   -97,   187,    30,  -153,
     -97,   188,    31,    32,    33,    34,    25,    56,   239,    66,
      36,   130,   278,   279,    40,    38,    22,    77,   201,   290,
     291,   227,   292,   202,    51,    79,   217,    80,   293,    60,
      73,   294,    57,   276,   203,    74,    75,   104,    81,   114,
     240,    96,   102,   309,    82,   174,   164,   302,   249,   250,
     251,   252,   307,   308,   107,   103,   310,   109,    58,   128,
     -90,    83,    59,   110,   312,    84,    85,   180,   318,   182,
     183,   184,   185,    30,   116,    60,   -92,    31,    32,    33,
      34,    60,    60,   123,   204,   205,   133,   137,   191,   206,
     192,   240,   207,   208,   209,   135,   210,   211,   212,   190,
     138,   193,   194,   195,   196,   191,   162,   192,   141,    86,
     215,   243,   244,   245,   246,   247,   248,   143,   193,   194,
     195,   196,   157,   144,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,    30,   163,   166,   168,
      31,    32,    33,    34,   169,   179,  -156,   214,   191,   216,
     192,   221,   145,   191,   225,   192,   226,    66,   146,   234,
     231,   193,   194,   195,   196,   232,   193,   194,   195,   196,
     147,   236,   238,   273,   299,   191,   300,   192,   148,    30,
     301,   303,   149,    31,    32,    33,    34,   306,   193,   194,
     195,   196,   191,    11,   192,   316,   150,   317,   113,    39,
     151,   274,    68,   132,    71,   193,   194,   195,   196,   191,
      72,   192,   277,   171,   191,   142,   192,   140,   297,   311,
     286,     0,   193,   194,   195,   196,     0,   193,   194,   195,
     196,     0,     0,   235
};

static const yytype_int16 yycheck[] =
{
      20,    55,   119,   115,    58,    67,   118,    96,   120,     1,
      17,    32,   124,     5,     6,    12,    36,    10,    38,    72,
      12,   163,    14,    89,    16,    34,   168,     1,     1,    38,
      39,    40,    41,     1,    43,    27,    29,    57,   150,    92,
      15,    33,    23,    96,    98,   157,    88,    67,    90,    24,
      88,    98,    25,    21,    88,   167,     0,    95,    50,    68,
      88,    95,    54,    55,    88,    89,    34,    95,   130,     7,
      38,    39,    40,    41,    34,    89,    96,    98,    38,    39,
      40,    41,    50,   103,   138,    94,    67,    68,    56,    98,
     179,    92,   234,    89,    75,    98,   238,    89,     4,    95,
      68,    98,    88,    30,   216,   112,    98,    71,    76,    95,
     130,    88,    80,   133,    88,    98,    90,    88,    95,   173,
      26,    95,     5,    32,    95,   237,    94,    92,    34,    94,
      98,    96,    38,    39,    40,    41,    98,    43,    98,    88,
      71,    90,   231,   232,    98,    71,     5,     6,     3,   266,
     267,   171,   269,     8,    89,    14,     9,    16,   270,   179,
      89,   273,    68,   225,    19,    89,    89,    89,    27,    89,
     190,    96,    93,     9,    33,   229,   123,   289,   197,   198,
     199,   200,   299,   300,    98,    93,   303,    98,    94,    89,
      94,    50,    98,    98,   306,    54,    55,   144,   315,   146,
     147,   148,   149,    34,    98,   225,    94,    38,    39,    40,
      41,   231,   232,    94,    69,    70,    93,    89,    71,    74,
      73,   241,    77,    78,    79,    98,    81,    82,    83,    22,
      94,    84,    85,    86,    87,    71,    94,    73,    89,    98,
      28,   191,   192,   193,   194,   195,   196,    89,    84,    85,
      86,    87,    72,    21,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,    34,    94,    98,    94,
      38,    39,    40,    41,    97,    90,    94,    28,    71,    31,
      73,    95,    50,    71,    22,    73,    89,    88,    56,    94,
      90,    84,    85,    86,    87,    90,    84,    85,    86,    87,
      68,    98,    94,    72,    90,    71,    90,    73,    76,    34,
      12,    11,    80,    38,    39,    40,    41,    72,    84,    85,
      86,    87,    71,     6,    73,    89,    94,    89,    74,    26,
      98,    97,    42,    98,    46,    84,    85,    86,    87,    71,
      46,    73,   229,    68,    71,   112,    73,   110,    97,   305,
     241,    -1,    84,    85,    86,    87,    -1,    84,    85,    86,
      87,    -1,    -1,    95
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   100,   101,     0,     1,    25,   102,    89,    98,     7,
     103,   107,   108,    89,    98,   109,    92,   104,    30,   111,
      71,    98,     5,   135,   146,    98,   112,   113,    32,   120,
      34,    38,    39,    40,    41,   110,    71,   147,    71,   113,
      98,   105,   121,   122,    15,    24,   123,   124,   125,   127,
     128,    89,   110,   136,     4,    26,    43,    68,    94,    98,
     110,   114,   115,   116,   119,     1,    88,    90,   122,   126,
     129,   124,   127,    89,    89,    89,     1,     6,    12,    14,
      16,    27,    33,    50,    54,    55,    98,   137,   138,   142,
     146,   148,   155,   157,   160,   164,    96,   105,   117,   118,
     110,   105,    93,    93,    89,    88,    89,    98,   114,    98,
      98,   106,   107,   106,    89,   165,    98,     1,   149,   156,
     158,   144,   145,    94,    72,    92,    96,   143,    89,   119,
      90,    12,   118,    93,    95,    98,   110,    89,    94,   130,
     130,    89,   135,    89,    21,    50,    56,    68,    76,    80,
      94,    98,   110,   173,   174,   175,   176,    72,   152,   173,
     137,   173,    94,    94,   176,   173,    98,   139,    94,    97,
     114,    68,   110,    32,   105,   131,   132,   133,   134,    90,
     176,   178,   176,   176,   176,   176,   173,    92,    96,   177,
      22,    71,    73,    84,    85,    86,    87,    23,    67,    68,
      75,     3,     8,    19,    69,    70,    74,    77,    78,    79,
      81,    82,    83,   173,    28,    28,    31,     9,   173,   180,
     180,    95,   141,   173,   180,    22,    89,   110,   105,    89,
      95,    90,    90,   119,    94,    95,    98,   179,    94,    98,
     110,   167,   168,   174,   174,   174,   174,   174,   174,   175,
     175,   175,   175,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   161,   153,   150,   173,   159,
      88,    95,    95,    72,    97,    95,   114,   132,   119,   119,
     180,   173,   180,   171,   169,   166,   168,    10,    29,   163,
     137,   137,   137,   173,   173,   140,    95,    97,    95,    90,
      90,    12,   173,    11,   154,   151,    72,   137,   137,     9,
     137,   154,   173,   172,   170,   162,    89,    89,   137
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    99,   100,   101,   102,   102,   104,   103,   105,   105,
     105,   105,   106,   107,   108,   108,   109,   109,   110,   110,
     110,   110,   110,   111,   111,   112,   112,   113,   114,   114,
     114,   115,   116,   117,   117,   118,   119,   119,   119,   119,
     119,   119,   119,   120,   120,   121,   121,   122,   123,   123,
     123,   123,   123,   124,   126,   125,   127,   129,   128,   130,
     130,   131,   131,   132,   132,   133,   134,   135,   136,   136,
     136,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     138,   139,   140,   138,   141,   138,   143,   142,   142,   142,
     144,   142,   145,   142,   142,   147,   146,   149,   150,   151,
     148,   152,   153,   148,   154,   154,   156,   155,   158,   159,
     157,   161,   162,   160,   163,   163,   165,   166,   164,   167,
     167,   169,   170,   168,   171,   172,   168,   173,   173,   173,
     173,   173,   173,   173,   174,   174,   174,   174,   174,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   176,   177,   176,   176,   178,   176,   176,   176,
     176,   176,   176,   176,   176,   179,   176,   176,   180,   180,
     180
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     0,     3,     2,     0,     3,     3,     1,
       3,     3,     2,     4,     0,     2,     5,     4,     1,     1,
       1,     1,     1,     0,     2,     2,     1,     4,     1,     1,
       1,     6,     3,     2,     1,     4,     1,     1,     3,     3,
       4,     5,     3,     0,     2,     2,     1,     4,     0,     2,
       2,     1,     1,     4,     0,     6,     4,     0,     4,     0,
       3,     3,     1,     3,     3,     1,     2,     1,     0,     3,
       3,     0,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     0,     8,     0,     6,     0,     5,     1,     1,
       0,     5,     0,     5,     4,     0,     4,     0,     0,     0,
       8,     0,     0,     7,     0,     2,     0,     5,     0,     0,
       6,     0,     0,    10,     1,     1,     0,     0,     7,     2,
       1,     0,     0,     6,     0,     0,     6,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     0,     5,     1,     0,     5,     1,     3,
       2,     2,     2,     2,     2,     0,     5,     3,     0,     3,
       1
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
#line 227 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 弹出无效的symtab */
	pop_symtab_stack();

	if (!err_occur())
	{
		NEW0(dag_forest, DAG);

		/* 该树节点的操作类型为TAIL，表示该树节点实现的是程序结束的操作。 */
		t = new_tree(TAIL, NULL, NULL, NULL);

		/* 初始化当前命名空间下的符号表 */
		t->u.generic.symtab = top_symtab_stack();
		
		/* 将AST节点挂到ast_forest后面 */
		list_append(top_ast_forest_stack(), t);

		/* generate dag forest. */
		gen_dag(top_ast_forest_stack(), dag_forest);

		pop_ast_forest_stack();
	}

	return 0;
}
#line 1696 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 3:
#line 256 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 初始化解析器 */
	parser_init();
	/* 创建系统符号表 */
	make_system_symtab();
	/* 创建全局符号表 */
	make_global_symtab();
}
#line 1709 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 4:
#line 267 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 初始化全局符号表的名称 */
	strcpy(Global_symtab->name, (yyvsp[-1].p_char));
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
#line 1731 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 6:
#line 289 "parser/spl.y" /* yacc.c:1646  */
    {
	main_env.u.main.tab = Global_symtab;
}
#line 1739 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 7:
#line 292 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1745 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 8:
#line 297 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 匹配 oCOMMA yNAME */
	p = new_symbol((yyvsp[0].p_char), DEF_UNKNOWN, TYPE_UNKNOWN);

	/* 移动到链表末尾 */
	q = (yyvsp[-2].p_symbol);
	while(q->next) {
		q = q->next;
	}

	/* 与新创建的symbol进行链接 */
	q->next = p;

	/* 永远指向头部 */
	(yyval.p_symbol) = (yyvsp[-2].p_symbol);
}
#line 1766 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 9:
#line 314 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 匹配 yNAME */
	p = new_symbol((yyvsp[0].p_char), DEF_UNKNOWN, TYPE_UNKNOWN);
	(yyval.p_symbol) = p;
}
#line 1776 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 10:
#line 319 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1782 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 11:
#line 320 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1788 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 13:
#line 328 "parser/spl.y" /* yacc.c:1646  */
    {/* 依次定义常量、自定义类型、变量以及自定义函数和过程（函数和过程不分先后顺序） */}
#line 1794 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 14:
#line 332 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1800 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 15:
#line 333 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1806 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 16:
#line 338 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 命名 */
	strncpy((yyvsp[-1].p_symbol)->name, (yyvsp[-3].p_char), NAME_LEN);
	/* 放入符号表 */
	add_symbol_to_table(top_symtab_stack(), (yyvsp[-1].p_symbol));
}
#line 1817 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 17:
#line 345 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 命名 */
	strncpy((yyvsp[-1].p_symbol)->name, (yyvsp[-3].p_char), NAME_LEN);
	/* 放入符号表 */
	add_symbol_to_table(top_symtab_stack(), (yyvsp[-1].p_symbol));
}
#line 1828 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 18:
#line 355 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 符号 */
	p = new_symbol("$$$", DEF_CONST, TYPE_INTEGER);

	/* 符号值 */
	p->v.i = (yyvsp[0].num);

	(yyval.p_symbol) = p;
}
#line 1842 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 19:
#line 365 "parser/spl.y" /* yacc.c:1646  */
    {
	p = new_symbol("$$$",DEF_CONST, TYPE_REAL);

	/* 字符串转化为浮点数 */
	p->v.f = atof((yyvsp[0].p_char));

	(yyval.p_symbol) = p;
}
#line 1855 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 20:
#line 374 "parser/spl.y" /* yacc.c:1646  */
    {
	p = new_symbol("$$$", DEF_CONST, TYPE_CHAR);

	p->v.c= (yyvsp[0].p_char)[1];

	(yyval.p_symbol) = p;
}
#line 1867 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 21:
#line 382 "parser/spl.y" /* yacc.c:1646  */
    {
	p = new_symbol("$$$", DEF_CONST,
		TYPE_STRING);

	p->v.s = strdup((yyvsp[0].p_char));

	(yyval.p_symbol) = p;
}
#line 1880 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 22:
#line 391 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 系统常量符号 */
	p = new_symbol("$$$", DEF_CONST, TYPE_UNKNOWN);

	switch((yyvsp[0].num))
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

	(yyval.p_symbol) = p;
}
#line 1918 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 23:
#line 427 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1924 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 24:
#line 428 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1930 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 25:
#line 432 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1936 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 26:
#line 433 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1942 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 27:
#line 438 "parser/spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-1].p_type)->name[0] == '$')
	{
		/* 全新的自定义类型符号 */
		(yyval.p_type) = (yyvsp[-1].p_type);
		/* 命名 */
		strncpy((yyval.p_type)->name, (yyvsp[-3].p_char), NAME_LEN);
	}
	else
	{
		/* 已有的自定义类型符号创建自定义类型 */
		(yyval.p_type) = clone_type((yyvsp[-1].p_type));
		/* 命名 */
		strncpy((yyval.p_type)->name, (yyvsp[-3].p_char), NAME_LEN);
		/* 添加到符号表 */
		add_type_to_table(top_symtab_stack(), (yyval.p_type));
	}
}
#line 1965 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 28:
#line 459 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1971 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 29:
#line 460 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1977 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 30:
#line 461 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 1983 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 31:
#line 466 "parser/spl.y" /* yacc.c:1646  */
    {
	(yyval.p_type) = new_array_type("$$$", (yyvsp[-3].p_type), (yyvsp[0].p_type));
	add_type_to_table(top_symtab_stack(), (yyval.p_type));
}
#line 1992 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 32:
#line 474 "parser/spl.y" /* yacc.c:1646  */
    {
	(yyval.p_type) = new_record_type("$$$", (yyvsp[-1].p_symbol));
 	add_type_to_table(top_symtab_stack(), (yyval.p_type));
}
#line 2001 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 33:
#line 482 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 指向属性符号链表的末尾 */
	for(p = (yyvsp[-1].p_symbol); p->next; p = p->next);

	/* 添加到属性符号链表末尾 */
	p->next = (yyvsp[0].p_symbol);

	(yyval.p_symbol) = (yyvsp[-1].p_symbol);
}
#line 2015 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 34:
#line 492 "parser/spl.y" /* yacc.c:1646  */
    {
	(yyval.p_symbol) = (yyvsp[0].p_symbol);
}
#line 2023 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 35:
#line 499 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 遍历名称符号表 */
	for(p = (yyvsp[-3].p_symbol); p; p = p->next) {
		/* 定义符号小类 */
		if((yyvsp[-1].p_type)->type_id == TYPE_SUBRANGE || (yyvsp[-1].p_type)->type_id == TYPE_ENUM)
		{
			/* 变量（子范围或枚举类型）的类型由其类型的成员（子范围或枚举类型中的成员）的类型定义 */
			p->type = (yyvsp[-1].p_type)->first->type;
			/* 检查子范围和枚举类型的符号值是否合法 */
			p->type_link = (yyvsp[-1].p_type);
		}
		else
		{
			p->type = (yyvsp[-1].p_type);
		}

		/* 定义符号大类 */
		p->defn = DEF_FIELD;
	}
	(yyval.p_symbol) = (yyvsp[-3].p_symbol);
}
#line 2049 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 36:
#line 524 "parser/spl.y" /* yacc.c:1646  */
    {
	/* char，integer，boolean，real, uchar, uinterger */
	pt = find_type_by_name((yyvsp[0].p_char));

	if(!pt)
		parse_error("Undeclared type name", (yyvsp[0].p_char));

	(yyval.p_type) = pt;
}
#line 2063 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 37:
#line 534 "parser/spl.y" /* yacc.c:1646  */
    {
  /* 用户自定义类型 */
	pt = find_type_by_name((yyvsp[0].p_char));

	if (!pt)
	{
		parse_error("Undeclared type name", (yyvsp[0].p_char));
		return 0;
	}

	(yyval.p_type) = pt;
}
#line 2080 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 38:
#line 547 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 枚举类型 */
	(yyval.p_type) = new_enum_type("$$$");

	/* 枚举类型的符号链表 */
	add_enum_elements((yyval.p_type), (yyvsp[-1].p_symbol));

	/* 枚举类型放入符号表 */
	add_type_to_table(top_symtab_stack(), (yyval.p_type));
}
#line 2095 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 39:
#line 558 "parser/spl.y" /* yacc.c:1646  */
    {
  /* 子范围类型的前后常量类型必须一致 */
	if((yyvsp[-2].p_symbol)->type->type_id != (yyvsp[0].p_symbol)->type->type_id)
	{
		parse_error("type mismatch", "");
		return 0;
	}
	
	/* 子范围类型 */
	(yyval.p_type) = new_subrange_type("$$$", (yyvsp[-2].p_symbol)->type->type_id);

	/* 子范围类型放入符号表 */
	add_type_to_table(top_symtab_stack(), (yyval.p_type));

	/* 子范围类型的上下界 */
	if((yyvsp[-2].p_symbol)->type->type_id == TYPE_INTEGER)
		set_subrange_bound((yyval.p_type), (int)(yyvsp[-2].p_symbol)->v.i, (int)(yyvsp[0].p_symbol)->v.i);
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_BOOLEAN)
		set_subrange_bound((yyval.p_type), (int)(yyvsp[-2].p_symbol)->v.b, (int)(yyvsp[0].p_symbol)->v.b);
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_CHAR)
		set_subrange_bound((yyval.p_type), (int)(yyvsp[-2].p_symbol)->v.c, (int)(yyvsp[0].p_symbol)->v.c);
	else
		parse_error("invalid element type of subrange","");
}
#line 2124 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 40:
#line 583 "parser/spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-2].p_symbol)->type->type_id != (yyvsp[0].p_symbol)->type->type_id){
		parse_error("type mismatch","");
		return 0;
	}

	(yyval.p_type) = new_subrange_type("$$$", (yyvsp[-2].p_symbol)->type->type_id);
		
	add_type_to_table(top_symtab_stack(), (yyval.p_type));

	if((yyvsp[-2].p_symbol)->type->type_id == TYPE_INTEGER){
		/* 转化为负数 */
		(yyvsp[-2].p_symbol)->v.i = -(yyvsp[-2].p_symbol)->v.i;
		set_subrange_bound((yyval.p_type), (int)(yyvsp[-2].p_symbol)->v.i, (int)(yyvsp[0].p_symbol)->v.i);
	}
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_BOOLEAN){
		/* 1转化为0，0转化为1 */
		(yyvsp[-2].p_symbol)->v.b ^= 1;
		set_subrange_bound((yyval.p_type), (int)(yyvsp[-2].p_symbol)->v.b,(int)(yyvsp[0].p_symbol)->v.b);
	}
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_CHAR)
		parse_error("invalid operator", "");
	else
   		parse_error("invalid element type of subrange", "");
}
#line 2154 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 41:
#line 609 "parser/spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-3].p_symbol)->type->type_id != (yyvsp[0].p_symbol)->type->type_id) {
		parse_error("type mismatch", "");
		return  0;
	}
	
	(yyval.p_type) = new_subrange_type("$$$", (yyvsp[-3].p_symbol)->type->type_id);

	add_type_to_table(top_symtab_stack(), (yyval.p_type));

	if((yyvsp[-3].p_symbol)->type->type_id == TYPE_INTEGER){
		(yyvsp[-3].p_symbol)->v.i = -(yyvsp[-3].p_symbol)->v.i;
		(yyvsp[0].p_symbol)->v.i = -(yyvsp[0].p_symbol)->v.i;
	
		set_subrange_bound((yyval.p_type), (int)(yyvsp[-3].p_symbol)->v.i, (int)(yyvsp[0].p_symbol)->v.i);
	}
	else if ((yyvsp[-3].p_symbol)->type->type_id == TYPE_BOOLEAN){
		(yyvsp[-3].p_symbol)->v.b ^= 1;
		(yyvsp[0].p_symbol)->v.b ^= 1;

		set_subrange_bound((yyval.p_type), (int)(yyvsp[-3].p_symbol)->v.b, (int)(yyvsp[0].p_symbol)->v.b);
	}
	else if ((yyvsp[-3].p_symbol)->type->type_id == TYPE_CHAR)
		parse_error("invalid operator", "");
	else
		parse_error("invalid element type of subrange", "");
}
#line 2186 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 42:
#line 637 "parser/spl.y" /* yacc.c:1646  */
    {
	
	/* 符号（枚举） */
	p = find_symbol(top_symtab_stack(), (yyvsp[-2].p_char));
	if(!p){
		parse_error("Undeclared identifier", (yyvsp[-2].p_char));
		install_temporary_symbol((yyvsp[-2].p_char), DEF_ENUM_ELEMENT, TYPE_INTEGER);
	}
	if(p->defn != DEF_ENUM_ELEMENT){
		parse_error("not an element identifier", (yyvsp[-2].p_char));
	}
	
	/* 符号（枚举） */
	q = find_symbol(top_symtab_stack(), (yyvsp[0].p_char));
	if(!q){
		parse_error("Undeclared identifier", (yyvsp[0].p_char));
		install_temporary_symbol((yyvsp[0].p_char), DEF_ENUM_ELEMENT, TYPE_INTEGER);
	}
	if(q->defn != DEF_ENUM_ELEMENT){
		parse_error("Not an element identifier", (yyvsp[0].p_char));
	}
	
	/* 子范围类型 */
	(yyval.p_type) = new_subrange_type("$$$", TYPE_INTEGER);
	/* 添加到符号表 */
	add_type_to_table(top_symtab_stack(), (yyval.p_type));
	/* 子范围类型的上下界 */
	set_subrange_bound((yyval.p_type), p->v.i, q->v.i);
}
#line 2220 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 43:
#line 669 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2226 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 44:
#line 670 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2232 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 45:
#line 674 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2238 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 46:
#line 675 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2244 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 47:
#line 680 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 对应的符号表 */
	ptab = top_symtab_stack();
	
	/* 遍历名称符号链表 */
	for(p = (yyvsp[-3].p_symbol); p;){
		if((yyvsp[-1].p_type)->type_id == TYPE_SUBRANGE || (yyvsp[-1].p_type)->type_id == TYPE_ENUM)
		{
			/* 变量（子范围以及枚举类型）的类型是由其类型中的成员（子范围或者枚举类型的成员）的类型定义 */
			p->type = (yyvsp[-1].p_type)->first->type;
			p->type_link = (yyvsp[-1].p_type);
		}
		else
		{
			p->type = (yyvsp[-1].p_type);
		}

		/* 定义符号大类 */
		p->defn = DEF_VAR;

		q = p; 
		p = p->next;
		q->next = NULL;

		/* 添加到符号表中 */
		add_symbol_to_table(ptab, q);
	}
}
#line 2277 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 49:
#line 712 "parser/spl.y" /* yacc.c:1646  */
    { }
#line 2283 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 50:
#line 713 "parser/spl.y" /* yacc.c:1646  */
    { }
#line 2289 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 51:
#line 714 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2295 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 52:
#line 715 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2301 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 53:
#line 720 "parser/spl.y" /* yacc.c:1646  */
    {
	if (!err_occur())
	{
		NEW0(dag_forest, DAG);

		/* 终点AST节点 */
		t = new_tree(TAIL, NULL, NULL, NULL);
		/* 对应的符号表 */
		t->u.generic.symtab = top_symtab_stack();
		/* 放入AST森林 */
		list_append(top_ast_forest_stack(), t);

		/* 生成AST森林 */
		gen_dag(top_ast_forest_stack(), dag_forest);

		/*  */
		pop_ast_forest_stack();

		/*  */
		list_append(&routine_forest, dag_forest->link);
	}

	/* 弹出函数对应的符号表 */
	pop_symtab_stack();
}
#line 2331 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 54:
#line 749 "parser/spl.y" /* yacc.c:1646  */
    {
	/* AST森林 */
	NEW0(ast_forest, TREE);
	push_ast_forest_stack(ast_forest);

	if(top_symtab_stack() != Global_symtab)
	{
		parse_error("can not def function in function", "");
		return 0;
	}

	/* 创建符号表 */
	ptab = new_symtab(Global_symtab);

	/* 记录自定义函数 */
	add_routine_to_table(top_symtab_stack(), ptab);

	/* 符号表压栈 */
	push_symtab_stack(ptab);
}
#line 2356 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 55:
#line 770 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 对应的符号表 */
	ptab = top_symtab_stack();

	/* 符号表命名 */
	strncpy(ptab->name, (yyvsp[-3].p_char), NAME_LEN);

	/* 符号表的汇编名称命名 */
	sprintf(ptab->rname, "rtn%03d", ptab->id);

	/* 符号表大类 */
	ptab->defn = DEF_FUNCT;
	
	/* 符号表小类 */
	if((yyvsp[0].p_type)->type_id == TYPE_SUBRANGE || (yyvsp[0].p_type)->type_id == TYPE_ENUM)
	{
		ptab->type = (yyvsp[0].p_type)->first->type;
		/* 当函数返回值为子范围或枚举时，需要检查返回值是否合法 */
		p->type_link = (yyvsp[0].p_type);
	}
	else
	{
		ptab->type = (yyvsp[0].p_type);
	}

	/* 函数符号 */
	p = new_symbol((yyvsp[-3].p_char), DEF_FUNCT, ptab->type->type_id);
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
#line 2402 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 56:
#line 815 "parser/spl.y" /* yacc.c:1646  */
    {

	if (!err_occur())
	{
		NEW0(dag_forest, DAG);

		t = new_tree(TAIL, NULL, NULL, NULL);
		t->u.generic.symtab = top_symtab_stack();
		list_append(top_ast_forest_stack(), t);

		gen_dag(top_ast_forest_stack(), dag_forest);
  
		pop_ast_forest_stack();;

		list_append(&routine_forest, dag_forest->link);
	}
	pop_symtab_stack();
}
#line 2425 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 57:
#line 837 "parser/spl.y" /* yacc.c:1646  */
    {
	NEW0(ast_forest, TREE);
	push_ast_forest_stack(ast_forest);

	if(top_symtab_stack() != Global_symtab)
	{
		parse_error("can not def function in function", "");
		return 0;
	}

	ptab = new_symtab(Global_symtab);

	add_routine_to_table(top_symtab_stack(), ptab);

	push_symtab_stack(ptab);
}
#line 2446 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 58:
#line 854 "parser/spl.y" /* yacc.c:1646  */
    {
	ptab = top_symtab_stack();
	strncpy(ptab->name, (yyvsp[-1].p_char), NAME_LEN);
	sprintf(ptab->rname, "rtn%03d", ptab->id);
	ptab->defn = DEF_PROC;

	p = new_symbol((yyvsp[-1].p_char), DEF_PROC, TYPE_VOID);
	add_symbol_to_table(ptab, p);
	reverse_parameters(ptab);

	Tree header;
	header = new_tree(HEADER, find_type_by_id(TYPE_VOID), NULL, NULL);
	list_append(top_ast_forest_stack(), header);
}
#line 2465 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 59:
#line 871 "parser/spl.y" /* yacc.c:1646  */
    {/* 参数部分可以为空 */}
#line 2471 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 60:
#line 872 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2477 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 61:
#line 876 "parser/spl.y" /* yacc.c:1646  */
    {/* 不同类型的参数之间使用符号';'进行分割 */}
#line 2483 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 62:
#line 877 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2489 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 63:
#line 882 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 对应的符号表 */
	ptab = top_symtab_stack();

	/* 遍历名称符号链表 */
	for(p = (yyvsp[-2].p_symbol); p;)
	{
		if((yyvsp[0].p_type)->type_id == TYPE_SUBRANGE || (yyvsp[0].p_type)->type_id == TYPE_ENUM)
		{
			p->type = (yyvsp[0].p_type)->first->type;
			p->type_link = (yyvsp[0].p_type);
		}
		else
		{
			p->type = (yyvsp[0].p_type);
		}
		
		p->defn = DEF_VALPARA;
		
		q = p; 
		p = p->next;
		q->next = NULL;

		/* 放入符号表中 */
		add_symbol_to_table(ptab, q);
	}
}
#line 2521 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 64:
#line 910 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 对应的符号表 */
	ptab = top_symtab_stack();

	/* 遍历名称符号链表 */
	for(p = (yyvsp[-2].p_symbol); p;)
	{
		if((yyvsp[0].p_type)->type_id == TYPE_SUBRANGE || (yyvsp[0].p_type)->type_id == TYPE_ENUM)
		{
			p->type = (yyvsp[0].p_type)->first->type;
			p->type_link = (yyvsp[0].p_type);
		}
		else
		{
			p->type = (yyvsp[0].p_type);
		}
		
		p->defn = DEF_VARPARA;

		q = p; p = p->next;
		q->next=NULL;

		/* 放入符号表中 */
		add_symbol_to_table(ptab, q);
	}
}
#line 2552 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 65:
#line 940 "parser/spl.y" /* yacc.c:1646  */
    { 
	(yyval.p_symbol) = (yyvsp[0].p_symbol);
}
#line 2560 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 66:
#line 947 "parser/spl.y" /* yacc.c:1646  */
    {
	(yyval.p_symbol) = (yyvsp[0].p_symbol);
}
#line 2568 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 67:
#line 953 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2574 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 68:
#line 957 "parser/spl.y" /* yacc.c:1646  */
    {/* 可以是空函数 */}
#line 2580 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 69:
#line 958 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2586 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 70:
#line 959 "parser/spl.y" /* yacc.c:1646  */
    {/* 错误处理 */}
#line 2592 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 71:
#line 964 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2598 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 72:
#line 965 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2604 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 73:
#line 966 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2610 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 74:
#line 967 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2616 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 75:
#line 968 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2622 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 76:
#line 969 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2628 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 77:
#line 970 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2634 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 78:
#line 971 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2640 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 79:
#line 972 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 2646 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 80:
#line 977 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 对应的符号 */
	p = find_symbol(top_symtab_stack(), (yyvsp[-2].p_char));
	if (p == NULL)
	{
		parse_error("undeclared identifier.", (yyvsp[-2].p_char));
		install_temporary_symbol((yyvsp[-2].p_char), DEF_VAR, (yyvsp[0].p_tree)->result_type->type_id);
	}

	/* 检查赋值是否合法 */
	if(p->type->type_id == TYPE_RECORD)
	{
		parse_error("lvalue expected", "");
	}
	if(p->type->type_id == TYPE_ARRAY)
	{
		if((yyvsp[0].p_tree)->result_type->type_id != TYPE_STRING)
		{
			parse_error("lvalue expected", "");
		}
	}

	/* 类型检查 */
	if((p->type->type_id != (yyvsp[0].p_tree)->result_type->type_id) &&
	(p->type->type_id != TYPE_ARRAY || p->type->last->type->type_id != TYPE_CHAR || (yyvsp[0].p_tree)->result_type->type_id != TYPE_STRING))
	{
		parse_error("type mismatch", "");
		return 0;  
	}


	/* 地址AST树 */
	t = address_tree(p);
	/* 赋值AST树 */
	(yyval.p_tree) = assign_tree(t, (yyvsp[0].p_tree));
	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), (yyval.p_tree));
}
#line 2689 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1016 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 对应的符号 */
	p = find_symbol(top_symtab_stack(), (yyvsp[-1].p_char));
	if(p == NULL)
	{
		parse_error("undefined identifier", (yyvsp[-1].p_char));
		return 0;
	}
	
	/* 检查赋值是否合法 */
	if(p->type->type_id != TYPE_ARRAY)
	{
		parse_error("var type mismatch", (yyvsp[-1].p_char));
		return 0;
	}
	
	push_term_stack(p);
}
#line 2712 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1035 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 获取符号 */
	p = top_term_stack();
	
	/* 数组AST节点 */
	t = array_index_tree(p, (yyvsp[-1].p_tree));

	push_ast_stack(t);
}
#line 2726 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1045 "parser/spl.y" /* yacc.c:1646  */
    {
	t = pop_ast_stack();

	/* 赋值AST节点 */
	(yyval.p_tree) = assign_tree(t, (yyvsp[0].p_tree));

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), (yyval.p_tree));
}
#line 2740 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1055 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 对应的符号 */
	p = find_symbol(top_symtab_stack(), (yyvsp[-2].p_char));
	if(!p || p->type->type_id != TYPE_RECORD){
		parse_error("Undeclared record vaiable", (yyvsp[-2].p_char));
		return 0;
	}

	/* 对应的属性 */
	q = find_field(p, (yyvsp[0].p_char));
	if(!q || q->defn != DEF_FIELD){
		parse_error("Undeclared field", (yyvsp[0].p_char));
		return 0;
	}


	/* 属性AST节点 */
	t = record_field_tree(p, q);

	push_ast_stack(t);
}
#line 2766 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1077 "parser/spl.y" /* yacc.c:1646  */
    {
	t = pop_ast_stack();

	/* 赋值AST节点 */
	(yyval.p_tree) = assign_tree(t, (yyvsp[0].p_tree));

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), (yyval.p_tree));
}
#line 2780 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1090 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 寻找自定义函数或者过程 */
	if((ptab = find_routine(top_symtab_stack(), (yyvsp[0].p_char))))
	{
		push_call_stack(ptab);
	}
  		
	else
	{
		parse_error("Undeclared funtion", (yyvsp[0].p_char));
		return  0;
	}
}
#line 2798 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1104 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 函数或过程调用AST节点 */
	(yyval.p_tree) = call_tree(top_call_stack(), args);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), (yyval.p_tree));

	pop_call_stack();
}
#line 2812 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1114 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 系统函数或者系统过程调用AST节点 */
	(yyval.p_tree) = sys_tree((yyvsp[0].p_lex)->attr, NULL);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), (yyval.p_tree));
}
#line 2824 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1122 "parser/spl.y" /* yacc.c:1646  */
    {
	(yyval.p_tree) = sys_tree((yyvsp[0].p_lex)->attr, NULL);

	list_append(top_ast_forest_stack(), (yyval.p_tree));
}
#line 2834 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1128 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 对应的系统函数或者系统过程的符号表 */
	rtn = find_sys_routine((yyvsp[0].p_lex)->attr);

	push_call_stack(rtn);
}
#line 2845 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1135 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 系统函数或者系统过程调用AST节点 */
	(yyval.p_tree) = sys_tree((yyvsp[-4].p_lex)->attr, args);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), (yyval.p_tree));

	pop_call_stack();
}
#line 2859 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1145 "parser/spl.y" /* yacc.c:1646  */
    {
	rtn = find_sys_routine((yyvsp[0].p_lex)->attr);

	push_call_stack(rtn);
}
#line 2869 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1151 "parser/spl.y" /* yacc.c:1646  */
    {
	(yyval.p_tree) = sys_tree((yyvsp[-4].p_lex)->attr, args);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), (yyval.p_tree));

	pop_call_stack();
}
#line 2882 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1160 "parser/spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-1].p_tree) == NULL){
		parse_error("too few parameters in call to", "read");
		return 0;
	}
	
	if (generic((yyvsp[-1].p_tree)->op) == LOAD)
	{
		if((yyvsp[-1].p_tree)->kids[0]) /* 数组或者记录 */
		{
			t = (yyvsp[-1].p_tree)->kids[0];
		}
		else
		{
			t = address_tree((yyvsp[-1].p_tree)->u.generic.sym);
		}
	}
	else
	{
		parse_error("pread need a variable argument", "");
		return 0;
	}

	/* 系统函数或者系统过程调用AST节点 */
	(yyval.p_tree) = sys_tree((yyvsp[-3].p_lex)->attr, t);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), (yyval.p_tree));
}
#line 2916 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1193 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 开始块AST节点 */
	t = new_tree(BLOCKBEG, NULL, NULL, NULL);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), t);
}
#line 2928 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1202 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 结束块AST节点 */
	t = new_tree(BLOCKEND, NULL, NULL, NULL);

	/* 放入AST森林 */
	list_append(top_ast_forest_stack(), t);
}
#line 2940 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1213 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 记录标签层级 */
	push_lbl_stack(if_label_count++);
}
#line 2949 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1218 "parser/spl.y" /* yacc.c:1646  */
    {
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_false_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（ELSE子句的入口） */
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 条件跳转AST节点（条件为假时跳转到ELSE标签的入口） */
	t = cond_jump_tree((yyvsp[-1].p_tree), false, new_label);
	list_append(top_ast_forest_stack(), t);
}
#line 2963 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1228 "parser/spl.y" /* yacc.c:1646  */
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
#line 2990 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1251 "parser/spl.y" /* yacc.c:1646  */
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
#line 3005 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1262 "parser/spl.y" /* yacc.c:1646  */
    {
	printf("expression expected.\n");
}
#line 3013 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1266 "parser/spl.y" /* yacc.c:1646  */
    {
	printf("then matched.\n");
}
#line 3021 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1273 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 3027 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1274 "parser/spl.y" /* yacc.c:1646  */
    {}
#line 3033 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1279 "parser/spl.y" /* yacc.c:1646  */
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
#line 3048 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1290 "parser/spl.y" /* yacc.c:1646  */
    {
	snprintf(mini_buf, sizeof(mini_buf) - 1, "repeat_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（REPEAT结构的入口） */
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 条件跳转AST节点（条件为真时，跳转到REPEAT结构的入口） */
	t = cond_jump_tree((yyvsp[0].p_tree), false, new_label);
	list_append(top_ast_forest_stack(), t);

	pop_lbl_stack();
}
#line 3064 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1305 "parser/spl.y" /* yacc.c:1646  */
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
#line 3080 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1317 "parser/spl.y" /* yacc.c:1646  */
    {
	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（WHILE结构的出口） */
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 条件跳转AST节点（条件为假时，跳转到WHILE结构的出口） */
	t = cond_jump_tree((yyvsp[-1].p_tree), false, exit_label);

	list_append(top_ast_forest_stack(), t);
}
#line 3095 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1328 "parser/spl.y" /* yacc.c:1646  */
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
#line 3122 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1354 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 变量对应的符号 */
	p = find_symbol(top_symtab_stack(), (yyvsp[-2].p_char));
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
	list_append(top_ast_forest_stack(), assign_tree(t, (yyvsp[0].p_tree)));

	push_lbl_stack(for_label_count++);
	snprintf(mini_buf, sizeof(mini_buf) - 1, "for_test_%d", for_label_count - 1);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（FOR结构的入口） */
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 标签AST节点（FOR结构的入口） */
	t = label_tree(test_label);
	list_append(top_ast_forest_stack(), t);
}
#line 3160 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1388 "parser/spl.y" /* yacc.c:1646  */
    {
	snprintf(mini_buf, sizeof(mini_buf) - 1, "for_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（FOR结构的出口） */
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 变量对应的符号 */
	p = find_symbol(top_symtab_stack(), (yyvsp[-6].p_char));
	/* 取值AST节点（获取变量的值） */
	t = id_factor_tree(NULL, p);

	if ((yyvsp[-2].num) == kTO)
	{
		if(t->result_type->type_id != (yyvsp[-1].p_tree)->result_type->type_id)
		{
			parse_error("type mismatch", "");
			return 0;
		}

		/* 比较AST节点 */
		t = compare_expr_tree(LE, t, (yyvsp[-1].p_tree));
	}
	else
	{
		if(t->result_type->type_id != (yyvsp[-1].p_tree)->result_type->type_id)
		{
			parse_error("type mismatch", "");
			return 0;
		}

		t = compare_expr_tree(GE, t, (yyvsp[-1].p_tree));
	}

	/* 条件跳转AST节点（条件为假时，跳转到FOR结构的出口） */
	t = cond_jump_tree(t, false, exit_label);
	list_append(top_ast_forest_stack(), t);
}
#line 3201 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1425 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 获取地址AST节点（FOR中条件判断相关的变量） */
	t = pop_ast_stack();

	if ((yyvsp[-4].num) == kTO)
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
#line 3240 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1463 "parser/spl.y" /* yacc.c:1646  */
    {
	(yyval.num) = kTO;
}
#line 3248 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1467 "parser/spl.y" /* yacc.c:1646  */
    {
	(yyval.num) = kDOWNTO;
}
#line 3256 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1474 "parser/spl.y" /* yacc.c:1646  */
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
#line 3277 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1491 "parser/spl.y" /* yacc.c:1646  */
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
		if((yyvsp[-2].p_tree)->result_type->type_id != cases[i + 1]->result_type->type_id)
		{
			parse_error("type mismatch", "");
			return 0;
		}
		t = compare_expr_tree(EQ, (yyvsp[-2].p_tree), cases[i + 1]);
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
#line 3323 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1542 "parser/spl.y" /* yacc.c:1646  */
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
	t = const_tree((yyvsp[0].p_symbol));
	/* 将常数AST节点（CASE子句判断条件）放入CASE子句链表 */
	list_append(case_list, t);
}
#line 3350 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1565 "parser/spl.y" /* yacc.c:1646  */
    {
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	/* 标签符号（CASE结构的出口） */
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	/* 跳转AST节点（CASE结构的出口） */
	t = jump_tree(exit_label);
	list_append(top_ast_forest_stack(), t);
}
#line 3364 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1576 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 变量对应的符号 */
	p = find_symbol(top_symtab_stack(),(yyvsp[0].p_char));
	if(!p){
			parse_error("Undeclared identifier",(yyvsp[0].p_char));
			install_temporary_symbol((yyvsp[0].p_char), DEF_CONST, TYPE_INTEGER);
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
#line 3397 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1605 "parser/spl.y" /* yacc.c:1646  */
    {
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = jump_tree(exit_label);
	list_append(top_ast_forest_stack(), t);
}
#line 3409 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1617 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（>=），由于优先级问题，放在expr表达式中（expression表达式中的运算优先级比expr中的要低），仅支持左结合 */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch >=", "");
		return 0;
	}

	(yyval.p_tree) = compare_expr_tree(GE, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3424 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1628 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（>） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch >", "");
		return 0;
	}

	(yyval.p_tree) = compare_expr_tree(GT, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3439 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1639 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（<=） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch <=", "");
		return 0;
	}

	(yyval.p_tree) = compare_expr_tree(LE, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3454 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1650 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（<） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch <", "");
		return 0;
	}

	(yyval.p_tree) = compare_expr_tree(LT, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3469 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1661 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（=） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch =", "");
		return 0;
	}

	(yyval.p_tree) = compare_expr_tree(EQ, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3484 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1672 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（!=，不相等） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch !=", "");
		return 0;
	}

	(yyval.p_tree) = compare_expr_tree(NE, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3499 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1683 "parser/spl.y" /* yacc.c:1646  */
    {
	(yyval.p_tree) = (yyvsp[0].p_tree);
}
#line 3507 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1690 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（+），由于优先级问题，放在expr表达式中（expr表达式中的运算优先级比term中的要低），仅支持左结合 */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch +", "");
		return 0;
	}

	(yyval.p_tree) = binary_expr_tree(ADD, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3522 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1701 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（-） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch -", "");
		return 0;
	}

	(yyval.p_tree) = binary_expr_tree(SUB, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3537 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1712 "parser/spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-2].p_tree)->result_type->type_id != TYPE_BOOLEAN || (yyvsp[0].p_tree)->result_type->type_id != TYPE_BOOLEAN)
	{
		parse_error("type mismatch ||", "");
		return 0;
	}
	(yyval.p_tree) = binary_expr_tree(OR, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3550 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1721 "parser/spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-2].p_tree)->result_type->type_id != TYPE_BOOLEAN || (yyvsp[0].p_tree)->result_type->type_id != TYPE_BOOLEAN)
	{
		parse_error("type mismatch ||", "");
		return 0;
	}
	(yyval.p_tree) = binary_expr_tree(OR, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3563 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1730 "parser/spl.y" /* yacc.c:1646  */
    {
	(yyval.p_tree) = (yyvsp[0].p_tree);
}
#line 3571 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1737 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（*），由于优先级问题，放在expr表达式中（运算符优先级最高），仅支持左结合。 */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch *", "");
		return 0;
	}

	(yyval.p_tree) = binary_expr_tree(MUL, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3586 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1748 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（\） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch \\", "");
		return 0;
	}

	(yyval.p_tree) = binary_expr_tree(DIV, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3601 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1759 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（div） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch div", "");
		return 0;
	}

	(yyval.p_tree) = binary_expr_tree(DIV, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3616 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1770 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（mod） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch mod", "");
		return 0;
	}

	(yyval.p_tree) = binary_expr_tree(MOD, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3631 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1781 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（mod） */
	if((yyvsp[-2].p_tree)->result_type->type_id != TYPE_INTEGER || (yyvsp[0].p_tree)->result_type->type_id != TYPE_INTEGER)
	{
		parse_error("type mismatch %", "");
		return 0;
	}

	(yyval.p_tree) = binary_expr_tree(MOD, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3646 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1792 "parser/spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-2].p_tree)->result_type->type_id != TYPE_BOOLEAN || (yyvsp[0].p_tree)->result_type->type_id != TYPE_BOOLEAN)
	{
		parse_error("type mismatch &&", "");
		return 0;
	}
	(yyval.p_tree) = binary_expr_tree(AND, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3659 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1801 "parser/spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-2].p_tree)->result_type->type_id != TYPE_BOOLEAN || (yyvsp[0].p_tree)->result_type->type_id != TYPE_BOOLEAN)
	{
		parse_error("type mismatch &&", "");
		return 0;
	}
	(yyval.p_tree) = binary_expr_tree(AND, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3672 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1811 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（&） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch &", "");
		return 0;
	}

	(yyval.p_tree) = binary_expr_tree(BAND, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3687 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1822 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（|） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch |", "");
		return 0;
	}

	(yyval.p_tree) = binary_expr_tree(BOR, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3702 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1833 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（^） */
	if((yyvsp[-2].p_tree)->result_type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
	{
		parse_error("type mismatch ^", "");
		return 0;
	}
	(yyval.p_tree) = binary_expr_tree(BXOR, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3716 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1843 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（>>） */
	if((yyvsp[-2].p_tree)->result_type->type_id != TYPE_INTEGER || (yyvsp[0].p_tree)->result_type->type_id != TYPE_INTEGER)
	{
		parse_error("type mismatch >>", "");
		return 0;
	}
	(yyval.p_tree) = binary_expr_tree(RSH, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3730 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1853 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（<<） */
	if((yyvsp[-2].p_tree)->result_type->type_id != TYPE_INTEGER || (yyvsp[0].p_tree)->result_type->type_id != TYPE_INTEGER)
	{
		parse_error("type mismatch <<", "");
		return 0;
	}
	(yyval.p_tree) = binary_expr_tree(LSH, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3744 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1864 "parser/spl.y" /* yacc.c:1646  */
    {
	(yyval.p_tree) = (yyvsp[0].p_tree);
}
#line 3752 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1871 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 对应的符号 */
	p = find_symbol(top_symtab_stack(), (yyvsp[0].p_char));
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
		parse_error("Undeclard identificr", (yyvsp[0].p_char));
		p = install_temporary_symbol((yyvsp[0].p_char), DEF_VAR, TYPE_INTEGER);
	}

	/* 取值AST节点 */
	(yyval.p_tree) = id_factor_tree(NULL, p);
}
#line 3778 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1893 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 寻找自定义函数或者过程 */
	if((ptab = find_routine(top_symtab_stack(), (yyvsp[0].p_char))))
  		push_call_stack(ptab);
	else
	{
		parse_error("Undeclared funtion or procedure", (yyvsp[0].p_char));
		return  0;
	}
}
#line 3793 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1904 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 自定义函数或者过程调用AST节点 */
	(yyval.p_tree) = call_tree(top_call_stack(), args);

	pop_call_stack();
}
#line 3804 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1911 "parser/spl.y" /* yacc.c:1646  */
    {
	ptab = find_sys_routine((yyvsp[0].p_lex)->attr);

	/* 系统函数或者过程调用AST节点 */
	(yyval.p_tree) = sys_tree((yyvsp[0].p_lex)->attr, NULL);
}
#line 3815 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1918 "parser/spl.y" /* yacc.c:1646  */
    {
	ptab = find_sys_routine((yyvsp[0].p_lex)->attr);
	push_call_stack(ptab);
}
#line 3824 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1923 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 获取当前需要调用的函数或者过程对应的符号表 */
	ptab = top_call_stack();

	/* 系统函数或者过程调用（有参调用） */
	(yyval.p_tree) = sys_tree((yyvsp[-4].p_lex)->attr, args);
}
#line 3836 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1931 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 常量（term中const_value由于只在表达式中使用一次，不需要对name字段进行命名），比如表达式 1+2+3 中的 1 */
	switch((yyvsp[0].p_symbol)->type->type_id){
		case TYPE_REAL:
		case TYPE_STRING:
			/* 通过全局符号表记录常量 */
			add_symbol_to_table(Global_symtab, (yyvsp[0].p_symbol));
			break;
		case TYPE_BOOLEAN:
			/* 通过汇编名称记录常量 */
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

	/* 常量AST树 */
	(yyval.p_tree) = const_tree((yyvsp[0].p_symbol));
}
#line 3869 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1960 "parser/spl.y" /* yacc.c:1646  */
    {
 	/* AST树（提高expression的优先级） */
	(yyval.p_tree) = (yyvsp[-1].p_tree);
}
#line 3878 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1965 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 一元操作符（not） */
	if((yyvsp[0].p_tree)->result_type->type_id != TYPE_BOOLEAN)
	{
		parse_error("type mismatch not", "");
		return 0;
	}

	(yyval.p_tree) = not_tree((yyvsp[0].p_tree));
}
#line 3893 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1976 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 一元操作符（not） */
	(yyval.p_tree) = not_tree((yyvsp[0].p_tree));
}
#line 3902 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1981 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 一元操作符（-） */
	if((yyvsp[0].p_tree)->result_type->type_id == TYPE_UINTEGER || (yyvsp[0].p_tree)->result_type->type_id == TYPE_BOOLEAN || (yyvsp[0].p_tree)->result_type->type_id == TYPE_CHAR || (yyvsp[0].p_tree)->result_type->type_id == TYPE_UCHAR)
	{
		parse_error("type mismatch -", "");
		return 0;
	}

	(yyval.p_tree) = neg_tree((yyvsp[0].p_tree));
}
#line 3917 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1992 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 一元操作符（~） */
	(yyval.p_tree) = com_tree((yyvsp[0].p_tree));
}
#line 3926 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1997 "parser/spl.y" /* yacc.c:1646  */
    {
	Type t;
	switch((yyvsp[-1].p_lex)->attr)
	{
		case cvBOOLEAN:
		{
			t = find_type_by_id(TYPE_BOOLEAN);
		}
		break;
		case cvINT:
		{
			t = find_type_by_id(TYPE_INTEGER);
		}
		break;
		case cvREAL:
		{
			t = find_type_by_id(TYPE_REAL);
		}
		break;
		case cvUINT:
		{
			t = find_type_by_id(TYPE_UINTEGER);
		}
		break;
		case cvUCHAR:
		{
			t = find_type_by_id(TYPE_UCHAR);
		}
		break;
		case cvCHAR:
		{
			t = find_type_by_id(TYPE_CHAR); 
		}
		break;
	}
	(yyval.p_tree) = conversion_tree((yyvsp[0].p_tree), t);
}
#line 3968 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 165:
#line 2035 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 寻找对应的符号 */
	p = find_symbol(top_symtab_stack(), (yyvsp[-1].p_char));
	
	/* 检查符号类型是否是数组 */
	if(!p || p->type->type_id != TYPE_ARRAY){
		parse_error("Undeclared array name",(yyvsp[-1].p_char));
		return  0;
	}

	/* 数组符号入栈（保存上下文） */
	push_term_stack(p);
}
#line 3986 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 166:
#line 2049 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 数组符号出栈（获取上下文） */
	p = pop_term_stack(p);
	/* 数组AST树 */
	t = array_index_tree(p, (yyvsp[-1].p_tree));
	/* 数组取值AST树 */
	(yyval.p_tree) = id_factor_tree(t, NULL);
}
#line 3999 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 167:
#line 2058 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 寻找对应的符号 */
	p = find_symbol(top_symtab_stack(), (yyvsp[-2].p_char));

	/* 检查符号类型是否是记录 */
	if(!p || p->type->type_id != TYPE_RECORD) {
		parse_error("Undeclared record variable",(yyvsp[-2].p_char));
		return  0;
	}

	/* 寻找记录类型变量对应的symbol */
	q = find_field(p, (yyvsp[0].p_char));

	/* 检查符号类型 */
	if(!q || q->defn != DEF_FIELD){
		parse_error("Undeclared field ",(yyvsp[0].p_char));
		return 0;
	}

	/* field的AST树 */
	t = record_field_tree(p, q);
	/* field取值AST树 */
	(yyval.p_tree) = id_factor_tree(t, NULL);
}
#line 4028 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 168:
#line 2086 "parser/spl.y" /* yacc.c:1646  */
    {
	/**/
	args = NULL; 
}
#line 4037 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 169:
#line 2091 "parser/spl.y" /* yacc.c:1646  */
    {
	/* 获取函数或者过程调用上下文 */
	rtn = top_call_stack();

	/* 从符号表的参数链表中获取下一个参数 */
	if (arg)
	{
		arg = arg->next;
	}

	/* 将参数放入参数AST树中 */
	args = arg_tree(args, rtn, arg, (yyvsp[0].p_tree)); 
}
#line 4055 "parser/rule.c" /* yacc.c:1646  */
    break;

  case 170:
#line 2105 "parser/spl.y" /* yacc.c:1646  */
    {
	args = NULL;

	/* 获取上下文环境（函数或者过程对应的符号表） */
	rtn = top_call_stack();

	/* 从符号表的参数链表中获取第一个参数 */
	if(rtn)
		arg = rtn->args;
	else
	{
		/*  */
		if(rtn->level >= 0)
		{
			parse_error("parse argument list error.", "");
			return 0;
		}
	}

	/* 初始化参数AST树 */
	args = arg_tree(args, rtn, arg, (yyvsp[0].p_tree));
}
#line 4082 "parser/rule.c" /* yacc.c:1646  */
    break;


#line 4086 "parser/rule.c" /* yacc.c:1646  */
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
#line 2129 "parser/spl.y" /* yacc.c:1906  */


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
	add_symbol_to_table(top_symtab_stack(), p);
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
