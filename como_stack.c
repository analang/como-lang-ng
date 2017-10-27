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

#include "como_stack.h"

int como_stack_push(como_stack **stack, void *value)
{
    if(*stack == NULL) 
    {
        como_stack* _list = malloc(sizeof(como_stack));
        _list->value = value;
        _list->next = NULL;
        *stack = _list;				
    } 
    else 
    {
        como_stack* prev = (*stack);
        como_stack* next = malloc(sizeof(como_stack));
        next->value = value;
        next->next = prev;
        (*stack) = next;							
    }

    return 1;
}