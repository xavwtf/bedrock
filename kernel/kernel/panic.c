#include <kernel/panic.h>
#include <stdio.h>

__attribute__((noreturn))
void kpanic(void) {
    // TODO: panic

    printf("The kernel has encountered an unrecoverable error.\nThe system will now halt.");
    asm volatile ("cli; hlt;");
    for (;;);
}