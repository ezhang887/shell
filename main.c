#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/io.h"
#include "include/commands.h"
#include "include/utils.h"

int main(){
    printf("Shell\n");
    int status = 1;
    while(status){
        printf(SHELL_LINE_HEADER);
        char* line = read_input();
        if (line == NULL || line[0] == '\n'){
            free(line);
            continue;
        }
        char** tokens = tokenize_input(line);
        status = run_command(tokens);
        free(line);
        free(tokens);
    }
    return 0;
}
