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

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "como_debug.h"
#include "como_compiler.h"

void como_debug_ex(const char *f, const char *fn, int ln, 
        const char* format, ...)
{
    fprintf(stderr, ANSI_COLOR_GREEN "debug: %s:%s:%d: ", f, fn, ln);
    va_list args;
    va_start (args, format);
    vfprintf (stderr, format, args);
    va_end (args);
    fprintf(stderr, ANSI_COLOR_RESET "\n");
    fflush(stderr);	
}

void __attribute__ ((noreturn)) como_error_noreturn_ex(ComoFrame *frame, const char *f, 
        const char *fn, int ln, const char* format, ...)
{
    fprintf(stderr, ANSI_COLOR_RED  "fatal: %s:%s:%d: ", f, fn, ln);
    va_list args;
    va_start (args, format);
    vfprintf (stderr, format, args);
    va_end (args);
    fprintf(stderr, ANSI_COLOR_RESET  "\n");

    if(frame != NULL) {
        como_print_stack_trace(frame);
    }

    fflush(stderr);	
    exit(1);
}
