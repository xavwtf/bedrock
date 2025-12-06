#include "pit.h"
#include "interrupt.h"

#include <kernel/time.h>
#include <kernel/io.h>
#include <kernel/tty.h>

#define PIT_CLOCK 1193182
#define HZ        100

#define PIT_C0    0x40
#define PIT_C1    0x41
#define PIT_C2    0x42
#define PIT_CMD   0x43

static volatile uint32_t ticks;

void pit_irq0(void) {
    ticks++;
}

void pit_init(void) {
    ticks = 0;

    uint16_t divisor = PIT_CLOCK / HZ;

    out8(PIT_CMD, 0b00110110); // 16-bit binary, square wave, lobyte/hibyte access, channel 0
    out8(PIT_C0, divisor & 0xFF); // send lobyte
    out8(PIT_C0, divisor >> 8); // send hibyte

    irq_register(0, (irq_handler_t)pit_irq0);
}

uint32_t uptime(void) {
    return ticks;
}

void sleep(uint32_t ms) {
    uint32_t target = ticks + (ms * HZ / 1000);
    while (ticks < target) {
        asm volatile ("hlt");
    }
}