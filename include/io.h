#ifndef PARSER_H
#define PARSER_H

#define TOKENIZE_BUF_SIZE 64

#define SHELL_LINE_HEADER ">>> "
#define EXIT_MESSAGE "Exiting shell............\n"

char *read_input();

char **tokenize_input(char *line);

#endif
