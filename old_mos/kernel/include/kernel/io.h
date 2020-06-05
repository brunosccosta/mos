#ifndef _IO_KERNEL_H
#define _IO_KERNEL_H

#include <stdint.h>

void output_byte(uint32_t addr, uint8_t value);
void output_word(uint32_t addr, uint16_t value);
void output_long(uint32_t addr, uint32_t value);

uint8_t  input_byte(uint32_t addr);
uint16_t input_word(uint32_t addr);
uint32_t input_long(uint32_t addr);

#endif
