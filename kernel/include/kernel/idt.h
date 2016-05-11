#ifndef _IDT_KERNEL_H
#define _IDT_KERNEL_H

#include <stdint.h>

/* Defines an IDT entry */
struct idt_entry
{
    uint16_t base_lo;
    uint16_t sel;        /* Our kernel segment goes here! */
    uint8_t  always0;     /* This will ALWAYS be set to 0! */
    uint8_t  flags;       /* Set using the above table! */
    uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_init();
void pic_init();
void idt_set_gate(uint16_t select, uint32_t offset, uint8_t flags, struct idt_entry *desc);

void isr_GP_exc();
void isr_PF_exc();
void isr_DZ_exc();

void isr_default_int();
void isr_schedule_int();

#endif
