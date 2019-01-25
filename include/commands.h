#ifndef COMMANDS_H
#define COMMANDS_H

#define EXIT_CODE 0
#define CONTINUE_CODE 1

#define CD 5863276
#define LS 5863588
#define PWD 193502992
#define HELP 6385292014
#define EXIT 6385204799

extern char* builtins[];

int launch_process(char **args);
int run_builtin(char *command, char **args);
int run_command(char **args);

int handle_ls(char **args);
int handle_cd(char **args);
int handle_pwd(char **args);

#endif
