%{

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "como_parser.h"

%}

%option outfile="como_lexer.c" header-file="como_lexer.h"
%option warn nodefault
%option reentrant noyywrap never-interactive nounistd yylineno
%option bison-bridge
%option nounput noinput

WHITE_SPACE [ \r\n\t]*
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
D   [0-9]


%% 

"function"  { return T_FUNCTION;  }
"class"     { return T_CLASS;     }
"public"    { return T_PUBLIC;    }
"private"   { return T_PRIVATE;   }
"protected" { return T_PROTECTED; }
"import"    { return T_IMPORT;    }

{WHITE_SPACE} { /* Skipping Blanks Today */ }
{L}{A}*         {
  size_t len = strlen(yytext);
  yylval->id = malloc(len + 1);
  memcpy(yylval->id, yytext, len + 1);
  return T_ID;
}

{D}+  { 
  yylval->lval = strtol(yytext, NULL, 10); 
  return T_INT; 
}

{D}+"."{D}+ {
  yylval->dval = atof(yytext);
  return T_DOUBLE;
}


L?\"(\\.|[^\\"])*\" { 
  size_t len = strlen(yytext);
  if(len > 2U) {
    yylval->stringliteral = malloc((len -2) + 1);
    memcpy(yylval->stringliteral, yytext + 1, len - 2);
    yylval->stringliteral[len - 2] = '\0';
    return T_STR_LIT;
  } else {
    yylval->stringliteral = malloc(1);
    yylval->stringliteral[0] = '\0';
    return T_STR_LIT;
  }
}

L?\'(\\.|[^\\'])*\' { 
  size_t len = strlen(yytext);
  if(len > 2U) {
    yylval->stringliteral = malloc((len -2) + 1);
    memcpy(yylval->stringliteral, yytext + 1, len - 2);
    yylval->stringliteral[len - 2] = '\0';
    return T_STR_LIT;
  } else {
    yylval->stringliteral = malloc(1);
    yylval->stringliteral[0] = '\0';
    return T_STR_LIT;
  }
}

.   { return yytext[0];            }

%%
