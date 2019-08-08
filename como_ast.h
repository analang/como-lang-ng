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

#ifndef COMO_AST_H
#define COMO_AST_H

#include <stddef.h>
#include <object.h>
#include <stdarg.h>

typedef enum 
{
    AST_NODE_TYPE_NUMBER, 
    AST_NODE_TYPE_STRING,
    AST_NODE_TYPE_ID,
    AST_NODE_TYPE_FOR,
    AST_NODE_TYPE_STATEMENT_LIST, 
    AST_NODE_TYPE_BIN_OP,
    AST_NODE_TYPE_IF, 
    AST_NODE_TYPE_WHILE, 
    AST_NODE_TYPE_FUNC_DECL, 
    AST_NODE_TYPE_CALL, 
    AST_NODE_TYPE_RET, 
    AST_NODE_TYPE_PRINT,
    AST_NODE_TYPE_UNARY_OP, 
    AST_NODE_TYPE_POSTFIX,
    AST_NODE_TYPE_TYPEOF,
    AST_NODE_TYPE_ASSERT,
    AST_NODE_TYPE_BOOL,
    AST_NODE_TYPE_ARRAY,
    AST_NODE_TYPE_SLOT_ACCESS,
} ast_node_type;

typedef enum 
{
    AST_POSTFIX_OP_INC, 
    AST_POSTFIX_OP_DEC,
} ast_postfix_op_type;

typedef enum {
    AST_UNARY_OP_MINUS,
    AST_UNARY_NOT,
} ast_unary_op_type;

typedef enum {
    AST_BINARY_OP_ADD, 
    AST_BINARY_OP_MINUS, 
    AST_BINARY_OP_ASSIGN,
    AST_BINARY_OP_TIMES, 
    AST_BINARY_OP_DIV, 
    AST_BINARY_OP_CMP,
    AST_BINARY_OP_LT, 
    AST_BINARY_OP_LTE,
    AST_BINARY_OP_GT, 
    AST_BINARY_OP_GTE,
    AST_BINARY_OP_NEQ,
    AST_BINARY_OP_REM,
    AST_BINARY_OP_AND,
} ast_binary_op_type;

typedef struct ast_node ast_node;

typedef struct 
{
    char   *name;
    size_t  length;
} ast_node_id;

typedef struct ast_node_statements ast_node_statements;

struct ast_node_statements 
{
    size_t     count;
    size_t     capacity;
    ast_node **statement_list;
};

typedef struct 
{
    ast_binary_op_type  type;
    ast_node           *left;
    ast_node           *right;
} ast_node_binary;

typedef struct 
{
    ast_unary_op_type   type;
    ast_node           *expr;
} ast_node_unary;

typedef struct 
{
    ast_postfix_op_type type;
    ast_node           *expr;
} ast_node_postfix;

typedef struct 
{
    ast_node *condition;
    ast_node *b1;
    ast_node *b2;
} ast_node_if;

typedef struct 
{
    ast_node *condition;
    ast_node *body;
} ast_node_while;

typedef struct 
{
    ast_node *initialization;
    ast_node *condition;
    ast_node *final_expression;
    ast_node *body;
} ast_node_for;

typedef struct 
{
    char     *name;
    size_t    name_length;
    ast_node *parameter_list;
    ast_node *body;	
} ast_node_function;

typedef struct 
{
    int       lineno;
    int       colno;
    ast_node *id;
    ast_node *arguments;
} ast_node_call;

typedef struct 
{
	ast_node *expr;
} ast_node_return;

typedef struct 
{
	ast_node *expr;	
} ast_node_print;

typedef struct 
{
    ast_node *expr; 
} ast_node_typeof;

typedef struct 
{
    int lineno;
    ast_node *expr; 
} ast_node_assert;

typedef struct 
{
    ast_node *value;
    ast_node *index;
} ast_node_slot_access;

typedef struct 
{
    ast_node *elements;
} ast_node_type_array;

struct ast_node 
{
    ast_node_type type;
    union 
    {
        long number_value;
        struct 
        {
            char  *value;
            size_t length;
        } string_value;
        ast_node_id          id_node;
        ast_node_statements  statements_node;
        ast_node_binary      binary_node;
        ast_node_unary       unary_node;
        ast_node_if          if_node;
        ast_node_while       while_node;
        ast_node_for         for_node;
        ast_node_function    function_node;
        ast_node_call        call_node;
        ast_node_return      return_node;
        ast_node_print       print_node;
        ast_node_postfix     postfix_node;
        ast_node_typeof      typeof_node;
        ast_node_assert      assert_node;
        ast_node_type_array  array_node;
        ast_node_slot_access slot_access_node;
    } u1;
};

#define AST_NODE_AS_ID(p) (p)->u1.id_node.name

extern void ast_node_free(ast_node *p);

ast_node *ast_node_create_slot_access(ast_node *value, ast_node *index);

ast_node *ast_node_create_array(ast_node *elements);

ast_node *ast_node_create_assert(ast_node *expression, int lineno);

ast_node *ast_node_create_tyepof(ast_node *expression);

extern ast_node *ast_node_create_postfix_op(ast_postfix_op_type type, 
        ast_node *expression);

extern ast_node *ast_node_create_unary_op(ast_unary_op_type, ast_node *);

extern ast_node *ast_node_create_number(long value);

extern ast_node *ast_node_create_statement_list(size_t count, ...);

extern void ast_node_statement_list_push(ast_node *node, ast_node *value);

extern ast_node *ast_node_create_binary_op(ast_binary_op_type type, 
        ast_node *left, ast_node *right);

extern ast_node *ast_node_create_id(const char *name);

extern ast_node *ast_node_create_if(ast_node *condition, ast_node *b1, 
        ast_node *b2);

extern ast_node *ast_node_create_while(ast_node *condition, ast_node *body);

extern ast_node *ast_node_create_for(ast_node *initialization, 
        ast_node *condition, ast_node *final_expression, ast_node *body);

extern ast_node *ast_node_create_function(const char *name, 
        ast_node *parameters, ast_node *body);

extern ast_node *ast_node_create_call(ast_node *id, ast_node *arguments, 
        int lineno, int col);

extern ast_node *ast_node_create_return(ast_node *expr);

extern ast_node *ast_node_create_print(ast_node *expr);

extern ast_node *ast_node_create_string_literal(const char *str);

extern void ast_node_free(ast_node *node);

extern void ast_node_dump_tree(ast_node *node);

#endif /* !COMO_AST_H */
