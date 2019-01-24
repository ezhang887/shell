#include "../include/commands.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    return status;
}
