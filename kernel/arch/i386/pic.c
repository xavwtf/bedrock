#include "pic.h"

#include <stdint.h>
#include <stdbool.h>
#include <kernel/io.h>

#define PIC1_CMD        0x20
#define PIC1_DATA       0x21
#define PIC2_CMD        0xA0
#define PIC2_DATA       0xA1

#define ICW1_ICW4       0x01
#define ICW1_SINGLE     0x02
#define ICW1_INTERVAL4  0x04
#define ICW1_LEVEL      0x08
#define ICW1_INIT       0x10

#define ICW4_8086       0x01
#define ICW4_AUTO       0x02
#define ICW4_BUF_SLAVE  0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM       0x10

#define CASCADE_IRQ     2

// ocw3 command words
#define PIC_REG_IRR     0x0A
#define PIC_REG_ISR     0x0B

#define PIC_EOI         0x20

void pic_remap(uint8_t master_offset, uint8_t slave_offset) {
    out8(PIC1_CMD, ICW1_INIT | ICW1_ICW4); // initialise master PIC
    io_wait();
    out8(PIC2_CMD, ICW1_INIT | ICW1_ICW4); // initialise slave PIC
    io_wait();
    out8(PIC1_DATA, master_offset); // tell the master its vector offset
    io_wait();
    out8(PIC2_DATA, slave_offset); // tell the slave its vector offset
    io_wait();
    out8(PIC1_DATA, 1 << CASCADE_IRQ); // tell the master it has a slave at IRQ2
    io_wait();
    out8(PIC2_DATA, 2); // tell the slave its cascade identity
    io_wait();

    out8(PIC1_DATA, ICW4_8086); // tell the master to use 8086 mode
    io_wait();
    out8(PIC2_DATA, ICW4_8086); // tell the slave to use 8086 mode
    io_wait();

    out8(PIC1_DATA, 0); // unmask master PIC
    out8(PIC2_DATA, 0); // unmask slave PIC

    return;
}

static uint16_t _pic_getreg(int ocw3) {
    out8(PIC1_CMD, ocw3);
    out8(PIC2_CMD, ocw3);

    return (in8(PIC2_CMD) << 8) | in8(PIC1_CMD);
}

uint16_t pic_getirr(void) {
    return _pic_getreg(PIC_REG_IRR);
}

uint16_t pic_getisr(void) {
    return _pic_getreg(PIC_REG_ISR);
}

void pic_sendeoimaster() {
    out8(PIC1_CMD, PIC_EOI);

    return;
}

void pic_sendeoislave() {
    out8(PIC2_CMD, PIC_EOI);

    return;
}

void pic_sendeoi(uint8_t irq) {
    if (irq > 7) pic_sendeoislave(); // if irq is handled by slave, send eoi to slave too
    pic_sendeoimaster();

    return;
}

void pic_setmask(uint8_t vector) {
    if (vector > 7) {
        uint8_t val = in8(PIC2_DATA) | (1 << (vector - 8));
        out8(PIC2_DATA, val);

        return;
    }

    uint8_t val = in8(PIC1_DATA) | (1 << vector);
    out8(PIC1_DATA, val);

    return;
}

void pic_clearmask(uint8_t vector) {
    if (vector > 7) {
        uint8_t val = in8(PIC2_DATA) & ~(1 << (vector - 8));
        out8(PIC2_DATA, val);

        return;
    }

    uint8_t val = in8(PIC1_DATA) & ~(1 << vector);
    out8(PIC1_DATA, val);

    return;
}

void pic_maskall(void) {
    out8(PIC1_DATA, 0xFF);
    out8(PIC2_DATA, 0xFF);

    return;
}

void pic_unmaskall(void) {
    out8(PIC1_DATA, 0);
    out8(PIC2_DATA, 0);

    return;
}

bool pic_isspurious(uint8_t vector) {
    // a spurious irq will always be either irq7 or irq15, if the irq is not present in either master's (irq7) or slave's (irq15) isr then it is spurious
    if (vector == 7 || vector == 15) {
        if (!((pic_getisr() >> vector) & 1)) return true;
    }

    return false;
}