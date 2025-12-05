#pragma once
#include <stdint.h>

static inline uint8_t in8(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %w1 %b0" : "=a"(ret) : "Nd"(port));

    return ret;
}

static inline void out8(uint16_t port, uint8_t val) {
    asm volatile ("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}