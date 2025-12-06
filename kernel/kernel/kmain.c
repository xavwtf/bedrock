#include <kernel/tty.h>

#if defined(__i386__)
#include "../arch/i386/gdt.h"
#include "../arch/i386/interrupt.h"
#include "../arch/i386/pit.h"
#endif

#include <stdio.h>

void kernel_main(void) {
    #if defined(__i386__)
    gdt_init();
    interrupt_init();
    pit_init();
    #endif

    // by this point architecture-specific differences should be abstracted away

    tty_init();
    printf("Hello world!\n");

    for (;;);
}