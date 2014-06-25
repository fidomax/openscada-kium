/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "func_analise.ypp" /* yacc.c:339  */

//OpenSCADA system module DAQ.JavaLikeCalc file: func_analise.ypp
/***************************************************************************
 *   Copyright (C) 2005-2014 by Roman Savochenko, <rom_as@oscada.org>      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; version 2 of the License.               *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <string.h>

#include <tsys.h>
#include <tmess.h>

#include "freefunc.h"
#include "freelib.h"
#include "virtual.h"

#define YYERROR_VERBOSE true

namespace JavaLikeCalc
{
char m_buf[STR_BUF_LEN];
struct YYLTYPE;

int yylex( );
void yyerror( const char *s );
void sfErr( const string &mess, YYLTYPE *ps );


#line 108 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 0
#endif


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
    ERR = 258,
    VAR_DIR = 259,
    IF = 260,
    ELSE = 261,
    WHILE = 262,
    FOR = 263,
    IN = 264,
    BREAK = 265,
    CONTINUE = 266,
    ADDEQ = 267,
    SUBEQ = 268,
    MULEQ = 269,
    DIVEQ = 270,
    BITSHLEFT = 271,
    BITSHRIGHT = 272,
    RETURN = 273,
    NEW = 274,
    OBJECT = 275,
    ARRAY = 276,
    REGEXP = 277,
    FUNC = 278,
    B_FUNC = 279,
    B_FUNC1 = 280,
    B_FUNC2 = 281,
    VAR = 282,
    CONST = 283,
    O_PRP_F = 284,
    OR = 285,
    AND = 286,
    GE = 287,
    LE = 288,
    EQ = 289,
    NE = 290,
    UN_MINUS = 291,
    INCREM = 292,
    DECREM = 293
  };
#endif
/* Tokens.  */
#define ERR 258
#define VAR_DIR 259
#define IF 260
#define ELSE 261
#define WHILE 262
#define FOR 263
#define IN 264
#define BREAK 265
#define CONTINUE 266
#define ADDEQ 267
#define SUBEQ 268
#define MULEQ 269
#define DIVEQ 270
#define BITSHLEFT 271
#define BITSHRIGHT 272
#define RETURN 273
#define NEW 274
#define OBJECT 275
#define ARRAY 276
#define REGEXP 277
#define FUNC 278
#define B_FUNC 279
#define B_FUNC1 280
#define B_FUNC2 281
#define VAR 282
#define CONST 283
#define O_PRP_F 284
#define OR 285
#define AND 286
#define GE 287
#define LE 288
#define EQ 289
#define NE 290
#define UN_MINUS 291
#define INCREM 292
#define DECREM 293

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 46 "func_analise.ypp" /* yacc.c:355  */

    int	id;		//Function id
    Reg	*reg;		//Variable and Constant registers list index and function list index
    int	fp_cnt;		//Function parameters counter
    int	prg_cd;		//Program code
    char op[256];	//Object's properties.

#line 229 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);



/* Copy the second part of user declarations.  */

#line 258 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:358  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   643

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  82
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  197

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,     2,     2,    48,    36,     2,
      55,    56,    46,    44,    61,    45,     2,    47,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    32,    54,
      39,    30,    38,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    59,     2,    60,    37,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    57,    35,    58,    51,     2,     2,     2,
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
      25,    26,    27,    28,    29,    33,    34,    40,    41,    42,
      43,    49,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    75,    75,    76,    77,    78,    79,    80,    81,    83,
      85,    87,    89,    91,    92,    93,    94,   111,   113,   114,
     115,   116,   117,   118,   120,   121,   129,   137,   145,   153,
     161,   170,   179,   180,   181,   188,   196,   205,   215,   225,
     235,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   262,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   278,   279,   280,   282,   283,   284,   285,   286,   287,
     288,   289,   290
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ERR", "VAR_DIR", "IF", "ELSE", "WHILE",
  "FOR", "IN", "BREAK", "CONTINUE", "ADDEQ", "SUBEQ", "MULEQ", "DIVEQ",
  "BITSHLEFT", "BITSHRIGHT", "RETURN", "NEW", "OBJECT", "ARRAY", "REGEXP",
  "FUNC", "B_FUNC", "B_FUNC1", "B_FUNC2", "VAR", "CONST", "O_PRP_F", "'='",
  "'?'", "':'", "OR", "AND", "'|'", "'&'", "'^'", "'>'", "'<'", "GE", "LE",
  "EQ", "NE", "'+'", "'-'", "'*'", "'/'", "'%'", "UN_MINUS", "'!'", "'~'",
  "INCREM", "DECREM", "';'", "'('", "')'", "'{'", "'}'", "'['", "']'",
  "','", "$accept", "root", "solver", "solve", "var", "assign", "expr",
  "prmlst", "if", "if_expr", "OR_expr", "AND_expr", "cycl", "end", YY_NULLPTR
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
      61,    63,    58,   285,   286,   124,    38,    94,    62,    60,
     287,   288,   289,   290,    43,    45,    42,    47,    37,   291,
      33,   126,   292,   293,    59,    40,    41,   123,   125,    91,
      93,    44
};
# endif

#define YYPACT_NINF -56

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-56)))

#define YYTABLE_NINF -83

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     149,   -56,     2,   105,   -56,   -22,   -39,   -56,   -35,   -32,
      -1,   192,    -9,   -56,   -56,   -56,   220,   -12,   -56,   -56,
     203,     7,     0,   -56,   -56,   104,    10,    13,    49,    56,
     -56,   203,   203,   203,     0,     0,   -56,   203,    40,   381,
     203,     3,   203,   203,   203,   203,    59,   203,   -56,   -56,
     -56,   203,   -56,     0,   414,   203,   248,   -10,    65,    75,
      76,   203,    44,   203,   203,   -11,   -11,   -11,   -14,   -14,
     447,   203,   -56,   -56,   203,   203,   -56,    79,   -56,   -56,
     -56,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   -56,   203,   203,   203,   203,
     546,   -55,   -56,   546,   546,   546,   546,   203,   546,   315,
     252,    41,   -56,   546,   -56,   -56,    82,   203,   203,   -28,
     -56,   480,   281,   -56,   546,   240,   240,   203,   579,   579,
     579,   584,   584,   584,   584,   584,   584,    89,    89,   -11,
     -11,   -11,   348,   546,   546,   546,     4,   203,    -4,   -56,
     182,    86,   203,   203,   -56,    -2,    45,   -56,   -56,   203,
      47,   -56,   111,   -56,   -56,   -56,    91,   -56,   -56,   182,
     546,   546,   -56,   -56,   513,   -56,   203,   152,   -56,    99,
     107,   -56,   546,   182,   -56,   182,     0,   -56,   -56,   -56,
      41,   -56,   -56,   108,   182,   -56,   -56
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,    32,     1,     0,     0,    81,     0,     0,
       0,     0,     0,    19,     4,     5,     0,     0,     2,    20,
       0,     0,    32,    13,    14,     0,     0,     0,     0,     0,
      33,     0,     0,     0,     0,     0,    15,     0,    35,     0,
      74,    32,     0,     0,     0,     0,    21,     0,    30,    31,
       7,     0,     6,    32,     0,     0,     0,     0,     0,     0,
       0,    74,     0,     0,     0,    69,    67,    68,    39,    40,
       0,     0,    37,    38,     0,     0,    34,    71,    78,    79,
      80,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    16,     0,     0,     0,     0,
      75,     0,    18,    26,    27,    28,    29,    74,    25,     0,
       0,    24,    77,    82,    81,    81,     0,    74,    74,     0,
      41,     0,     0,    56,    36,    59,    60,    74,    53,    54,
      55,    62,    61,    63,    64,    65,    66,    48,    49,    50,
      51,    52,     0,    82,    82,    82,     0,    74,     0,    22,
      32,     0,     0,     0,    45,     0,     0,    44,    42,     0,
       0,    72,     0,    57,    58,    17,    76,    23,    82,    32,
      82,    82,    46,    47,     0,    73,     0,     8,    82,     0,
       0,    43,    82,    32,    10,    32,    32,    70,    82,    82,
      82,     9,    12,     0,    32,    82,    11
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -56,   -56,   151,    19,    -3,   -13,    -8,   -20,   -56,   -56,
     -56,   -56,   -43,   -49
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    15,    38,    17,   100,   101,   150,    97,
      98,    99,    21,    18
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,   146,     4,    39,     5,    19,   147,     5,     6,    57,
       7,     8,    54,     9,    10,    46,    20,    76,    77,    56,
      22,    11,    23,    65,    66,    67,    12,    13,   157,    70,
      13,    68,    69,   147,   103,   104,   105,   106,    16,   108,
     111,   119,    52,   109,   115,    51,    40,   113,    96,    53,
     110,    53,   167,    24,   172,   121,   122,   147,   165,   147,
      14,   102,    55,   124,   151,    61,   125,   126,    62,    46,
      71,   152,   153,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   148,   142,   143,
     144,   145,    72,    73,   162,   163,   164,   155,   156,    51,
     120,   173,    53,   175,    63,   -82,   147,   160,   147,     5,
       6,    64,     7,     8,   107,     9,    10,    76,    77,   177,
     116,   179,   180,    11,    58,    59,    60,   166,    12,   184,
     117,   118,    13,   187,   127,    92,    93,    94,   154,   191,
     192,   193,   169,   176,   170,   171,   196,    16,    96,    -4,
       1,   174,   147,    -4,    -4,   185,    -4,    -4,   183,    -4,
      -4,   186,    14,     0,   194,    41,    16,    -4,   182,   168,
       0,     0,    -4,   190,     0,     0,    -4,     0,     0,     0,
      16,     0,    16,   110,     0,     0,     5,     6,   178,     7,
       8,    16,     9,    10,     0,     0,     5,     0,     0,     0,
      11,     0,   188,    -4,   189,    12,    -4,     5,     0,    13,
      -4,    25,     0,   195,     0,    26,    27,    28,    29,    13,
      30,     0,    25,     0,     0,     0,    26,    27,    28,    29,
      13,    30,    42,    43,    44,    45,     0,    31,     0,    14,
       0,     0,    32,    33,    34,    35,    36,    37,    31,    46,
      47,     0,     0,    32,    33,    34,    35,   114,    37,     0,
      42,    43,    44,    45,    42,    43,    44,    45,    76,    77,
       0,     0,    48,    49,    50,     0,     0,    46,    47,    51,
       0,    46,    47,     0,    90,    91,    92,    93,    94,     0,
       0,     0,     0,     0,     0,     0,     0,    74,    75,    96,
      48,    49,     0,     0,    48,    49,     0,    51,     0,    76,
      77,    51,    78,     0,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       0,    74,    75,     0,     0,     0,     0,     0,     0,     0,
      96,     0,   159,    76,    77,     0,    78,     0,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    74,    75,     0,     0,     0,     0,
       0,     0,     0,     0,    96,   149,    76,    77,     0,    78,
       0,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    74,    75,     0,
       0,     0,     0,     0,     0,     0,     0,    96,   161,    76,
      77,     0,    78,     0,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      74,    75,     0,     0,     0,    95,     0,     0,     0,     0,
      96,     0,    76,    77,     0,    78,     0,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    74,    75,     0,     0,     0,     0,     0,
     112,     0,     0,    96,     0,    76,    77,     0,    78,     0,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    74,    75,     0,     0,
       0,     0,     0,   123,     0,     0,    96,     0,    76,    77,
       0,    78,     0,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    74,
      75,     0,     0,     0,     0,     0,   158,     0,     0,    96,
       0,    76,    77,     0,    78,     0,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    74,    75,     0,     0,     0,     0,     0,   181,
       0,     0,    96,     0,    76,    77,     0,    78,     0,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    74,    75,     0,     0,     0,
      74,    75,     0,     0,     0,    96,     0,    76,    77,     0,
       0,     0,    76,    77,     0,     0,     0,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    90,    91,
      92,    93,    94,     0,     0,     0,     0,     0,    96,     0,
       0,     0,     0,    96
};

static const yytype_int16 yycheck[] =
{
       3,    56,     0,    11,     4,    27,    61,     4,     5,    22,
       7,     8,    20,    10,    11,    29,    55,    28,    29,    22,
      55,    18,    54,    31,    32,    33,    23,    27,    56,    37,
      27,    34,    35,    61,    42,    43,    44,    45,    41,    47,
      53,    61,    54,    51,    54,    59,    55,    55,    59,    61,
      53,    61,    56,    54,    56,    63,    64,    61,    54,    61,
      57,    58,    55,    71,   113,    55,    74,    75,    55,    29,
      30,   114,   115,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,   107,    96,    97,
      98,    99,    52,    53,   143,   144,   145,   117,   118,    59,
      56,    56,    61,    56,    55,     0,    61,   127,    61,     4,
       5,    55,     7,     8,    55,    10,    11,    28,    29,   168,
      55,   170,   171,    18,    20,    21,    22,   147,    23,   178,
      55,    55,    27,   182,    55,    46,    47,    48,    56,   188,
     189,   190,    56,    32,   152,   153,   195,   150,    59,     0,
       1,   159,    61,     4,     5,    56,     7,     8,     6,    10,
      11,    54,    57,    -1,    56,    14,   169,    18,   176,   150,
      -1,    -1,    23,   186,    -1,    -1,    27,    -1,    -1,    -1,
     183,    -1,   185,   186,    -1,    -1,     4,     5,   169,     7,
       8,   194,    10,    11,    -1,    -1,     4,    -1,    -1,    -1,
      18,    -1,   183,    54,   185,    23,    57,     4,    -1,    27,
      61,    19,    -1,   194,    -1,    23,    24,    25,    26,    27,
      28,    -1,    19,    -1,    -1,    -1,    23,    24,    25,    26,
      27,    28,    12,    13,    14,    15,    -1,    45,    -1,    57,
      -1,    -1,    50,    51,    52,    53,    54,    55,    45,    29,
      30,    -1,    -1,    50,    51,    52,    53,     9,    55,    -1,
      12,    13,    14,    15,    12,    13,    14,    15,    28,    29,
      -1,    -1,    52,    53,    54,    -1,    -1,    29,    30,    59,
      -1,    29,    30,    -1,    44,    45,    46,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    59,
      52,    53,    -1,    -1,    52,    53,    -1,    59,    -1,    28,
      29,    59,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    -1,    61,    28,    29,    -1,    31,    -1,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    16,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    28,    29,    -1,    31,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    28,
      29,    -1,    31,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      16,    17,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,
      59,    -1,    28,    29,    -1,    31,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    16,    17,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    59,    -1,    28,    29,    -1,    31,    -1,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    16,    17,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    59,    -1,    28,    29,
      -1,    31,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    16,
      17,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    59,
      -1,    28,    29,    -1,    31,    -1,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    16,    17,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    59,    -1,    28,    29,    -1,    31,    -1,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    16,    17,    -1,    -1,    -1,
      16,    17,    -1,    -1,    -1,    59,    -1,    28,    29,    -1,
      -1,    -1,    28,    29,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    44,    45,
      46,    47,    48,    -1,    -1,    -1,    -1,    -1,    59,    -1,
      -1,    -1,    -1,    59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    63,    64,     0,     4,     5,     7,     8,    10,
      11,    18,    23,    27,    57,    65,    66,    67,    75,    27,
      55,    74,    55,    54,    54,    19,    23,    24,    25,    26,
      28,    45,    50,    51,    52,    53,    54,    55,    66,    68,
      55,    64,    12,    13,    14,    15,    29,    30,    52,    53,
      54,    59,    54,    61,    68,    55,    66,    67,    20,    21,
      22,    55,    55,    55,    55,    68,    68,    68,    66,    66,
      68,    30,    52,    53,    16,    17,    28,    29,    31,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    54,    59,    71,    72,    73,
      68,    69,    58,    68,    68,    68,    68,    55,    68,    68,
      66,    67,    56,    68,     9,    54,    55,    55,    55,    69,
      56,    68,    68,    56,    68,    68,    68,    55,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    56,    61,    69,    60,
      70,    75,    74,    74,    56,    69,    69,    56,    56,    61,
      69,    60,    75,    75,    75,    54,    69,    56,    65,    56,
      68,    68,    56,    56,    68,    56,    32,    75,    65,    75,
      75,    56,    68,     6,    75,    56,    54,    75,    65,    65,
      67,    75,    75,    75,    56,    65,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    62,    63,    63,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    66,
      66,    66,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    68,    69,    69,    69,    70,    71,    72,
      73,    74,    75
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     2,     2,     2,     7,    10,
       8,    13,    10,     2,     2,     2,     3,     5,     3,     1,
       2,     2,     4,     5,     3,     3,     3,     3,     3,     3,
       2,     2,     0,     1,     2,     1,     3,     2,     2,     2,
       2,     3,     4,     6,     4,     4,     5,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     4,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     2,
       7,     2,     4,     5,     0,     1,     3,     0,     1,     1,
       1,     0,     0
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
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
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 76 "func_analise.ypp" /* yacc.c:1646  */
    { sfErr("",&yylloc); YYABORT; }
#line 1646 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 80 "func_analise.ypp" /* yacc.c:1646  */
    { (yyvsp[-1].reg)->free(); }
#line 1652 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 82 "func_analise.ypp" /* yacc.c:1646  */
    { try{ p_fnc->cdCond((yyvsp[-4].reg),(yyvsp[-2].prg_cd),(yyvsp[0].prg_cd),(yyvsp[0].prg_cd)); } catch(TError err){ sfErr(err.mess,&(yylsp[-6])); YYABORT; } }
#line 1658 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 84 "func_analise.ypp" /* yacc.c:1646  */
    { try{ p_fnc->cdCond((yyvsp[-7].reg),(yyvsp[-5].prg_cd),(yyvsp[-3].prg_cd),(yyvsp[0].prg_cd)); } catch(TError err){ sfErr(err.mess,&(yylsp[-9])); YYABORT; } }
#line 1664 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 86 "func_analise.ypp" /* yacc.c:1646  */
    { try{ p_fnc->cdCycle((yyvsp[-6].prg_cd),(yyvsp[-4].reg),(yyvsp[-3].prg_cd),(yyvsp[0].prg_cd),0); } catch(TError err){ sfErr(err.mess,&(yylsp[-7])); YYABORT; } }
#line 1670 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 88 "func_analise.ypp" /* yacc.c:1646  */
    { try{ p_fnc->cdCycle((yyvsp[-8].prg_cd),(yyvsp[-7].reg),(yyvsp[-3].prg_cd),(yyvsp[0].prg_cd),(yyvsp[-6].prg_cd)); } catch(TError err){ sfErr(err.mess,&(yylsp[-12])); YYABORT; } }
#line 1676 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 90 "func_analise.ypp" /* yacc.c:1646  */
    { try{ p_fnc->cdCycleObj((yyvsp[-5].prg_cd),(yyvsp[-4].reg),(yyvsp[-3].prg_cd),(yyvsp[0].prg_cd),(yyvsp[-7].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-9])); YYABORT; } }
#line 1682 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 91 "func_analise.ypp" /* yacc.c:1646  */
    { p_fnc->prg=p_fnc->prg+(char)Reg::Break; }
#line 1688 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 92 "func_analise.ypp" /* yacc.c:1646  */
    { p_fnc->prg=p_fnc->prg+(char)Reg::Continue; }
#line 1694 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 93 "func_analise.ypp" /* yacc.c:1646  */
    { p_fnc->prg+=(char)Reg::EndFull; }
#line 1700 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 95 "func_analise.ypp" /* yacc.c:1646  */
    {
		for( int i_io = 0; i_io < p_fnc->ioSize(); i_io++ )
		    if( p_fnc->io(i_io)->flg()&IO::Return )
		    {
			Reg *rez = p_fnc->regAt(p_fnc->regGet(p_fnc->io(i_io)->id()));
			if( !rez )
			{
			    rez = p_fnc->regAt(p_fnc->regNew(true));
			    rez->setName(p_fnc->io(i_io)->id());
			    rez->setVar(i_io); rez->setLock(true);
			}
			p_fnc->cdAssign(rez,(yyvsp[-1].reg));
			break;
		    }
		p_fnc->prg+=(char)Reg::EndFull;
	    }
#line 1721 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 112 "func_analise.ypp" /* yacc.c:1646  */
    { try{ p_fnc->cdExtFnc((yyvsp[-4].id),(yyvsp[-2].fp_cnt),true); } catch(TError err){ sfErr(err.mess,&(yylsp[-4])); YYABORT; } }
#line 1727 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 114 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.reg) = (yyvsp[0].reg); }
#line 1733 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 115 "func_analise.ypp" /* yacc.c:1646  */
    { (yyvsp[0].reg)->setType(Reg::String); (yyval.reg) = (yyvsp[0].reg); }
#line 1739 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 116 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.reg) = p_fnc->cdProp((yyvsp[-1].reg),(yyvsp[0].op)); }
#line 1745 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 117 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.reg) = p_fnc->cdProp((yyvsp[-3].reg),"",(yyvsp[-1].reg)); }
#line 1751 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 119 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdObjFnc(p_fnc->cdProp((yyvsp[-4].reg),(yyvsp[-3].op)),(yyvsp[-1].fp_cnt)); } catch(TError err){ sfErr(err.mess,&(yylsp[-4])); YYABORT; } }
#line 1757 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 122 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[-2].reg)->type() == Reg::Free) (yyvsp[-2].reg)->setType((yyvsp[0].reg)->vType(p_fnc));
		    p_fnc->cdAssign((yyvsp[-2].reg), (yyvsp[0].reg));
		} catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; }
	    }
#line 1769 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 130 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[-2].reg)->type() == Reg::Free) throw TError(p_fnc->nodePath().c_str(), _("Variable '%s' is used but undefined"), (yyvsp[-2].reg)->name().c_str());
		    p_fnc->cdAssign((yyvsp[-2].reg), p_fnc->cdBinaryOp(Reg::Add,(yyvsp[-2].reg),(yyvsp[0].reg)));
		} catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; }
	    }
#line 1781 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 138 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[-2].reg)->type() == Reg::Free) throw TError(p_fnc->nodePath().c_str(), _("Variable '%s' is used but undefined"), (yyvsp[-2].reg)->name().c_str());
		    p_fnc->cdAssign((yyvsp[-2].reg), p_fnc->cdBinaryOp(Reg::Sub,(yyvsp[-2].reg),(yyvsp[0].reg)));
		} catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; }
	    }
#line 1793 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 146 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[-2].reg)->type() == Reg::Free) throw TError(p_fnc->nodePath().c_str(), _("Variable '%s' is used but undefined"), (yyvsp[-2].reg)->name().c_str());
		    p_fnc->cdAssign((yyvsp[-2].reg), p_fnc->cdBinaryOp(Reg::Mul,(yyvsp[-2].reg),(yyvsp[0].reg)));
		} catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; }
	    }
#line 1805 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 154 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[-2].reg)->type() == Reg::Free) throw TError(p_fnc->nodePath().c_str(), _("Variable '%s' is used but undefined"), (yyvsp[-2].reg)->name().c_str());
		    p_fnc->cdAssign((yyvsp[-2].reg), p_fnc->cdBinaryOp(Reg::Div,(yyvsp[-2].reg),(yyvsp[0].reg)));
		} catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; }
	    }
#line 1817 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 162 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[-1].reg)->type() == Reg::Free) throw TError(p_fnc->nodePath().c_str(), _("Variable '%s' is used but undefined"), (yyvsp[-1].reg)->name().c_str());
		    Reg *reg = p_fnc->regTmpNew(); *reg = 1;
		    p_fnc->cdAssign((yyvsp[-1].reg), p_fnc->cdBinaryOp(Reg::Add,(yyvsp[-1].reg),reg));
		} catch(TError err){ sfErr(err.mess,&(yylsp[-1])); YYABORT; }
	    }
#line 1830 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 171 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[-1].reg)->type() == Reg::Free) throw TError(p_fnc->nodePath().c_str(), _("Variable '%s' is used but undefined"), (yyvsp[-1].reg)->name().c_str());
		    Reg *reg = p_fnc->regTmpNew(); *reg = 1;
		    p_fnc->cdAssign((yyvsp[-1].reg), p_fnc->cdBinaryOp(Reg::Sub,(yyvsp[-1].reg),reg));
		} catch(TError err){ sfErr(err.mess,&(yylsp[-1])); YYABORT; }
	    }
#line 1843 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 180 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.reg) = (yyvsp[0].reg); }
#line 1849 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 182 "func_analise.ypp" /* yacc.c:1646  */
    {
		if((yyvsp[-1].reg)->type() != Reg::String || (yyvsp[0].reg)->type() != Reg::String) throw TError(p_fnc->nodePath().c_str(),_("Error constant after constant"));
		(yyvsp[-1].reg)->val().s->append(*((yyvsp[0].reg)->val().s));
		(yyvsp[0].reg)->free();
		(yyval.reg) = (yyvsp[-1].reg);
	    }
#line 1860 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 189 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[0].reg)->type() == Reg::Free) throw TError(p_fnc->nodePath().c_str(), _("Variable '%s' is used but undefined"), (yyvsp[0].reg)->name().c_str());
		    (yyval.reg) = (yyvsp[0].reg);
		} catch(TError err){ sfErr(err.mess,&(yylsp[0])); YYABORT; }
	    }
#line 1872 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 197 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[-2].reg)->type() == Reg::Free) (yyvsp[-2].reg)->setType((yyvsp[0].reg)->vType(p_fnc));
		    p_fnc->cdAssign((yyvsp[-2].reg), (yyvsp[0].reg));
		    (yyval.reg) = (yyvsp[-2].reg);
		} catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; }
	    }
#line 1885 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 206 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[-1].reg)->type() == Reg::Free) throw TError(p_fnc->nodePath().c_str(), _("Variable '%s' is used but undefined"), (yyvsp[-1].reg)->name().c_str());
		    (yyval.reg) = p_fnc->cdMove(NULL, (yyvsp[-1].reg));
		    Reg *reg = p_fnc->regTmpNew(); *reg = 1;
		    p_fnc->cdAssign((yyvsp[-1].reg), p_fnc->cdBinaryOp(Reg::Add,(yyvsp[-1].reg),reg));
		} catch(TError err){ sfErr(err.mess,&(yylsp[-1])); YYABORT; }
	    }
#line 1899 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 216 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[-1].reg)->type() == Reg::Free) throw TError(p_fnc->nodePath().c_str(), _("Variable '%s' is used but undefined"), (yyvsp[-1].reg)->name().c_str());
		    (yyval.reg) = p_fnc->cdMove(NULL, (yyvsp[-1].reg));
		    Reg *reg = p_fnc->regTmpNew(); *reg = 1;
		    p_fnc->cdAssign((yyvsp[-1].reg), p_fnc->cdBinaryOp(Reg::Sub,(yyvsp[-1].reg),reg));
		} catch(TError err){ sfErr(err.mess,&(yylsp[-1])); YYABORT; }
	    }
#line 1913 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 226 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[0].reg)->type() == Reg::Free) throw TError(p_fnc->nodePath().c_str(), _("Variable '%s' is used but undefined"), (yyvsp[0].reg)->name().c_str());
		    Reg *reg = p_fnc->regTmpNew(); *reg = 1;
		    p_fnc->cdAssign((yyvsp[0].reg), p_fnc->cdBinaryOp(Reg::Add,(yyvsp[0].reg),reg));
		    (yyval.reg) = (yyvsp[0].reg);
		} catch(TError err){ sfErr(err.mess,&(yylsp[-1])); YYABORT; }
	    }
#line 1927 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 236 "func_analise.ypp" /* yacc.c:1646  */
    {
		try
		{
		    if((yyvsp[0].reg)->type() == Reg::Free) throw TError(p_fnc->nodePath().c_str(), _("Variable '%s' is used but undefined"), (yyvsp[0].reg)->name().c_str());
		    Reg *reg = p_fnc->regTmpNew(); *reg = 1;
		    p_fnc->cdAssign((yyvsp[0].reg), p_fnc->cdBinaryOp(Reg::Sub,(yyvsp[0].reg),reg));
		    (yyval.reg) = (yyvsp[0].reg);
		} catch(TError err){ sfErr(err.mess,&(yylsp[-1])); YYABORT; }
	    }
#line 1941 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 245 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBldFnc((yyvsp[-2].id)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 1947 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 246 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBldFnc((yyvsp[-3].id),(yyvsp[-1].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-3])); YYABORT; } }
#line 1953 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 247 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBldFnc((yyvsp[-5].id),(yyvsp[-3].reg),(yyvsp[-1].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-5])); YYABORT; } }
#line 1959 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 248 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdExtFnc((yyvsp[-3].id),(yyvsp[-1].fp_cnt)); } catch(TError err){ sfErr(err.mess,&(yylsp[-3])); YYABORT; } }
#line 1965 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 249 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdMviObject(); } catch(TError err){ sfErr(err.mess,&(yylsp[-3])); YYABORT; } }
#line 1971 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 250 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdMviArray((yyvsp[-1].fp_cnt)); } catch(TError err){ sfErr(err.mess,&(yylsp[-4])); YYABORT; } }
#line 1977 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 251 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdMviRegExp((yyvsp[-1].fp_cnt)); } catch(TError err){ sfErr(err.mess,&(yylsp[-4])); YYABORT; } }
#line 1983 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 252 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::Add,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 1989 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 253 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::Sub,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 1995 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 254 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::Mul,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2001 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 255 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::Div,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2007 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 256 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::RstI,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2013 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 257 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::BitOr,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2019 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 258 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::BitAnd,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2025 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 259 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::BitXor,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2031 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 260 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.reg) = (yyvsp[-1].reg); }
#line 2037 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 262 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdCondBinaryOp((yyvsp[-2].prg_cd),(yyvsp[-3].reg),(yyvsp[-1].reg),(yyvsp[0].prg_cd)); } catch(TError err){ sfErr(err.mess,&(yylsp[-3])); YYABORT; } }
#line 2043 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 264 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdCondBinaryOp((yyvsp[-2].prg_cd),(yyvsp[-3].reg),(yyvsp[-1].reg),(yyvsp[0].prg_cd)); } catch(TError err){ sfErr(err.mess,&(yylsp[-3])); YYABORT; } }
#line 2049 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 265 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::BitShLeft,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2055 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 266 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::BitShRight,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2061 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 267 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::LT,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2067 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 268 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::GT,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2073 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 269 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::GEQ,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2079 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 270 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::LEQ,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2085 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 271 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::EQU,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2091 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 272 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdBinaryOp(Reg::NEQ,(yyvsp[-2].reg),(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-2])); YYABORT; } }
#line 2097 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 273 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdUnaryOp(Reg::Not,(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-1])); YYABORT; } }
#line 2103 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 274 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdUnaryOp(Reg::BitNot,(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-1])); YYABORT; } }
#line 2109 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 275 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdUnaryOp(Reg::Neg,(yyvsp[0].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-1])); YYABORT; } }
#line 2115 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 277 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdCond((yyvsp[-6].reg),(yyvsp[-5].prg_cd),(yyvsp[-3].prg_cd),(yyvsp[0].prg_cd),(yyvsp[-4].reg),(yyvsp[-1].reg)); } catch(TError err){ sfErr(err.mess,&(yylsp[-6])); YYABORT; } }
#line 2121 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 278 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.reg) = p_fnc->cdProp((yyvsp[-1].reg),(yyvsp[0].op)); }
#line 2127 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 279 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.reg) = p_fnc->cdProp((yyvsp[-3].reg),"",(yyvsp[-1].reg)); }
#line 2133 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 281 "func_analise.ypp" /* yacc.c:1646  */
    { try{ (yyval.reg) = p_fnc->cdObjFnc(p_fnc->cdProp((yyvsp[-4].reg),(yyvsp[-3].op)),(yyvsp[-1].fp_cnt)); } catch(TError err){ sfErr(err.mess,&(yylsp[-4])); YYABORT; } }
#line 2139 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 282 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.fp_cnt) = 0; }
#line 2145 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 283 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.fp_cnt) = 1; p_fnc->f_prmst.push_front((yyvsp[0].reg)); }
#line 2151 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 284 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.fp_cnt) = (yyvsp[-2].fp_cnt) + (yyvsp[0].fp_cnt); }
#line 2157 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 285 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.prg_cd) = p_fnc->prg.size(); p_fnc->prg=p_fnc->prg+(char)Reg::If+"RR00nn"; }
#line 2163 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 286 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.prg_cd) = p_fnc->prg.size(); p_fnc->prg=p_fnc->prg+(char)Reg::If+"RR00nn"; }
#line 2169 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 287 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.prg_cd) = p_fnc->prg.size(); p_fnc->prg=p_fnc->prg+(char)Reg::LCOr+"RRrrRRnn"; }
#line 2175 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 288 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.prg_cd) = p_fnc->prg.size(); p_fnc->prg=p_fnc->prg+(char)Reg::LCAnd+"RRrrRRnn"; }
#line 2181 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 289 "func_analise.ypp" /* yacc.c:1646  */
    { (yyval.prg_cd) = p_fnc->prg.size(); p_fnc->prg=p_fnc->prg+(char)Reg::Cycle+"RRbbaann"; }
#line 2187 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 290 "func_analise.ypp" /* yacc.c:1646  */
    { p_fnc->prg+=(char)Reg::End; (yyval.prg_cd) = p_fnc->prg.size(); }
#line 2193 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
    break;


#line 2197 "daq_JavaLikeCalc_la-func_analise.cpp" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 292 "func_analise.ypp" /* yacc.c:1906  */


void sfErr( const string &mess, YYLTYPE *ps )
{
    snprintf(m_buf, sizeof(m_buf), _("%s, pos: (%d,%d)-(%d,%d)."),
	mess.c_str(), ps->first_line, ps->first_column, ps->last_line, ps->last_column);
    yyerror(m_buf);
}

void yyerror( const char *s )	{ p_fnc->p_err += s; }

int yylex( )
{
    unsigned c = 0, st_pos;
    unsigned &pos = p_fnc->la_pos;
    string &prog = p_fnc->sprg;

    if(pos == 0) { yylloc.last_line = yylloc.last_column = 1; }

retry:
    //> Empty space
    while(pos < prog.size() &&
	((c = prog[pos]) == ' ' || c == '\n' || c == '\t' ||
	c == '\f' || c == '\r' || c == '\v'))
    {
	if(c == '\n')	{ yylloc.last_column = 1; yylloc.last_line++; }
	else yylloc.last_column++;
	pos++;
    }
    //> End string
    if(pos >= prog.size()) return 0;
    //> Comentars // and /* ... */
    if(prog.substr(pos,2) == "//")
    {
	pos += 2;
	while(pos < prog.size() && prog[pos] != '\n') pos++;
	goto retry;
    }
    if(prog.substr(pos,2) == "/*")
    {
	pos += 2;
	while(pos < prog.size() && prog.substr(pos-1,2) != "*/")
	{
	    if(prog[pos] == '\n')	{ yylloc.last_column = 1; yylloc.last_line++; }
	    else yylloc.last_column++;
	    pos++;
	}
	pos++;
	goto retry;
    }

    yylloc.first_line = yylloc.last_line;
    yylloc.first_column = yylloc.last_column;

    //Number
    if(isdigit(c) || (c == '.' && (pos+1) < prog.size() && isdigit(prog[pos+1])))
    {
	st_pos = pos;
	int tp = 0;	//Type constant (0-detect;1-dec;2-oct;3-hex;4-real)
	if(c == '.')	tp = 4;
	else
	{
	    while(pos < prog.size() && isdigit(c=prog[pos]))
	    { pos++; yylloc.last_column++; }
	    if(pos >= prog.size())			tp = (prog[st_pos]=='0')?2:1;
	    else if(c == 'x' || c == 'X')		tp = 3;
	    else if(c == '.' || c == 'e' || c == 'E')	tp = 4;
	    else tp = (prog[st_pos]=='0') ? 2 : 1;
	}
	if(tp == 1)
	{
	    yylval.reg = p_fnc->regTmpNew();
	    *yylval.reg = (int64_t)strtoll(prog.substr(st_pos,pos-st_pos).c_str(),NULL,10);
	    return CONST;
	}
	else if(tp == 2)
	{
	    yylloc.last_column -= pos-st_pos;
	    pos = st_pos;
	    while(pos < prog.size() && (c=prog[pos]) >= '0' && c <= '7')
	    { pos++; yylloc.last_column++; }

	    yylval.reg = p_fnc->regTmpNew();
	    *yylval.reg = (int64_t)strtoll(prog.substr(st_pos,pos-st_pos).c_str(),NULL,8);
	    return CONST;
	}
	else if(tp == 3)
	{
	    pos++; yylloc.last_column++;
	    while(pos < prog.size() && (isdigit(c=prog[pos]) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
	    { pos++; yylloc.last_column++; }

	    yylval.reg = p_fnc->regTmpNew();
	    *yylval.reg = (int64_t)strtoll(prog.substr(st_pos,pos-st_pos).c_str(),NULL,16);
	    return CONST;
	}
	else if(tp == 4)
	{
	    bool e_ok = (c=='e'||c=='E') ? true : false;
	    pos++; yylloc.last_column++;
	    while(pos < prog.size() && (isdigit(c=prog[pos]) || c == 'E' || c == 'e' ||
		((c == '+' || c == '-') && ((prog[pos-1]) == 'e' || (prog[pos-1]) == 'E'))))
	    {
		if(c == 'E' || c == 'e')
		{
		    if(e_ok)	break;
		    else e_ok = true;
		}
		pos++; yylloc.last_column++;
	    }

	    yylval.reg = p_fnc->regTmpNew();
	    *yylval.reg = atof(prog.substr(st_pos,pos-st_pos).c_str());
	    return CONST;
	}
	else return 0;
    }
    //String
    if(c == '"' && (pos+1) < prog.size())
    {
	st_pos = ++pos;
	string rez_str;
	yylloc.last_column++;
	while(pos < prog.size() && prog[pos] != '"' && prog[pos] != '\n')
	{
	    int elSzPass = 1;
	    if(prog[pos] == '\\' && (pos+1) < prog.size())
	    {
		switch(prog[pos+1])
		{
		    case 'n':	rez_str += '\n';	break;
		    case 't':	rez_str += '\t';	break;
		    case 'b':	rez_str += '\b';	break;
		    case 'f':	rez_str += '\f';	break;
		    case 'r':	rez_str += '\r';	break;
		    case 'x': case 'X':
			if((pos+3) < prog.size() && isxdigit(prog[pos+2]) && isxdigit(prog[pos+3]))
			{ rez_str += (char)strtol(prog.substr(pos+2,2).c_str(),NULL,16); elSzPass += 2; }
			break;
		    default:
			if((pos+3) < prog.size() && prog[pos+1] >= '0' && prog[pos+1] <= '7' &&
						    prog[pos+2] >= '0' && prog[pos+2] <= '7' &&
						    prog[pos+3] >= '0' && prog[pos+3] <= '7')
			{ rez_str += (char)strtol(prog.substr(pos+1,3).c_str(),NULL,8); elSzPass += 2; }
			else rez_str += prog[pos+1];
		}
		elSzPass++;
	    }
	    else rez_str += prog[pos];
	    pos += elSzPass; yylloc.last_column += elSzPass;
	}
	if(pos >= prog.size())
	{
	    yyerror(_("Unexpected end program, expect end string symbol '\"', "));
	    return ERR;
	}
	else if(prog[pos] == '\n')
	{
	    yyerror(_("The next line symbol failed into string, "));
	    return ERR;
	}
	yylloc.last_column++;

	yylval.reg = p_fnc->regTmpNew();
	*yylval.reg = rez_str;
	//*yylval.reg = prog.substr(st_pos,pos-st_pos);
	pos++;
	return CONST;
    }
    //Symbols
    if(c == '_' || isalpha(c) || c > 0x7F)
    {
	bool is_dot = false;
	st_pos = pos;
	while(pos < prog.size() && ((c = prog[pos]) == '_' || c == '.' || isalnum(c) || c > 0x7F))
	{
	    if(c == '.') is_dot = true;
	    pos++;
	    yylloc.last_column++;
	}
	string smb_nm = prog.substr(st_pos,pos-st_pos);
	//Keywords
	if(smb_nm == "if")	return IF;
	if(smb_nm == "else")	return ELSE;
	if(smb_nm == "while")	return WHILE;
	if(smb_nm == "for")	return FOR;
	if(smb_nm == "break")	return BREAK;
	if(smb_nm == "continue")return CONTINUE;
	if(smb_nm == "return")	return RETURN;
	if(smb_nm == "new")	return NEW;
	if(smb_nm == "Object")	return OBJECT;
	if(smb_nm == "Array")	return ARRAY;
	if(smb_nm == "RegExp")	return REGEXP;
	if(smb_nm == "using")
	{
	    char buf[255]; buf[0] = 0;
	    while(pos < prog.size() && prog[pos] != ';') pos++;
	    if(pos < prog.size())
		sscanf(prog.substr(st_pos,pos-st_pos).c_str(),"using %254s",buf);
	    if(pos >= prog.size() || buf[0] == 0)
	    {
		yyerror(_("Using namespace is error or empty, "));
		return ERR;
	    }
	    string fVal;
	    for(int off = 0; !(fVal=TSYS::strSepParse(p_fnc->mUsings,0,';',&off)).empty(); )
		if(fVal == buf) break;
	    if(fVal.empty())	p_fnc->mUsings = p_fnc->mUsings+buf+";";
	    pos++;
	    goto retry;
	}
	//Boolean
	if(smb_nm == "true" || smb_nm == "false")
	{
	    yylval.reg = p_fnc->regTmpNew();
	    *yylval.reg = (smb_nm == "true") ? true : false;
	    return CONST;
	}
	//Constants
	NConst *cnst_v;
	if((cnst_v = mod->constGet(smb_nm.c_str())) != NULL)
	{
	    yylval.reg = p_fnc->regTmpNew();
	    switch(cnst_v->tp)
	    {
		case TFld::Real:	*yylval.reg = TSYS::getUnalignDbl(cnst_v->val.data());	break;
		case TFld::Integer:	*yylval.reg = (int64_t)TSYS::getUnalign64(cnst_v->val.data());	break;
		case TFld::Boolean:	*yylval.reg = (char)cnst_v->val[0];	break;
		case TFld::String:	*yylval.reg = cnst_v->val;		break;
		default: break;
	    }
	    return CONST;
	}
	//Constant objects
	string sel = TSYS::strSepParse(smb_nm,0,'.');
	if(sel == "SYS" || sel == "arguments")
	{
	    yylval.reg = p_fnc->regTmpNew();
	    yylval.reg->setType(Reg::Obj);
    	    yylval.reg->setName(sel);
	    pos -= (smb_nm.size()-sel.size());
	    yylloc.last_column -= (smb_nm.size()-sel.size());
    	    return VAR;
	}

	//Find buildin function
	if(c == '(' && mod->bFuncGet( smb_nm.c_str() ) != NULL)
	{
	    yylval.id = mod->bFuncGet(smb_nm.c_str())->code;
	    switch(mod->bFuncGet(smb_nm.c_str())->prm)
	    {
		case 0: return B_FUNC;
		case 1: return B_FUNC1;
		case 2: return B_FUNC2;
		default:
		    yyerror(_("Build in function has too much parameters, "));
		    return ERR;
	    }
	}

	//> Find external or object's functions
	if(c == '(')
	{
	    //>> External functions
	    if(p_fnc->funcGet(smb_nm) >= 0)
	    {
		yylval.id = p_fnc->funcGet(smb_nm);
		return FUNC;
	    }

	    //>> Check for object's functions and system object's function
	    //string sel = TSYS::strSepParse(smb_nm,0,'.');
	    if((yylval.reg=p_fnc->regAt(p_fnc->regGet(sel))) || (yylval.reg=p_fnc->regAt(p_fnc->ioGet(sel))))
	    {
		pos -= (smb_nm.size()-sel.size());
		yylloc.last_column -= (smb_nm.size()-sel.size());
		return VAR;
	    }

	    yyerror(_("Function error, "));
	    return ERR;
	}

	//> Check allow registers
	if(p_fnc->regGet(smb_nm) >= 0)
	{
	    yylval.reg = p_fnc->regAt(p_fnc->regGet(smb_nm));
	    return VAR;
	}

	//> Global attributes and object's parameters.
	if(is_dot)
	{
	    //>> Check to parameter attribute (TValue)
	    try
	    {
		AutoHD<TVal> vl = SYS->daq().at().at(TSYS::strSepParse(smb_nm,0,'.')).at().
						     at(TSYS::strSepParse(smb_nm,1,'.')).at().
						     at(TSYS::strSepParse(smb_nm,2,'.')).at().
						     vlAt(TSYS::strSepParse(smb_nm,3,'.'));
		yylval.reg = p_fnc->regAt(p_fnc->regNew(true));
		yylval.reg->setName(smb_nm);
		yylval.reg->setPAttr(vl);
		yylval.reg->setLock(true);
		return VAR;
	    }catch(...){ }

	    //>> Check for object's parameters
	    //string sel = TSYS::strSepParse(smb_nm,0,'.');
	    if((yylval.reg=p_fnc->regAt(p_fnc->regGet(sel))) || (yylval.reg=p_fnc->regAt(p_fnc->ioGet(sel))))
	    {
		pos -= (smb_nm.size()-sel.size());
		yylloc.last_column -= (smb_nm.size()-sel.size());
		return VAR;
	    }

	    yyerror(_("Symbol error, "));
	    return ERR;
	}
	//Check IO
	if((yylval.reg=p_fnc->regAt(p_fnc->ioGet(smb_nm)))) return VAR;

	//Keywords
	if(smb_nm == "in")	return IN;
	if(smb_nm == "var")	return VAR_DIR;

	//Get new register
	yylval.reg = p_fnc->regAt(p_fnc->regNew(true));
	yylval.reg->setName(smb_nm);
	yylval.reg->setLock(true);
	return VAR;
    }
    //Object's properties or functions
    else if(c == '.' && (pos+1) < prog.size())
    {
	st_pos = ++pos;
	yylloc.last_column++;
	while(pos < prog.size() && ((c = prog[pos]) == '_' || isalpha(c) || (pos > st_pos && isdigit(c)) || c > 0x7F))
	{ pos++; yylloc.last_column++; }
	if((pos-st_pos) > 255) { yyerror(_("Object's properties too long, ")); return ERR; }
	strncpy(yylval.op,prog.substr(st_pos,pos-st_pos).data(),255);
	// p_fnc->o_prpf.push_back(prog.substr(st_pos,pos-st_pos));
	return O_PRP_F;
    }
    //Multi symbol operations
    else if(prog.substr(pos,2) == "++") { pos += 2; yylloc.last_column += 2; return INCREM; }
    else if(prog.substr(pos,2) == "--") { pos += 2; yylloc.last_column += 2; return DECREM; }
    else if(prog.substr(pos,2) == "||") { pos += 2; yylloc.last_column += 2; return OR; }
    else if(prog.substr(pos,2) == "&&") { pos += 2; yylloc.last_column += 2; return AND; }
    else if(prog.substr(pos,2) == ">=") { pos += 2; yylloc.last_column += 2; return GE; }
    else if(prog.substr(pos,2) == "<=") { pos += 2; yylloc.last_column += 2; return LE; }
    else if(prog.substr(pos,2) == "==") { pos += 2; yylloc.last_column += 2; return EQ; }
    else if(prog.substr(pos,2) == "!=") { pos += 2; yylloc.last_column += 2; return NE; }
    else if(prog.substr(pos,2) == "<<") { pos += 2; yylloc.last_column += 2; return BITSHLEFT; }
    else if(prog.substr(pos,2) == ">>") { pos += 2; yylloc.last_column += 2; return BITSHRIGHT; }
    else if(prog.substr(pos,2) == "+=") { pos += 2; yylloc.last_column += 2; return ADDEQ; }
    else if(prog.substr(pos,2) == "-=") { pos += 2; yylloc.last_column += 2; return SUBEQ; }
    else if(prog.substr(pos,2) == "*=") { pos += 2; yylloc.last_column += 2; return MULEQ; }
    else if(prog.substr(pos,2) == "/=") { pos += 2; yylloc.last_column += 2; return DIVEQ; }
    else { pos++; yylloc.last_column++; }

    return c;
}

}
