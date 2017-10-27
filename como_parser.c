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
#include "como_io.h"

#define YYERROR_VERBOSE

int yyerror(YYLTYPE * lvalp, ast_node** ast, yyscan_t scanner, const char* msg)
{
	printf("parse error: %s in file \"%s\" on line %d:%d\n", msg, 
		get_active_file_name(), lvalp->first_line, lvalp->first_column);
	
	exit(1);
}


#line 102 "y.tab.c" /* yacc.c:339  */

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
#line 37 "como_parser.y" /* yacc.c:355  */


extern ast_node *como_parse(const char *filename);


#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif


#line 144 "y.tab.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    END = 0,
    T_CMP = 258,
    T_LTE = 259,
    T_AND = 260,
    T_NEQ = 261,
    T_TYPEOF = 262,
    T_GTE = 263,
    T_IF = 264,
    T_ELSE = 265,
    T_WHILE = 266,
    T_FOR = 267,
    T_FUNC = 268,
    T_RETURN = 269,
    T_PRINT = 270,
    T_NOELSE = 271,
    T_INC = 272,
    T_DEC = 273,
    T_FUNCTION = 274,
    T_ASSERT = 275,
    T_NUM = 276,
    T_ID = 277,
    T_STR_LIT = 278
  };
#endif
/* Tokens.  */
#define END 0
#define T_CMP 258
#define T_LTE 259
#define T_AND 260
#define T_NEQ 261
#define T_TYPEOF 262
#define T_GTE 263
#define T_IF 264
#define T_ELSE 265
#define T_WHILE 266
#define T_FOR 267
#define T_FUNC 268
#define T_RETURN 269
#define T_PRINT 270
#define T_NOELSE 271
#define T_INC 272
#define T_DEC 273
#define T_FUNCTION 274
#define T_ASSERT 275
#define T_NUM 276
#define T_ID 277
#define T_STR_LIT 278

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 59 "como_parser.y" /* yacc.c:355  */

	long number;
	char* id;
	char* stringliteral;
	ast_node* ast;

#line 211 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
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

#line 241 "y.tab.c" /* yacc.c:358  */

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
#define YYLAST   217

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  128

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   278

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    16,     2,     2,     2,    15,     2,     2,
      33,    34,    13,    12,    40,    11,     2,    14,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
       9,    32,    10,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    36,     2,    37,     2,     2,     2,     2,
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
       5,     6,     7,     8,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   127,   127,   131,   132,   136,   140,   141,   145,   149,
     149,   153,   155,   157,   159,   161,   165,   172,   178,   184,
     188,   189,   193,   197,   199,   201,   203,   209,   213,   220,
     224,   226,   228,   232,   238,   245,   247,   251,   253,   257,
     261,   263,   267,   269,   273,   278,   280,   282,   284,   286,
     288,   292,   296,   300,   304,   308,   312,   316,   320,   325,
     330,   335,   339,   343,   347,   349,   351,   353
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"EOF\"", "error", "$undefined", "T_CMP", "T_LTE", "T_AND", "T_NEQ",
  "T_TYPEOF", "T_GTE", "'<'", "'>'", "'-'", "'+'", "'*'", "'/'", "'%'",
  "'!'", "T_IF", "T_ELSE", "T_WHILE", "T_FOR", "T_FUNC", "T_RETURN",
  "T_PRINT", "T_NOELSE", "T_INC", "T_DEC", "T_FUNCTION", "T_ASSERT",
  "T_NUM", "T_ID", "T_STR_LIT", "'='", "'('", "')'", "';'", "'{'", "'}'",
  "'['", "']'", "','", "$accept", "start", "top_statement_list",
  "top_statement", "inner_statement_list", "inner_statement",
  "function_keyword", "statement", "assignment_statement",
  "print_statement", "assert_statement", "return_statement",
  "optional_expression", "compound_statement", "expression_statement",
  "primary_expression", "if_statement_without_else", "selection_statement",
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
       0,   256,   257,   258,   259,   260,   261,   262,   263,    60,
      62,    45,    43,    42,    47,    37,    33,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,    61,    40,    41,    59,   123,   125,    91,    93,
      44
};
# endif

#define YYPACT_NINF -49

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-49)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -49,    20,   102,   -49,   130,   130,   130,   -20,    11,    15,
     -49,   130,    57,   -49,    58,   -49,   -21,   -49,   130,   -49,
     130,   -49,     5,   -49,    71,    72,    73,   -49,   -49,   -49,
      46,    74,   -49,   -49,   139,     6,   190,   143,   -49,   130,
     130,    70,    75,    76,   130,   130,   -49,   -49,   130,   130,
      13,    66,    76,    77,    86,   -49,    78,   -49,   -49,   -49,
     -49,   130,    79,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   -28,    -5,    80,    82,   -49,
      -4,     2,    76,    93,   -49,   -49,   -49,   -49,   -49,   130,
      98,   -31,   -49,   161,   172,   182,   190,    41,   196,   201,
     143,    61,    65,   119,   -49,    79,    79,   130,   -49,   -49,
     -49,   -49,   -49,   105,    96,   -49,   -49,   -49,   -49,    63,
      79,    98,   130,   -49,   -49,     7,    79,   -49
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,     0,     0,     0,     0,     0,     0,
       9,    21,     0,    10,     0,    64,    65,    66,     0,     7,
      41,     3,     0,     5,     0,     0,     0,    15,    12,    13,
       0,    30,    14,    11,    27,    65,    67,    61,    62,     0,
       0,     0,     0,    20,     0,     0,    58,    59,     0,    41,
       0,     0,    44,     0,    40,    42,     0,    23,    24,    25,
      26,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    19,
       0,     0,    16,     0,    49,    22,     6,     8,    63,     0,
      36,     0,    31,    53,    56,    54,    55,    57,    50,    51,
      46,    45,    47,    48,    52,     0,     0,     0,    17,    18,
      60,    43,    39,     0,    35,    37,    28,    29,    32,     0,
       0,     0,     0,    34,    38,     0,     0,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -49,   -49,   -49,   -49,   -49,   -49,   -49,   111,   123,   -49,
     -49,   -49,   -49,   -48,   -49,    -2,   -49,   -49,   -49,   -49,
     -49,    68,   168,   -49,    90,    -3
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    21,    51,    86,    22,    23,    24,    25,
      26,    27,    42,    28,    29,    52,    31,    32,    33,   113,
     114,   115,    53,    54,    55,    34
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      30,    36,    37,    38,    46,    47,   105,    61,   116,    43,
      61,    48,    49,    39,    92,    50,    63,    64,    65,    66,
       3,    67,    68,    69,    70,    71,    72,    73,    74,   106,
     108,    46,    47,    61,    61,    56,   109,    75,    76,    49,
      61,   126,    80,    81,    40,    61,    82,    84,    41,    30,
      68,    69,    70,    71,    72,    73,    74,   117,   118,    91,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   123,     4,    72,    73,    74,     5,   127,    73,
      74,    60,     6,     7,    61,     8,     9,    10,    11,    12,
      44,    45,    62,    13,    14,    15,    16,    17,   122,    18,
      77,    61,    19,    85,    20,   119,    57,    58,    59,     4,
      79,    90,    48,     5,    61,    19,    88,   107,     6,     7,
     125,     8,     9,    10,    11,    12,    89,   110,   112,    13,
      14,    15,    16,    17,    74,    18,   121,     4,    19,   120,
      20,     5,    63,    64,    65,    66,     6,    67,    68,    69,
      70,    71,    72,    73,    74,    71,    72,    73,    74,    15,
      35,    17,    87,    18,    78,    64,    65,    66,    20,    67,
      68,    69,    70,    71,    72,    73,    74,    65,    66,   111,
      67,    68,    69,    70,    71,    72,    73,    74,    66,   124,
      67,    68,    69,    70,    71,    72,    73,    74,    67,    68,
      69,    70,    71,    72,    73,    74,    69,    70,    71,    72,
      73,    74,    70,    71,    72,    73,    74,    83
};

static const yytype_uint8 yycheck[] =
{
       2,     4,     5,     6,    25,    26,    34,    38,    39,    11,
      38,    32,    33,    33,    62,    18,     3,     4,     5,     6,
       0,     8,     9,    10,    11,    12,    13,    14,    15,    34,
      34,    25,    26,    38,    38,    30,    34,    39,    40,    33,
      38,    34,    44,    45,    33,    38,    48,    34,    33,    51,
       9,    10,    11,    12,    13,    14,    15,   105,   106,    61,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,   120,     7,    13,    14,    15,    11,   126,    14,
      15,    35,    16,    17,    38,    19,    20,    21,    22,    23,
      33,    33,    18,    27,    28,    29,    30,    31,    35,    33,
      30,    38,    36,    37,    38,   107,    35,    35,    35,     7,
      35,    33,    32,    11,    38,    36,    39,    35,    16,    17,
     122,    19,    20,    21,    22,    23,    40,    34,    30,    27,
      28,    29,    30,    31,    15,    33,    40,     7,    36,    34,
      38,    11,     3,     4,     5,     6,    16,     8,     9,    10,
      11,    12,    13,    14,    15,    12,    13,    14,    15,    29,
      30,    31,    51,    33,    41,     4,     5,     6,    38,     8,
       9,    10,    11,    12,    13,    14,    15,     5,     6,    89,
       8,     9,    10,    11,    12,    13,    14,    15,     6,   121,
       8,     9,    10,    11,    12,    13,    14,    15,     8,     9,
      10,    11,    12,    13,    14,    15,    10,    11,    12,    13,
      14,    15,    11,    12,    13,    14,    15,    49
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    42,    43,     0,     7,    11,    16,    17,    19,    20,
      21,    22,    23,    27,    28,    29,    30,    31,    33,    36,
      38,    44,    47,    48,    49,    50,    51,    52,    54,    55,
      56,    57,    58,    59,    66,    30,    66,    66,    66,    33,
      33,    33,    53,    56,    33,    33,    25,    26,    32,    33,
      66,    45,    56,    63,    64,    65,    30,    35,    35,    35,
      35,    38,    18,     3,     4,     5,     6,     8,     9,    10,
      11,    12,    13,    14,    15,    56,    56,    30,    49,    35,
      56,    56,    56,    63,    34,    37,    46,    48,    39,    40,
      33,    56,    54,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    34,    34,    35,    34,    34,
      34,    65,    30,    60,    61,    62,    39,    54,    54,    56,
      34,    40,    35,    54,    62,    56,    34,    54
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    45,    45,    46,    47,
      47,    48,    48,    48,    48,    48,    49,    50,    51,    52,
      53,    53,    54,    55,    55,    55,    55,    56,    56,    57,
      58,    58,    58,    58,    59,    60,    60,    61,    61,    62,
      63,    63,    64,    64,    65,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     2,     0,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     4,     4,     3,
       1,     0,     3,     2,     2,     2,     2,     1,     4,     5,
       1,     3,     5,     9,     6,     1,     0,     1,     3,     1,
       1,     0,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       4,     2,     2,     3,     1,     1,     1,     2
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
#line 127 "como_parser.y" /* yacc.c:1646  */
    { *ast = (yyvsp[0].ast); }
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 131 "como_parser.y" /* yacc.c:1646  */
    { ast_node_statement_list_push((yyvsp[-1].ast), (yyvsp[0].ast)); (yyval.ast) = (yyvsp[-1].ast); }
#line 1535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 132 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(0); }
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 136 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 140 "como_parser.y" /* yacc.c:1646  */
    { ast_node_statement_list_push((yyvsp[-1].ast), (yyvsp[0].ast)); (yyval.ast) = (yyvsp[-1].ast); }
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 141 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(0); }
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 145 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 153 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 155 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 157 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 159 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 161 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 165 "como_parser.y" /* yacc.c:1646  */
    {
 		(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_ASSIGN, ast_node_create_id((yyvsp[-2].id)), (yyvsp[0].ast)); 
 		free((yyvsp[-2].id)); 
	}
#line 1604 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 172 "como_parser.y" /* yacc.c:1646  */
    {
		(yyval.ast) = ast_node_create_print((yyvsp[-1].ast));
	}
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 178 "como_parser.y" /* yacc.c:1646  */
    {
        (yyval.ast) = ast_node_create_assert((yyvsp[-1].ast), (yylsp[-3]).first_line);
    }
#line 1620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 184 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_return((yyvsp[-1].ast)); }
#line 1626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 188 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 189 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = NULL; }
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 193 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1644 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 197 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1650 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 199 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1656 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 201 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 203 "como_parser.y" /* yacc.c:1646  */
    {
  (yyval.ast) = (yyvsp[-1].ast);
 }
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 209 "como_parser.y" /* yacc.c:1646  */
    {
    (yyval.ast) = (yyvsp[0].ast);
  }
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 213 "como_parser.y" /* yacc.c:1646  */
    {
    (yyval.ast) = ast_node_create_slot_access((yyvsp[-3].ast), (yyvsp[-1].ast));
  }
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 220 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_if((yyvsp[-2].ast), (yyvsp[0].ast), NULL); }
#line 1692 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 224 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1698 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 226 "como_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].ast)->u1.if_node.b2 = (yyvsp[0].ast); (yyval.ast) = (yyvsp[-2].ast); }
#line 1704 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 228 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) = ast_node_create_while((yyvsp[-2].ast), (yyvsp[0].ast));
 }
#line 1712 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 232 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) = ast_node_create_for((yyvsp[-6].ast), (yyvsp[-4].ast), (yyvsp[-2].ast), (yyvsp[0].ast));
 }
#line 1720 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 238 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_function((yyvsp[-4].id), (yyvsp[-2].ast), (yyvsp[0].ast));
	free((yyvsp[-4].id));
 }
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 245 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 247 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(0); }
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 251 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(1, (yyvsp[0].ast)); }
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 253 "como_parser.y" /* yacc.c:1646  */
    { ast_node_statement_list_push((yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast) = (yyvsp[-2].ast); }
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 257 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_id((yyvsp[0].id)); free((yyvsp[0].id)); }
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 261 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 263 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(0); }
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 267 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_statement_list(1, (yyvsp[0].ast)); }
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 269 "como_parser.y" /* yacc.c:1646  */
    { ast_node_statement_list_push((yyvsp[-2].ast), (yyvsp[0].ast)); (yyval.ast) = (yyvsp[-2].ast); }
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 273 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[0].ast); }
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 278 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_ADD, (yyvsp[-2].ast), (yyvsp[0].ast));   }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 280 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_MINUS, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 282 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_TIMES, (yyvsp[-2].ast), (yyvsp[0].ast)); }
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 284 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_DIV, (yyvsp[-2].ast), (yyvsp[0].ast));   }
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 286 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = (yyvsp[-1].ast); }
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 288 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_LT, (yyvsp[-2].ast), (yyvsp[0].ast));   
 }
#line 1827 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 292 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_GT, (yyvsp[-2].ast), (yyvsp[0].ast));   
 }
#line 1835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 296 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_REM, (yyvsp[-2].ast), (yyvsp[0].ast));
 }
#line 1843 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 300 "como_parser.y" /* yacc.c:1646  */
    { 
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_CMP, (yyvsp[-2].ast), (yyvsp[0].ast));   
 }
#line 1851 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 304 "como_parser.y" /* yacc.c:1646  */
    {
  (yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_AND, (yyvsp[-2].ast), (yyvsp[0].ast));
 }
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 308 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_NEQ, (yyvsp[-2].ast), (yyvsp[0].ast));   
 }
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 312 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_LTE, (yyvsp[-2].ast), (yyvsp[0].ast));   
 }
#line 1875 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 316 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) = ast_node_create_binary_op(AST_BINARY_OP_GTE, (yyvsp[-2].ast), (yyvsp[0].ast)); 
 }
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 320 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) =ast_node_create_postfix_op(AST_POSTFIX_OP_INC, ast_node_create_id((yyvsp[-1].id)));
  	free((yyvsp[-1].id));
 }
#line 1892 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 325 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) =ast_node_create_postfix_op(AST_POSTFIX_OP_DEC, ast_node_create_id((yyvsp[-1].id)));
  	free((yyvsp[-1].id));
 }
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 330 "como_parser.y" /* yacc.c:1646  */
    {
	(yyval.ast) = ast_node_create_call(ast_node_create_id((yyvsp[-3].id)), (yyvsp[-1].ast), (yylsp[-3]).first_line, (yylsp[-3]).first_column);
  	free((yyvsp[-3].id));
 }
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 335 "como_parser.y" /* yacc.c:1646  */
    {
 	(yyval.ast) = ast_node_create_unary_op(AST_UNARY_OP_MINUS, (yyvsp[0].ast));
 }
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 339 "como_parser.y" /* yacc.c:1646  */
    {
  (yyval.ast) = ast_node_create_unary_op(AST_UNARY_NOT, (yyvsp[0].ast));
 }
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 343 "como_parser.y" /* yacc.c:1646  */
    {
    (yyval.ast) = ast_node_create_array((yyvsp[-1].ast));
 }
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 347 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_number((yyvsp[0].number)); }
#line 1940 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 349 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_id((yyvsp[0].id));  free((yyvsp[0].id)); }
#line 1946 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 351 "como_parser.y" /* yacc.c:1646  */
    { (yyval.ast) = ast_node_create_string_literal((yyvsp[0].stringliteral)); free((yyvsp[0].stringliteral)); }
#line 1952 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 353 "como_parser.y" /* yacc.c:1646  */
    {
    (yyval.ast) =ast_node_create_tyepof((yyvsp[0].ast));
 }
#line 1960 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1964 "y.tab.c" /* yacc.c:1646  */
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
#line 358 "como_parser.y" /* yacc.c:1906  */


ast_node *como_parse(const char *filename)
{
    ast_node* statements;
    yyscan_t scanner;
    YY_BUFFER_STATE state;
    char* text;

    text = como_read_file(filename);

    if(text == NULL) 
    {
        goto fail;
    }
    
    if(yylex_init(&scanner)) 
    {
        goto fail;
    }

    state = yy_scan_string(text, scanner);

    if(yyparse(&statements, scanner)) 
    {
        goto fail;
    }

    yy_delete_buffer(state, scanner);

    yylex_destroy(scanner);

    free(text);

    return statements;

fail:
  fprintf(stdout, "Error parsing file '%s'\n", filename);
  fflush(stdout);
  exit(1);
}


