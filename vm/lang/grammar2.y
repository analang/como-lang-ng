%{

  #include <stdio.h>

  #include "como_parser.h"
  #include "como_lexer.h"


  int yyerror(ast_node **ast, yyscan_t scanner, const char* msg)
  {
    (void)ast;
    fprintf(stderr, "como: error parsing: %s\n", msg);
  }

  /*
   object literals,
   array literals,
   functions,
   classes with single inheritence, and access modifiers
   */
%}

%code requires {
  #include <stdio.h>

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

  typedef struct ast_node {
    void *padding;
  } ast_node;

}

%union {
  long lval;
  double dval;
  char* id;
  char* stringliteral;
  ast_node *ast;
}

%token <lval> T_INT
%token <dval> T_DOUBLE
%token <id> T_ID
%token <stringliteral> T_STR_LIT
%token T_FUNCTION
%token T_CLASS;
%token T_PUBLIC
%token T_PROTECTED
%token T_PRIVATE
%token T_NEW
%token T_IMPORT

%type<ast> function_statement function_statements function_def statements statement program constant primary_expression assignment_expression unary_expression optional_argument_list argument_list argument postfix_expression

%type<ast> key opt_key_vpairs key_vpairs keyvpair
%type<ast> class_statements class_statement class_def
%type<ast> import_stmt dotted_name import_name

%start program

%expect 0
%error-verbose
%defines "como_parser.h"
%pure-parser

%lex-param   { yyscan_t scanner }
%parse-param { ast_node** ast   }
%parse-param { yyscan_t scanner }

%%


program: 
  statements { $$ = $1; }
;

statements:
  statements statement { $$ = $1;    }
| %empty               { $$ = (ast_node *)NULL; }
;

statement:
  assignment_expression     ';' { $$ = $1; }
| function_def              { $$ = $1; }
| import_stmt optional_semi { $$ = $1; }
| class_def                 { $$ = $1; }
;

optional_semi: 
  ';'
| %empty
;

import_stmt:
  T_IMPORT dotted_name { $$ = $2; }
;

dotted_name:
  import_name                   { $$ = $1; }
| dotted_name '.' import_name   { $$ = $1; }
;

import_name:
  T_ID { $$ = (ast_node *)NULL; }
;

// So we don't have nested functions 
function_statements:
  function_statements function_statement { $$ = $1; }
| %empty { $$ = (ast_node *)NULL; }

;

function_statement:
  assignment_expression ';' { $$ = $1; }
;
  
function_def:
  T_FUNCTION T_ID '(' ')' '{' function_statements '}' { $$ = $6; }
;


access_modifier:
  T_PUBLIC | T_PROTECTED | T_PRIVATE 
;

class_statements:
  class_statements class_statement { $$ = $1;   }
| %empty                           { $$ = NULL; }

class_statement:
  access_modifier function_def { $$ = $2; }
;

class_def:
  T_CLASS T_ID '{' class_statements '}' { $$ = $4; }
;

primary_expression:
  T_ID                              { $$ = (ast_node *)NULL; }
| constant                          { $$ = $1;               }
// TODO, have a ( function_expression ) here in order to prevent access
// to a function expreesion as FE[0] FE.a
| '(' assignment_expression ')'     { $$ = (ast_node *)NULL; }
| '{' opt_key_vpairs '}'            { $$ = (ast_node *)NULL; }
| '[' optional_argument_list ']'    { $$ = (ast_node *)NULL; }
// TODO possibly a function expression
;

opt_key_vpairs:
  key_vpairs { $$ = $1; }
| %empty { $$ = (ast_node *)NULL; }
;

key_vpairs:
  keyvpair { $$ = $1; }
| key_vpairs ',' keyvpair { $$ = $1; }
;

keyvpair:
  key ':' assignment_expression { $$ = (ast_node *)NULL; }
;

key:
  T_ID       { $$ = (ast_node *)NULL; }
| T_STR_LIT  { $$ = (ast_node *)NULL; }
;

constant: 
  T_INT            { $$ = (ast_node *)1;    }
| T_DOUBLE         { $$ = (ast_node *)NULL; }
| T_STR_LIT        { $$ = (ast_node *)NULL; }
;

assignment_expression:
  unary_expression '=' assignment_expression {
    // TODO check for valid left hand unary expressions
    if($1 == (ast_node *)1) {
      fprintf(stderr, "Can't assign to a literal, tried to assign to int\n");
      YYERROR;
    }
    $$ = (ast_node *)NULL;
  }
| T_NEW postfix_expression { $$ = $2; }
| postfix_expression '+' postfix_expression { $$ = $1; }
| postfix_expression '-' postfix_expression { $$ = $1; }
| postfix_expression { $$ = $1; }
;

unary_expression: 
  postfix_expression { $$ = $1; }
;

optional_argument_list:
  argument_list { $$ = $1;               }
| %empty        { $$ = (ast_node *)NULL; }
;

argument_list:
  argument { $$ = (ast_node *)NULL; }
| argument_list ',' argument { $$ = $1; }
;

argument:
  assignment_expression { $$ = (ast_node *)NULL; }
;

postfix_expression:
  primary_expression  { $$ = $1; }
| postfix_expression '[' assignment_expression ']' { $$ = (ast_node *)NULL; }
| postfix_expression '(' optional_argument_list ')' { $$ = (ast_node *)NULL; }
| postfix_expression '.' T_ID { $$ = (ast_node *)NULL; }
;

%%

#include "como_lexer.h"
#include "io.c"

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


int main(int argc, char **argv)
{
  ast_node *program = como_parse(argv[1]);

  return 0;
}
