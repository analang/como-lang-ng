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

#include <object.h>
#include <stdarg.h>
#include <float.h>

#include "como_object.h"

void como_printf(const char *format, ...) {
    va_list args;
    va_start (args, format);
    while(*format) {
        if(*format == ':') {
            Object *arg;
            format++;
            switch(*format) {
                case 'S':
                    arg = va_arg(args, Object *);
                    fprintf(stdout, "%s", O_SVAL(arg)->value);
                break;
                case 'L':
                    arg = va_arg(args, Object *);
                    fprintf(stdout, "%ld", O_LVAL(arg));
                break;
                case 'F':
                    arg = va_arg(args, Object *);
                    fprintf(stdout, "%.*G", DBL_DIG, O_DVAL(arg));
                break;
                default:
                    format--;
                    fputc(*format, stdout);
                break;
            }
        } else {
            fputc(*format, stdout);
        }
        format++;
    }
    va_end (args);
}

int como_object_is_truthy(Object *obj)
{
    /* C truthiness */
    if(O_TYPE(obj) == IS_LONG && O_LVAL(obj) == 0L)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}