#ifndef UTILS_H
#define UTILS_H

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_WHITE   "\x1b[37m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BOLD         "\033[1m"
#define ANSI_NO_BOLD      "\033[22m"

void printf_color(char *color_code, int bold, char *string, ...);

void assert_equals(char *a, char *b);

//djb2 hash
unsigned long hash(char *str);

int is_executable(char *file);

#endif
