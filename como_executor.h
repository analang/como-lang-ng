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

#ifndef COMO_EXECUTE_H
#define COMO_EXECUTE_H

#include <object.h>

#include "como_opcode.h"

typedef void(*como_opcode_handler)(Object *arg1, Object *arg2, 
        Object **retval);

extern const como_opcode_handler como_opcode_handler_table[COMO_OPCODE_MAX];

#endif /* !COMO_EXECUTE_H */
