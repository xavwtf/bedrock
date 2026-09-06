#include <stdio.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

int puts(const char* str) {
    return printf("%s\n", str);
}