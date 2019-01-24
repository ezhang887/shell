#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parser.h"

char *read_input(){
    char *line = NULL;
    size_t bufsize = 0;
    //error
    if (getline(&line, &bufsize, stdin) == -1){
        return NULL;
    }
    return line;
}

char **tokenize_input(char* line){
    assert(line);

    int bufsize = TOKENIZE_BUF_SIZE;
    int curr_pos = 0;
    char *delim = " \t\r\n\a";

    char **tokens = malloc(bufsize*sizeof(char*));
    char *curr_token;

    assert(tokens);

    curr_token = strtok(line, delim);
    while(curr_token){
        tokens[curr_pos] = curr_token;
        curr_pos++;

        if (curr_pos >= bufsize){
            bufsize += TOKENIZE_BUF_SIZE;
            tokens = realloc(tokens, bufsize*sizeof(char*));
            assert(tokens);
        }

        //for each subsequent call on the same string for the next token, strtok takes in NULL
        curr_token = strtok(NULL, delim);
    }

    tokens[curr_pos] = NULL;
    return tokens;
}
