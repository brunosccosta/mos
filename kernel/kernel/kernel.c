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
void kernel_main()
{
    /* Initialize terminal interface */
    terminal_initialize();

    /* Since there is no support for newlines in terminal_putchar
     * yet, '\n' will produce some VGA specific character instead.
     * This is normal.
     */
    terminal_writestring("Welcome to MOS\n");
    terminal_writestring("M Operating System\n\n\n");
    
    terminal_writestring("Testing colors...\n");
    test_colors();
}

void test_colors()
{
	terminal_writestring_color("  ", COLOR_BLACK, COLOR_BLACK);
    terminal_writestring_color("  ", COLOR_BLACK, COLOR_BLUE);
    terminal_writestring_color("  ", COLOR_BLACK, COLOR_GREEN);
    terminal_writestring_color("  ", COLOR_BLACK, COLOR_CYAN);
    terminal_writestring_color("  ", COLOR_BLACK, COLOR_RED);
    terminal_writestring_color("  ", COLOR_BLACK, COLOR_MAGENTA);
    terminal_writestring_color("  ", COLOR_BLACK, COLOR_BROWN);
    terminal_writestring_color("  ", COLOR_BLACK, COLOR_WHITE);
}
