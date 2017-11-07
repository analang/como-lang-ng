#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <limits.h>
#include <object.h>

#include "como_opcode.h"

#define OP(i) ((i) >> 24 & 0xff)
#define OP1(i)  ((i) >> 8 & 0xffff)
#define FLAG(i) ((i) & 0xff)

typedef struct Frame {
    Object *name;       /* String        */
    Object *code;       /* Array of Long */
    Object *pc;         /* Long          */
    Object *constants;  /* Array         */
    Object *locals;     /* Map           */
    Object *stack;      /* Array         */
    Object *exception;
    long   sp;         /* Index into stack, UNSAFE */
    struct Frame *parent;
} Frame;

#define CONSTANT_PTR(frame) \
    ((O_AVAL((frame)->constants)->size) - 1)

#define add_obj_constant(frame, object) \
    arrayPushEx((frame)->constants, (object))

#define add_int_constant(frame, ival) \
    add_obj_constant((frame), newLong((long)(ival)))

#define add_string_constant(frame, sval) \
    add_obj_constant((frame), newString((sval)))

#define add_double_constant(frame, dval) \
    add_obj_constant((frame), newDouble((dval)))

#define add_local(frame, key, value) \
    mapInsertEx((frame)->locals, (key), (value))

static Frame *GLOBAL_FRAME;

static void init_frame(char *name, Frame *frame, Frame *parent)
{
    frame->name      = newString(name);
    frame->code      = newArray(8);
    frame->pc        = newLong(0L);
    frame->constants = newArray(8);
    frame->locals    = newMap(8);
    frame->stack     = newArray(8);
    frame->exception = NULL;
    frame->sp        = 0;
    frame->parent    = parent;
}

#define PACK_INSTRUCTION(opcode, argument, flag) \
    ((((uint8_t)(opcode)) << 24) | (((uint16_t)(argument)) << 8) | ((uint8_t)(flag)))

#define emit(frame, opcode, argument, flag) \
    arrayPushEx((frame)->code, newLong( \
        (long)PACK_INSTRUCTION( \
                (opcode), (argument), (flag) \
            ) \
        ) \
    ) \

static Frame *create_add_function()
{
    Frame *frame = malloc(sizeof(*frame));

    init_frame("add", frame, GLOBAL_FRAME);

    emit(frame, IADD,    0, 0);
    emit(frame, IRETURN, 0, 0);

    return frame;
}

#define Object_TypeCheck(obj, type) \
    (O_TYPE((obj)) == (type))

static Object *do_add(Object *ob1, Object *ob2)
{
    if(Object_TypeCheck(ob1, IS_STRING) &&
            Object_TypeCheck(ob2, IS_STRING)) 
    {
        return stringCat(ob1, ob2);
    } 
    else if(Object_TypeCheck(ob1, IS_LONG) &&
            Object_TypeCheck(ob2, IS_LONG))
    {

        return newLong(O_LVAL(ob1) + O_LVAL(ob2));
    }
    else if
        ((Object_TypeCheck(ob1, IS_DOUBLE) || Object_TypeCheck(ob1, IS_LONG))
            && ((Object_TypeCheck(ob2, IS_DOUBLE) || 
                    Object_TypeCheck(ob2, IS_LONG))))
    {
        double left, right;

        if(Object_TypeCheck(ob1, IS_DOUBLE))
        {
            left = O_DVAL(ob1);
        }
        else 
        {      
            left = (double)O_LVAL(ob1);
        }

        if(Object_TypeCheck(ob2, IS_DOUBLE))
        {
            right = O_DVAL(ob2);
        }
        else
        {
            right = (double)O_LVAL(ob2);
        }

        return newDouble(left + right);
    }
    else
    {
        /* TODO Set exception */
        return NULL;
    }
}

static Object *Como_EvalFrameEx(Frame *frame)
{

#define VM_CASE(o) switch(o)

#define VM_TARGET(x) case x:

#define VM_BREAK() break

#define FETCH() \
    ((int)(((((uint32_t)( \
     O_LVAL( \
         O_AVAL((frame)->code) \
                ->table[O_LVAL(frame->pc)++] \
        ) \
    )) >> 24) & 0xff))) \

#define ARG() \
    (((uint32_t)O_LVAL(O_AVAL((frame)->code)->table[((int)O_LVAL(frame->pc))-1])) >> 8 & 0xffff)

#define CONSTANT(indi) \
    O_AVAL(frame->constants)->table[(indi)]

#define PUSH(o) \
    O_AVAL(frame->stack)->table[frame->sp++] = o

#define POP() \
    (O_AVAL(frame->stack)->table[--frame->sp])

#define Set_Exception(frame, message) \
    frame->exception = newString(message)

#define EMPTY() \
    (frame->sp == 0)

    Object *left, *right, *result, *value, *retval = NULL;
    uint32_t arg = -1;

    for(;;)
    {
        fprintf(stderr, "Executing frame %s\n", O_SVAL(frame->name)->value);
        if(frame->parent) {
            fprintf(stderr, "\tI was called from %s\n",
                O_SVAL(frame->parent->name)->value);
        }

        VM_CASE(FETCH()) 
        { 

            VM_TARGET(LOAD_CONST)
            {
                PUSH(CONSTANT(ARG()));

                VM_BREAK();
            }
            VM_TARGET(LOAD_NAME)
            {
                value = CONSTANT(ARG());

                result = mapSearchEx(frame->locals, O_SVAL(value)->value);

                if(result == NULL)
                {
                    Set_Exception(frame, "undefined symbol");
                }
                else
                {
                    PUSH(result);
                }

                VM_BREAK();
            }
            VM_TARGET(CALL_FUNCTION)
            {
                value = POP();
                arg = ARG();
                int i = arg;

                if(!Object_TypeCheck(value, IS_POINTER))
                {
                    Set_Exception(frame, "cannot call a non callable value");
                }
                else
                {
                    Frame *this_function = (Frame *)O_PTVAL(value);
                    Frame *old_frame = frame;

                    /* Setup the function stack
                     * TODO when there are named locals (parameters),
                       make sure to swap them in
                     */
                    while(i--)
                    {
                        /* As you can see this is a hack, as PUSH, POP
                           cannot have the frame specified 
                         */
                        Object *_ = POP();
                        frame = this_function;
                        PUSH(_);
                        frame = old_frame;
                    }

                    result = Como_EvalFrameEx(this_function);

                    PUSH(result);
                    // Recursive call to this current C function
                    // TODO setup stack
                }

                VM_BREAK();
            }
            VM_TARGET(IADD)
            {
                right = POP();
                left  = POP();
                
                result = do_add(left, right);

                if(result == NULL)
                    Set_Exception(frame, "unsupported operand types for +");
                else 
                    PUSH(result);

                VM_BREAK();
            }
            VM_TARGET(IRETURN)
            {
                if(!EMPTY())
                    retval = POP();

                goto done;

                VM_BREAK();
            }
            VM_TARGET(HALT) 
            {
                goto done;
            }
        }

        if(frame->exception != NULL) 
        {
            fprintf(stderr, "Exception: %s\n", O_SVAL(frame->exception)->value);
            goto done;
        }
    }

done:
    return retval;
}

int main(void)
{

    struct Frame frame;

    init_frame("main", &frame, NULL);

    GLOBAL_FRAME = &frame;

    Frame *add_function = create_add_function();
    add_local(&frame, "add", newPointer(add_function));
    
    add_int_constant(&frame, -150);
    emit(&frame, LOAD_CONST, CONSTANT_PTR(&frame), 0);

    add_double_constant(&frame,  50.5);
    emit(&frame, LOAD_CONST, CONSTANT_PTR(&frame), 0);

    add_string_constant(&frame, "add");
    emit(&frame, LOAD_NAME, CONSTANT_PTR(&frame), 0);

    emit(&frame, CALL_FUNCTION, 2, 0);


    emit(&frame, IRETURN, 0, 0);
    emit(&frame, HALT,    0, 0);

    Object *retval = Como_EvalFrameEx(&frame);

    OBJECT_DUMP(retval);

    return 0;
}
