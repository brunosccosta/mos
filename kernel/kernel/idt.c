#include <kernel/idt.h>
#include <kernel/io.h>

#include <stdio.h>
#include <string.h>

#define IDTBASE    0x00
#define IDTSIZE    0xFF

struct idt_ptr idtr;

extern void _isr0();
extern void _isr8();
extern void _isr13();

extern void _irq1();

void idt_init()
{
	struct idt_entry* idt = (struct idt_entry*) IDTBASE;
	
	memset(idt, 0, sizeof(struct idt_entry) * IDTSIZE);
		
	idtr.limit = (uint16_t) IDTSIZE * 8;
	idtr.base = (uint32_t) IDTBASE;
	
	// Exceptions	
	idt_set_gate(0x08, (uint32_t) _isr0, 0x8E, &idt[0]);	/* Division by zero */
	idt_set_gate(0x08, (uint32_t) _isr8, 0x8E, &idt[8]);  	/* Double Fault */
	idt_set_gate(0x08, (uint32_t) _isr13, 0x8E, &idt[13]);  /* General Protection */
	
	// Keyboard Interruption
	idt_set_gate(0x08, (uint32_t) _irq1, 0x8E, &idt[33]);   /* Keyboard */
	
	/* Load the IDTR registry */
    asm("lidtl (idtr)");
    
	printf("IDT is alive.\n");
}

void idt_set_gate(uint16_t select, uint32_t offset, uint8_t flags, struct idt_entry *desc)
{   
    desc->base_lo = (offset & 0x0000ffff);
    desc->base_hi = (offset & 0xffff0000) >> 16;
    
    desc->sel = select;
    desc->flags = flags;
   
	desc->always0 = 0x0;
}

void fault_handler(struct regs *r)
{
    if (r->int_no < 32)
    {
        printf("Exception %d. System Halted!\n", r->int_no);
        for (;;);
    }
}

void irq_handler_1(struct regs *r)
{
	printf("Keyboard\n");
}

void pic_init(void)
{
    /* Initialization of ICW1 */
    output_byte(0x20, 0x11);
    output_byte(0xA0, 0x11);

    /* Initialization of ICW2 */
    output_byte(0x21, 0x20);
    output_byte(0xA1, 0x28);

    /* Initialization of ICW3 */
    output_byte(0x21, 0x04);
    output_byte(0xA1, 0x02);

    /* Initialization of ICW4 */
    output_byte(0x21, 0x01);
    output_byte(0xA1, 0x01);

    /* mask interrupts */
    output_byte(0x21, 0xfd);
    output_byte(0xA1, 0xff);
    
    printf("PIC Initialized.\n");
}
