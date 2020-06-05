
#include <kernel/io.h>

void output_byte(uint32_t addr, uint8_t value)
{
    asm("outb %%al, %%dx" :: "d" (addr), "a" (value));
}

void output_word(uint32_t addr, uint16_t value)
{
    asm("outw %%ax, %%dx" :: "d" (addr), "a" (value));
}

void output_long(uint32_t addr, uint32_t value)
{
    asm("outl %%eax, %%dx" : : "d" (addr), "a" (value));
}

uint8_t input_byte(uint32_t addr)
{
    uint8_t _value;
    asm("inb %%dx, %%al" : "=a" (_value) : "d" (addr));
    return _value;
}

uint16_t input_word(uint32_t addr)
{
    uint16_t _value;
    asm("inw %%dx, %%ax" : "=a" (_value) : "d" (addr));
    return _value;
}

uint32_t input_long(uint32_t addr)
{
    uint32_t _value;
    asm("inl %%dx, %%eax" : "=a" (_value) : "d" (addr));
    return _value;
}
