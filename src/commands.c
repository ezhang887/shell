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
    return 1;
}

int run_builtin(int builtin_idx, char** args){
    int rv = 1;
    switch (builtin_idx) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            rv = 0;
            break;
        default:
            rv = 1;
            break;
    }
    return rv;
}

int run_command(char** args){
    if (!args[0]){
        return 1;
    }
    int num_builtins = sizeof(builtins)/sizeof(char*);
    for(int i=0; i<num_builtins; i++){
        if (strcmp(args[0], builtins[i]) == 0){
            return run_builtin(i, args);
        }
    }
    return launch_process(args);
}
