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

    ret->flags = 0;

    if(oper != NULL) {
    	ret->flags |= COMO_OP_CODE_OPERAND_USED; 
    }

    // TODO, line numbers
    
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

static void print_object(Object *obj)
{
    if(Obj_CheckExact(obj, IS_STRING)) {
        fprintf(stdout, "%s\n", O_SVAL(obj)->value);
    } else {
        char *str = objectToString(obj);
        fprintf(stdout, "%s\n", str);
        free(str);
    }
}


static int exception = 0;
static char exmessage[1024];

#define Como_SetError(fmt, ...) do { \
    exception = 1; \
    memset(exmessage, 0, sizeof(exmessage)); \
    sprintf(exmessage, fmt, __VA_ARGS__); \
} while(0)

 

static void Como_EnterFrameDebug(ComoFrame *frame)
{
    fprintf(stderr, " ---\n");
    fprintf(stderr, " --- Frame: %s at <%p>\n", 
           O_SVAL(frame->name)->value, (void *)frame);

    fprintf(stderr, " --- Stack at <%p>\n", (void *)frame->cf_stack);
    fprintf(stderr, " --- Symtab at <%p>\n", (void *)frame->cf_symtab);
    fprintf(stderr, " ---\n");
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

    #define OPR_DECREF(Opcode) do { \
    	(Opcode)->flags |= COMO_OP_CODE_OPERAND_FREE; \
	O_DECREF((Opcode)->operand); \
        (Opcode)->operand = NULL; \
    } while(0)
    
    #define TARGET(Name) \
        case Name:

    #define VM_CONTINUE() \
        goto next_opcode

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

    #define EMPTY() (frame->cf_sp  == 0)

    Object *retval = NULL;

    for(;;)
    {
	ComoOpCode *opcode = NEXT_OPCODE();
       
#ifdef COMO_DEBUG
    fprintf(stderr, "%s\n", instrstr(opcode));
#endif

        switch(opcode->op_code) 
        {
            TARGET(HALT)
            {
                goto exit;
            }

            TARGET(IPRINT)
            {
                Object *value = POP();
                
                print_object(value);

                O_DECREF(value);

                VM_DISPATCH();
            }

            TARGET(LOAD_NAME)
            {
                Object *arg = OP1();
                Object *value =
                    mapSearchEx(frame->cf_symtab, O_SVAL(arg)->value);

                if(value == NULL)
                {
                    Como_SetError(
                        "Undefined symbol, %s", O_SVAL(arg)->value
                    );
                } 
                else 
                {
                    PUSH(value);
                }

                OPR_DECREF(opcode);

                VM_DISPATCH();
            }

            TARGET(LOAD_CONST)
            {
                Object *arg   = OP1();
                PUSH(arg);

                O_INCRREF(arg);

                VM_DISPATCH();
            }

            /* STORE_NAME "foo" */
            TARGET(STORE_NAME) 
            {
                Object *value = POP();
                Object *name  = OP1();

                mapInsertEx(frame->cf_symtab, O_SVAL(name)->value, value);

                O_INCRREF(value);

                OPR_DECREF(opcode);

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


                O_DECREF(left);
                O_DECREF(right);
                
                VM_DISPATCH();              
            }
        }

        if(exception) {
            como_error_noreturn(frame, exmessage);
        }
    }

exit:
    /* Pop remaining stack entries */
    while(!EMPTY()) {
        Object *obj = POP();
        object_print_stats(obj);
        O_DECREF(obj);
    }

        return retval;
}


static void destroy_frame(ComoFrame *frame)
{
    uint32_t i;

    objectDestroy(frame->lineno);
    objectDestroy(frame->filename);
    
    for(i = 0; i < mapCapacity(frame->cf_symtab); i++) {
        Bucket *b = mapGetBucket(frame->cf_symtab, i);

        while(b != NULL) {
            Bucket *bn = b->next;
            String *key = b->key;
            free(key->value);
            free(key);
            free(b);
            b = bn;
        }
    }

    free(O_MVAL(frame->cf_symtab)->buckets);
    free(O_MVAL(frame->cf_symtab));
    free(frame->cf_symtab);
    
    objectDestroy(frame->namedparameters);
    objectDestroy(frame->name);
    
    for(i = 0; i < O_AVAL(frame->code)->size; i++)
    {
	ComoOpCode *op = (ComoOpCode *)O_PTVAL((O_AVAL(frame->code))->table[i]);

	if((op->flags & COMO_OP_CODE_OPERAND_USED) &&
	   !(op->flags & COMO_OP_CODE_OPERAND_FREE)) 
	{
		objectDestroy(op->operand);
	}

	free(op);
    }
   
    objectDestroy(frame->code);

    fprintf(stdout, " --- Stack Pointer:   %d\n", (int)frame->cf_sp);
    fprintf(stdout, " --- Program Counter: %d\n", (int)frame->pc);
    
    free(frame);    
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

    destroy_frame(global_frame);
}


void como_compile_ast(ast_node *p, const char *filename) {
    _como_compile_ast(p, filename, 0);
}


char *get_active_file_name(void) {
    return "-";
}
