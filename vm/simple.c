#include <signal.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <limits.h>

#include "como_opcode.h"

/* Opcode 1 byte opcode, 2 byte argument, 1 byte flag 
 *
 *
 *
 *
 * 0x010000FE
 * OPCODE ARGUMENT FLAG
 * 01     0000     FE
 *
 * */

#define OP(i) ((i) >> 24 & 0xff)
#define OP1(i)  ((i) >> 8 & 0xffff)
#define FLAG(i) ((i) & 0xff)

typedef struct Frame {
    long f_co[USHRT_MAX + 1]; /* Constants */
    long f_co_pos;               /* constants pointer */
    
    int code[255];            /* Bytecode */
    int pc;                   /* Program counter */
    


    long stack[255];          /* Value stack */
    long sp;                  /* Stack pointer */
} Frame;

static void init_frame(Frame *frame)
{
    memset(frame->f_co, 0, sizeof(frame->f_co));
    frame->f_co_pos = 0;
    memset(frame->code, 0, sizeof(frame->code));
    frame->pc = 0;
    memset(frame->stack, 0, sizeof(frame->stack));
    frame->sp = 0;
}

#define TRACE(op) do { \
    printf("%#010X\n", op); \
} while(0)


static int Como_EvalFrameEx(Frame *frame)
{
    #define NEXT_OPCODE() ((frame->code[frame->pc++]) >> 24 & 0xff)
    #define ARG() ((frame->code[frame->pc - 1]) >> 8 & 0xffff)
    #define TARGET(x) case x: 
    #define VM_DISPATCH() break
    #define PUSH(x) frame->stack[frame->sp++] = x
    #define POP() frame->stack[--frame->sp]
    #define CONSTANT(x) frame->f_co[x]
    #define EMPTY() frame->sp == 0

    int retval = 0;
    int arg = -1;
    int a, b, op;

    for(;;)
    {
        op = NEXT_OPCODE();

        TRACE(frame->code[frame->pc - 1]);

        fprintf(stderr, "pc=%d\n", frame->pc);

        switch(op)
        {
            TARGET(LOAD_CONST) 
            {   
                arg = ARG();

                PUSH(CONSTANT(arg));

                VM_DISPATCH();
            }

            TARGET(IADD)
            {
                a = POP();
                b = POP();

                PUSH(a + b);

                VM_DISPATCH();
            }

            TARGET(IRETURN)
            {

                if(!EMPTY()) {
                    retval = POP();
                }

                VM_DISPATCH();
            }

            TARGET(HALT)
            {
                goto exit;
            }
        }
    }

exit:
    return retval;
}

int main(void)
{

    struct Frame frame;

    init_frame(&frame);

    frame.f_co[frame.f_co_pos++] = 150;
    frame.code[frame.pc++] = (LOAD_CONST << 24) | ((frame.f_co_pos -1) << 8) | (UCHAR_MAX - 1);
    frame.f_co[frame.f_co_pos++] = 50;
    frame.code[frame.pc++] = (LOAD_CONST << 24) | ((frame.f_co_pos -1) << 8) | (UCHAR_MAX - 1);

    frame.code[frame.pc++] = (IADD << 24) | ((0) << 8) | (0);
    frame.code[frame.pc++] = (IRETURN << 24) | ((0) << 8) | (0);
    frame.code[frame.pc++] = (HALT << 24) | ((0) << 8) | (0);

    /* reset the program counter, execute */
    frame.pc = 0;
    int retval = Como_EvalFrameEx(&frame);

    fprintf(stdout, "%d\n", retval);


#if 0
    uint32_t instruction;
  
                  /* LOAD_NAME ARG FLAG */
    instruction = (LOAD_NAME << 24) | (USHRT_MAX << 8) | (UCHAR_MAX - 1);

    fprintf(stdout,
        "op=%d, arg=%u, flag=%u\n", 
        OP(instruction), 
        OP1(instruction),
        FLAG(instruction)
    );

#endif

    return 0;
}
