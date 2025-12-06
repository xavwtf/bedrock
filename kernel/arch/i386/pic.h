#pragma once

#include <stdint.h>

void pic_remap(uint8_t, uint8_t);
uint16_t pic_getirr(void);
uint16_t pic_getisr(void);
void pic_sendeoi(uint8_t);

void pic_setmask(uint8_t);
void pic_clearmask(uint8_t);
void pic_maskall(void);
void pic_unmaskall(void);