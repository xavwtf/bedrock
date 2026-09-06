#include <stdio.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

int putchar(int in_c) {
#if defined(__is_libk)
    char c = (char)in_c;
    tty_putc(c);
#else
    // TODO: libc equivalent
#endif
    return in_c;
}