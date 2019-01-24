#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/parser.h"
#include "include/commands.h"

int main(){
    printf("Shell\n");
    while(1){
        printf(">>> ");
        char* line = read_input();
        if (line == NULL){
            continue;
        }
        char** tokens = tokenize_input(line);
        if (strcmp(line, "exit") == 0){
            free(line);
            free(tokens);
            printf("Exiting shell............\n\n\n");
            break;
        }
        launch_process(tokens);
        //cleanup
        free(line);
        free(tokens);
    }
    return 0;
}
