#pragma once
#include <stddef.h>

void tty_init(void);
void tty_putc(char);
void tty_writen(const char*, size_t);
void tty_puts(const char*);