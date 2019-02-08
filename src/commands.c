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
    "exit",
    ""
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
            rv = handle_help(args);
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
    int ls_a = 0;
    if (args[1] && args[1][0] == '-'){
        ls_a = args[1][1] == 'a';
    }
    if (n == -1){
        perror("[handle_ls], error with scandir");
    }
    else{
        for(int i=0; i<n; i++){
            struct dirent *curr = files[i];
            if (!ls_a){
                if (curr->d_name[0] == '.'){
                    continue;
                }
            }
            if (curr->d_type == DT_DIR){
                printf_color(ANSI_COLOR_BLUE, 1, "%s", curr->d_name);
                printf("   ");
            }
            else if (is_executable(curr->d_name)){
                printf_color(ANSI_COLOR_GREEN, 1, "%s", curr->d_name);
                printf("   ");
            }
            else if (curr->d_type == DT_REG){
                printf_color(ANSI_COLOR_WHITE, 0, "%s", curr->d_name);
                printf("   ");
            }
            else{
                printf_color(ANSI_COLOR_CYAN, 0, "%s", curr->d_name);
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

int handle_pwd(char **args){
    assert_equals("pwd", args[0]);

    char cwd[128];
    char* rv = getcwd(cwd, sizeof(cwd));
    if (!rv){
        perror("[handle_pwd], error with getcwd");
    }
    printf_color(ANSI_COLOR_CYAN, 1, "%s\n", cwd);
    return CONTINUE_CODE;
}

int handle_help(char **args){
    assert_equals("help", args[0]);
    for(int i=0; strcmp(builtins[i],"") != 0; i++){
        printf_color(ANSI_COLOR_CYAN, 1, "%s\n", builtins[i]);
    }
    return CONTINUE_CODE;
}
