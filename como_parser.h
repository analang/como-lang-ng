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
#line 37 "como_parser.y" /* yacc.c:1909  */


extern ast_node *como_parse(const char *filename);


#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif


#line 56 "como_parser.h" /* yacc.c:1909  */

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
#line 59 "como_parser.y" /* yacc.c:1909  */

	long number;
	char* id;
	char* stringliteral;
	ast_node* ast;

#line 123 "como_parser.h" /* yacc.c:1909  */
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
