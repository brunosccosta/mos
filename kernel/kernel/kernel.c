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
    terminal_writestring("Welcome to MOS\n");
    terminal_writestring("M Operating System\n\n\n");
    
    terminal_writestring("Testing colors...\n");
    test_colors();
}

void test_colors()
{
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_BLACK));
	terminal_writestring("  ");
	
	terminal_setcolor(make_color(COLOR_BLACK, COLOR_BLUE));
    terminal_writestring("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_GREEN));
    terminal_writestring("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_CYAN));
    terminal_writestring("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_RED));
    terminal_writestring("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_MAGENTA));
    terminal_writestring("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_BROWN));
    terminal_writestring("  ");
    
    terminal_setcolor(make_color(COLOR_BLACK, COLOR_WHITE));
    terminal_writestring("  ");
}
