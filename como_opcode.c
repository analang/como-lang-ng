#include <string.h>
#include <stdlib.h>

#include "como_opcode.h"
#include "como_debug.h"
#include "como_compiler.h"

const char * const str_opcodelist[] = {
    "INONE", "LOAD_CONST", "STORE_NAME", "LOAD_NAME", "IS_LESS_THAN",
    "JZ", "IPRINT", "IADD", "JMP", "IRETURN", "NOP", "LABEL", "HALT"
};

static char opcodebuffer[1024];

const char *instrstr(ComoOpCode *op)
{       
    memset(opcodebuffer, 0, sizeof(opcodebuffer));

    const char *opcode = str_opcodelist[op->op_code];

    memcpy(opcodebuffer, opcode, strlen(opcode));
    memcpy(opcodebuffer + strlen(opcode), " ", 1);

    if(op->operand != NULL)
    {
        char *operand = objectToString(op->operand);

        memcpy(opcodebuffer + strlen(opcode) + 1, operand, 
                strlen(operand) + 1);

        free(operand);
    }

    return opcodebuffer;
}

