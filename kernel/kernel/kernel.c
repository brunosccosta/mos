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

#include <stdio.h>
  
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

void test_colors();

void kernel_early()
{
	/* Initialize terminal interface */
    terminal_initialize();
}

void kernel_main()
{
	/* Welcome message */
    printf("Welcome to MOS\n");
    printf("M Operating System\n\n\n");
    
    printf("Testing colors...\n");
    test_colors();

    printf("\n\n\nTesting numbers:\n");
    printf("Base-10 numbers: %d, %d, %d, %d\n", 5, 15, -2, -23);
    printf("Base-16 numbers: %x, %x\n", 0xFF, 0x234);
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
