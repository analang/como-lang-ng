#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "como_ast.h"
#include "como_globals.h"
#include "como_debug.h"

void ast_node_free(ast_node *p)
{
	if(!p)
		return;
	switch(p->type) {
		case AST_NODE_TYPE_BOOL:
			/* Not implemented */
			assert(0);
		break;
		case AST_NODE_TYPE_SLOT_ACCESS:
			ast_node_free(p->u1.slot_access_node.value);
			ast_node_free(p->u1.slot_access_node.index);
			free(p);
		break;
		case AST_NODE_TYPE_ARRAY:
			ast_node_free(p->u1.array_node.elements);
			free(p);
		break;
		case AST_NODE_TYPE_ASSERT:
			ast_node_free(p->u1.assert_node.expr);
			free(p);			
		break;
		case AST_NODE_TYPE_TYPEOF:
			ast_node_free(p->u1.typeof_node.expr);
			free(p);			
		break;
		case AST_NODE_TYPE_UNARY_OP:
			ast_node_free(p->u1.unary_node.expr);
			free(p);
		break;
		case AST_NODE_TYPE_POSTFIX:
			ast_node_free(p->u1.postfix_node.expr);
			free(p);
		break;
		case AST_NODE_TYPE_WHILE:
			ast_node_free(p->u1.while_node.condition);
			ast_node_free(p->u1.while_node.body);
			free(p);
		break;
		case AST_NODE_TYPE_FOR:
			ast_node_free(p->u1.for_node.initialization);
			ast_node_free(p->u1.for_node.condition);
			ast_node_free(p->u1.for_node.final_expression);			
			ast_node_free(p->u1.for_node.body);	
			free(p);
		break;
		case AST_NODE_TYPE_STRING:
			free(p->u1.string_value.value);
			free(p);
		break;
		case AST_NODE_TYPE_RET:
			ast_node_free(p->u1.return_node.expr);
			free(p);
		break;
		case AST_NODE_TYPE_IF:
			ast_node_free(p->u1.if_node.condition);
			ast_node_free(p->u1.if_node.b1);
			ast_node_free(p->u1.if_node.b2);
			free(p);
		break;
		case AST_NODE_TYPE_NUMBER:
			free(p);
		break;
		case AST_NODE_TYPE_STATEMENT_LIST: {
			size_t i;
			for(i = 0; i < p->u1.statements_node.count; i++) {
				ast_node_free(p->u1.statements_node.statement_list[i]);
			}
			free(p->u1.statements_node.statement_list);
			free(p);
		} 
		break;
		case AST_NODE_TYPE_BIN_OP:
			ast_node_free(p->u1.binary_node.left);
			ast_node_free(p->u1.binary_node.right);
			free(p);
		break;
		case AST_NODE_TYPE_ID:
			free(p->u1.id_node.name);
			free(p);
		break;
		case AST_NODE_TYPE_FUNC_DECL:
			free(p->u1.function_node.name);
			ast_node_free(p->u1.function_node.parameter_list);
			ast_node_free(p->u1.function_node.body);
			free(p);		
		break;
		case AST_NODE_TYPE_PRINT:
			ast_node_free(p->u1.print_node.expr);
			free(p);		
		break;
		case AST_NODE_TYPE_CALL:
			ast_node_free(p->u1.call_node.id);
			ast_node_free(p->u1.call_node.arguments);
			free(p);		
		break;
		default:
			como_error_noreturn(NULL, "p->type not implemented (%d)", p->type);
		break;
	}
}