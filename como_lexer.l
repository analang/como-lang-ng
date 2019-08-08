%{
/*
 * Copyright (c) 2016 Ryan McCullagh <me@ryanmccullagh.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include "como_globals.h"
#include "como_ast.h"
#include "como_parser.h"

static void update_loc(YYLTYPE *loc, char* text)
{
    loc->first_line = loc->last_line;
    loc->first_column = loc->last_column;
    int i;
    for(i = 0; text[i] != '\0'; i++) 
    {
        if(text[i] == '\n') 
        {
            loc->last_line++;
            loc->last_column = 0;
        } 
        else 
        {
            loc->last_column++;
        }
    }
}

#define YY_USER_ACTION update_loc(yylloc, yytext);	

%}

%option outfile="como_lexer.c" header-file="como_lexer.h"
%option warn nodefault

%option reentrant noyywrap never-interactive nounistd yylineno
%option bison-bridge
%option bison-locations nounput noinput

%x COMMENT

WHITE_SPACE	[ \r\n\t]*
L		[a-zA-Z_]
A		[a-zA-Z_0-9]
D   [0-9]

%%

"//".*\n                            ;

"/*"                                BEGIN(COMMENT);                                                                                                                                                   
<COMMENT>"/*"                       ;                                                                                        
<COMMENT>"*/"                       BEGIN(INITIAL);                                                                                                                                                   
<COMMENT>"EOF"                      ;                                                                                                            
<COMMENT>.|"\n"                     ;

"assert"        { return T_ASSERT; }
"typeof"		{ return T_TYPEOF; }
"if"		    { return T_IF;     }
"else"          { return T_ELSE;   }
"while"         { return T_WHILE;  }
"for"			{ return T_FOR;    }
"func"          { return T_FUNC;     }
"function"      { return T_FUNCTION; }
"print"         { return T_PRINT;  }
"return"        { return T_RETURN; }
"=="            { return T_CMP;    }
"!="            { return T_NEQ;    }
"<="            { return T_LTE;    }
">="            { return T_GTE;    }
"++"            { return T_INC;    }
"--"            { return T_DEC;    }
"&&"            { return T_AND;    }

{WHITE_SPACE}	{ /* Skipping Blanks Today */ }
{L}{A}*         {
	size_t len = strlen(yytext);
	yylval->id = malloc(len + 1);
	memcpy(yylval->id, yytext, len + 1);
	return T_ID;
}

{D}+		      { 
	yylval->number = strtol(yytext, NULL, 10); 
	return T_NUM; 
}

L?\"(\\.|[^\\"])*\"	{ 
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

L?\'(\\.|[^\\'])*\'	{ 
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

.		{ return yytext[0];				     }

%%

