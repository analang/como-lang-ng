#include <stdlib.h>
#include <stdio.h>

#include "../como_io.h"

int main(void)
{
    char *contents = como_read_file("test_como_io.c");

    if(contents == NULL) {
        printf("ERROR READING");
    }

    printf("%s", contents);

    free(contents);

    
    contents = como_read_file("THIS_DOES_NOT_EXIST");
    if(contents == NULL) {
        printf("success\n");
    }


    return 0;
}      
