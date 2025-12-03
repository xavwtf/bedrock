#include <stdio.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

int puts(const char* str) {
#if defined(__is_libk)
    tty_puts(str);
#else
    // TODO: libc equivalent
#endif
}