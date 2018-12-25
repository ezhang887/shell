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
            printf("Exiting shell............\n");
            break;
        }
        if (line != NULL){
            free(line);
        }
    }
    return 0;
}
