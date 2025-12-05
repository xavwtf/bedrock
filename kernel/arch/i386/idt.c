#include "idt.h"

#include <stdint.h>

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t offset_high;
} __attribute__((packed));

struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr;

struct idt_entry idt[256];
extern uint32_t isr_stub_table[];

void idt_setdescriptor(uint8_t vector, uint32_t offset, uint16_t selector, uint8_t flags) {
    idt[vector].offset_low = offset & 0xFFFF;
    idt[vector].selector = selector;
    idt[vector].reserved = 0;
    idt[vector].flags = flags;
    idt[vector].offset_high = (offset >> 16) & 0xFFFF;
}

void idt_init(void) {
    // disable interrupts, this isn't explicitly required but should we get an irq during the process we could triple fault
    asm volatile ("cli");

    // loading the idt is very similar to the gdt. we have our idtr struct, which we should populate
    idtr.base = (uint32_t)&idt;
    idtr.limit = sizeof (struct idt_entry) * 256 - 1;

    // now we need to populate the idt with isr stubs from the isr_stub_table
    for (int i = 0; i < 32; i++) {
        idt_setdescriptor(i, (uint32_t)isr_stub_table[i], 0x08, 0b10001110);
    }

    // load the idtr into the idtr register
    asm volatile (
        "lidt (%0)"
        : : "r"(&idtr)
    );

    // we can re-enable interrupts now, and they should be mapped to our new isrs.
    asm volatile ("sti");

    // the idt should now be set up, nice.
    return;
} 