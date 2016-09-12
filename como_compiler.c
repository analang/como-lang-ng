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
#include <object.h>
#include <assert.h>

#include "como_ast.h"
#include "como_stack.h"
#include "como_debug.h"
#include "como_opcode.h"
#include "como_globals.h"
#include "como_parser.h"
#include "como_lexer.h"
#include "como_compiler.h"
#include "como_io.h"

static ComoFrame *global_frame = NULL;

static void push(ComoFrame *frame, Object *value)
{
    if(frame->cf_sp >= COMO_DEFAULT_FRAME_STACKSIZE) 
    {
        como_error_noreturn("error stack overflow tried to push onto #%zu", 
                frame->cf_sp);
    } 
    else 
    {
        frame->cf_stack[frame->cf_sp++] = value;
        frame->cf_stack_size++;
    }
}

static Object *pop(ComoFrame *frame) 
{
    Object *retval = NULL;
    
    if(frame->cf_sp == 0) 
    {
        como_error_noreturn("stack underflow, tried to go before 0");
    } 
    else 
    {
        retval = frame->cf_stack[--frame->cf_sp];
        --frame->cf_stack_size;
    }

    return retval;
}

static ComoOpCode *create_op(unsigned char op, Object *oper) 
{
    ComoOpCode *ret = malloc(sizeof(ComoOpCode));
    ret->op_code = op;
    ret->operand = oper;
    return ret;
}

static ComoFrame *create_frame(Object *code) 
{
    size_t i;
    ComoFrame *frame = malloc(sizeof(ComoFrame));

    frame->cf_sp = 0;
    frame->cf_stack_size = 0;

    for(i = 0; i < (size_t)COMO_DEFAULT_FRAME_STACKSIZE; i++) {
        frame->cf_stack[i] = NULL;
    }

    frame->cf_symtab = newMap(4);
    frame->code = code;
    frame->next = NULL;
    frame->namedparameters = newArray(2);
    frame->filename = NULL;

    return frame;
}


static void como_compile(ast_node* p, ComoFrame *frame)
{
    assert(p);

    switch(p->type) 
    {
        default:
            como_error_noreturn("Invalid node type(%d)", p->type);
        break;
        case AST_NODE_TYPE_STRING:
            arrayPushEx(frame->code, newPointer((void *)create_op(LOAD_CONST, 
                newString(p->u1.string_value.value)))); 
        break;
        case AST_NODE_TYPE_PRINT:
            como_compile(p->u1.print_node.expr, frame);
            arrayPushEx(frame->code, 
                newPointer((void *)create_op(IPRINT, NULL)));
        break;
        case AST_NODE_TYPE_NUMBER:
            arrayPushEx(frame->code, newPointer((void *)create_op(LOAD_CONST, 
                newLong((long)p->u1.number_value))));
        break;
        case AST_NODE_TYPE_ID:
            arrayPushEx(frame->code, newPointer((void *)create_op(LOAD_NAME, 
                newString(p->u1.string_value.value)))); 
        break;
        case AST_NODE_TYPE_RET:
            if(p->u1.return_node.expr != NULL) 
            {
                como_compile(p->u1.return_node.expr, frame);
                arrayPushEx(frame->code, newPointer((void *)create_op(IRETURN, 
                    newLong(1L))));
            } 
            else 
            {
                arrayPushEx(frame->code, newPointer((void *)create_op(IRETURN, 
                    newLong(0L))));
            }
        break;
        case AST_NODE_TYPE_STATEMENT_LIST: 
        {
            size_t i;
            for(i = 0; i < p->u1.statements_node.count; i++) 
            {
                ast_node* stmt = p->u1.statements_node.statement_list[i];
                como_compile(stmt, frame);
            }
        } 
        break;
        case AST_NODE_TYPE_WHILE: 
        {
            Object *l = newLong((long)(O_AVAL(frame->code)->size));
            arrayPushEx(frame->code, newPointer((void *)create_op(LABEL, l)));
            
            Object *l2 = newLong(0);
            como_compile(p->u1.while_node.condition, frame);
            arrayPushEx(frame->code, newPointer((void *)create_op(JZ, l2)));

            como_compile(p->u1.while_node.body, frame);
            arrayPushEx(frame->code, newPointer((void *)create_op(JMP, 
                    newLong(O_LVAL(l)))));
        
            Object *l3 = newLong((long)(O_AVAL(frame->code)->size));
    
            arrayPushEx(frame->code, newPointer((void *)create_op(LABEL, 
                    l3))); 

            O_LVAL(l2) = O_LVAL(l3);
        }
        break;
        case AST_NODE_TYPE_FOR: 
        {
            Object *l = newLong((long)(O_AVAL(frame->code)->size));
            arrayPushEx(frame->code, newPointer((void *)create_op(LABEL, 
                    l))); 
            
            Object *l2 = newLong(0);
            como_compile(p->u1.for_node.initialization, frame);
            como_compile(p->u1.for_node.condition, frame);
            arrayPushEx(frame->code, newPointer((void *)create_op(JZ, 
                    l2))); 

            Object *l4 = newLong((long)(O_AVAL(frame->code)->size));
            /* label for the body */
            arrayPushEx(frame->code, newPointer((void *)create_op(LABEL, 
                    l4)));    

            como_compile(p->u1.for_node.body, frame);
            
            como_compile(p->u1.for_node.final_expression, frame);

            como_compile(p->u1.for_node.condition, frame);
            arrayPushEx(frame->code, newPointer((void *)create_op(JZ, 
                    l2))); 

            arrayPushEx(frame->code, newPointer((void *)create_op(JMP, 
                    newLong(O_LVAL(l4))))); 
        
            Object *l3 = newLong((long)(O_AVAL(frame->code)->size));
    
            arrayPushEx(frame->code, newPointer((void *)create_op(LABEL, 
                l3))); 
        
            O_LVAL(l2) = O_LVAL(l3);
        }
        break;
        case AST_NODE_TYPE_IF: 
        {
            Object *l2 = newLong(0);
            Object *l4 = newLong(0);
            como_compile(p->u1.if_node.condition, frame);
        
            arrayPushEx(frame->code, newPointer((void *)create_op(JZ, 
                l2))); 

            como_compile(p->u1.if_node.b1, frame);

            arrayPushEx(frame->code, newPointer((void *)create_op(JMP, 
                    l4))); 
            
            Object *l3 = newLong((long)(O_AVAL(frame->code)->size));
        
            arrayPushEx(frame->code, newPointer((void *)create_op(LABEL, 
                    l3))); 

            if(p->u1.if_node.b2 != NULL) {
                como_compile(p->u1.if_node.b2, frame);
            }
        
            O_LVAL(l2) = O_LVAL(l3);
            O_LVAL(l4) = (long)(O_AVAL(frame->code)->size);

            arrayPushEx(frame->code, newPointer((void *)create_op(LABEL, 
                    newLong((long)(O_AVAL(frame->code)->size))))); 

        } 
        break;
        case AST_NODE_TYPE_FUNC_DECL: 
        { 
            const char *name = p->u1.function_node.name;
            Object *func_decl = newArray(4);
            Object *func_decl_parameters = newArray(2);
            ComoFrame *func_decl_frame = create_frame(func_decl);
            func_decl_frame->namedparameters = func_decl_parameters;

            if(frame->filename != NULL) 
            {
                func_decl_frame->filename = copyObject(frame->filename);
            } 
            else 
            {
                func_decl_frame->filename = newString("<unknown>");
            }

            size_t i;
            ast_node_statements *parameters = &p->u1.function_node
                .parameter_list->u1
                .statements_node;

            for(i = 0; i < parameters->count; i++)
            {
                arrayPushEx(func_decl_parameters, newString(
                            AST_NODE_AS_ID(
                                parameters->statement_list[i]
                            )
                        )
                );
            }

            arrayPushEx(func_decl_frame->code, newPointer((void *)create_op(
                    LOAD_CONST, newString(name)))); 
            arrayPushEx(func_decl_frame->code, newPointer((void *)create_op(
                    STORE_NAME, newString("__FUNCTION__"))));

            como_compile(p->u1.function_node.body, func_decl_frame);

            Array *temp = O_AVAL(func_decl_frame->code);
            Object *temp2 = temp->table[temp->size - 1];

            ComoOpCode *opcode = (ComoOpCode *)(O_PTVAL(temp2));

            if(opcode->op_code != IRETURN) 
            {
                arrayPushEx(func_decl_frame->code, newPointer(
                    (void *)create_op(LOAD_CONST, newLong(0L)))); 
                arrayPushEx(func_decl_frame->code, newPointer(
                    (void *)create_op(IRETURN, newLong(1L))));           
            } 

            /* All functions are inserted into the global frame, sigh */
            mapInsertEx(frame->cf_symtab, name, newPointer(
                (void *)func_decl_frame));

            break;
        } 
        case AST_NODE_TYPE_CALL: 
        {
            const char *name = p->u1.call_node.id->u1.id_node.name;
            const long argcount = (long)p->u1
                .call_node
                .arguments->u1
                .statements_node
                .count;

            como_compile(p->u1.call_node.arguments, frame);
            arrayPushEx(frame->code, newPointer(
                    (void *)create_op(LOAD_CONST, newLong(argcount)))); 

            arrayPushEx(frame->code, newPointer(
                    (void *)create_op(LOAD_NAME, newString(name))));

            arrayPushEx(frame->code, newPointer(
                    (void *)create_op(CALL_FUNCTION, newString(name))));

            break;
        } 
        case AST_NODE_TYPE_POSTFIX: 
        {
            Object *name = newString(AST_NODE_AS_ID(p->u1.postfix_node.expr));
            switch(p->u1.postfix_node.type) 
            {
                case AST_POSTFIX_OP_INC:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(POSTFIX_INC, name)));
                break;
                case AST_POSTFIX_OP_DEC:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(POSTFIX_DEC, name)));
                break;
            }
            break;
        }
        case AST_NODE_TYPE_UNARY_OP: 
        {
            switch(p->u1.unary_node.type) 
            {
                case AST_UNARY_OP_MINUS:
                    como_compile(p->u1.unary_node.expr, frame);
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(UNARY_MINUS, NULL)));
                break;
            }
        }
        break;
        case AST_NODE_TYPE_BIN_OP: 
        {
            if(p->u1.binary_node.type != AST_BINARY_OP_ASSIGN) 
            {
                como_compile(p->u1.binary_node.left, frame);
                como_compile(p->u1.binary_node.right, frame);       
            }  
            switch(p->u1.binary_node.type) 
            {
                case AST_BINARY_OP_REM:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(IREM, NULL)));
                break;  
                case AST_BINARY_OP_LTE:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(IS_LESS_THAN_OR_EQUAL, NULL)));
                break;  
                case AST_BINARY_OP_GTE:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(IS_GREATER_THAN_OR_EQUAL, NULL)));
                break;
                case AST_BINARY_OP_LT: 
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(IS_LESS_THAN, NULL)));                    
                break;
                case AST_BINARY_OP_GT:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(IS_GREATER_THAN, NULL)));  
                break;
                case AST_BINARY_OP_CMP:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(IS_EQUAL, NULL)));  
                break;
                case AST_BINARY_OP_NEQ:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(IS_NOT_EQUAL, NULL)));  
                break;
                case AST_BINARY_OP_MINUS: 
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(IMINUS, NULL)));  
                break;
                case AST_BINARY_OP_DIV:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(IDIV, NULL)));  
                break;
                case AST_BINARY_OP_ADD:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(IADD, NULL)));  
                break;
                case AST_BINARY_OP_TIMES:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(ITIMES, NULL)));  
                break;
                case AST_BINARY_OP_ASSIGN: 
                    como_compile(p->u1.binary_node.right, frame);
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(STORE_NAME, newString(
                            p->u1.binary_node.left->u1.id_node.name))));        
                break;
            }   
        } break;
    }
}

static void como_execute(ComoFrame *frame) 
{
    size_t i;
    for(i = 0; i < O_AVAL(frame->code)->size; i++) 
    {
        ComoOpCode *opcode = ((ComoOpCode *)(O_PTVAL(O_AVAL(frame->code)
                ->table[i])));
        
        switch(opcode->op_code) 
        {
            default: 
            {
                como_error_noreturn("Invalid OpCode got %d", opcode->op_code);
            }
            case POSTFIX_INC: 
            {
                Object *value = NULL;
                value = mapSearchEx(frame->cf_symtab, 
                    O_SVAL(opcode->operand)->value);

                if(value == NULL) 
                {
                    como_error_noreturn("undefined variable '%s'", 
                        O_SVAL(opcode->operand)->value);
                } 
                else 
                {
                    if(O_TYPE(value) != IS_LONG) 
                    {
                        como_error_noreturn("unsupported value for POSTFIX_INC");
                    } 
                    else 
                    {
                        long oldvalue = O_LVAL(value);
                        O_LVAL(value) = oldvalue + 1;
                        push(frame, newLong(oldvalue));
                    }   
                }
                break;        
            }
            case POSTFIX_DEC: {
                Object *value = NULL;
                value = mapSearchEx(frame->cf_symtab, 
                    O_SVAL(opcode->operand)->value);

                if(value == NULL) {
                    como_error_noreturn("undefined variable '%s'", 
                        O_SVAL(opcode->operand)->value);
                } else {
                    if(O_TYPE(value) != IS_LONG) {
                        como_error_noreturn("unsupported value for POSTFIX_DEC");
                    } else {
                        long oldvalue = O_LVAL(value);
                        O_LVAL(value) = oldvalue - 1;
                        push(frame, newLong(oldvalue));
                    }   
                }
                break;        
            }
            case IS_LESS_THAN: {
                    Object *right = pop(frame);
                    Object *left = pop(frame);
                    assert(right);
                    assert(left);

                    if(objectValueIsLessThan(left, right)) {
                            push(frame, newLong(1L));
                    } else {
                            push(frame, newLong(0L));
                    }
                    break;
            }
            case IADD: {
                    Object *right = pop(frame);
                    Object *left = pop(frame);
                    assert(right);
                    assert(left);

                    if(O_TYPE(left) == IS_LONG && O_TYPE(right) == IS_LONG) {
                            long value = O_LVAL(left) + O_LVAL(right);
                            push(frame, newLong(value));
                    } else {
                            char *left_str = objectToString(left);
                            char *right_str = objectToString(right);
                            Object *s1 = newString(left_str);
                            Object *s2 = newString(right_str);
                            Object *value = stringCat(s1, s2);
                            push(frame, value);
                            objectDestroy(s1);
                            objectDestroy(s2);
                            free(left_str);
                            free(right_str);	
                    }
                    break;
            }
            case IMINUS: {
                Object *right = pop(frame);
                Object *left = pop(frame);
                assert(right);
                assert(left);
                if(O_TYPE(left) != IS_LONG && O_TYPE(right) != IS_LONG) {
                    como_error_noreturn("unsupported value for IMINUS");
                } else {
                    push(frame, newLong(O_LVAL(left) - O_LVAL(right)));
                }      
                break;
            }
            case IREM: {
                Object *right = pop(frame);
                Object *left = pop(frame);
                assert(right);
                assert(left);
                if(O_TYPE(left) != IS_LONG && O_TYPE(right) != IS_LONG) {
                    como_error_noreturn("unsupported value for IREM");
                } else {
                    push(frame, newLong(O_LVAL(left) % O_LVAL(right)));
                }      
                break;
            }
            case IS_GREATER_THAN_OR_EQUAL: 
            {
                Object *right = pop(frame);
                Object *left = pop(frame);
                if(objectValueIsGreaterThan(left, right)
                        || objectValueCompare(left, right)) 
                {
                    push(frame, newLong(1L));
                }
                else
                {
                    push(frame, newLong(0L));
                }
                break;
            }
            case IS_LESS_THAN_OR_EQUAL: 
            {
                Object *right = pop(frame);
                Object *left = pop(frame);
                assert(right);
                assert(left);

                if(objectValueCompare(left, right)
                        || objectValueIsLessThan(left, right)) 
                {
                    push(frame, newLong(1L));
                } 
                else 
                {
                    push(frame, newLong(0L));
                }
                break;
            }
            case JZ: 
            {
                Object *cond = pop(frame);
                if(O_TYPE(cond) == IS_LONG && O_LVAL(cond) == 0) 
                {
                    i = (size_t)O_LVAL(opcode->operand);      
                    continue;          
                }
                break;
            }
            case JMP: 
            {
                i = (size_t)O_LVAL(opcode->operand);
                continue;
            }
            case LABEL: 
            {
                break;
            }
            case HALT: 
            {
                break;
            }
            case IS_NOT_EQUAL: 
            {
                Object *right = pop(frame);
                Object *left = pop(frame);

                if(!objectValueCompare(left, right)) 
                {
                    push(frame, newLong(1L));
                } 
                else 
                {
                    push(frame, newLong(0L));
                }
                break;
            }
            case LOAD_CONST: 
            {
                push(frame, opcode->operand);
                break;
            }
            case STORE_NAME: 
            {
                Object *value = pop(frame);
                mapInsertEx(frame->cf_symtab, 
                    O_SVAL(opcode->operand)->value, value);
                break;
            }
	    /* This is where recursion was broken, don't do *ex */
            case LOAD_NAME: 
            {
                Object *value = NULL;
                value = mapSearch(frame->cf_symtab, 
                                O_SVAL(opcode->operand)->value);
                if(value) 
                {
                    push(frame, value);
                    break;
                } 
                else 
                {
                    value = mapSearch(global_frame->cf_symtab, 
                                    O_SVAL(opcode->operand)->value);
                }

                if(value == NULL) 
                {
                    como_error_noreturn("undefined variable '%s'", 
                        O_SVAL(opcode->operand)->value);
                }
                
                push(frame, value);
                break;
            }
            case CALL_FUNCTION: {
                Object *fn = pop(frame);
                Object *argcount = pop(frame);
                long i = O_LVAL(argcount);
                ComoFrame *fnframe;
                if(O_TYPE(fn) != IS_POINTER) {
                    como_error_noreturn("name '%s' is not callable",
                        O_SVAL(opcode->operand)->value);
                }
                fnframe = (ComoFrame *)O_PTVAL(fn);
                if(O_LVAL(argcount) != (long)(O_AVAL(fnframe->namedparameters)->size)) {
                    como_error_noreturn("callable '%s' expects %ld arguments, but %ld were given",
                        O_SVAL(opcode->operand)->value, 
                        (long)(O_AVAL(fnframe->namedparameters)->size), 
                        O_LVAL(argcount));
                }

                while(i--) {
                    como_debug("getting %ldth argument for function call '%s'",
                        i, O_SVAL(opcode->operand)->value);
                    Object *argname = O_AVAL(fnframe->namedparameters)->table[i];

                    Object *argvalue = pop(frame);
                    mapInsert(fnframe->cf_symtab, O_SVAL(argname)->value,
                        argvalue);
                }

                como_execute(fnframe);
                
                push(frame, pop(fnframe));

                /* Now, clear the symbol table */
                objectDestroy(fnframe->cf_symtab);
                fnframe->cf_symtab = newMap(2);

                break;
            }
						case IS_EQUAL: {
							Object *right = pop(frame);
							Object *left = pop(frame);
							push(frame, newLong((long)objectValueCompare(left, right)));
							break;
						}
            case ITIMES: {
                Object *right = pop(frame);
                Object *left = pop(frame);
                assert(right);
								assert(left);

								if(O_TYPE(right) != IS_LONG && O_TYPE(left) != IS_LONG) {
                    como_error_noreturn("invalid operands for ITIMES");
                }
								como_debug("ITIMES: %d, %d", O_TYPE(left),
											O_TYPE(right));

                long value = O_LVAL(left) * O_LVAL(right);
                push(frame, newLong(value));
                break;
            }
            case IRETURN: {
                /* If there wasn't a return statement found in func body*
								 * The compiler will insert a 1 as the operand if 
								 * the AST had an expression for the return statement,
								 * otherwise, it will be 0
								 * The actual value to be returned is popped from the stack
								 */
								if(! (O_LVAL(opcode->operand))) {
                    push(frame, newLong(0L));
                }
                return;
            }
            case IPRINT: {
                Object *value = pop(frame);
                size_t len = 0;
                char *sval = objectToStringLength(value, &len);
                fprintf(stdout, "%s\n", sval);
                fflush(stdout);
                free(sval);
                break;          
            }
        }
    }
}

static void como_compile_ast(ast_node *p, const char *filename) {
    Object *main_code = newArray(4);
    global_frame = create_frame(main_code);
    global_frame->filename = newString(filename);
    mapInsertEx(global_frame->cf_symtab, "__FUNCTION__", 
        newString("__main__"));

    (void)como_compile(p, global_frame);
    
    arrayPushEx(main_code, newPointer((void *)create_op(HALT, NULL)));

    (void)como_execute(global_frame);
}

char *get_active_file_name(void) {
    return "-";
		return O_SVAL(global_frame->filename)->value;
}

int como_ast_create(const char *filename)
{
    ast_node* statements;
    yyscan_t scanner;
    YY_BUFFER_STATE state;
    char* text;

    text = como_read_file(filename);

    if(!text) {
        printf("file '%s' not found\n", filename);
        return 1;
    }
    
    if(yylex_init(&scanner)) {
        como_error_noreturn("yylex_init returned NULL");
    }

    state = yy_scan_string(text, scanner);

    if(yyparse(&statements, scanner)) {
        como_error_noreturn("yyparse returned NULL");
    }

    yy_delete_buffer(state, scanner);

    yylex_destroy(scanner);

    como_compile_ast(statements, filename);

    return 0;
}
