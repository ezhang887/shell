#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/parser.h"

int main(){
    printf("Shell\n");
    while(1){
        printf(">>> ");
        char* line = read_input();
        if (line == NULL){
            continue;
        }
        if (strcmp(line, "exit\n") == 0){
            free(line);
            printf("Exiting shell............\n\n\n");
            break;
        }
        char** tokens = tokenize_input(line);
        free(line);
        free(tokens);
    }
    return 0;
}
