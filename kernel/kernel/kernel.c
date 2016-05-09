/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This kernel needs to be compiled with a ix86-elf compiler"
#endif

#include <kernel/vga.h>
#include <kernel/tty.h>
#include <kernel/gdt.h>

#include <stdio.h>
  
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

void kernel_main()
{
	printf("Initializing internals...\n");
    
    /* Initializing GDT */
    gdt_init();
    
    /* Welcome message */
    printf("\n\nWelcome to MOS\n");
    printf("M Operating System\n\n\n");
        
    panic("End of kernel main.");
    for(;;);
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
