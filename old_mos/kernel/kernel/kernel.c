/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

#include <kernel/multiboot.h>

#include <kernel/vga.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>

#include <stdio.h>

#define KERNEL_END 0x10000
  
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

void test_colors();
void panic(char *msg);

void kernel_early()
{
	/* Initialize terminal interface */
    terminal_initialize();
}

void kernel_main(multiboot_info_t* mbd)
{
	printf("Reading memory...\n");
	unsigned long size = 0;
	memory_map_t* mmap = mbd->mmap_addr;
	while(mmap < mbd->mmap_addr + mbd->mmap_length)
	{
		if (mmap->type == 1 && mmap->base_addr_low >= KERNEL_END)
		{
			size += mmap->length_low;
		}
		
		mmap = (memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(unsigned int) );
	}
	printf("Size: %d\n\n", size);
	
	printf("Initializing internals...\n");
    
    /* Initializing GDT and IDT */
    gdt_init();
    idt_init();
    pic_init();
    asm("sti");
    printf("Interruptions are enabled! Proceed with caution\n");
    
    /* Welcome message */
    printf("\n\nWelcome to MOS\n");
    printf("M Operating System\n\n\n");
                
    for(;;);
    
    panic("End of kernel main.\n");
}

void test_colors()
{
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_BLACK));
	printf("  ");
	
	terminal_setcolor(make_color(COLOR_BLACK, COLOR_BLUE));
    printf("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_GREEN));
    printf("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_CYAN));
    printf("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_RED));
    printf("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_MAGENTA));
    printf("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_BROWN));
    printf("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_WHITE));
    printf("  ");

    terminal_set_default_color();
}

void panic(char *msg)
{
	terminal_setcolor(make_color(COLOR_BLACK, COLOR_RED));
    printf(msg);
}
