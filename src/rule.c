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

extern char *yytext; /* flex用于记录匹配到的字符串 */
symtab *ptab; /* 符号表表头 */
symbol *p, *q;
tree   *t;
type *pt, *qt;
int temp;

/* 记录term上下文 */
symbol* pop_term_stack();
symbol* top_term_stack();
void push_term_stack(symbol * p);

Env global_env;
Env main_env;

Symtab	rtn = NULL; /* 表示system routine */
Symbol	arg = NULL;

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

List pop_case_ast_stack();
List top_case_ast_stack();
void push_case_ast_stack(List newlist);

struct list ast_forest;
struct list para_list;				/* for parameter list. */
List  case_list = NULL;
struct list dag_forest;				/* for dags. */
Tree args; /* 参数AST树 */
Tree now_function; /* 当前函数的AST树 */
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

int parser_init();

Symbol install_temporary_symbol(char *name, int deftype, int typeid);
Type install_temporary_type(char *name, int deftype, int typeid);

void trap_in_debug();

#ifdef DEBUG
#define DEBUG_POINT	trap_in_debug();
#endif


#line 146 "rule.c" /* yacc.c:339  */

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
    yNAME = 344
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 81 "spl.y" /* yacc.c:355  */

	char 		p_char[NAME_LEN];
	int 		num;
	int 		ascii;
	Symbol 		p_symbol; /* 符号 */
	Type		p_type; /* 类型 */
	KEYENTRY	*p_lex; /* 关键字 */
	Tree 		p_tree;

#line 286 "rule.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_RULE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 303 "rule.c" /* yacc.c:358  */

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
#define YYLAST   370

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  90
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  83
/* YYNRULES -- Number of rules.  */
#define YYNRULES  160
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  299

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   344

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
      85,    86,    87,    88,    89
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   200,   200,   236,   249,   264,   269,   268,   281,   298,
     304,   305,   309,   313,   317,   318,   322,   329,   339,   349,
     358,   367,   376,   418,   419,   423,   424,   428,   450,   451,
     452,   456,   467,   477,   488,   496,   519,   529,   542,   554,
     584,   618,   648,   690,   691,   695,   696,   700,   731,   732,
     733,   734,   735,   739,   762,   761,   816,   836,   835,   865,
     866,   874,   875,   879,   907,   936,   940,   947,   951,   952,
     953,   958,   959,   963,   964,   965,   966,   967,   968,   969,
     970,   971,   972,   976,  1035,  1049,  1034,  1074,  1073,  1100,
    1114,  1113,  1133,  1139,  1138,  1158,  1175,  1174,  1191,  1196,
    1209,  1190,  1248,  1252,  1247,  1259,  1260,  1265,  1264,  1288,
    1298,  1287,  1332,  1362,  1331,  1416,  1420,  1428,  1444,  1427,
    1479,  1480,  1485,  1503,  1484,  1513,  1542,  1512,  1553,  1557,
    1562,  1567,  1572,  1577,  1582,  1587,  1594,  1599,  1604,  1609,
    1616,  1621,  1626,  1631,  1636,  1641,  1648,  1682,  1681,  1700,
    1708,  1707,  1720,  1749,  1754,  1759,  1765,  1764,  1788,  1816,
    1830
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
  "oRB", "yNAME", "$accept", "program", "first_act_at_prog",
  "program_head", "sub_program", "$@1", "name_list", "sub_routine",
  "routine_head", "const_part", "const_expr_list", "const_value",
  "type_part", "type_decl_list", "type_definition", "type_decl",
  "array_type_decl", "record_type_decl", "field_decl_list", "field_decl",
  "simple_type_decl", "var_part", "var_decl_list", "var_decl",
  "routine_part", "function_decl", "function_head", "$@2",
  "procedure_decl", "procedure_head", "$@3", "parameters",
  "para_decl_list", "para_type_list", "val_para_list", "var_para_list",
  "routine_body", "stmt_list", "stmt", "non_label_stmt", "assign_stmt",
  "$@4", "$@5", "$@6", "proc_stmt", "$@7", "$@8", "compound_stmt", "$@9",
  "if_stmt", "$@10", "$@11", "$@12", "$@13", "$@14", "else_clause",
  "repeat_stmt", "$@15", "while_stmt", "$@16", "$@17", "for_stmt", "$@18",
  "$@19", "direction", "case_stmt", "$@20", "$@21", "case_expr_list",
  "case_expr", "$@22", "$@23", "$@24", "$@25", "goto_stmt", "expression",
  "expr", "term", "factor", "$@26", "$@27", "$@28", "args_list", YY_NULLPTR
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
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344
};
# endif

#define YYPACT_NINF -153

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-153)))

#define YYTABLE_NINF -151

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -153,    23,     9,  -153,   -70,   -55,    59,  -153,   -19,    13,
      -5,  -153,    62,  -153,    30,    16,  -153,   104,    33,    98,
     317,    67,  -153,  -153,  -153,    68,    33,  -153,    51,    -2,
    -153,  -153,  -153,  -153,  -153,    64,   317,  -153,   143,  -153,
      14,    40,    51,  -153,  -153,  -153,    -2,  -153,    65,  -153,
      70,  -153,    71,    53,    79,    51,  -153,   317,    51,    72,
      75,    93,  -153,  -153,  -153,   -40,    86,   143,  -153,    89,
      90,  -153,  -153,    59,    59,  -153,   101,  -153,  -153,    95,
     108,    19,  -153,  -153,    97,   106,   107,   -39,   103,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,   217,
      41,    -1,  -153,   110,   -46,   100,   317,  -153,  -153,  -153,
    -153,   116,   113,   113,   120,   104,   125,  -153,   204,   137,
    -153,  -153,   204,  -153,   204,   207,   121,   204,   204,   126,
    -153,   129,  -153,   128,   143,  -153,  -153,   -17,  -153,  -153,
    -153,  -153,    -6,   138,  -153,  -153,  -153,  -153,   204,   132,
     204,   204,    49,  -153,   202,     6,    11,  -153,   204,   199,
     234,   140,    88,  -153,   204,   136,   293,  -153,   204,   204,
     208,   154,   317,  -153,    51,   166,   -30,  -153,   165,   170,
     217,  -153,   167,  -153,   277,   162,  -153,   171,   256,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   293,  -153,  -153,   204,  -153,   293,   -33,
    -153,   186,   245,     7,   143,  -153,  -153,   166,    -6,  -153,
     217,   217,  -153,   204,  -153,  -153,   204,   204,  -153,  -153,
     256,  -153,     6,     6,     6,     6,     6,     6,    11,    11,
      11,  -153,  -153,  -153,  -153,  -153,    12,   191,   191,   293,
     191,   204,  -153,   204,  -153,  -153,  -153,  -153,  -153,  -153,
      20,   261,    21,   183,   187,   254,  -153,  -153,  -153,   204,
     257,  -153,  -153,   293,   293,   211,  -153,  -153,  -153,   191,
     191,  -153,   164,   191,  -153,   257,   204,  -153,  -153,  -153,
    -153,  -153,   293,   192,   195,   191,  -153,  -153,  -153
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,    14,     5,     0,     0,
       0,     6,    23,     4,     0,    15,     2,     0,     0,    43,
       0,     0,    96,     7,    67,     0,    24,    26,     0,    48,
      22,    21,    18,    19,    20,     0,     0,    68,     0,    25,
       0,     0,    44,    46,    54,    57,    13,    51,     0,    52,
       0,    17,     0,     0,     0,     0,    36,     0,     0,    37,
       0,     0,    29,    30,    28,     0,     0,     0,    45,     0,
       0,    49,    50,    14,    14,    16,     0,   117,    97,     0,
       0,     0,   107,   109,     0,    92,     0,    89,     0,    72,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     0,
       0,     0,    34,     0,     0,     0,     0,    27,    11,    10,
       8,     0,    59,    59,     0,     0,     0,    70,     0,     0,
     128,   102,     0,    68,     0,    73,     0,     0,     0,     0,
      84,     0,    69,     0,     0,    32,    33,     0,    38,    42,
      39,    47,     0,     0,    58,    53,    12,    56,     0,   149,
       0,     0,   146,   152,     0,   135,   139,   145,     0,     0,
       0,     0,     0,    71,     0,     0,    83,    87,     0,     0,
       0,     0,     0,    40,     0,    65,     0,    62,     0,     0,
       0,   154,     0,   155,     0,     0,   156,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   112,   103,    99,     0,   110,   160,     0,
      95,     0,     0,     0,     0,    35,    41,    66,     0,    60,
       0,     0,    55,     0,   153,   158,     0,     0,   125,   122,
     118,   121,   133,   134,   132,   131,   130,   129,   138,   136,
     137,   144,   142,   143,   140,   141,     0,    73,    73,   108,
      73,     0,    94,     0,    85,    91,    31,    61,    63,    64,
       0,     0,     0,     0,     0,     0,   120,   116,   115,     0,
     105,   100,   111,   159,    88,     0,   151,   157,   148,    73,
      73,   119,     0,    73,   104,   105,     0,   126,   123,   113,
     106,   101,    86,     0,     0,    73,   127,   124,   114
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -153,  -153,  -153,  -153,  -153,  -153,   -51,   212,   281,  -153,
    -153,   -20,  -153,  -153,   262,   -66,  -153,  -153,  -153,   189,
     -96,  -153,  -153,   249,  -153,   246,  -153,  -153,   251,  -153,
    -153,   182,  -153,    85,  -153,  -153,   197,   181,    34,   190,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,   -12,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,    45,  -153,  -153,  -153,  -153,
    -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,  -153,   109,
    -153,  -153,  -153,  -153,  -153,  -116,   134,   -84,   -72,  -153,
    -153,  -153,  -152
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     6,    10,    17,    41,   114,   115,    12,
      15,   153,    19,    26,    27,    61,    62,    63,   101,   102,
      64,    29,    42,    43,    46,    47,    48,    69,    49,    50,
      70,   143,   176,   177,   178,   179,    23,    53,    88,    89,
      90,   168,   275,   211,    91,   131,   126,    92,    37,    93,
     122,   248,   285,   159,   247,   284,    94,   123,    95,   124,
     250,    96,   246,   295,   269,    97,   118,   265,   230,   231,
     264,   294,   263,   293,    98,   208,   155,   156,   157,   187,
     182,   226,   209
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,   111,   154,   133,   100,    24,   160,   104,   162,     7,
       4,   135,   166,    44,   198,    65,    52,   213,    60,   199,
     121,    30,   267,     3,    45,    31,    32,    33,    34,   174,
     195,   200,    66,   128,     8,   184,     5,   103,   108,   109,
     138,   -98,   203,   129,   268,   251,   -90,    60,   130,   218,
     100,   172,   212,   252,    76,   165,   219,   -98,    22,    77,
      13,   -98,   -98,   -98,   -98,    78,     9,    79,   171,    80,
      81,   260,   -98,   196,   197,   262,   181,    16,   183,    60,
     201,   202,    82,    40,   222,   251,   140,   -98,    40,    83,
     249,   175,    -9,   255,    -9,    18,    84,   207,   251,   251,
      -9,    20,    14,    24,   -98,    21,   276,   278,   -98,    22,
     261,   238,   239,   240,    60,    85,    86,   173,    66,    66,
      67,   134,    25,   217,   258,   259,   241,   242,   243,   244,
     245,   185,   -73,    28,  -147,   273,   186,   274,    36,    38,
      40,    76,    87,    51,    73,    22,    77,    54,   256,    74,
      75,   120,   216,   282,    79,   105,    80,    81,   106,   189,
      60,   190,   191,   192,   193,   194,    99,   175,   229,    82,
     292,    55,   107,   289,   206,   110,    83,   125,   112,   113,
     117,    30,   132,    84,   119,    31,    32,    33,    34,   139,
      56,   -93,   127,   137,    60,   141,    22,    77,   142,   145,
      60,    60,    85,    86,   147,    79,   164,    80,    81,   158,
     229,    57,    22,    77,   169,   167,   170,  -150,   180,   -73,
      82,    79,   210,    80,    81,   188,   148,    83,    58,    87,
     204,   214,    59,   215,    84,   189,    82,   190,   191,   192,
     193,   194,    30,    83,    66,   220,    31,    32,    33,    34,
     221,   225,   223,    85,    86,    30,   227,   149,   253,    31,
      32,    33,    34,   279,    56,   205,   281,   280,   283,    85,
      86,   296,   150,   189,   297,   190,   191,   192,   193,   194,
      87,   270,   271,   286,   272,    57,   116,    11,    39,   151,
     136,    68,    71,   152,    30,   144,    87,    72,    31,    32,
      33,    34,    58,   257,   161,   189,    59,   190,   191,   192,
     193,   194,   146,   287,   288,   163,   189,   290,   190,   191,
     192,   193,   194,   232,   233,   234,   235,   236,   237,   298,
     291,     0,   189,   254,   190,   191,   192,   193,   194,   266,
       0,     0,     0,     0,     0,   228,     0,     0,   189,   277,
     190,   191,   192,   193,   194,    30,     0,     0,     0,    31,
      32,    33,    34,   224,   189,     0,   190,   191,   192,   193,
     194
};

static const yytype_int16 yycheck[] =
{
      20,    67,   118,    99,    55,    17,   122,    58,   124,    79,
       1,    12,   128,    15,     3,     1,    36,   169,    38,     8,
       1,    38,    10,     0,    26,    42,    43,    44,    45,    35,
      24,    20,    78,    72,    89,   151,    27,    57,    78,    79,
      86,    22,   158,    82,    32,    78,    85,    67,    87,    79,
     101,    68,   168,    86,     1,   127,    86,    38,     5,     6,
      79,    42,    43,    44,    45,    12,     7,    14,   134,    16,
      17,   223,    53,    67,    68,   227,   148,    82,   150,    99,
      69,    70,    29,    89,   180,    78,   106,    68,    89,    36,
     206,   142,    78,    86,    80,    33,    43,     9,    78,    78,
      86,    71,    89,   115,    85,    89,    86,    86,    89,     5,
     226,   195,   196,   197,   134,    62,    63,   137,    78,    78,
      80,    80,    89,   174,   220,   221,   198,   199,   200,   201,
     202,    82,    79,    35,    85,   251,    87,   253,    71,    71,
      89,     1,    89,    79,    79,     5,     6,     4,   214,    79,
      79,    43,   172,   269,    14,    83,    16,    17,    83,    71,
     180,    73,    74,    75,    76,    77,    87,   218,   188,    29,
     286,    28,    79,     9,    34,    89,    36,    80,    89,    89,
      79,    38,    79,    43,    89,    42,    43,    44,    45,    89,
      47,    85,    85,    83,   214,    79,     5,     6,    85,    79,
     220,   221,    62,    63,    79,    14,    85,    16,    17,    72,
     230,    68,     5,     6,    85,    89,    88,    85,    80,    79,
      29,    14,    86,    16,    17,    23,    22,    36,    85,    89,
      31,    23,    89,    79,    43,    71,    29,    73,    74,    75,
      76,    77,    38,    36,    78,    80,    42,    43,    44,    45,
      80,    89,    85,    62,    63,    38,    85,    53,    72,    42,
      43,    44,    45,    80,    47,    31,    12,    80,    11,    62,
      63,    79,    68,    71,    79,    73,    74,    75,    76,    77,
      89,   247,   248,    72,   250,    68,    74,     6,    26,    85,
     101,    42,    46,    89,    38,   113,    89,    46,    42,    43,
      44,    45,    85,   218,   123,    71,    89,    73,    74,    75,
      76,    77,   115,   279,   280,   125,    71,   283,    73,    74,
      75,    76,    77,   189,   190,   191,   192,   193,   194,   295,
     285,    -1,    71,    88,    73,    74,    75,    76,    77,   230,
      -1,    -1,    -1,    -1,    -1,    89,    -1,    -1,    71,    88,
      73,    74,    75,    76,    77,    38,    -1,    -1,    -1,    42,
      43,    44,    45,    86,    71,    -1,    73,    74,    75,    76,
      77
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    91,    92,     0,     1,    27,    93,    79,    89,     7,
      94,    98,    99,    79,    89,   100,    82,    95,    33,   102,
      71,    89,     5,   126,   137,    89,   103,   104,    35,   111,
      38,    42,    43,    44,    45,   101,    71,   138,    71,   104,
      89,    96,   112,   113,    15,    26,   114,   115,   116,   118,
     119,    79,   101,   127,     4,    28,    47,    68,    85,    89,
     101,   105,   106,   107,   110,     1,    78,    80,   113,   117,
     120,   115,   118,    79,    79,    79,     1,     6,    12,    14,
      16,    17,    29,    36,    43,    62,    63,    89,   128,   129,
     130,   134,   137,   139,   146,   148,   151,   155,   164,    87,
      96,   108,   109,   101,    96,    83,    83,    79,    78,    79,
      89,   105,    89,    89,    97,    98,    97,    79,   156,    89,
      43,     1,   140,   147,   149,    80,   136,    85,    72,    82,
      87,   135,    79,   110,    80,    12,   109,    83,    86,    89,
     101,    79,    85,   121,   121,    79,   126,    79,    22,    53,
      68,    85,    89,   101,   165,   166,   167,   168,    72,   143,
     165,   127,   165,   129,    85,   168,   165,    89,   131,    85,
      88,   105,    68,   101,    35,    96,   122,   123,   124,   125,
      80,   168,   170,   168,   165,    82,    87,   169,    23,    71,
      73,    74,    75,    76,    77,    24,    67,    68,     3,     8,
      20,    69,    70,   165,    31,    31,    34,     9,   165,   172,
      86,   133,   165,   172,    23,    79,   101,    96,    79,    86,
      80,    80,   110,    85,    86,    89,   171,    85,    89,   101,
     158,   159,   166,   166,   166,   166,   166,   166,   167,   167,
     167,   168,   168,   168,   168,   168,   152,   144,   141,   165,
     150,    78,    86,    72,    88,    86,   105,   123,   110,   110,
     172,   165,   172,   162,   160,   157,   159,    10,    32,   154,
     128,   128,   128,   165,   165,   132,    86,    88,    86,    80,
      80,    12,   165,    11,   145,   142,    72,   128,   128,     9,
     128,   145,   165,   163,   161,   153,    79,    79,   128
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    90,    91,    92,    93,    93,    95,    94,    96,    96,
      96,    96,    97,    98,    99,    99,   100,   100,   101,   101,
     101,   101,   101,   102,   102,   103,   103,   104,   105,   105,
     105,   106,   107,   108,   108,   109,   110,   110,   110,   110,
     110,   110,   110,   111,   111,   112,   112,   113,   114,   114,
     114,   114,   114,   115,   117,   116,   118,   120,   119,   121,
     121,   122,   122,   123,   123,   124,   125,   126,   127,   127,
     127,   128,   128,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   130,   131,   132,   130,   133,   130,   134,
     135,   134,   134,   136,   134,   134,   138,   137,   140,   141,
     142,   139,   143,   144,   139,   145,   145,   147,   146,   149,
     150,   148,   152,   153,   151,   154,   154,   156,   157,   155,
     158,   158,   160,   161,   159,   162,   163,   159,   164,   165,
     165,   165,   165,   165,   165,   165,   166,   166,   166,   166,
     167,   167,   167,   167,   167,   167,   168,   169,   168,   168,
     170,   168,   168,   168,   168,   168,   171,   168,   168,   172,
     172
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
       3,     3,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     0,     8,     0,     6,     1,
       0,     5,     1,     0,     5,     4,     0,     4,     0,     0,
       0,     8,     0,     0,     7,     0,     2,     0,     5,     0,
       0,     6,     0,     0,    10,     1,     1,     0,     0,     7,
       2,     1,     0,     0,     6,     0,     0,     6,     2,     3,
       3,     3,     3,     3,     3,     1,     3,     3,     3,     1,
       3,     3,     3,     3,     3,     1,     1,     0,     5,     1,
       0,     5,     1,     3,     2,     2,     0,     5,     3,     3,
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
#line 201 "spl.y" /* yacc.c:1646  */
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
		list_append(&ast_forest, t);

		/* generate dag forest. */
		gen_dag(&ast_forest, &dag_forest);

		/* emit asm code. */
		emit_code(&dag_forest);

		(*(IR->main_end))(&main_env);

		/* call end interface. */
		(*(IR->program_end))(&global_env);
	}

	return 0;
}
#line 1667 "rule.c" /* yacc.c:1646  */
    break;

  case 3:
#line 237 "spl.y" /* yacc.c:1646  */
    {
	/* 初始化解析器 */
	parser_init();
	/* 创建全局符号表 */
	make_global_symtab();
	/* 创建系统符号表 */
	make_system_symtab();
	/* 将全局符号表压入符号表栈中 */
	push_symtab_stack(Global_symtab);
}
#line 1682 "rule.c" /* yacc.c:1646  */
    break;

  case 4:
#line 250 "spl.y" /* yacc.c:1646  */
    {
	/* 初始化全局符号表的名称 */
	strcpy(Global_symtab->name, (yyvsp[-1].p_char));
	/* 初始化全局符号表的汇编名称 */
	snprintf(Global_symtab->rname, sizeof(Global_symtab->rname), "main");
	/* 初始化大类 */
	Global_symtab->defn = DEF_PROG;

	global_env.u.program.tab = Global_symtab;
	/* call initialization interface. */
	(*(IR->program_begin))(&global_env);


}
#line 1701 "rule.c" /* yacc.c:1646  */
    break;

  case 6:
#line 269 "spl.y" /* yacc.c:1646  */
    {
	main_env.u.main.tab = Global_symtab;
	(*(IR->main_begin))(&main_env);
	list_clear(&ast_forest);
	list_clear(&para_list);
	
	push_symtab_stack(Global_symtab);
}
#line 1714 "rule.c" /* yacc.c:1646  */
    break;

  case 7:
#line 277 "spl.y" /* yacc.c:1646  */
    {}
#line 1720 "rule.c" /* yacc.c:1646  */
    break;

  case 8:
#line 282 "spl.y" /* yacc.c:1646  */
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
#line 1741 "rule.c" /* yacc.c:1646  */
    break;

  case 9:
#line 299 "spl.y" /* yacc.c:1646  */
    {
	/* 匹配 yNAME */
	p = new_symbol((yyvsp[0].p_char), DEF_UNKNOWN, TYPE_UNKNOWN);
	(yyval.p_symbol) = p;
}
#line 1751 "rule.c" /* yacc.c:1646  */
    break;

  case 10:
#line 304 "spl.y" /* yacc.c:1646  */
    {}
#line 1757 "rule.c" /* yacc.c:1646  */
    break;

  case 11:
#line 305 "spl.y" /* yacc.c:1646  */
    {}
#line 1763 "rule.c" /* yacc.c:1646  */
    break;

  case 13:
#line 313 "spl.y" /* yacc.c:1646  */
    {/* 依次定义常量、自定义类型以及变量和routine（函数以及过程） */}
#line 1769 "rule.c" /* yacc.c:1646  */
    break;

  case 14:
#line 317 "spl.y" /* yacc.c:1646  */
    {}
#line 1775 "rule.c" /* yacc.c:1646  */
    break;

  case 15:
#line 318 "spl.y" /* yacc.c:1646  */
    {}
#line 1781 "rule.c" /* yacc.c:1646  */
    break;

  case 16:
#line 323 "spl.y" /* yacc.c:1646  */
    {
	/* 给const_value命名 */
	strncpy((yyvsp[-1].p_symbol)->name, (yyvsp[-3].p_char), NAME_LEN);
	/* 将const类型symbol放入符号表中 */
	add_symbol_to_table(top_symtab_stack(), (yyvsp[-1].p_symbol));
}
#line 1792 "rule.c" /* yacc.c:1646  */
    break;

  case 17:
#line 330 "spl.y" /* yacc.c:1646  */
    {
	/* 给const_value命名 */
	strncpy((yyvsp[-1].p_symbol)->name, (yyvsp[-3].p_char), NAME_LEN);
	/* 将const类型symbol放入符号表中 */
	add_symbol_to_table(top_symtab_stack(), (yyvsp[-1].p_symbol));
}
#line 1803 "rule.c" /* yacc.c:1646  */
    break;

  case 18:
#line 340 "spl.y" /* yacc.c:1646  */
    {
	/* 先采用默认命名，随后会被正确命名 */
	p = new_symbol("$$$", DEF_CONST,
		TYPE_INTEGER);

	/* 给symbol赋值 */
	p->v.i = (yyvsp[0].num);
	(yyval.p_symbol) = p;
}
#line 1817 "rule.c" /* yacc.c:1646  */
    break;

  case 19:
#line 350 "spl.y" /* yacc.c:1646  */
    {
	p = new_symbol("$$$",DEF_CONST,
		TYPE_REAL);

	/* 给symbol赋值，将字符串转化为浮点数 */
	p->v.f = atof((yyvsp[0].p_char));
	(yyval.p_symbol) = p;
}
#line 1830 "rule.c" /* yacc.c:1646  */
    break;

  case 20:
#line 359 "spl.y" /* yacc.c:1646  */
    {
	p = new_symbol("$$$", DEF_CONST,
		TYPE_CHAR);

	/* 给symbol赋值 */
	p->v.c= (yyvsp[0].p_char)[1];
	(yyval.p_symbol) = p;
}
#line 1843 "rule.c" /* yacc.c:1646  */
    break;

  case 21:
#line 368 "spl.y" /* yacc.c:1646  */
    {
	p = new_symbol("$$$", DEF_CONST,
		TYPE_STRING);

	/* 给symbol赋值，字符串 */
	p->v.s = strdup((yyvsp[0].p_char));
	(yyval.p_symbol) = p;
}
#line 1856 "rule.c" /* yacc.c:1646  */
    break;

  case 22:
#line 377 "spl.y" /* yacc.c:1646  */
    {
	p = new_symbol("$$$", DEF_CONST,
		TYPE_UNKNOWN);

	switch((yyvsp[0].num))
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

	(yyval.p_symbol) = p;
}
#line 1899 "rule.c" /* yacc.c:1646  */
    break;

  case 23:
#line 418 "spl.y" /* yacc.c:1646  */
    {}
#line 1905 "rule.c" /* yacc.c:1646  */
    break;

  case 24:
#line 419 "spl.y" /* yacc.c:1646  */
    {}
#line 1911 "rule.c" /* yacc.c:1646  */
    break;

  case 25:
#line 423 "spl.y" /* yacc.c:1646  */
    {}
#line 1917 "rule.c" /* yacc.c:1646  */
    break;

  case 26:
#line 424 "spl.y" /* yacc.c:1646  */
    {}
#line 1923 "rule.c" /* yacc.c:1646  */
    break;

  case 27:
#line 429 "spl.y" /* yacc.c:1646  */
    {
	if((yyvsp[-1].p_type)->name[0] == '$')
	{
		/* 新创建的自定义类型符号 */
		(yyval.p_type) = (yyvsp[-1].p_type);
		/* 自定义类型符号命名 */
		strncpy((yyval.p_type)->name, (yyvsp[-3].p_char), NAME_LEN);
	}
	else{
		/* 使用自定义类型符号创建自定义类型，直接clone已有的自定义类型符号 */
		(yyval.p_type) = clone_type((yyvsp[-1].p_type));
		/* 自定义类型符号命名 */
		strncpy((yyval.p_type)->name, (yyvsp[-3].p_char), NAME_LEN);
		/* 将类型添加到符号表中 */
		add_type_to_table(
			top_symtab_stack(), (yyval.p_type));
	}
}
#line 1946 "rule.c" /* yacc.c:1646  */
    break;

  case 28:
#line 450 "spl.y" /* yacc.c:1646  */
    {}
#line 1952 "rule.c" /* yacc.c:1646  */
    break;

  case 29:
#line 451 "spl.y" /* yacc.c:1646  */
    {}
#line 1958 "rule.c" /* yacc.c:1646  */
    break;

  case 30:
#line 452 "spl.y" /* yacc.c:1646  */
    {}
#line 1964 "rule.c" /* yacc.c:1646  */
    break;

  case 31:
#line 457 "spl.y" /* yacc.c:1646  */
    {
	/* 创建一个自定义数组类型 */
	(yyval.p_type) = new_array_type("$$$", (yyvsp[-3].p_type), (yyvsp[0].p_type));
	/* 添加到符号表中 */
	add_type_to_table(
		top_symtab_stack(),(yyval.p_type));
}
#line 1976 "rule.c" /* yacc.c:1646  */
    break;

  case 32:
#line 468 "spl.y" /* yacc.c:1646  */
    {
	/* 创建一个自定义RECORD类型 */
	(yyval.p_type) = new_record_type("$$$", (yyvsp[-1].p_symbol));
	/* 添加到符号表中 */
 	add_type_to_table(top_symtab_stack(), (yyval.p_type));
}
#line 1987 "rule.c" /* yacc.c:1646  */
    break;

  case 33:
#line 478 "spl.y" /* yacc.c:1646  */
    {
	/* 将指针移动到链表的末尾 */
	for(p = (yyvsp[-1].p_symbol); p->next; p = p->next);

	/* 链接创建的record属性成员 */
	p->next = (yyvsp[0].p_symbol);

	/* 定义为链表的record属性符号链表的头部 */
	(yyval.p_symbol) = (yyvsp[-1].p_symbol);  
}
#line 2002 "rule.c" /* yacc.c:1646  */
    break;

  case 34:
#line 489 "spl.y" /* yacc.c:1646  */
    {
	/* record关键字之后，必须定义至少一个属性 */
	(yyval.p_symbol) = (yyvsp[0].p_symbol);
}
#line 2011 "rule.c" /* yacc.c:1646  */
    break;

  case 35:
#line 497 "spl.y" /* yacc.c:1646  */
    {
	/* type_decl可以是已经定义的自定义类型（已经位于符号表中）或者现场定义的自定义类型，
		 也就是说可以直接使用record上面定义的自定义类型 */
	for(p = (yyvsp[-3].p_symbol); p; p = p->next) {

		if((yyvsp[-1].p_type)->type_id == TYPE_SUBRANGE || (yyvsp[-1].p_type)->type_id == TYPE_ENUM)
			/* 子范围类型 */
			p->type = (yyvsp[-1].p_type)->first->type;
		else
		  /* 可以是任意类型 */
			p->type = find_type_by_id((yyvsp[-1].p_type)->type_id);

		/* 主要用于检查enum或者subrange类型变量的赋值操作是否合法 */
		p->type_link = (yyvsp[-1].p_type);
		/* 符号大类定义 */
		p->defn = DEF_FIELD;
	}
	(yyval.p_symbol) = (yyvsp[-3].p_symbol);
}
#line 2035 "rule.c" /* yacc.c:1646  */
    break;

  case 36:
#line 520 "spl.y" /* yacc.c:1646  */
    {
	/* 系统类型（char，integer，boolean，real） */
	pt = find_type_by_name((yyvsp[0].p_char));

	if(!pt)
		parse_error("Undeclared type name",(yyvsp[0].p_char));

	(yyval.p_type) = pt;
}
#line 2049 "rule.c" /* yacc.c:1646  */
    break;

  case 37:
#line 530 "spl.y" /* yacc.c:1646  */
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
#line 2066 "rule.c" /* yacc.c:1646  */
    break;

  case 38:
#line 543 "spl.y" /* yacc.c:1646  */
    {
	/* 初始化一个枚举类型 */
	(yyval.p_type) = new_enum_type("$$$");

	/* 初始化枚举类型的符号链表 */
	add_enum_elements((yyval.p_type), (yyvsp[-1].p_symbol));

	/* 将枚举类型放入符号表 */
	add_type_to_table(
		top_symtab_stack(),(yyval.p_type));
}
#line 2082 "rule.c" /* yacc.c:1646  */
    break;

  case 39:
#line 555 "spl.y" /* yacc.c:1646  */
    {
  /* 检查oDOTDOT前后的类型是否一致 */
	if((yyvsp[-2].p_symbol)->type->type_id != (yyvsp[0].p_symbol)->type->type_id){
		parse_error("type mismatch","");
		return 0;
	}
	
	/* 初始化一个子范围类型 */
	(yyval.p_type) = new_subrange_type("$$$", (yyvsp[-2].p_symbol)->type->type_id);

	/* 将子范围类型放入符号表 */
	add_type_to_table(
		top_symtab_stack(), (yyval.p_type));

	/* 初始化子范围类型的上下界限，
	 上下界的类型必须可以强制转换为int类型（integer、boolean、char），
	 char类型可以转化为相应的ASCII码。 */
	if((yyvsp[-2].p_symbol)->type->type_id == TYPE_INTEGER)
		set_subrange_bound((yyval.p_type),
			(int)(yyvsp[-2].p_symbol)->v.i, (int)(yyvsp[0].p_symbol)->v.i);
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_BOOLEAN)
		set_subrange_bound((yyval.p_type),
			(int)(yyvsp[-2].p_symbol)->v.b, (int)(yyvsp[0].p_symbol)->v.b);
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_CHAR)
		set_subrange_bound((yyval.p_type),
			(int)(yyvsp[-2].p_symbol)->v.c, (int)(yyvsp[0].p_symbol)->v.c);
	else
		parse_error("invalid element type of subrange","");
}
#line 2116 "rule.c" /* yacc.c:1646  */
    break;

  case 40:
#line 585 "spl.y" /* yacc.c:1646  */
    {
	/* 检查oDOTDOT前后的类型是否一致 */
	if((yyvsp[-2].p_symbol)->type->type_id != (yyvsp[0].p_symbol)->type->type_id){
		parse_error("type mismatch","");
		return 0;
	}

	/* 初始化一个子范围类型 */
	(yyval.p_type) = new_subrange_type("$$$", (yyvsp[-2].p_symbol)->type->type_id);
		
	/* 将子范围类型放入符号表 */
	add_type_to_table(
		top_symtab_stack(), (yyval.p_type));

	/* 初始化子范围类型的上下界限，
	 上下界的类型必须可以强制转换为int类型（integer、boolean），
	 char类型可以转化为相应的ASCII码。 */
	if((yyvsp[-2].p_symbol)->type->type_id == TYPE_INTEGER){
		(yyvsp[-2].p_symbol)->v.i= -(yyvsp[-2].p_symbol)->v.i;
		set_subrange_bound((yyval.p_type),
			(int)(yyvsp[-2].p_symbol)->v.i, (int)(yyvsp[0].p_symbol)->v.i);
	}
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_BOOLEAN){
		/* 将const_value按位异或，经过转化后，1变成0，0变成1。 */
		(yyvsp[-2].p_symbol)->v.b ^= 1;
		set_subrange_bound((yyval.p_type),
			(int)(yyvsp[-2].p_symbol)->v.b,(int)(yyvsp[0].p_symbol)->v.b);
	}
	else if ((yyvsp[-2].p_symbol)->type->type_id == TYPE_CHAR)
		parse_error("invalid operator","");
	else
   		parse_error("invalid element type of subrange","");
}
#line 2154 "rule.c" /* yacc.c:1646  */
    break;

  case 41:
#line 619 "spl.y" /* yacc.c:1646  */
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
#line 2188 "rule.c" /* yacc.c:1646  */
    break;

  case 42:
#line 649 "spl.y" /* yacc.c:1646  */
    {
	
	/* 通过自定义类型名称从符号表中寻找自定义类型 */
	p = find_element(top_symtab_stack(), (yyvsp[-2].p_char));
	if(!p){
		parse_error("Undeclared identifier", (yyvsp[-2].p_char));
		/* 一个临时的DEF_ELEMENT大类，TYPE_INTEGER小类的符号作为局部变量添加到符号表中 */
		install_temporary_symbol((yyvsp[-2].p_char), DEF_ELEMENT, TYPE_INTEGER);
	}
	/* 检查用户自定义类型关联的符号是否是ELEMENT类型 */
	if(p->defn != DEF_ELEMENT){
		parse_error("not an element identifier", (yyvsp[-2].p_char));
	}
	
	/* 寻找用户自定义类型关联的符号 */
	q = find_element(top_symtab_stack(), (yyvsp[0].p_char));
	if(!q){
		parse_error("Undeclared identifier", (yyvsp[0].p_char));
		/* 一个临时的DEF_ELEMENT大类，TYPE_INTEGER小类的符号作为局部变量添加到符号表中 */
		install_temporary_symbol((yyvsp[0].p_char), DEF_ELEMENT, TYPE_INTEGER);
	}
	/* 检查用户自定义类型关联的符号是否是ELEMENT类型 */
	if(q->defn != DEF_ELEMENT){
		parse_error("Not an element identifier", (yyvsp[0].p_char));
	}
	
	if(p && q){
		/* p和q都存在，创建一个TYPE_INTEGER类型的子范围类型， */
		(yyval.p_type) = new_subrange_type("$$$", TYPE_INTEGER);
		/* 子范围类型添加到符号表中 */
		add_type_to_table(
			top_symtab_stack(), (yyval.p_type));
		/* 设置子范围类型的上下界 */
		set_subrange_bound((yyval.p_type), p->v.i, q->v.i);
	}
	else
		(yyval.p_type) = NULL;
}
#line 2231 "rule.c" /* yacc.c:1646  */
    break;

  case 43:
#line 690 "spl.y" /* yacc.c:1646  */
    {}
#line 2237 "rule.c" /* yacc.c:1646  */
    break;

  case 44:
#line 691 "spl.y" /* yacc.c:1646  */
    {}
#line 2243 "rule.c" /* yacc.c:1646  */
    break;

  case 45:
#line 695 "spl.y" /* yacc.c:1646  */
    {}
#line 2249 "rule.c" /* yacc.c:1646  */
    break;

  case 46:
#line 696 "spl.y" /* yacc.c:1646  */
    {}
#line 2255 "rule.c" /* yacc.c:1646  */
    break;

  case 47:
#line 701 "spl.y" /* yacc.c:1646  */
    {
	/* 获取对应的符号表 */
	ptab = top_symtab_stack();
	
	/* 遍历符号表 */
	for(p = (yyvsp[-3].p_symbol); p ;){
		if((yyvsp[-1].p_type)->type_id == TYPE_SUBRANGE || (yyvsp[-1].p_type)->type_id == TYPE_ENUM)
			/* 其中TYPE_ENUM类型符号只能是integer，TYPE_SUBRANGE类型符号可以是char或者integer，
			 对TYPE_SUBRANGE以及TYPE_ENUM类型符号定义的变量进行操作时，实际上只能对其中一个元素进行操作。
			 那enum(enum1, enum2)类型的变量来说，要么是enum1要么是enum2，不能即是enum1又是enum2. */
			p->type = find_type_by_id((yyvsp[-1].p_type)->first->type->type_id);
		else
			p->type = find_type_by_id((yyvsp[-1].p_type)->type_id);

		/* 主要用于检查enum或者subrange类型变量的赋值操作是否合法 */
		p->type_link = (yyvsp[-1].p_type);
		/* 定义符号大类 */
		p->defn = DEF_VAR;

		q = p; 
		p = p->next;
		q->next = NULL;
		/* 将变量添加到符号表中 */
		add_symbol_to_table(ptab, q);
	}
	(yyvsp[-3].p_symbol) = NULL;
}
#line 2287 "rule.c" /* yacc.c:1646  */
    break;

  case 48:
#line 731 "spl.y" /* yacc.c:1646  */
    {}
#line 2293 "rule.c" /* yacc.c:1646  */
    break;

  case 49:
#line 732 "spl.y" /* yacc.c:1646  */
    {/* 自定义函数可以嵌套 */}
#line 2299 "rule.c" /* yacc.c:1646  */
    break;

  case 50:
#line 733 "spl.y" /* yacc.c:1646  */
    {/*  自定义过程可以嵌套 */}
#line 2305 "rule.c" /* yacc.c:1646  */
    break;

  case 51:
#line 734 "spl.y" /* yacc.c:1646  */
    {}
#line 2311 "rule.c" /* yacc.c:1646  */
    break;

  case 52:
#line 735 "spl.y" /* yacc.c:1646  */
    {}
#line 2317 "rule.c" /* yacc.c:1646  */
    break;

  case 53:
#line 740 "spl.y" /* yacc.c:1646  */
    {
	if (!err_occur())
	{
		/* 清除dag森林 */
		list_clear(&dag_forest);
		t = new_tree(TAIL, NULL, NULL, NULL);
		t->u.generic.symtab = top_symtab_stack();
		list_append(&ast_forest, t);

		/* generate dag forest. */
		gen_dag(&ast_forest, &dag_forest);

		/* emit asm code. */
		emit_code(&dag_forest);
	}

	pop_symtab_stack();
}
#line 2340 "rule.c" /* yacc.c:1646  */
    break;

  case 54:
#line 762 "spl.y" /* yacc.c:1646  */
    {

	list_clear(&ast_forest);
	list_clear(&para_list);

	/* 创建符号表 */
	ptab = new_symtab(top_symtab_stack());
	push_symtab_stack(ptab);
}
#line 2354 "rule.c" /* yacc.c:1646  */
    break;

  case 55:
#line 772 "spl.y" /* yacc.c:1646  */
    {
	/* 获取对应的符号表 */
	ptab = top_symtab_stack();
	/* 使用函数名对符号表进行命名 */
	strncpy(ptab->name, (yyvsp[-3].p_char), NAME_LEN);
	/* 使用符号表对函数表中汇编代码进行命名 */
	sprintf(ptab->rname, "rtn%03d", ptab->id);
	/* 初始化符号表大类 */
	ptab->defn = DEF_FUNCT;
	
	/* 初始化函数符号表类型（定义函数的返回值） */
	if((yyvsp[0].p_type)->type_id == TYPE_SUBRANGE)
		ptab->type = (yyvsp[0].p_type)->first->type;
	else if((yyvsp[0].p_type)->type_id == TYPE_ENUM)
		ptab->type = find_type_by_id(TYPE_INTEGER);
	else
		ptab->type = find_type_by_id((yyvsp[0].p_type)->type_id);
	p = new_symbol((yyvsp[-3].p_char), DEF_FUNCT, ptab->type->type_id);
	p->type_link = (yyvsp[0].p_type);

	/* 将函数对应的符号表添加到符号链表中 */
	add_symbol_to_table(ptab, p);
	/* 将函数对应的符号表中的参数符号链表反转 */
	reverse_parameters(ptab);

	{
		/* 生成一颗AST树 */
		Tree header;
		/* 定义指令以及返回值 */
		header = new_tree(HEADER, ptab->type, NULL, NULL);
		/* 定义参数链表 */
		header->u.header.para = &para_list;
		/* 定义对应的符号表 */
		header->u.header.symtab = ptab;
		/* 将AST树放入AST森林中 */
		list_append(&ast_forest, header);

		/* 生成一颗以header书为根的子树，存放函数体信息 */
		now_function = new_tree(FUNCTION, ptab->type, header, NULL);
	}
}
#line 2400 "rule.c" /* yacc.c:1646  */
    break;

  case 56:
#line 817 "spl.y" /* yacc.c:1646  */
    {
	{
		list_clear(&dag_forest);
		t = new_tree(TAIL, NULL, NULL, NULL);
		list_append(&ast_forest, t);

		/* generate dag forest. */
		gen_dag(&ast_forest, &dag_forest);

		/* emit asm code. */
		emit_code(&dag_forest);
	}

	pop_symtab_stack();
}
#line 2420 "rule.c" /* yacc.c:1646  */
    break;

  case 57:
#line 836 "spl.y" /* yacc.c:1646  */
    {
	list_clear(&ast_forest);
	list_clear(&para_list);

	ptab = new_symtab(top_symtab_stack());
	push_symtab_stack(ptab);
}
#line 2432 "rule.c" /* yacc.c:1646  */
    break;

  case 58:
#line 844 "spl.y" /* yacc.c:1646  */
    {
	ptab = top_symtab_stack();
	strncpy(ptab->name, (yyvsp[-1].p_char), NAME_LEN);
	sprintf(ptab->rname, "rtn%03d",ptab->id);
	ptab->defn = DEF_PROC;
	p = new_symbol((yyvsp[-1].p_char), DEF_PROC, TYPE_VOID);
	add_symbol_to_table(ptab,p);
	reverse_parameters(ptab);

	{
		Tree header;
		
		header = new_tree(HEADER, find_type_by_id(TYPE_VOID), NULL, NULL);
		header->u.header.para = &para_list;
		list_append(&ast_forest, header);
		now_function = new_tree(ROUTINE, find_type_by_id(TYPE_VOID), header, NULL);
	}
}
#line 2455 "rule.c" /* yacc.c:1646  */
    break;

  case 59:
#line 865 "spl.y" /* yacc.c:1646  */
    {/* 参数部分可以为空 */}
#line 2461 "rule.c" /* yacc.c:1646  */
    break;

  case 60:
#line 867 "spl.y" /* yacc.c:1646  */
    {
	ptab = top_symtab_stack();
	ptab->local_size = 0;
}
#line 2470 "rule.c" /* yacc.c:1646  */
    break;

  case 61:
#line 874 "spl.y" /* yacc.c:1646  */
    {/* 不同类型的参数之间使用符号';'进行分割 */}
#line 2476 "rule.c" /* yacc.c:1646  */
    break;

  case 62:
#line 875 "spl.y" /* yacc.c:1646  */
    {}
#line 2482 "rule.c" /* yacc.c:1646  */
    break;

  case 63:
#line 880 "spl.y" /* yacc.c:1646  */
    {
	/* 获取当前符号表 */
	ptab = top_symtab_stack();

	for(p = (yyvsp[-2].p_symbol); p;)
	{
		/* 初始化val_para_list符号链表中的符号的大类以及小类 */
		if((yyvsp[0].p_type)->type_id == TYPE_SUBRANGE || (yyvsp[0].p_type)->type_id == TYPE_ENUM)
			p->type = (yyvsp[0].p_type)->first->type;
		else
			p->type = find_type_by_id((yyvsp[0].p_type)->type_id);
		p->type_link = (yyvsp[0].p_type);
		p->defn = DEF_VALPARA;

		q = p; 
		p = p->next;
		q->next = NULL;

		/* 将符号放入符号表中 */
		add_symbol_to_table(ptab, q);

		/* append to paralist. */
		list_append(&para_list, q);
	}

	(yyvsp[-2].p_symbol) = NULL;
}
#line 2514 "rule.c" /* yacc.c:1646  */
    break;

  case 64:
#line 908 "spl.y" /* yacc.c:1646  */
    {
	ptab = top_symtab_stack();

	for(p = (yyvsp[-2].p_symbol); p;)
	{
		/* 初始化val_para_list符号链表中的符号的大类以及小类 */
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
		/* 将符号放入符号表中 */
		add_symbol_to_table(ptab,q);

		/* append to para_list. */
		list_append(&para_list, q);
	}
	(yyvsp[-2].p_symbol) = NULL;
}
#line 2544 "rule.c" /* yacc.c:1646  */
    break;

  case 65:
#line 936 "spl.y" /* yacc.c:1646  */
    {/* 默认val_para_list的值等于name_list的值 */}
#line 2550 "rule.c" /* yacc.c:1646  */
    break;

  case 66:
#line 941 "spl.y" /* yacc.c:1646  */
    {
	(yyval.p_symbol) = (yyvsp[0].p_symbol);
}
#line 2558 "rule.c" /* yacc.c:1646  */
    break;

  case 67:
#line 947 "spl.y" /* yacc.c:1646  */
    {/* 混合类型的语句（算数，赋值，判断，循环，跳转等） */}
#line 2564 "rule.c" /* yacc.c:1646  */
    break;

  case 68:
#line 951 "spl.y" /* yacc.c:1646  */
    {/* 可以是空函数 */}
#line 2570 "rule.c" /* yacc.c:1646  */
    break;

  case 69:
#line 952 "spl.y" /* yacc.c:1646  */
    {}
#line 2576 "rule.c" /* yacc.c:1646  */
    break;

  case 70:
#line 953 "spl.y" /* yacc.c:1646  */
    {/* 错误处理 */}
#line 2582 "rule.c" /* yacc.c:1646  */
    break;

  case 71:
#line 958 "spl.y" /* yacc.c:1646  */
    {/* 用于case语句 */}
#line 2588 "rule.c" /* yacc.c:1646  */
    break;

  case 72:
#line 959 "spl.y" /* yacc.c:1646  */
    {}
#line 2594 "rule.c" /* yacc.c:1646  */
    break;

  case 73:
#line 963 "spl.y" /* yacc.c:1646  */
    {}
#line 2600 "rule.c" /* yacc.c:1646  */
    break;

  case 74:
#line 964 "spl.y" /* yacc.c:1646  */
    { }
#line 2606 "rule.c" /* yacc.c:1646  */
    break;

  case 75:
#line 965 "spl.y" /* yacc.c:1646  */
    { /* 过程或者函数调用 */ }
#line 2612 "rule.c" /* yacc.c:1646  */
    break;

  case 76:
#line 966 "spl.y" /* yacc.c:1646  */
    {/* compound_stmt可以嵌套 */}
#line 2618 "rule.c" /* yacc.c:1646  */
    break;

  case 77:
#line 967 "spl.y" /* yacc.c:1646  */
    { }
#line 2624 "rule.c" /* yacc.c:1646  */
    break;

  case 78:
#line 968 "spl.y" /* yacc.c:1646  */
    { }
#line 2630 "rule.c" /* yacc.c:1646  */
    break;

  case 79:
#line 969 "spl.y" /* yacc.c:1646  */
    { }
#line 2636 "rule.c" /* yacc.c:1646  */
    break;

  case 80:
#line 970 "spl.y" /* yacc.c:1646  */
    { }
#line 2642 "rule.c" /* yacc.c:1646  */
    break;

  case 81:
#line 971 "spl.y" /* yacc.c:1646  */
    { }
#line 2648 "rule.c" /* yacc.c:1646  */
    break;

  case 82:
#line 972 "spl.y" /* yacc.c:1646  */
    { }
#line 2654 "rule.c" /* yacc.c:1646  */
    break;

  case 83:
#line 977 "spl.y" /* yacc.c:1646  */
    {
	/* 寻找对应的符号 */
	p = find_symbol(top_symtab_stack(), (yyvsp[-2].p_char));
	if (p == NULL)
	{
		parse_error("Undefined identifier", (yyvsp[-2].p_char));
		p = install_temporary_symbol((yyvsp[-2].p_char), DEF_VAR, TYPE_INTEGER);
	}

	/* 检查赋值形式是否合法 */
	if(p->type->type_id == TYPE_ARRAY
		||p->type->type_id == TYPE_RECORD)
	{
		parse_error("lvalue expected","");
		/* return 0; */
	}

	if (p && p->defn != DEF_FUNCT)
	{
	/* 检查yNAME和expression的类型是否匹配 */

		if(p->type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
		{
			parse_error("type mismatch","");
			/* return 0; */
		}
	}
	else
	{
		/* 函数或者过程 */
		ptab = find_routine((yyvsp[-2].p_char));
		if(ptab)
		{
		/* 检查yNAME和expression的类型是否匹配 */
			if(ptab->type->type_id != (yyvsp[0].p_tree)->result_type->type_id)
			{
				parse_error("type mismatch","");
				/* return 0; */
			}
		}
		else{
			parse_error("Undeclared identifier.",(yyvsp[-2].p_char));
			/* 定义一个临时symbol，使得同一个错误在程序接下来的执行过程中不会反复出现 */
			install_temporary_symbol((yyvsp[-2].p_char), DEF_VAR, (yyvsp[0].p_tree)->result_type->type_id);
			/* return 0; */
		}
	}

	/* 地址AST树 */
	t = address_tree(NULL, p);

	/* 赋值AST树 */
	(yyval.p_tree) = assign_tree(t, (yyvsp[0].p_tree));
	
	/* 放入AST森林 */
	list_append(&ast_forest, (yyval.p_tree));
}
#line 2716 "rule.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1035 "spl.y" /* yacc.c:1646  */
    {
	/* 符号表 */
	p = find_symbol(top_symtab_stack(), (yyvsp[-1].p_char));

	/* 检查符号类型 */
	if(!p || p->type->type_id != TYPE_ARRAY){
		parse_error("Undeclared array name",(yyvsp[-1].p_char));
		return 0;
	}
	
	/* 将当前符号压栈 */
	push_term_stack(p);
}
#line 2734 "rule.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1049 "spl.y" /* yacc.c:1646  */
    {
	/* 获取符号 */
	p = top_term_stack();
	
	/* 数组AST节点（定位数组项） */
	t = array_factor_tree(p, (yyvsp[-1].p_tree));

	/* 地址AST节点（定位变量） */
	t = address_tree(t, p);

	/* 当前AST节点压栈 */
	push_ast_stack(t);
}
#line 2752 "rule.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1063 "spl.y" /* yacc.c:1646  */
    {
	/* 获取AST节点 */
	t = pop_ast_stack();

	/* 赋值AST节点 */
	(yyval.p_tree) = assign_tree(t, (yyvsp[0].p_tree));

	/* 放入AST森林 */
	list_append(&ast_forest, (yyval.p_tree));
}
#line 2767 "rule.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1074 "spl.y" /* yacc.c:1646  */
    {
	p = find_symbol(top_symtab_stack(), (yyvsp[-2].p_char));
	if(!p || p->type->type_id != TYPE_RECORD){
		parse_error("Undeclared record vaiable", (yyvsp[-2].p_char));
		return 0;
	}

	q = find_field(p, (yyvsp[0].p_char));
	if(!q || q->defn != DEF_FIELD){
		parse_error("Undeclared field", (yyvsp[0].p_char));
		return 0;
	}

	t = field_tree(p, q);
	t = address_tree(t, q);
	push_ast_stack(t);
}
#line 2789 "rule.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1092 "spl.y" /* yacc.c:1646  */
    {
	t = pop_ast_stack();
	(yyval.p_tree) = assign_tree(t, (yyvsp[0].p_tree));
	list_append(&ast_forest, (yyval.p_tree));
}
#line 2799 "rule.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1101 "spl.y" /* yacc.c:1646  */
    {
	/* 符号表 */
	ptab = find_routine((yyvsp[0].p_char));
	if(!ptab || ptab->defn != DEF_PROC){
		parse_error("Undeclared procedure", (yyvsp[0].p_char));
		return 0;
	}

	/* 初始化调用AST节点 */
	(yyval.p_tree) = call_tree(ptab, NULL);
	list_append(&ast_forest, (yyval.p_tree));
}
#line 2816 "rule.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1114 "spl.y" /* yacc.c:1646  */
    {
	/* 符号表 */
	ptab = find_routine((yyvsp[0].p_char));
	if(!ptab || ptab->defn != DEF_PROC){
			parse_error("Undeclared procedure", (yyvsp[0].p_char));
			return 0;
	}

	/* 保存调用上下文 */
	push_call_stack(ptab);
}
#line 2832 "rule.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1126 "spl.y" /* yacc.c:1646  */
    {
	/* 初始化调用AST节点，其中args表示参数AST节点。 */
	(yyval.p_tree) = call_tree(top_call_stack(), args);
	list_append(&ast_forest, (yyval.p_tree));
  /* 清除调用上下文 */
	pop_call_stack();
}
#line 2844 "rule.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1134 "spl.y" /* yacc.c:1646  */
    {
	(yyval.p_tree) = sys_tree((yyvsp[0].p_lex)->attr, NULL);
	list_append(&ast_forest, (yyval.p_tree));
}
#line 2853 "rule.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1139 "spl.y" /* yacc.c:1646  */
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
#line 2870 "rule.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1152 "spl.y" /* yacc.c:1646  */
    {
	(yyval.p_tree) = sys_tree((yyvsp[-4].p_lex)->attr, args);
	list_append(&ast_forest, (yyval.p_tree));
	
	pop_call_stack();
}
#line 2881 "rule.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1159 "spl.y" /* yacc.c:1646  */
    {
	if(!(yyvsp[-1].p_tree)){
		parse_error("too few parameters in call to", "read");
		return 0;
	}
	if (generic((yyvsp[-1].p_tree)->op) == LOAD)
		t = address_tree(NULL, (yyvsp[-1].p_tree)->u.generic.sym);
	else
		t = address_tree((yyvsp[-1].p_tree), (yyvsp[-1].p_tree)->u.generic.sym);
	(yyval.p_tree) = sys_tree(pREAD, t);
	list_append(&ast_forest, (yyval.p_tree));
}
#line 2898 "rule.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1175 "spl.y" /* yacc.c:1646  */
    {
	/* 标记block开始 */
	t = new_tree(BLOCKBEG, NULL, NULL, NULL);
	list_append(&ast_forest, t);
}
#line 2908 "rule.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1182 "spl.y" /* yacc.c:1646  */
    {
	/* 标记block结束 */
	t = new_tree(BLOCKEND, NULL, NULL, NULL);
	list_append(&ast_forest, t);
}
#line 2918 "rule.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1191 "spl.y" /* yacc.c:1646  */
    {
	/* 记录标签层级 */
	push_lbl_stack(if_label_count++);
}
#line 2927 "rule.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1196 "spl.y" /* yacc.c:1646  */
    {
	/* 初始化名称 */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_false_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;

	/* 初始化符号 */
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	/* 初始化条件跳转AST节点（expression为假时，进行跳转，为真时继续往下执行） */
	t = cond_jump_tree((yyvsp[-1].p_tree), false, new_label);
	list_append(&ast_forest, t);
}
#line 2944 "rule.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1209 "spl.y" /* yacc.c:1646  */
    {
  /* 初始化符号 */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_false_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	/* 初始化IF标签AST节点（指定结束的位置） */
	t = label_tree(new_label);

	/* 记录AST节点 */
	push_ast_stack(t);

	/* 初始化符号 */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	/* 初始化IF跳转AST节点（执行完毕后跳转到结束位置，如果kELSE那部分内容存在则跳过） */
	t = jump_tree(exit_label);
	list_append(&ast_forest, t);
	
	/* 获取AST节点 */
	t = pop_ast_stack();

	list_append(&ast_forest, t);
}
#line 2975 "rule.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1236 "spl.y" /* yacc.c:1646  */
    {
	/* 初始化符号 */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "if_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	/* 初始化ELSE标签AST节点 */
	t = label_tree(exit_label);
	list_append(&ast_forest, t);
	pop_lbl_stack();
}
#line 2991 "rule.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1248 "spl.y" /* yacc.c:1646  */
    {
	printf("expression expected.\n");
}
#line 2999 "rule.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1252 "spl.y" /* yacc.c:1646  */
    {
	printf("then matched.\n");
}
#line 3007 "rule.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1259 "spl.y" /* yacc.c:1646  */
    {}
#line 3013 "rule.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1260 "spl.y" /* yacc.c:1646  */
    {}
#line 3019 "rule.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1265 "spl.y" /* yacc.c:1646  */
    {
	/* 初始化REPEAT标签节点 */
	push_lbl_stack(repeat_label_count++);
	snprintf(mini_buf, sizeof(mini_buf) - 1, "repeat_%d", repeat_label_count - 1);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = label_tree(new_label);
	list_append(&ast_forest, t);
}
#line 3033 "rule.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1275 "spl.y" /* yacc.c:1646  */
    {
	/* 初始化REPEAT条件跳转AST节点 */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "repeat_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	new_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = cond_jump_tree((yyvsp[0].p_tree), false, new_label);
	list_append(&ast_forest, t);
	pop_lbl_stack();
}
#line 3047 "rule.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1288 "spl.y" /* yacc.c:1646  */
    {
  /* 初始化WHILE标签AST节点 */
	push_lbl_stack(while_label_count++);
	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_test_%d", while_label_count - 1);
	mini_buf[sizeof(mini_buf) - 1] = 0;
	test_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = label_tree(test_label);
	list_append(&ast_forest, t);
}
#line 3061 "rule.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1298 "spl.y" /* yacc.c:1646  */
    {
	/* 初始化WHILE条件跳转AST节点 */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = cond_jump_tree((yyvsp[-1].p_tree), false, exit_label);
	list_append(&ast_forest, t);
}
#line 3074 "rule.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1307 "spl.y" /* yacc.c:1646  */
    {
	/* generate while_exit_%d label tree and push. */
	snprintf(mini_buf, sizeof(mini_buf) - 1, "while_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = label_tree(exit_label);
	push_ast_stack(t);

	/* 初始化跳转AST节点（跳转到WHILE标签） */
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
}
#line 3100 "rule.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1332 "spl.y" /* yacc.c:1646  */
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
}
#line 3134 "rule.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1362 "spl.y" /* yacc.c:1646  */
    {
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
}
#line 3160 "rule.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1384 "spl.y" /* yacc.c:1646  */
    {
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
}
#line 3194 "rule.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1417 "spl.y" /* yacc.c:1646  */
    {
	(yyval.num) = kTO;
}
#line 3202 "rule.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1421 "spl.y" /* yacc.c:1646  */
    {
	(yyval.num) = kDOWNTO;
}
#line 3210 "rule.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1428 "spl.y" /* yacc.c:1646  */
    {
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
}
#line 3230 "rule.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1444 "spl.y" /* yacc.c:1646  */
    {
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
			
			t = compare_expr_tree(EQ, (yyvsp[-2].p_tree), cases[i + 1]);
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
}
#line 3266 "rule.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1485 "spl.y" /* yacc.c:1646  */
    {
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
}
#line 3288 "rule.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1503 "spl.y" /* yacc.c:1646  */
    {
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);

	t = jump_tree(exit_label);
	list_append(&ast_forest, t);
}
#line 3301 "rule.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1513 "spl.y" /* yacc.c:1646  */
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
}
#line 3334 "rule.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1542 "spl.y" /* yacc.c:1646  */
    {
	snprintf(mini_buf, sizeof(mini_buf) - 1, "switch_exit_%d", top_lbl_stack());
	mini_buf[sizeof(mini_buf) - 1] = 0;
	exit_label = new_symbol(mini_buf, DEF_LABEL, TYPE_VOID);
	t = jump_tree(exit_label);
	list_append(&ast_forest, t);
}
#line 3346 "rule.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1558 "spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（>=），由于优先级问题，放在expr表达式中（expression表达式中的运算优先级比expr中的要低），仅支持左结合 */
	(yyval.p_tree) = compare_expr_tree(GE, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3355 "rule.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1563 "spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（>），由于优先级问题，放在expr表达式中（expression表达式中的运算优先级比expr中的要低），仅支持左结合 */
	(yyval.p_tree) = compare_expr_tree(GT, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3364 "rule.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1568 "spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（<=），由于优先级问题，放在expr表达式中（expression表达式中的运算优先级比expr中的要低），仅支持左结合 */
	(yyval.p_tree) = compare_expr_tree(LE, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3373 "rule.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1573 "spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（<），由于优先级问题，放在expr表达式中（expression表达式中的运算优先级比expr中的要低），仅支持左结合 */
	(yyval.p_tree) = compare_expr_tree(LT, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3382 "rule.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1578 "spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（=），由于优先级问题，放在expr表达式中（expression表达式中的运算优先级比expr中的要低），仅支持左结合 */
	(yyval.p_tree) = compare_expr_tree(EQ, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3391 "rule.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1583 "spl.y" /* yacc.c:1646  */
    {
	/* 比较运算AST树（<>，表示不想等），由于优先级问题，放在expr表达式中（expression表达式中的运算优先级比expr中的要低），仅支持左结合 */
	(yyval.p_tree) = compare_expr_tree(NE, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3400 "rule.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1588 "spl.y" /* yacc.c:1646  */
    {
	(yyval.p_tree) = (yyvsp[0].p_tree);
}
#line 3408 "rule.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1595 "spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（+），由于优先级问题，放在expr表达式中（expr表达式中的运算优先级比term中的要低），仅支持左结合 */
	(yyval.p_tree) = binary_expr_tree(ADD, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3417 "rule.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1600 "spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（-），由于优先级问题，放在expr表达式中（expr表达式中的运算优先级比term中的要低），仅支持左结合 */
	(yyval.p_tree) = binary_expr_tree(SUB, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3426 "rule.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1605 "spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（or），由于优先级问题，放在expr表达式中（expr表达式中的运算优先级比term中的要低），仅支持左结合  */
	(yyval.p_tree) = binary_expr_tree(OR, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3435 "rule.c" /* yacc.c:1646  */
    break;

  case 139:
#line 1610 "spl.y" /* yacc.c:1646  */
    {
	(yyval.p_tree) = (yyvsp[0].p_tree);
}
#line 3443 "rule.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1617 "spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（*），由于优先级问题，放在expr表达式中（运算符优先级最高），仅支持左结合。 */
	(yyval.p_tree) = binary_expr_tree(MUL, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3452 "rule.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1622 "spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（/），由于优先级问题，放在expr表达式中（运算符优先级最高），仅支持左结合。 */
	(yyval.p_tree) = binary_expr_tree(DIV, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3461 "rule.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1627 "spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（div），由于优先级问题，放在expr表达式中（运算符优先级最高），仅支持左结合。 */
	(yyval.p_tree) = binary_expr_tree(DIV, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3470 "rule.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1632 "spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（mod），由于优先级问题，放在expr表达式中（运算符优先级最高），仅支持左结合。 */
	(yyval.p_tree) = binary_expr_tree(MOD, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3479 "rule.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1637 "spl.y" /* yacc.c:1646  */
    {
	/* 二元运算AST树（and），由于优先级问题，放在expr表达式中（运算符优先级最高），仅支持左结合。 */
	(yyval.p_tree) = binary_expr_tree(AND, (yyvsp[-2].p_tree), (yyvsp[0].p_tree));
}
#line 3488 "rule.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1642 "spl.y" /* yacc.c:1646  */
    {
	(yyval.p_tree) = (yyvsp[0].p_tree);
}
#line 3496 "rule.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1649 "spl.y" /* yacc.c:1646  */
    {
	/* 因素，表达式的基本组成部分之一（因素和操作符） */
	p = NULL;

	if((p = find_symbol(top_symtab_stack(), (yyvsp[0].p_char))))
	{
		/* 普通符号，不能直接对array以及record类型的符号进行运算操作（需要制定下标或者属性） */
		if(p->type->type_id == TYPE_ARRAY
			||p->type->type_id == TYPE_RECORD)
		{
			parse_error("rvalue expected",  "");
			return 0;
		}
	}
	else if ((ptab = find_routine((yyvsp[0].p_char))) == NULL) /* 寻找自定义函数或者过程 */
	{
		parse_error("Undeclard identificr", (yyvsp[0].p_char));
		/* 既不是普通符号也不是自定义函数或者过程，
		 创建一个临时符号（目的是为了让解析程序可以继续往下执行） */
		p = install_temporary_symbol((yyvsp[0].p_char), DEF_VAR, TYPE_INTEGER);
	}
	if (p)
	{
		/* 普通符号 */
		(yyval.p_tree) = id_factor_tree(NULL, p);
	}
	else
	{
		/* 自定义函数或者过程调用（无参数调用） */
		(yyval.p_tree) = call_tree(ptab, NULL);
	}
}
#line 3533 "rule.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1682 "spl.y" /* yacc.c:1646  */
    {
	/* 寻找自定义函数或者过程 */
	if((ptab = find_routine((yyvsp[0].p_char))))
  		push_call_stack(ptab);
	else
	{
		parse_error("Undeclared funtion",(yyvsp[0].p_char));
		return  0;
	}
}
#line 3548 "rule.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1693 "spl.y" /* yacc.c:1646  */
    {
	/* 自定义函数或者过程调用（有参调用） */
	(yyval.p_tree) = call_tree(ptab, args);

	/* 函数调用结束，当前上下文退栈 */
	pop_call_stack();
}
#line 3560 "rule.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1701 "spl.y" /* yacc.c:1646  */
    {
	ptab = find_sys_routine((yyvsp[0].p_lex)->attr);

	/* 系统函数或者过程调用（无参调用） */
	(yyval.p_tree) = sys_tree((yyvsp[0].p_lex)->attr, NULL);
}
#line 3571 "rule.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1708 "spl.y" /* yacc.c:1646  */
    {
	ptab = find_sys_routine((yyvsp[0].p_lex)->attr);
	push_call_stack(ptab);
}
#line 3580 "rule.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1713 "spl.y" /* yacc.c:1646  */
    {
	/* 获取当前需要调用的函数或者过程对应的符号表 */
	ptab = top_call_stack();

	/* 系统函数或者过程调用（有参调用） */
	(yyval.p_tree) = sys_tree((yyvsp[-4].p_lex)->attr, args);
}
#line 3592 "rule.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1721 "spl.y" /* yacc.c:1646  */
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
#line 3625 "rule.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1750 "spl.y" /* yacc.c:1646  */
    {
 	/* AST树（提高expression的优先级） */
	(yyval.p_tree) = (yyvsp[-1].p_tree);
}
#line 3634 "rule.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1755 "spl.y" /* yacc.c:1646  */
    {
	/* 一元操作符（not） */
	(yyval.p_tree) = not_tree((yyvsp[0].p_tree));
}
#line 3643 "rule.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1760 "spl.y" /* yacc.c:1646  */
    {
	/* 一元操作符（-） */
	(yyval.p_tree) = neg_tree((yyvsp[0].p_tree));
}
#line 3652 "rule.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1765 "spl.y" /* yacc.c:1646  */
    {
	/* 寻找对应的符号 */
	p = find_symbol(
		top_symtab_stack(), (yyvsp[-1].p_char));
	
	/* 检查符号类型是否是数组 */
	if(!p || p->type->type_id != TYPE_ARRAY){
		parse_error("Undeclared array name",(yyvsp[-1].p_char));
		return  0;
	}

	/* 数组符号入栈（保存上下文） */
	push_term_stack(p);
}
#line 3671 "rule.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1780 "spl.y" /* yacc.c:1646  */
    {
	/* 数组符号出栈（获取上下文） */
	p = pop_term_stack(p);
	/* 数组AST树 */
	t = array_factor_tree(p, (yyvsp[-1].p_tree));
	/* 数组取值AST树 */
	(yyval.p_tree) = id_factor_tree(t, p);
}
#line 3684 "rule.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1789 "spl.y" /* yacc.c:1646  */
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
	t = field_tree(p, q);
	/* field取值AST树 */
	(yyval.p_tree) = id_factor_tree(t, q);
}
#line 3713 "rule.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1817 "spl.y" /* yacc.c:1646  */
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
#line 3731 "rule.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1831 "spl.y" /* yacc.c:1646  */
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
	args = arg_tree(args, rtn, arg, (yyvsp[0].p_tree));
}
#line 3754 "rule.c" /* yacc.c:1646  */
    break;


#line 3758 "rule.c" /* yacc.c:1646  */
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
#line 1851 "spl.y" /* yacc.c:1906  */


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
	memset(&ast_forest, 0, sizeof(ast_forest));
	memset(&para_list, 0, sizeof(para_list));
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
