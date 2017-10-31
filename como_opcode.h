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

#ifndef COMO_OPCODE_H
#define COMO_OPCODE_H

#include <object.h>

typedef struct ComoOpCode 
{
    unsigned char op_code;
    unsigned int  flags;
    unsigned int  lineno;
    Object       *operand;
} ComoOpCode;

#define INONE                           0x00
#define LOAD_CONST                      0x01
#define STORE_NAME                      0x02
#define LOAD_NAME                       0x03
#define IS_LESS_THAN                    0x04
#define JZ                              0x05
#define IPRINT                          0x06
#define IADD                            0x07
#define JMP                             0x08
#define IRETURN                         0x09
#define NOP                             0x0a
#define LABEL                           0x0b
#define HALT                            0x0c
#define IS_EQUAL                        0x0d
#define IDIV                            0x0e
#define ITIMES                          0x0f
#define IMINUS                          0x10
#define IS_GREATER_THAN                 0x11
#define IS_NOT_EQUAL                    0x12
#define IS_GREATER_THAN_OR_EQUAL        0x13
#define IS_LESS_THAN_OR_EQUAL           0x14
#define DEFINE_FUNCTION                 0x15
#define CALL_FUNCTION                   0x16
#define POSTFIX_INC                     0x17
#define UNARY_MINUS                     0x18
#define IREM                            0x19
#define POSTFIX_DEC                     0x20
#define ITYPEOF                         0x21
#define IASSERT                         0x22
#define UNARY_NOT                       0x23
#define IAND                            0x24
#define CREATE_ARRAY                    0x25
#define GET_FIELD                       0x26
#define LOAD_STRING                     0x27
#define COMO_OPCODE_MAX                 0x28

extern const char * const str_opcodelist[];

extern const char *instrstr(ComoOpCode *op);

//extern ComoOpCode *create_op(unsigned char op, int lineno, Object *arg);

#endif /* !COMO_OPCODE_H */
