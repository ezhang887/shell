#ifndef COMMANDS_H
#define COMMANDS_H

extern char* builtins[];

int launch_process(char **args);

int run_builtin(int builtin_idx, char** args);

int run_command(char** args);

#endif
