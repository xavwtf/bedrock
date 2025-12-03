#include <stdlib.h>
#include <stdio.h>

__attribute__((__noreturn__))
void abort(void) {
#if defined(__is_libk)
    // TODO: kernel panic
    printf("bedrock kernel: panic (abort())");
#else
    // TODO: libc equivalent, terminate process
    printf("abort()");
#endif
    while (1) { }
    __builtin_unreachable();
}