#include "../include/utils.h"

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

void printf_color(char *color_code, int bold, char *str, ...){
    if (bold){
        printf("%s", ANSI_BOLD);
    }
    else{
        printf("%s", ANSI_NO_BOLD);
    }
    printf("%s", color_code);

    va_list arg_list;
    va_start(arg_list, str);
    vprintf(str, arg_list);
    va_end(arg_list);

    printf(ANSI_COLOR_RESET);
}

void assert_equals(char *a, char *b){
    assert(strcmp(a, b) == 0);
}

//djb2 hash
unsigned long hash(char *str){
    unsigned long hash = 5381;
    for(char* c = str; *c != '\0'; c++){
        hash = ((hash << 5) + hash) + *c;
    }
    return hash;
}

int is_executable(char *file){
    struct stat sb;
    return stat(file, &sb) == 0 && sb.st_mode & S_IEXEC;
}
