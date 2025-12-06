#pragma once
#include <stdint.h>

static inline uint8_t in8(uint16_t port) {
    uint8_t ret;
    asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));

    return ret;
}

static inline void out8(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

// takes advantage of the i/o overhead to wait a few microseconds. not useful for anything but pic remapping really
static inline void io_wait(void) {
    out8(0x80, 0);
}