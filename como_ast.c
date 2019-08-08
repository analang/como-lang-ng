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

#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "como_ast.h"
#include "como_globals.h"

ast_node *ast_node_create_slot_access(ast_node *value, ast_node *index)
{
    ast_node *retval = malloc(sizeof(ast_node));    
    retval->type = AST_NODE_TYPE_SLOT_ACCESS;
    retval->u1.slot_access_node.value = value;
    retval->u1.slot_access_node.index = index;
    return retval;
}

ast_node *ast_node_create_array(ast_node *elements)
{
    ast_node *retval = malloc(sizeof(ast_node));    
    retval->type = AST_NODE_TYPE_ARRAY;
    retval->u1.array_node.elements = elements;
    return retval;
}

ast_node *ast_node_create_assert(ast_node *expression, int lineno) 
{
    
    ast_node *retval = malloc(sizeof(ast_node));    
    retval->type = AST_NODE_TYPE_ASSERT;
    retval->u1.assert_node.expr = expression;
    retval->u1.assert_node.lineno = lineno;
    return retval;
}

ast_node *ast_node_create_tyepof(ast_node *expression) 
{
    
    ast_node *retval = malloc(sizeof(ast_node));    
    retval->type = AST_NODE_TYPE_TYPEOF;
    retval->u1.typeof_node.expr = expression;
    return retval;
}

ast_node *ast_node_create_postfix_op(ast_postfix_op_type type,
    ast_node *expression) 
{
    
    ast_node *retval = malloc(sizeof(ast_node));    
    retval->type = AST_NODE_TYPE_POSTFIX;
    retval->u1.postfix_node.type = type;
    retval->u1.postfix_node.expr = expression;
    return retval;
}

ast_node *ast_node_create_unary_op(ast_unary_op_type type, ast_node *expr)
{
    ast_node *retval = malloc(sizeof(ast_node));
    retval->type = AST_NODE_TYPE_UNARY_OP;
    retval->u1.unary_node.type = type;
    retval->u1.unary_node.expr = expr;
    return retval;
}

ast_node *ast_node_create_number(long value)
{
    ast_node *retval = malloc(sizeof(ast_node));
    retval->type = AST_NODE_TYPE_NUMBER;
    retval->u1.number_value = value;
    return retval;
}

ast_node *ast_node_create_statement_list(size_t count, ...)
{
    va_list va;
    size_t i;

    ast_node *retval = malloc(sizeof(ast_node));
    retval->type = AST_NODE_TYPE_STATEMENT_LIST;

    if(count > 0) 
    {	
        retval->u1.statements_node.count = count;
        retval->u1.statements_node.capacity = count;
        retval->u1.statements_node.statement_list = 
                malloc(sizeof(ast_node) * (count));
        va_start(va, count);

        for(i = 0; i < count; i++) 
        {
            retval->u1.statements_node.statement_list[i] = 
                va_arg(va, ast_node *);
        }

        va_end(va);
    } 
    else 
    {
        retval->u1.statements_node.count = 0;
        retval->u1.statements_node.capacity = 2;
        retval->u1.statements_node.statement_list = 
            malloc(sizeof(ast_node) * 2);
        retval->u1.statements_node.statement_list[0] = NULL;
        retval->u1.statements_node.statement_list[1] = NULL;
    }

    return retval;
}

void ast_node_statement_list_push(ast_node *node, ast_node *value)
{
    if(node->u1.statements_node.count >= node->u1.statements_node.capacity) 
    {	
        node->u1.statements_node.capacity += 1;

        size_t new_capacity = node->u1.statements_node.capacity;	

        node->u1.statements_node.statement_list = 
        realloc(node->u1.statements_node.statement_list, 
        sizeof(ast_node) * new_capacity);

        node->u1.statements_node.statement_list[
        node->u1.statements_node.count++] = value;	
    } 
    else 
    {
        node->u1.statements_node.statement_list[
            node->u1.statements_node.count++] = value;	
    }
}

ast_node *ast_node_create_binary_op(ast_binary_op_type type, ast_node *left, 
        ast_node *right)
{
    ast_node *retval = malloc(sizeof(ast_node));
    
    retval->type = AST_NODE_TYPE_BIN_OP;
    retval->u1.binary_node.type = type;
    retval->u1.binary_node.left = left;
    retval->u1.binary_node.right = right;

    return retval;
}

ast_node *ast_node_create_id(const char *name)
{
    ast_node *retval = malloc(sizeof(ast_node));
    retval->type = AST_NODE_TYPE_ID;
    
    size_t len = strlen(name);
    
    retval->u1.id_node.length = len;
    retval->u1.id_node.name = malloc(len + 1);
    
    memcpy(retval->u1.id_node.name, name, len + 1);
    
    return retval;
}

ast_node *ast_node_create_if(ast_node *condition, ast_node *b1, ast_node *b2)
{
    ast_node *retval = malloc(sizeof(ast_node));

    retval->type = AST_NODE_TYPE_IF;
    retval->u1.if_node.condition = condition;
    retval->u1.if_node.b1 = b1;
    retval->u1.if_node.b2 = b2;
    
    return retval;
}

ast_node *ast_node_create_while(ast_node *condition, ast_node *body)
{
    ast_node *retval = malloc(sizeof(ast_node));
    
    retval->type = AST_NODE_TYPE_WHILE;
    retval->u1.while_node.condition = condition;
    retval->u1.while_node.body = body;
    
    return retval;
}

ast_node *ast_node_create_for(ast_node *initialization, 
        ast_node *condition, ast_node *final_expression, ast_node *body) 
{
    ast_node *retval = malloc(sizeof(ast_node));

    retval->type = AST_NODE_TYPE_FOR;
    retval->u1.for_node.initialization = initialization;
    retval->u1.for_node.condition = condition;
    retval->u1.for_node.final_expression = final_expression;
    retval->u1.for_node.body = body;

    return retval;	
}

ast_node *ast_node_create_function(const char *name, ast_node *parameters, 
        ast_node *body)
{
    ast_node *retval = malloc(sizeof(ast_node));
    
    retval->type = AST_NODE_TYPE_FUNC_DECL;
    
    size_t len = strlen(name);
    
    retval->u1.function_node.name_length = len;
    retval->u1.function_node.name = malloc(len + 1);
    
    memcpy(retval->u1.function_node.name, name, len + 1);
    
    retval->u1.function_node.parameter_list = parameters;
    retval->u1.function_node.body = body;	
    
    return retval;
}

ast_node *ast_node_create_call(ast_node *id, ast_node *args, int lineno, 
        int col)
{
    ast_node *retval = malloc(sizeof(ast_node));

    retval->type = AST_NODE_TYPE_CALL;
    retval->u1.call_node.id = id;
    retval->u1.call_node.arguments = args;
    retval->u1.call_node.lineno = lineno;
    retval->u1.call_node.colno = col;

    return retval;
}

ast_node *ast_node_create_return(ast_node *expr)
{
    ast_node *retval = malloc(sizeof(ast_node));
    
    retval->type = AST_NODE_TYPE_RET;
    retval->u1.return_node.expr = expr;
    
    return retval;
}


ast_node *ast_node_create_print(ast_node *expr)
{
    ast_node *retval = malloc(sizeof(ast_node));
    
    retval->type = AST_NODE_TYPE_PRINT;
    retval->u1.print_node.expr = expr;
    
    return retval;
}

ast_node *ast_node_create_string_literal(const char *str)
{
    ast_node *retval = malloc(sizeof(ast_node));
    
    retval->type = AST_NODE_TYPE_STRING;
    retval->u1.string_value.length = strlen(str);
    retval->u1.string_value.value = malloc(retval->u1.string_value.length + 1);
    
    memcpy(retval->u1.string_value.value, str, retval->u1.string_value.length);
    
    retval->u1.string_value.value[retval->u1.string_value.length] = '\0';
    
    return retval;
}





























