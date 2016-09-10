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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "como_parser.y" /* yacc.c:339  */

/*
*  Copyright (c) 2016 Ryan McCullagh <me@ryanmccullagh.com>
*
*  This program is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "como_globals.h"
#include "como_ast.h"
#include "como_parser.h"
#include "como_lexer.h"

#define YYERROR_VERBOSE

int yyerror(YYLTYPE * lvalp, ast_node** ast, yyscan_t scanner, const char* msg)
{
	printf("parse error: %s in file \"%s\" on line %d:%d\n", msg, 
		get_active_file_name(), lvalp->first_line, lvalp->first_column);
	
	exit(1);
}


#line 101 "como_parser.c" /* yacc.c:339  */

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
   by #include "como_parser.h".  */
#ifndef YY_YY_COMO_PARSER_H_INCLUDED
# define YY_YY_COMO_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 36 "como_parser.y" /* yacc.c:355  */


#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif


#line 140 "como_parser.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    END = 0,
    T_CMP = 258,
    T_LTE = 259,
    T_NEQ = 260,
    T_GTE = 261,
    T_IF = 262,
    T_ELSE = 263,
    T_WHILE = 264,
    T_FOR = 265,
    T_FUNC = 266,
    T_RETURN = 267,
    T_PRINT = 268,
    T_NOELSE = 269,
    T_INC = 270,
    T_DEC = 271,
    T_FUNCTION = 272,
    T_NUM = 273,
    T_ID = 274,
    T_STR_LIT = 275
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 56 "como_parser.y" /* yacc.c:355  */

	long number;
	char* id;
	char* stringliteral;
	ast_node* ast;

#line 181 "como_parser.c" /* yacc.c:355  */
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



int yyparse (ast_node** ast, yyscan_t scanner);

#endif /* !YY_YY_COMO_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 209 "como_parser.c" /* yacc.c:358  */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   259

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  59
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  109

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   275

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    13,     2,     2,
      29,    30,    11,    10,    34,     9,     2,    12,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    31,
       7,    28,     8,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
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
       5,     6,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   117,   117,   121,   122,   126,   130,   131,   135,   139,
     139,   143,   145,   147,   149,   151,   155,   162,   168,   172,
     173,   177,   181,   183,   185,   189,   193,   195,   197,   201,
     207,   214,   216,   220,   222,   226,   230,   232,   236,   238,
     242,   247,   249,   251,   253,   255,   257,   261,   265,   269,
     273,   277,   281,   285,   290,   295,   300,   304,   306,   308
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"EOF\"", "error", "$undefined", "T_CMP", "T_LTE", "T_NEQ", "T_GTE",
  "'<'", "'>'", "'-'", "'+'", "'*'", "'/'", "'%'", "T_IF", "T_ELSE",
  "T_WHILE", "T_FOR", "T_FUNC", "T_RETURN", "T_PRINT", "T_NOELSE", "T_INC",
  "T_DEC", "T_FUNCTION", "T_NUM", "T_ID", "T_STR_LIT", "'='", "'('", "')'",
  "';'", "'{'", "'}'", "','", "$accept", "start", "top_statement_list",
  "top_statement", "inner_statement_list", "inner_statement",
  "function_keyword", "statement", "assignment_statement",
  "print_statement", "return_statement", "optional_expression",
  "compound_statement", "expression_statement",
  "if_statement_without_else", "selection_statement",
  "function_decl_statement", "optional_parameter_list", "parameter_list",
  "parameter", "optional_argument_list", "argument_list", "argument",
  "expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,    60,    62,    45,
      43,    42,    47,    37,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,    61,    40,
      41,    59,   123,   125,    44
};
# endif

#define YYPACT_NINF -34

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-34)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -34,     6,   203,   -34,    64,   -20,   -17,     4,   -34,    64,
       5,   -34,   -34,   -21,   -34,    64,   -34,   -34,    41,   -34,
      55,    56,   -34,   -34,   -34,    77,   -34,   -34,    11,   -19,
      59,    64,    64,    68,    65,   233,    64,   -34,   -34,    64,
      64,    97,   182,    66,   -34,   -34,    90,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,   -34,   108,
     136,    69,    67,   -34,   147,   233,    93,    91,   -34,   233,
     -34,   -34,   -34,   -34,    98,   -34,   124,    70,   161,   240,
     246,    28,    59,    18,    13,   113,   -34,    90,    90,    64,
     -34,   -34,    64,   -34,   131,   128,   -34,   -34,   -34,    53,
     -34,    90,    98,    64,   -34,   -34,   175,    90,   -34
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,     0,     0,     0,     0,     9,    20,
       0,    10,    57,    58,    59,     0,     7,     3,     0,     5,
       0,     0,    15,    12,    13,    26,    14,    11,     0,    58,
      56,     0,     0,     0,     0,    19,     0,    53,    54,     0,
      37,     0,     0,     0,    23,    24,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    22,     0,
       0,     0,     0,    18,     0,    16,     0,    36,    38,    40,
      45,    21,     6,     8,    32,    27,    49,    51,    50,    52,
      46,    47,    42,    41,    43,    44,    48,     0,     0,     0,
      17,    55,     0,    35,     0,    31,    33,    25,    28,     0,
      39,     0,     0,     0,    30,    34,     0,     0,    29
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -34,   -34,   -34,   -34,   -34,   -34,   -34,   121,   132,   -34,
     -34,   -34,   -33,   -34,   -34,   -34,   -34,   -34,   -34,    62,
     -34,   -34,    83,    -4
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    17,    42,    72,    18,    19,    20,    21,
      22,    34,    23,    24,    25,    26,    27,    94,    95,    96,
      66,    67,    68,    28
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      30,    37,    38,    37,    38,    35,     3,    39,    40,    31,
      40,    41,    32,    75,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,    56,    57,    59,    60,    55,
      56,    57,    64,    33,    36,    65,    69,    53,    54,    55,
      56,    57,    58,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    97,    98,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    43,   104,    54,
      55,    56,    57,     4,   108,    49,    50,    51,    52,    53,
      54,    55,    56,    57,   103,    99,    44,    45,    69,    12,
      29,    14,    46,    15,    61,    74,    63,    39,    89,   106,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    16,    91,    93,    92,    57,    70,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    87,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,   101,   102,    73,   105,    62,    88,    50,    51,    52,
      53,    54,    55,    56,    57,   100,     0,    90,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,     0,
       0,     4,     0,     0,     0,     0,     5,     0,     6,     7,
       8,     9,    10,     0,     0,   107,    11,    12,    13,    14,
       0,    15,     4,     0,    16,    71,     0,     5,     0,     6,
       7,     8,     9,    10,     0,     0,     0,    11,    12,    13,
      14,     0,    15,     0,     0,    16,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    51,    52,    53,
      54,    55,    56,    57,    52,    53,    54,    55,    56,    57
};

static const yytype_int8 yycheck[] =
{
       4,    22,    23,    22,    23,     9,     0,    28,    29,    29,
      29,    15,    29,    46,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    12,    13,    31,    32,    11,
      12,    13,    36,    29,    29,    39,    40,     9,    10,    11,
      12,    13,    31,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    87,    88,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    26,   101,    10,
      11,    12,    13,     9,   107,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    31,    89,    31,    31,    92,    25,
      26,    27,    15,    29,    26,    29,    31,    28,    31,   103,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    32,    30,    26,    34,    13,    30,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    30,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    30,    34,    42,   102,    33,    30,     6,     7,     8,
       9,    10,    11,    12,    13,    92,    -1,    30,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    14,    -1,    16,    17,
      18,    19,    20,    -1,    -1,    30,    24,    25,    26,    27,
      -1,    29,     9,    -1,    32,    33,    -1,    14,    -1,    16,
      17,    18,    19,    20,    -1,    -1,    -1,    24,    25,    26,
      27,    -1,    29,    -1,    -1,    32,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     7,     8,     9,
      10,    11,    12,    13,     8,     9,    10,    11,    12,    13
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    36,    37,     0,     9,    14,    16,    17,    18,    19,
      20,    24,    25,    26,    27,    29,    32,    38,    41,    42,
      43,    44,    45,    47,    48,    49,    50,    51,    58,    26,
      58,    29,    29,    29,    46,    58,    29,    22,    23,    28,
      29,    58,    39,    26,    31,    31,    15,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    31,    58,
      58,    26,    43,    31,    58,    58,    55,    56,    57,    58,
      30,    33,    40,    42,    29,    47,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    30,    30,    31,
      30,    30,    34,    26,    52,    53,    54,    47,    47,    58,
      57,    30,    34,    31,    47,    54,    58,    30,    47
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    35,    36,    37,    37,    38,    39,    39,    40,    41,
      41,    42,    42,    42,    42,    42,    43,    44,    45,    46,
      46,    47,    48,    48,    48,    49,    50,    50,    50,    50,
      51,    52,    52,    53,    53,    54,    55,    55,    56,    56,
      57,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     4,     3,     1,
       0,     3,     2,     2,     2,     5,     1,     3,     5,     9,
       6,     1,     0,     1,     3,     1,     1,     0,     1,     3,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     4,     2,     1,     1,     1
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
      yyerror (&yylloc, ast, scanner, YY_("syntax error: cannot back up")); \
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
                  Type, Value, Location, ast, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ast_node** ast, yyscan_t scanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (ast);
  YYUSE (scanner);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, ast_node** ast, yyscan_t scanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, ast, scanner);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, ast_node** ast, yyscan_t scanner)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , ast, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, ast, scanner); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, ast_node** ast, yyscan_t scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (ast);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (ast_node** ast, yyscan_t scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
        case 2:
#line 117 "como_parser.y" /* yacc.c:1646  */
    { *ast = (yyvsp[0].ast); }
#line 1494 "como_parser.c" /* yacc.c:1646  */
    break;

  case 3:
#line 121 "como_parser.y" /* yacc.c:1646  */
    { ast_node_statement_list_push((yyvsp[-1].ast), (yyvsp[0].ast)); (yyval.ast) = (yyvsp[-1].ast); }
#line 1500 "como_parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 122 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(0); }
#line 1506 "como_parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 126 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1512 "como_parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 130 "como_parser.y" /* yacc.c:1646  */
    { ast_node_statement_list_push((yyvsp[-1].ast), (yyvsp[0].ast)); (yyval.ast) = (yyvsp[-1].ast); }
#line 1518 "como_parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 131 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(0); }
#line 1524 "como_parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 135 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1530 "como_parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 143 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1536 "como_parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 145 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1542 "como_parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 147 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1548 "como_parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 149 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1554 "como_parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 151 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1560 "como_parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 155 "como_parser.y" /* yacc.c:1646  */
    {
 		(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_ASSIGN, ast_node_create_id((yyvsp[-2].id)), (yyvsp[0].ast)); 
 		free((yyvsp[-2].id)); 
	}
#line 1569 "como_parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 162 "como_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = ast_node_create_print((yyvsp[-1].ast));
	}
#line 1577 "como_parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 168 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_return((yyvsp[-1].ast)); }
#line 1583 "como_parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 172 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1589 "como_parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 173 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = NULL; }
#line 1595 "como_parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 177 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1601 "como_parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 181 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1607 "como_parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 183 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1613 "como_parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 185 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1619 "como_parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 189 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_if((yyvsp[-2].ast), (yyvsp[0].ast), NULL); }
#line 1625 "como_parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 193 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1631 "como_parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 195 "como_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].ast)->u1.if_node.b2 = (yyvsp[0].ast); (yyval.ast) = (yyvsp[-2].ast); }
#line 1637 "como_parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 197 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) = ast_node_create_while((yyvsp[-2].ast), (yyvsp[0].ast));
 }
#line 1645 "como_parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 201 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) = ast_node_create_for((yyvsp[-6].ast), (yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
 }
#line 1653 "como_parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 207 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_function((yyvsp[-4].id), (yyvsp[-2].ast), (yyvsp[0].ast));
	free((yyvsp[-4].id));
 }
#line 1662 "como_parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 214 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1668 "como_parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 216 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(0); }
#line 1674 "como_parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 220 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(1, (yyvsp[0].ast)); }
#line 1680 "como_parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 222 "como_parser.y" /* yacc.c:1646  */
    { ast_node_statement_list_push((yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast) = (yyvsp[-2].ast); }
#line 1686 "como_parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 226 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_id((yyvsp[0].id)); free((yyvsp[0].id)); }
#line 1692 "como_parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 230 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1698 "como_parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 232 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(0); }
#line 1704 "como_parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 236 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(1, (yyvsp[0].ast)); }
#line 1710 "como_parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 238 "como_parser.y" /* yacc.c:1646  */
    { ast_node_statement_list_push((yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast) = (yyvsp[-2].ast); }
#line 1716 "como_parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 242 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1722 "como_parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 247 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_ADD, (yyvsp[-2].ast), (yyvsp[0].ast));   }
#line 1728 "como_parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 249 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_MINUS, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1734 "como_parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 251 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_TIMES, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1740 "como_parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 253 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_DIV, (yyvsp[-2].ast), (yyvsp[0].ast));   }
#line 1746 "como_parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 255 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1752 "como_parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 257 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_LT, (yyvsp[-2].ast), (yyvsp[0].ast));   
 }
#line 1760 "como_parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 261 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_GT, (yyvsp[-2].ast), (yyvsp[0].ast));   
 }
#line 1768 "como_parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 265 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_REM, (yyvsp[-2].ast), (yyvsp[0].ast));
 }
#line 1776 "como_parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 269 "como_parser.y" /* yacc.c:1646  */
    { 
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_CMP, (yyvsp[-2].ast), (yyvsp[0].ast));   
 }
#line 1784 "como_parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 273 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_NEQ, (yyvsp[-2].ast), (yyvsp[0].ast));   
 }
#line 1792 "como_parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 277 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_LTE, (yyvsp[-2].ast), (yyvsp[0].ast));   
 }
#line 1800 "como_parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 281 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_GTE, (yyvsp[-2].ast), (yyvsp[0].ast)); 
 }
#line 1808 "como_parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 285 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) =ast_node_create_postfix_op(AST_POSTFIX_OP_INC, ast_node_create_id((yyvsp[-1].id)));
  	free((yyvsp[-1].id));
 }
#line 1817 "como_parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 290 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) =ast_node_create_postfix_op(AST_POSTFIX_OP_DEC, ast_node_create_id((yyvsp[-1].id)));
  	free((yyvsp[-1].id));
 }
#line 1826 "como_parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 295 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_call(ast_node_create_id((yyvsp[-3].id)), (yyvsp[-1].ast), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
  	free((yyvsp[-3].id));
 }
#line 1835 "como_parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 300 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) = ast_node_create_unary_op(AST_UNARY_OP_MINUS, (yyvsp[0].ast));
 }
#line 1843 "como_parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 304 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_number((yyvsp[0].number)); }
#line 1849 "como_parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 306 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_id((yyvsp[0].id));  free((yyvsp[0].id)); }
#line 1855 "como_parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 308 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_string_literal((yyvsp[0].stringliteral)); free((yyvsp[0].stringliteral)); }
#line 1861 "como_parser.c" /* yacc.c:1646  */
    break;


#line 1865 "como_parser.c" /* yacc.c:1646  */
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
      yyerror (&yylloc, ast, scanner, YY_("syntax error"));
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
        yyerror (&yylloc, ast, scanner, yymsgp);
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
                      yytoken, &yylval, &yylloc, ast, scanner);
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
                  yystos[yystate], yyvsp, yylsp, ast, scanner);
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
  yyerror (&yylloc, ast, scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, ast, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, ast, scanner);
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
#line 311 "como_parser.y" /* yacc.c:1906  */



