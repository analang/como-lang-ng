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

#ifndef COMO_DEBUG_H
#define COMO_DEBUG_H

#include <stdarg.h>

#ifdef COMO_DEBUG
#define COMO_HAVE_DEBUG 1
#endif

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


void __attribute__ ((noreturn)) como_error_noreturn_ex(const char *f, 
        const char *fn, int ln, const char* format, ...);

#define como_error_noreturn(format, ...) \
    como_error_noreturn_ex(__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)  

#ifdef COMO_HAVE_DEBUG
#define como_debug(format, ...) \
        como_debug_ex(__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)

void como_debug_ex(const char *f, 
        const char *fn, int ln, const char* format, ...);

#else
#define como_debug(format, ...)
#endif

#ifdef COMO_WARNING 
#define como_warning(format, ...) \
        como_warning_ex(__FILE__, __func__, __LINE__, format, ##__VA_ARGS__)

void como_warning_ex(const char *f, 
        const char *fn, int ln, const char* format, ...);

#else
#define como_warning(format, ...)
#endif


#define COMO_OOM() do { \
	como_error_noreturn("out of memory"); \
} while(0)

#endif /* !COMO_DEBUG_H */

