#include <kernel/idt.h>
#include <kernel/io.h>

#include <stdio.h>
#include <string.h>

#define IDTBASE    0x00
#define IDTSIZE    0xFF

struct idt_ptr idtr;

extern void _asm_int_0();
extern void _asm_int_1();

extern void _asm_exc_DZ(void);
extern void _asm_exc_GP(void);
extern void _asm_exc_PF(void);
extern void _asm_schedule(void);

void idt_init()
{
	int i;
	struct idt_entry* idt = (struct idt_entry*) IDTBASE;
	
	memset(idt, 0, sizeof(struct idt_entry) * IDTSIZE);
		
	idtr.limit = (uint16_t) IDTSIZE * 8;
	idtr.base = (uint32_t) IDTBASE;
	
	for (i = 0; i < IDTSIZE; i++)
        idt_set_gate(0x08, (uint32_t) _asm_schedule, 0x8E, &idt[i]);
	
	// Exceptions	
	idt_set_gate(0x08, (uint32_t) _asm_exc_DZ, 0x8E, &idt[0]);   /* Division by zero */
	idt_set_gate(0x08, (uint32_t) _asm_exc_GP, 0x8E, &idt[13]);  /* General Protection */
    idt_set_gate(0x08, (uint32_t) _asm_exc_PF, 0x8E, &idt[14]);  /* Page Fault */
	
	// Keyboard Interruption
	idt_set_gate(0x08, (uint32_t) _asm_int_1, 0x8E, &idt[33]);   /* Keyboard */
	
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

void isr_GP_exc()
{
	printf("General Protection Exception.");
	asm("hlt");
}

void isr_PF_exc()
{
	printf("Page Fault Exception.");
	asm("hlt");
}

void isr_DZ_exc()
{
	printf("Division by zero Exception.");
	asm("hlt");
}

void isr_default_int()
{
	printf("Interruption\n");
}

void isr_schedule_int()
{
	//printf("Schedule int");
	output_byte(0x20,0x20);
	output_byte(0xA0,0x20);
}

void pic_init(void)
{
    /* Initialization of ICW1 */
    output_byte(0x20, 0x11);
    output_byte(0xA0, 0x11);

    /* Initialization of ICW2 */
    output_byte(0x21, 0x20);    /* start vector = 32 */
    output_byte(0xA1, 0x70);    /* start vector = 96 */

    /* Initialization of ICW3 */
    output_byte(0x21, 0x04);
    output_byte(0xA1, 0x02);

    /* Initialization of ICW4 */
    output_byte(0x21, 0x01);
    output_byte(0xA1, 0x01);

    /* mask interrupts */
    output_byte(0x21, 0x0);
    output_byte(0xA1, 0x0);
    
    printf("PIC Initialized.\n");
}
