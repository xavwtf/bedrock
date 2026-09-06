#pragma once

#if defined(__i386__)
#include "../../arch/i386/interrupt.h"
#endif

__attribute__((noreturn))
void kpanic(char* message);

__attribute__((noreturn))
void kpanic_exception(char* message, struct interrupt_frame* frame);