#include "interrupt.h"
#include "pic.h"

#include <stdint.h>
#include <string.h>

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
extern uint32_t irq_stub_table[];

static volatile irq_handler_t irq_handlers[16];

void idt_setdescriptor(uint8_t vector, uint32_t offset, uint16_t selector, uint8_t flags) {
    idt[vector].offset_low = offset & 0xFFFF;
    idt[vector].selector = selector;
    idt[vector].reserved = 0;
    idt[vector].flags = flags;
    idt[vector].offset_high = (offset >> 16) & 0xFFFF;
}

void interrupt_init(void) {
    // zero out the idt
    memset(&idt, 0, sizeof(idt));

    // remap the PIC
    pic_remap(0x20, 0x28); // this offsets master vectors by 0x20, and slave vectors by 0x28, to avoid conflicts with CPU exception vectors
    
    // now we need to populate the idt with isr stubs from the isr_stub_table
    for (int i = 0; i < 32; i++) {
        idt_setdescriptor(i, isr_stub_table[i], 0x08, 0b10001110);
    }

    // we can load our irq stubs from the irq_stub_table. these call irq_dispatch.
    for (int i = 0; i < 16; i++) {
        idt_setdescriptor(0x20 + i, irq_stub_table[i], 0x08, 0b10001110);
    }

    // loading the idt is very similar to the gdt. we have our idtr struct, which we should write to
    idtr.base = (uint32_t)&idt;
    idtr.limit = sizeof(idt) - 1;

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

void irq_register(uint8_t irq, irq_handler_t handler) {
    irq_handlers[irq] = handler;
}

void irq_dispatcher(uint32_t irq) {
    if (irq >= 16) return; // uhh

    if (pic_isspurious(irq)) {
        if (irq == 15) pic_sendeoimaster();
        return;
    }

    if (irq_handlers[irq]) {
        irq_handlers[irq]();
    } else {
        // do nothing for now
        // TODO: add default IRQ handler
    }

    pic_sendeoi(irq);
}