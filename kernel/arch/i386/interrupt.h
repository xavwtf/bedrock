#pragma once

#include <stdint.h>

typedef void (*irq_handler_t)(void);

void idt_init(void);
void idt_setdescriptor(uint8_t, uint32_t, uint16_t, uint8_t);

void irq_register(uint8_t, irq_handler_t);