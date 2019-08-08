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

#include "como_executor.h"

static void como_opcode_default_handler(Object *, Object *, Object **);

#define COMO_OPCODE_HANDLER_INONE        como_opcode_default_handler
#define COMO_OPCODE_HANDLER_LOAD_CONST   como_opcode_default_handler
#define COMO_OPCODE_HANDLER_STORE_NAME   como_opcode_default_handler
#define COMO_OPCODE_HANDLER_LOAD_NAME    como_opcode_default_handler
#define COMO_OPCODE_HANDLER_IS_LESS_THAN como_opcode_default_handler
#define COMO_OPCODE_HANDLER_JZ           como_opcode_default_handler
#define COMO_OPCODE_HANDLER_IPRINT       como_opcode_default_handler
#define COMO_OPCODE_HANDLER_IADD         como_opcode_default_handler
#define COMO_OPCODE_HANDLER_JMP          como_opcode_default_handler
#define COMO_OPCODE_HANDLER_IRETURN      como_opcode_default_handler
#define COMO_OPCODE_HANDLER_NOP          como_opcode_default_handler
#define COMO_OPCODE_HANDLER_LABEL        como_opcode_default_handler
#define COMO_OPCODE_HANDLER_HALT         como_opcode_default_handler
#define COMO_OPCODE_HANDLER_IS_EQUAL     como_opcode_default_handler
#define COMO_OPCODE_HANDLER_IDIV         como_opcode_default_handler
#define COMO_OPCODE_HANDLER_ITIMES       como_opcode_default_handler
#define COMO_OPCODE_HANDLER_IS_GREATER_THAN \
    como_opcode_default_handler
#define COMO_OPCODE_HANDLER_IS_NOT_EQUAL como_opcode_default_handler
#define COMO_OPCODE_HANDLER_IS_GREATER_THAN_OR_EQUAL \
    como_opcode_default_handler
#define COMO_OPCODE_HANDLER_IS_LESS_THAN_OR_EQUAL \
    como_opcode_default_handler
#define COMO_OPCODE_HANDLER_DEFINE_FUNCTION \
    como_opcode_default_handler
#define COMO_OPCODE_HANDLER_CALL_FUNCTION como_opcode_default_handler
#define COMO_OPCODE_HANDLER_POSTFIX_INC   como_opcode_default_handler
#define COMO_OPCODE_HANDLER_UNARY_MINUS   como_opcode_default_handler
#define COMO_OPCODE_HANDLER_IREM          como_opcode_default_handler
#define COMO_OPCODE_HANDLER_POSTFIX_DEC   como_opcode_default_handler

const como_opcode_handler como_opcode_handler_table[COMO_OPCODE_MAX] = {
    [INONE]                    = COMO_OPCODE_HANDLER_INONE,
    [LOAD_CONST]               = COMO_OPCODE_HANDLER_LOAD_CONST,
    [STORE_NAME]               = COMO_OPCODE_HANDLER_STORE_NAME,
    [LOAD_NAME]                = COMO_OPCODE_HANDLER_LOAD_NAME,
    [IS_LESS_THAN]             = COMO_OPCODE_HANDLER_IS_LESS_THAN,
    [JZ]                       = COMO_OPCODE_HANDLER_JZ,
    [IPRINT]                   = COMO_OPCODE_HANDLER_IPRINT,
    [IADD]                     = COMO_OPCODE_HANDLER_IADD,
    [JMP]                      = COMO_OPCODE_HANDLER_JMP,
    [IRETURN]                  = COMO_OPCODE_HANDLER_IRETURN,
    [NOP]                      = COMO_OPCODE_HANDLER_NOP,
    [LABEL]                    = COMO_OPCODE_HANDLER_LABEL,
    [HALT]                     = COMO_OPCODE_HANDLER_HALT,
    [IS_EQUAL]                 = COMO_OPCODE_HANDLER_IS_EQUAL,
    [IDIV]                     = COMO_OPCODE_HANDLER_IDIV,
    [ITIMES]                   = COMO_OPCODE_HANDLER_ITIMES,
    [IS_GREATER_THAN]          = COMO_OPCODE_HANDLER_IS_GREATER_THAN,
    [IS_NOT_EQUAL]             = COMO_OPCODE_HANDLER_IS_NOT_EQUAL,
    [IS_GREATER_THAN_OR_EQUAL] = 
        COMO_OPCODE_HANDLER_IS_GREATER_THAN_OR_EQUAL,
    [IS_LESS_THAN_OR_EQUAL]    = 
        COMO_OPCODE_HANDLER_IS_LESS_THAN_OR_EQUAL,
    [DEFINE_FUNCTION]          = COMO_OPCODE_HANDLER_DEFINE_FUNCTION,
    [CALL_FUNCTION]            = COMO_OPCODE_HANDLER_CALL_FUNCTION,
    [POSTFIX_INC]              = COMO_OPCODE_HANDLER_POSTFIX_INC,
    [UNARY_MINUS]              = COMO_OPCODE_HANDLER_UNARY_MINUS,
    [IREM]                     = COMO_OPCODE_HANDLER_IREM,
    [POSTFIX_DEC]              = COMO_OPCODE_HANDLER_POSTFIX_DEC,
};

static void como_opcode_default_handler(Object *arg1, Object *arg2, 
        Object **retval)
{      
    /* TODO */   
}
