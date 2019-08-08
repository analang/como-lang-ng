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

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "como_io.h"

/**
 * POSIX compliant 
 */
char *como_read_file(const char *path)
{
    int fd;
    off_t length;
    char *buffer;
    ssize_t nread;
    struct stat stat_buffer;

    fd = open(path, O_RDONLY);
    
    if(fd == -1) 
    {
        return NULL;
    }

    if((fstat(fd, &stat_buffer) != 0))
    {
        close(fd);
        return NULL;
    }

    if(!S_ISREG(stat_buffer.st_mode))
    {
        close(fd);
        return NULL;
    }

    length = stat_buffer.st_size;

    if(length + 1 < length)
    {
        close(fd);
        return NULL;
    }

    buffer = malloc(length + 1);
    
    if(buffer == NULL)
    {
        close(fd);
        free(buffer);
        return NULL;
    }

    nread = read(fd, buffer, (size_t)length);

    if(nread != length)
    {
        close(fd);
        free(buffer);
        return NULL;
    }

    close(fd);

    buffer[length] = '\0';

    return buffer;
}
