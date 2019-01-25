#include "../include/commands.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char* builtins[] = {
    "cd",
    "ls",
    "help",
    "exit"
};

int launch_process(char **args){
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0){
        execvp(args[0], args);
        //execvp only returns if an error has occured
        perror("Error, unknown command");
        exit(1);
    }
    else if (pid == -1){
        perror("Error with forking");
    }
    else{
        waitpid(pid, &status, WUNTRACED);
    }
    return CONTINUE_CODE;
}

int run_builtin(int builtin_idx, char **args){
    int rv = CONTINUE_CODE;
    switch (builtin_idx) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            rv = EXIT_CODE;
            break;
        default:
            rv = CONTINUE_CODE;
            break;
    }
    return rv;
}

int run_command(char **args){
    if (!args[0]){
        return CONTINUE_CODE;
    }
    int num_builtins = sizeof(builtins)/sizeof(char*);
    for(int i=0; i<num_builtins; i++){
        if (strcmp(args[0], builtins[i]) == 0){
            return run_builtin(i, args);
        }
    }
    return launch_process(args);
}

int handle_ls(char **args){
    return CONTINUE_CODE;
}
