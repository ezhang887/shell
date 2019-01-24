#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/io.h"
#include "include/commands.h"

int main(){
    printf("Shell\n");
    while(1){
        printf(SHELL_LINE_HEADER);
        char* line = read_input();
        if (line == NULL){
            continue;
        }
        char** tokens = tokenize_input(line);
        if (strcmp(line, EXIT_KEYWORD) == 0){
            free(line);
            free(tokens);
            printf(EXIT_MESSAGE);
            break;
        }
        launch_process(tokens);
        //cleanup
        free(line);
        free(tokens);
    }
    return 0;
}
