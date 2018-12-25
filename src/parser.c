#include <stdio.h>
#include <stdlib.h>

#include "../include/parser.h"

char* read_input(){
    char* line = NULL;
    size_t bufsize = 0;
    //error
    if (getline(&line, &bufsize, stdin) == -1){
        return NULL;
    }
    printf("Input: %s", line);
    return line;
}

char** tokenize_input(){
    int bufsize = 64;
    int curr_pos = 0;
    char* delim = " \t\r\n\a";
}
