#include <kernel/tty.h>
#include "vga.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_ADDR (uint16_t*)0xB8000

#define pos(x, y) y * VGA_WIDTH + x;

static size_t tty_x;
static size_t tty_y;
static size_t tty_colour;
static uint16_t* tty_buf;

void tty_init(void) {
    tty_x = 0;
    tty_y = 0;
    tty_colour = vga_make_colour(VGA_COLOUR_WHITE, VGA_COLOUR_BLACK);
    tty_buf = VGA_ADDR;

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t idx = pos(x, y);
            tty_buf[idx] = vga_make_entry(' ', tty_colour);
        }
    }
}

void tty_setcolour(uint8_t colour) {
    tty_colour = colour;
}

void tty_putat(unsigned char c, uint8_t colour, size_t x, size_t y) {
    const size_t idx = pos(x, y);
    tty_buf[idx] = vga_make_entry(c, colour);
}

void tty_putc(char c) {
    unsigned char uc = c;
    tty_putat(uc, tty_colour, tty_x, tty_y);

    if (++tty_x == VGA_WIDTH) {
        tty_x = 0;
        if (++tty_y == VGA_HEIGHT) {
            tty_y = 0;
        }
    }
}

void tty_writen(const char* str, size_t size) {
    for (size_t i = 0; i < size; i++) tty_putc(str[i]);
}

void tty_puts(const char* str) {
    tty_writen(str, strlen(str));
}