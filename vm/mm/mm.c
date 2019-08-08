#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct _mem_header {
  unsigned int size;
  struct block *next;  
} mem_header;
