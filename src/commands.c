#include "../include/commands.h"
#include "../include/utils.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

char* builtins[] = {
    "cd",
    "ls", 
    "pwd",
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

int run_builtin(char *command, char **args){
    int rv = CONTINUE_CODE;
    switch (hash(command)) {
        case CD:
            rv = handle_cd(args);
            break;
        case LS:
            rv = handle_ls(args);
            break;
        case PWD:
            rv = handle_pwd(args);
            break;
        case HELP:
            break;
        case EXIT:
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
            return run_builtin(args[0], args);
        }
    }
    return launch_process(args);
}

int handle_ls(char **args){
    assert_equals("ls", args[0]);

    struct dirent **files;
    int n = scandir(".", &files, NULL, alphasort);
    if (n == -1){
        perror("[handle_ls], error with scandir");
    }
    else{
        for(int i=0; i<n; i++){
            struct dirent *curr = files[i];
            if (curr->d_type == DT_REG){
                printf_color(ANSI_COLOR_BLUE, "%s", curr->d_name);
                printf("   ");
            }
            else if (curr->d_type == DT_DIR){
                printf_color(ANSI_COLOR_GREEN, "%s", curr->d_name);
                printf("   ");
            }
            else{
                printf_color(ANSI_COLOR_CYAN, "%s", curr->d_name);
                printf("   ");
            }
        }
    }
    printf("\n");
    for(int i=0; i<n; i++){
        free(files[i]);
    }
    free(files);
    return CONTINUE_CODE;
}

int handle_cd(char **args){
    assert_equals("cd", args[0]);

    char* path = args[1];
    int rv = chdir(path);
    if (rv == -1){
        perror("[handle_cd], error with chdir");
    }
    return CONTINUE_CODE;
}

int handle_pwd(char** args){
    assert_equals("pwd", args[0]);

    char cwd[64];
    char* rv = getcwd(cwd, sizeof(cwd));
    if (!rv){
        perror("[handle_pwd], error with getcwd");
    }
    printf_color(ANSI_COLOR_CYAN, "%s\n", cwd);
    return CONTINUE_CODE;
}
