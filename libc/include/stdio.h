#pragma once

#include <sys/cdefs.h>

#define EOF (-1)

#ifdef __cplusplus
extern "C" {
#endif

int putchar(int);
int puts(const char*);
int printf(const char* __restrict, ...);

#ifdef __cplusplus
}
#endif