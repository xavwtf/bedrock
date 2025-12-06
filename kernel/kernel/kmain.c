#include <kernel/tty.h>
#include <kernel/multiboot.h>
#include <kernel/panic.h>

#if defined(__i386__)
#include "../arch/i386/gdt.h"
#include "../arch/i386/interrupt.h"
#include "../arch/i386/pit.h"
#endif

#include <stdio.h>

void kernel_main(uint32_t magic, multiboot_info_t* mbi) {
    tty_init();

    // check our bootloader magic value. if it doesn't match expected, panic
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        kpanic();
    }

    #if defined(__i386__)
    gdt_init();
    interrupt_init();
    pit_init();
    #endif

    printf("Hello world!\n");

    for (;;);
}