#pragma once

#include <stdint.h>

typedef void (*irq_handler_t)(void);

struct interrupt_frame {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t ds, es;

    uint32_t vector;
    uint32_t error;

    uint32_t eip, cs, eflags;
};

void interrupt_init(void);
void idt_setdescriptor(uint8_t, uint32_t, uint16_t, uint8_t);

void irq_register(uint8_t, irq_handler_t);