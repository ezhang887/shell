#include "../include/utils.h"

#include <stdio.h>
#include <stdarg.h>

int printf_color(char* color_code, char* str, ...){
    int rv = printf("%s", color_code);

    va_list arg_list;
    va_start(arg_list, str);
    rv += vprintf(str, arg_list);
    va_end(arg_list);

    rv += printf(ANSI_COLOR_RESET);
    return rv;
}
