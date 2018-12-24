#include <stdio.h>
#include "../include/parser.h"

char* read_input(){
    char* line = NULL;
    size_t size = 0;
    //error
    if (getline(&line, &size, stdin) == -1){
        return NULL;
    }
    printf("Input: %s", line);
    return line;
}
