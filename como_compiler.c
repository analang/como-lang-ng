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

#define COMO_COMPILER 1

#include "como_ast.h"
#include "como_stack.h"
#include "como_debug.h"
#include "como_opcode.h"
#include "como_globals.h"
#include "como_parser.h"
#include "como_lexer.h"
#include "como_compiler.h"
#include "como_io.h"
#include "como_object.h"


static ComoFrame *global_frame = NULL;

static void call_stack_push(como_stack **stack, Object *name, Object *lineno) 
{
    Object *call_site_tuple = newArray(2);
    arrayPushEx(call_site_tuple, name);
    arrayPushEx(call_site_tuple, lineno);

    como_stack_push(stack, call_site_tuple);
}


void como_print_stack_trace(ComoFrame *frame) 
{
    como_printf("stack trace for frame: \":S\" (last called, first)\n", frame->name);
    
    while(frame != NULL) {
        como_printf("  at :S (:S::L)\n", frame->name, frame->filename, frame->lineno);
        frame = frame->next;
    }
}

static void _como_asm_dump(FILE *fp, ComoFrame *frame);

static void 
como_op_code_array_push(ComoFrame *frame, unsigned char op_code, Object *arg1) {
    ComoOpCode *op = malloc( sizeof( ComoOpCode ) );

    op->op_code = op_code;
    op->operand = arg1;

    arrayPushEx( frame->code, newPointer( (void *) op) );
}

#define como_op_code_get(frame, index) \
    (ComoOpCode *)O_PTVAL(O_AVAL((frame)->code)->table[(index)]);


static void push(ComoFrame *frame, Object *value)
{
    if(frame->cf_sp >= COMO_DEFAULT_FRAME_STACKSIZE) 
    {
        como_error_noreturn(frame, "error stack overflow tried to push onto #%zu", 
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
        como_error_noreturn(frame, "stack underflow, tried to go before 0");
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
    ret->flags = 0;

    if(oper != NULL) {
    	ret->flags |= COMO_OP_CODE_OPERAND_USED; 
    }

    ret->operand = oper;
    return ret;
}

static ComoFrame *create_frame(Object *code, const char *name) 
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
    frame->pc = 0;
    frame->next = NULL;
    frame->namedparameters = newArray(2);
    frame->filename = NULL;
    frame->call_stack = NULL;
    frame->name = newString(name);
    frame->caller = NULL;
    return frame;
}

static Object *como_proxy_not_null_check(Object *maybe)
{
    if(maybe == NULL) 
    {
        como_error_noreturn(NULL, "allocation of Object failed, exiting");
    }

    return maybe;
}

#define COMO_TRACE1(x) fprintf(stderr, "%s\n", #x)
#define COMO_TRACEVAR(x, fmt, ...) do { \
        fprintf(stderr, "%s ", #x); \
        fprintf(stderr, fmt, ##__VA_ARGS__); \
        fprintf(stderr, "\n"); \
        fflush(stderr); \
} while(0)

static void _como_asm_dump(FILE *fp, ComoFrame *frame) 
{
    (void)fp;

    uint32_t x;
    for(x = 0; x < O_MVAL(frame->cf_symtab)->capacity; x++) {
        Bucket *bucket = O_MVAL(frame->cf_symtab)->buckets[x];
        while(bucket != NULL) {
            Object *value = bucket->value;
            if(O_TYPE(value) == IS_POINTER) {
                ComoFrame *fm = (ComoFrame *)O_PTVAL(value);
                fprintf(stdout, "function %s() {\n", bucket->key->value);
                _como_asm_dump(stdout, fm);
                fprintf(stdout, "}\n");
            }
            bucket = bucket->next;
        }
    }

    size_t i;
    for(i = 0; i < O_AVAL(frame->code)->size; i++) 
    {
        fprintf(stderr, "%zu\t", i);

        ComoOpCode *opcode = como_op_code_get(frame, i);
                
        switch(opcode->op_code) 
        {
            default: 
            {
                como_error_noreturn(NULL, "Invalid OpCode got %d", opcode->op_code);
            }
            case GET_FIELD:
            {
                COMO_TRACE1(GET_FIELD);
                break;
            }
            case CREATE_ARRAY:
            {
                COMO_TRACE1(CREATE_ARRAY);
                break;
            }
            case IAND:
            {
                COMO_TRACE1(IAND);
                break;
            }
            case IASSERT:
            {
                COMO_TRACE1(IASSERT);
                break;
            }
            case UNARY_NOT:
            {
                COMO_TRACE1(UNARY_NOT);
                break;
            }
            case ITYPEOF:
            {
                COMO_TRACE1(ITYPEOF);
                break;
            }
            case POSTFIX_INC: 
            {
                COMO_TRACEVAR(POSTFIX_INC, "%s", O_SVAL(opcode->operand)->value);
                break;        
            }
            case POSTFIX_DEC: {
                COMO_TRACEVAR(POSTFIX_DEC, "%s", O_SVAL(opcode->operand)->value);
                break;        
            }
            case IS_LESS_THAN: {
                COMO_TRACE1(IS_LESS_THAN);
                break;
            }
            case IADD: {
                COMO_TRACE1(IADD);
                break;
            }
            case IMINUS: {
                COMO_TRACE1(IMINUS);     
                break;
            }
            case IREM: {
                COMO_TRACE1(IREM);      
                break;
            }
            case IS_GREATER_THAN_OR_EQUAL: 
            {
                COMO_TRACE1(IS_GREATER_THAN_OR_EQUAL);
                break;
            }
            case IS_LESS_THAN_OR_EQUAL: 
            {
                COMO_TRACE1(IS_LESS_THAN_OR_EQUAL);
                break;
            }
            case JZ: 
            {
                COMO_TRACEVAR(JZ, "%ld", O_LVAL(opcode->operand));
                break;
            }
            case JMP: 
            {
                COMO_TRACEVAR(JMP, "%ld", O_LVAL(opcode->operand));
                break;
            }
            case LABEL: 
            {
                COMO_TRACE1(LABEL);
                break;
            }
            case HALT: 
            {
                COMO_TRACE1(HALT);
                break;
            }
            case IS_NOT_EQUAL: 
            {
                COMO_TRACE1(IS_NOT_EQUAL);
                break;
            }
            case LOAD_CONST: 
            {
                char *sval = objectToString(opcode->operand);
                COMO_TRACEVAR(LOAD_CONST, "%s", sval);
                free(sval);
                break;
            }
            case STORE_NAME: 
            {
                COMO_TRACEVAR(STORE_NAME, "%s", O_SVAL(opcode->operand)->value);
                break;
            }
        /* This is where recursion was broken, don't do *ex */
            case LOAD_NAME: 
            {
                COMO_TRACEVAR(LOAD_NAME, "%s", O_SVAL(opcode->operand)->value);
                break;
            }
            case CALL_FUNCTION: {
                COMO_TRACE1(CALL_FUNCTION);
                break;
            }
            case IS_EQUAL: {
                COMO_TRACE1(IS_EQUAL);
                break;
            }
            case ITIMES: {
                COMO_TRACE1(ITIMES);
                break;
            }
            case IRETURN: {
                COMO_TRACEVAR(IRETURN, "%ld", O_LVAL(opcode->operand));
                break;
            }
            case IPRINT: {
                COMO_TRACE1(IPRINT);
                break;          
            }
        }
    }
}

void como_compile(ast_node* p, ComoFrame *frame)
{
    #define COMO_CHECKED(result) \
        como_proxy_not_null_check((result))

    assert(p);

    switch(p->type) 
    {
        default:
            como_error_noreturn(NULL, "Invalid node type(%d)", p->type);
        break;
        case AST_NODE_TYPE_SLOT_ACCESS:
            como_compile(p->u1.slot_access_node.value, frame);
            como_compile(p->u1.slot_access_node.index, frame);
            como_op_code_array_push(frame, GET_FIELD,  NULL);
        break;
        case AST_NODE_TYPE_ARRAY:
        {
            ssize_t element_count = p->u1.array_node.elements->u1.statements_node.count;
            while(element_count--) {
                como_compile(p->u1.array_node.elements->u1.statements_node.statement_list[(size_t)element_count], frame);
            }
            /* Last value on stack has the array length */
            como_op_code_array_push(frame, LOAD_CONST, 
                newLong((long)(p->u1.array_node.elements->u1.statements_node.count)));
            como_op_code_array_push(frame, CREATE_ARRAY, NULL);
            break;
        }
        case AST_NODE_TYPE_ASSERT:
            como_compile(p->u1.assert_node.expr, frame);

            como_op_code_array_push(frame, LOAD_CONST, 
                COMO_CHECKED(newLong((long)p->u1.assert_node.lineno)));

            como_op_code_array_push(frame, IASSERT, NULL);

        break;
        case AST_NODE_TYPE_TYPEOF:
            como_compile(p->u1.typeof_node.expr, frame);
            arrayPushEx(frame->code, newPointer((void *)create_op(ITYPEOF, NULL)));
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
            ComoFrame *func_decl_frame = create_frame(func_decl, name);
            func_decl_frame->lineno = newLong(0L);
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
            mapInsert(frame->cf_symtab, name, newPointer(
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

            int lineno = p->u1.call_node.lineno;
            int colno = p->u1.call_node.colno;

            como_compile(p->u1.call_node.arguments, frame);

            arrayPushEx(frame->code, newPointer(
                    (void *)create_op(LOAD_CONST, newLong(argcount)))); 

            arrayPushEx(frame->code, newPointer(
                    (void *)create_op(LOAD_NAME, newString(name))));

            arrayPushEx(frame->code, newPointer(
                    (void *)create_op(LOAD_CONST, newLong((long)lineno))));

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
                case AST_UNARY_NOT:
                    como_compile(p->u1.unary_node.expr, frame);
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(UNARY_NOT, NULL)));
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
                case AST_BINARY_OP_AND:
                    arrayPushEx(frame->code, newPointer(
                        (void *)create_op(IAND, NULL)));
                break;
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

static Object *builtin_len(Object *args) 
{   

    Object *value = O_AVAL(args)->table[ 0 ];

    if(O_TYPE(value) == IS_ARRAY)
        return newLong((long)O_AVAL(value)->size);
    else if(O_TYPE(value) == IS_STRING)
        return newLong((long)O_SVAL(value)->length);
    else
        return newLong(0L);
}

static Object *builtin_write(Object *args) 
{
    Object *arg = O_AVAL(args)->table[ 0 ];

    if(O_TYPE(arg) == IS_STRING) {
        int n = fputs(O_SVAL(arg)->value, stdout);
        return newLong((long)n);
    }
    char *sval = objectToString(arg);

    int n = fprintf(stdout, "%s", sval);

    fflush(stdout);

    free(sval);

    return newLong((long)n);
}


static void como_execute(ComoFrame *frame, ComoFrame *callingframe) 
{
    size_t i;
    for(i = 0; i < O_AVAL(frame->code)->size; i++) 
    {
        ComoOpCode *opcode = como_op_code_get(frame, i);
                
        switch(opcode->op_code) 
        {
            default: 
            {
                como_error_noreturn(NULL, "Invalid OpCode got %d", opcode->op_code);
            }
            case UNARY_MINUS:
            {
                Object *value = pop(frame);

                if(O_TYPE(value) != IS_LONG) {
                    como_error_noreturn(frame, "UNARY_MINUS can only be used on ints");
                }

                push(frame, newLong(-O_LVAL(value)));

                break;
            }
            case GET_FIELD:
            {
                
                Object *index = pop(frame);
                Object *value = pop(frame);

                if(O_TYPE(value) != IS_STRING && O_TYPE(value) != IS_ARRAY) {
                    como_error_noreturn(frame, "Can't get dimension value of non object\n");
                } 

                if(O_TYPE(index) == IS_LONG) {
                    long lindex = O_LVAL(index);

                    if(O_TYPE(value) == IS_ARRAY) {
                        if(lindex >= 0 && lindex < (long)O_AVAL(value)->size) {
                            push(frame, O_AVAL(value)->table[lindex]);
                        } else {
                            push(frame, newNull());
                        }
                    } else {
                        if(lindex >= 0 && lindex < (long)O_SVAL(value)->length) {
                            char c[2];
                            c[0] = O_SVAL(value)->value[lindex];
                            c[1] = '\0';
                            push(frame, newString(c));
                        } else {
                            push(frame, newNull());
                        } 
                    }
                } else {
                    como_error_noreturn(frame, 
                        "Only ints are acceptable as slot access values");
                }
                break;
            }
            case CREATE_ARRAY:
            {
                Object *olength = pop(frame);
                size_t length = (size_t)O_LVAL(olength);
                Object *array = newArray(length == 0 ? 2 : length);
                size_t i;
                for(i = 0; i < length; i++) {
                    Object *temp = pop(frame);
                    arrayPush(array, temp);
                }
                push(frame, array);
                break;
            }
            case IAND:
            {
                Object *obj1 = pop(frame);
                Object *obj2 = pop(frame);

                if(como_object_is_truthy(obj1) && como_object_is_truthy(obj2)) 
                {
                    push(frame, newLong(1L));
                }
                else
                {
                    push(frame, newLong(0L));
                }  

                break;
            }
            case IASSERT:
            {

                Object *lineno = pop(frame);
                Object *obj = pop(frame);
                
                if(!como_object_is_truthy(obj)) {
                    como_error_noreturn(frame, "como: assertion failed on line %d\n", O_LVAL(lineno));
                }

                break;
            }
            case UNARY_NOT:
            {

                Object *obj = pop(frame);

                if(como_object_is_truthy(obj)) 
                {
                    push(frame, newLong(0L));
                }
                else
                {
                    push(frame, newLong(1L));
                }

                break;
            }
            case ITYPEOF:
            {

                Object *obj = pop(frame);
            
                /* Hack */
                if(O_TYPE(obj) == IS_POINTER) 
                {
                    push(frame, newString("function"));
                } 
                else if(O_TYPE(obj) == IS_NULL) 
                {
                    push(frame, newString("undefined"));
                }
                else 
                {
                    char *str = objectTypeStr(obj);
                    push(frame, newString(str));
                    free(str);
                }

                break;
            }
            case POSTFIX_INC: 
            {

                Object *value = NULL;
                value = mapSearchEx(frame->cf_symtab, 
                    O_SVAL(opcode->operand)->value);

                if(value == NULL) 
                {
                    como_error_noreturn(frame, "undefined variable '%s'", 
                        O_SVAL(opcode->operand)->value);
                } 
                else 
                {
                    if(O_TYPE(value) != IS_LONG) 
                    {
                        como_error_noreturn(frame, "unsupported value for POSTFIX_INC");
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
                    como_error_noreturn(frame, "undefined variable '%s'", 
                        O_SVAL(opcode->operand)->value);
                } else {
                    if(O_TYPE(value) != IS_LONG) {
                        como_error_noreturn(frame, "unsupported value for POSTFIX_DEC");
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
                if(! (O_TYPE(left) == IS_LONG && O_TYPE(right) == IS_LONG)) {
                    como_error_noreturn(frame, "unsupported value for IMINUS");
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
                    como_error_noreturn(frame, "unsupported value for IREM");
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
                mapInsert(frame->cf_symtab, 
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
                    /* Hack */
                    /* LOAD_NAME "identifier"
                       TYPEOF 
                     */
                    ComoOpCode *next_opcode = ((ComoOpCode *)(O_PTVAL(O_AVAL(frame->code)->table[i + 1])));

                    if(next_opcode->op_code == ITYPEOF) {
                        push(frame, newNull());
                    } else {
                        como_error_noreturn(frame, 
                            "LOAD_NAME: undefined variable '%s'", O_SVAL(opcode->operand)->value);
                    }
                } 
                else 
                {
                    push(frame, value);
                }

                break;
            }
            case CALL_FUNCTION: {
                Object *lineno = pop(frame);
                Object *fn = pop(frame);
                Object *argcount = pop(frame);
                long i = O_LVAL(argcount);
                ComoFrame *fnframe;

                if(O_TYPE(fn) != IS_POINTER && O_TYPE(fn) != IS_FUNCTION) {
                    como_error_noreturn(frame, "name '%s' is not callable",
                        O_SVAL(opcode->operand)->value);
                }


                if(O_TYPE(fn) == IS_FUNCTION) {
                    frame->next = callingframe;

                    Object *args = newArray((size_t)i);
                    ComoBuiltinFunction *builtin = (ComoBuiltinFunction *)O_FVAL(fn);
                    while(i--) {
                        Object *argvalue = pop(frame);
                        arrayPush(args, argvalue);
                    }
                    Object *retval = builtin->handler(args);
                    push(frame, retval);
                } else {
                    fnframe = (ComoFrame *)O_PTVAL(fn);
                    

                    /*
                    if(callingframe) {                    
                        fprintf(stderr, "INFO: %s called me : I'm %s\n", O_SVAL(callingframe->name)->value,
                            O_SVAL(frame->name)->value);
                    
                        callingframe->next = fnframe;
                        frame->next = callingframe;
                    }
                    */

                    frame->next = callingframe;                    
                    fnframe->next = frame;
                    fnframe->lineno = lineno;
                    
                    /* 1/2
                     * 
                     * What is happening here?
                     *
                     * If this is a recursive call, we need to save the state of the current symbol table so we don't
                     * lose it upon a call to itself
                     */
                    Object *old_sym_tab = copyObject(fnframe->cf_symtab);

                    if(O_LVAL(argcount) != (long)(O_AVAL(fnframe->namedparameters)->size)) {
                        como_error_noreturn(fnframe, "callable '%s' expects %ld arguments, but %ld were given",
                            O_SVAL(opcode->operand)->value, (long)(O_AVAL(fnframe->namedparameters)->size), 
                            O_LVAL(argcount));
                    }

                    while(i--) {
                        Object *argname = O_AVAL(fnframe->namedparameters)->table[i];

                        Object *argvalue = pop(frame);
                        mapInsert(fnframe->cf_symtab, O_SVAL(argname)->value,
                            argvalue);
                    }

                    como_execute(fnframe, frame);

                    push(frame, pop(fnframe));    

                    /* 2/2
                     *
                     * Restore the previous value of the function frames symbol table
                     */
                    fnframe->cf_symtab = old_sym_tab;
                }
                break;
            }
            case IS_EQUAL: {
                Object *right = pop(frame);
                Object *left = pop(frame);
                Object *value = newLong((long)objectValueCompare(left, right));
                push(frame, value);
                break;
            }
            case ITIMES: {
                Object *right = pop(frame);
                Object *left = pop(frame);

                if(O_TYPE(right) != IS_LONG && O_TYPE(left) != IS_LONG) {
                    como_error_noreturn(frame, "invalid operands for ITIMES");
                }

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
                if(O_TYPE(value) == IS_ARRAY) {
                    (void )fputc((int)'[', stdout);
                    Object *item;
                    size_t len;
                    char *sval;
                    size_t i = 0;
                    COMO_ARRAY_FOREACH(value, item) {
                        len = 0;
                        sval = objectToStringLength(item, &len);
                        (void )fputs((const char *)sval, stdout);
                        if(i + 1 != O_AVAL(value)->size) {
                            (void )fputs(", ", stdout);
                        }
                        free(sval);
                        i++;
                    } COMO_ARRAY_FOREACH_END();
                    (void )fputc((int)']', stdout);
                    (void )fputc((int)'\n', stdout);
                    fflush(stdout);
                } else {
                    size_t len = 0;
                    char *sval = objectToStringLength(value, &len);
                    fprintf(stdout, "%s\n", sval);
                    fflush(stdout);
                    free(sval);
                }
                break;          
            }
        }
    }
}


static void _como_compile_ast(ast_node *p, const char *filename, int dump_asm) {
    Object *main_code = newArray(4);
    global_frame = create_frame(main_code, "__main__");
    global_frame->lineno = newLong(0L);
    global_frame->filename = newString(filename);
    mapInsertEx(global_frame->cf_symtab, "__FUNCTION__", 
        newString("__main__"));

    ComoBuiltinFunction len_function;
    len_function.handler = builtin_len;

    ComoBuiltinFunction write_function;
    write_function.handler = builtin_write;

    mapInsertEx(global_frame->cf_symtab, "len", newFunction((void *)&len_function));
    mapInsertEx(global_frame->cf_symtab, "write", newFunction((void *)&write_function));


    call_stack_push(&global_frame->call_stack, newString("__main__"), newLong(0L));
    
    (void)como_compile(p, global_frame);
    
    arrayPushEx(main_code, newPointer((void *)create_op(HALT, NULL)));

    if(!dump_asm)
        (void)como_execute(global_frame, NULL);
    else
        _como_asm_dump(stdout, global_frame);
}

void como_dump_asm(ast_node *p, const char *filename) {
    _como_compile_ast(p, filename, 1);
}

