#pragma once

#include <stdint.h>

void idt_init(void);

void idt_setdescriptor(uint8_t, uint32_t, uint16_t, uint8_t);