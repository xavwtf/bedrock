#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static bool print(const char* data, size_t length) {
    const unsigned char* bytes = (const unsigned char*)data;
    for (size_t i = 0; i < length; i++) {
        if (putchar(bytes[i]) == EOF) {
            return false;
        }
    }

    return true;
}

int printf(const char* restrict format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int written = 0;

    while (*format != '\0') {
        if (*format != '%') {
            if (!print(format, 1)) return -1;
            written++;
            format++;
            continue;
        }
        
        format++;

        if (*format == '\0') return -1;

        if (*format == '%') {
            if (!print(format, 1)) return -1;
            written++;
            format++;
            continue;
        } else if (*format == 'c') {
            int value = va_arg(parameters, int);
            char c = (char)value;

            if (!print(&c, 1)) return -1;

            format++;
            written++;
        } else if (*format == 's') {
            const char* str = va_arg(parameters, const char*);
            size_t len = strlen(str);

            if (!print(str, len)) return -1;

            format++;
            written += len;
        } else {
            if (!print("%", 1)) return -1;
            if (!print(format, 1)) return -1;

            format++;
            written += 2;
        }
    }

    va_end(parameters);
    return written;
}