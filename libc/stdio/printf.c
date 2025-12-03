#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int printf(const char* restrict format, ...) {
    // TODO: implement printf formatting
    puts(format);

    return strlen(format);
}