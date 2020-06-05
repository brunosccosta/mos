#include "../cpu/isr.h"

#include "../drivers/screen.h"

void kernel_main() {
    clear_screen();

    kprint("Welcome to MOS\n");
    
    isr_install();
    kprint("Interruptions enabled.\n");

    // Enabling IRQs
    irq_install();
    kprint("IRQs enabled.\n");

    kprint("\n\n> ");
}
