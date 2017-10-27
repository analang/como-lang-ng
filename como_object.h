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

#ifndef COMO_OBJECT_UTIL
#define COMO_OBJECT_UTIL

#include <object.h>
#include <stdarg.h>

typedef struct ComoBuiltinFunction 
{
    Object *(*handler)(Object *);
} ComoBuiltinFunction;

#define Obj_CheckExact(Obj, Type) \
    (O_TYPE((Obj)) == (Type))

#define ComoString_Check(obj) O_TYPE((obj)) == IS_STRING ? 1 : 0

#define COMO__ARRAY_FOREACH(_ar) do { \
    size_t _i; \
    for(_i = 0; _i < O_AVAL((_ar))->size; _i++) { \
        Object* _value = O_AVAL((_ar))->table[_i]; \

#define COMO_ARRAY_FOREACH(_ar, _val) \
    COMO__ARRAY_FOREACH(_ar) \
    _val = _value; \

#define COMO_ARRAY_FOREACH_END() \
    } \
} while(0)

void como_printf(const char *format, ...);

int como_object_is_truthy(Object *obj);

#endif