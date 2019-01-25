#ifndef COMMANDS_H
#define COMMANDS_H

#define EXIT_CODE 0
#define CONTINUE_CODE 1

extern char* builtins[];

int launch_process(char **args);
int run_builtin(int builtin_idx, char **args);
int run_command(char **args);

int handle_ls(char **args);
int handle_cd(char **args);

#endif
