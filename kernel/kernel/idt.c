#include <kernel/idt.h>

#include <stdio.h>
#include <string.h>

#define IDTBASE    0x00
#define IDTSIZE    0xFF

struct idt_ptr idtr;

void idt_init()
{
	struct idt_entry* idt = (struct idt_entry*) IDTBASE;
	
	memset(idt, 0, sizeof(struct idt_entry) * IDTSIZE);
		
	idtr.limit = (uint16_t) IDTSIZE * 8;
	idtr.base = (uint32_t) IDTBASE;
	
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
