#pragma once

#include <stdint.h>

// https://en.wikipedia.org/wiki/VGA_text_mode
enum vga_colour {
    VGA_COLOUR_BLACK = 0,
    VGA_COLOUR_BLUE = 1,
    VGA_COLOUR_GREEN = 2,
    VGA_COLOUR_CYAN = 3,
    VGA_COLOUR_RED = 4,
    VGA_COLOUR_MAGENTA = 5,
    VGA_COLOUR_BROWN = 6,
    VGA_COLOUR_LIGHT_GRAY = 7,
    VGA_COLOUR_DARK_GRAY = 8,
    VGA_COLOUR_LIGHT_BLUE = 9,
    VGA_COLOUR_LIGHT_GREEN = 10,
    VGA_COLOUR_LIGHT_CYAN = 11,
    VGA_COLOUR_LIGHT_RED = 12,
    VGA_COLOUR_LIGHT_MAGENTA = 13,
    VGA_COLOUR_LIGHT_BROWN = 14,
    VGA_COLOUR_WHITE = 15,
};

static inline uint8_t vga_make_colour(enum vga_colour fore, enum vga_colour back) {
    return fore | back << 4;
}

static inline uint16_t vga_make_entry(unsigned char c, uint8_t colour) {
    return (uint16_t)c | (uint16_t)colour << 8;
}