#include <kernel/gdt.h>
#include <stdio.h>

#define GDTSIZE 3
#define GDTBASE 0x00000800

struct gdt_ptr gdtr;

void gdt_init()
{
	struct gdt_entry* gdt = (struct gdt_entry*) GDTBASE;
	
	gdt_set_gate(0x0, 0x0, 0x0, 0x0, &gdt[0]);
    gdt_set_gate(0x0, 0xFFFFF, 0x9A, 0xCF, &gdt[1]);  /* kcode */
    gdt_set_gate(0x0, 0xFFFFF, 0x92, 0xCF, &gdt[2]);  /* kdata */
	
	gdtr.limit = (uint16_t) GDTSIZE * 8;
	gdtr.base = (uint32_t) GDTBASE;
	
	gdt_flush(); 
	printf("Global Descriptor Table is alive.\n");
}

void gdt_flush()
{
	/* load the gdtr registry */
	asm("lgdtl (gdtr)");
	printf("GDTR was set. gdtr.size=%d gdtr.base=%x\n", gdtr.limit, gdtr.base);
	
	asm("   movw $0x10, %ax	\n \
            movw %ax, %ds	\n \
            movw %ax, %es	\n \
            movw %ax, %fs	\n \
            movw %ax, %gs	\n \
            ljmp $0x08, $next	\n \
            next:		\n");
	printf("Segments reloaded.\n");
}

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(uint32_t base, uint32_t limite, uint8_t acces, uint8_t other, struct gdt_entry *desc)
{
	desc->lim0_15 = (limite & 0xffff);
	desc->base0_15 = (base & 0xffff);
	desc->base16_23 = (base & 0xff0000) >> 16;
	desc->acces = acces;
	desc->lim16_19 = (limite & 0xf0000) >> 16;
	desc->other = (other & 0xff) >> 4;
	desc->base24_31 = (base & 0xff000000) >> 24;
}
