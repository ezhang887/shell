#ifndef PARSER_H
#define PARSER_H

#define TOKENIZE_BUF_SIZE 64

char *read_input();

char **tokenize_input(char *line);

#endif
