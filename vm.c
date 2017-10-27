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

static ComoOpCode *create_op(unsigned char op, Object *oper) 
{
    ComoOpCode *ret = malloc(sizeof(ComoOpCode));
    ret->op_code = op;
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

/* VM main loop */
Object *Como_EvalFrame(ComoFrame *frame)
{       
    #define O_INCRREF(O) \
        O_REFCNT((O))++

    #define O_DECREF(O) do { \
        if(--O_REFCNT((O)) == 0) { \
            objectDestroy((O)); \
        } \
    } while(0) 
    
    #define TARGET(Name) \
        case Name:

    #define VM_CONTINUE() \
        continue

    #define VM_DISPATCH() \
        break

    #define NEXT_OPCODE() \
        (ComoOpCode *)O_PTVAL(O_AVAL((frame)->code)->table[(frame)->pc++]);

    #define POP() \
        frame->cf_stack[--frame->cf_sp]

    #define PUSH(Obj) \
        frame->cf_stack[frame->cf_sp++] = Obj

    #define OP1() \
        opcode->operand

    Object *retval = NULL;

    for(;;)
    {
        ComoOpCode *opcode = NEXT_OPCODE();
        
        switch(opcode->op_code) 
        {
            default: 
            {
                fprintf(stderr, "Invalid OpCode: %d opcode->op_code\n");
                exit(1);
            }

            TARGET(HALT)
            {
                return retval;
            }

            TARGET(LOAD_CONST)
            {
                Object *arg   = OP1();
                PUSH(arg);
                O_INCRREF(arg);

                VM_DISPATCH();
            }

            TARGET(STORE_NAME) 
            {
                Object *value = POP();
                Object *name  = OP1();

                mapInsert(frame->cf_symtab, O_SVAL(name)->value, value);

                O_INCRREF(value);

                O_DECREF(name);

                VM_DISPATCH();
            }
            TARGET(IADD)
            {
                Object *right = POP();
                Object *left  = POP();

                if(Obj_CheckExact(right, IS_LONG) && 
                    Obj_CheckExact(left, IS_LONG))
                {
                    long result = O_LVAL(left) + O_LVAL(right);

                    O_DECREF(left);
                    O_DECREF(right);

                    PUSH(newLong(result));
                } 
                else
                {
                    /* Temp char buffers */
                    char *_s1 = objectToString(left);
                    char *_s2 = objectToString(right);

                    Object *s1 = newString(_s1);
                    Object *s2 = newString(_s2);

                    Object *result = stringCat(s1, s2);

                    free(_s1);
                    free(_s2);

                    O_DECREF(s1);
                    O_DECREF(s2);

                    PUSH(result);
                }

                VM_DISPATCH();              
            }
        }
    }

    return retval;
}


static void _como_compile_ast(ast_node *p, const char *filename, int dump_asm) {
    Object *main_code = newArray(4);
    
    global_frame = create_frame(main_code, "__main__");
    global_frame->lineno = newLong(0L);
    global_frame->filename = newString(filename);

    como_compile(p, global_frame);
    
    arrayPushEx(main_code, newPointer((void *)create_op(HALT, NULL)));

    if(!dump_asm)
        (void)Como_EvalFrame(global_frame);

}


void como_compile_ast(ast_node *p, const char *filename) {
    _como_compile_ast(p, filename, 0);
}


char *get_active_file_name(void) {
    return "-";
}