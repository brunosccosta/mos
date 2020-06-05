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

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    uint16_t gs, fs, es, ds;      						/* pushed the segs last */
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; 	/* pushed by 'pusha' */
    uint32_t int_no, err_code;							/* our 'push byte #' and ecodes do this */
    uint32_t eip, cs, eflags, useresp, ss;				/* pushed by the processor automatically */ 
};

void idt_init();
void pic_init();
void idt_set_gate(uint16_t select, uint32_t offset, uint8_t flags, struct idt_entry *desc);

void fault_handler(struct regs *r);
void irq_handler_1(struct regs *r);

#endif
