#include "shell.h"

#include <stdint.h>

#include "../drivers/screen.h"

#include "../libc/string.h"
#include "../libc/mem.h"

void cmd_end() {
    kprint("Stopping the CPU. Bye!\n");
    asm volatile("hlt");
}

void cmd_page() {
    /* Lesson 22: Code to test kmalloc, the rest is unchanged */
    uint32_t phys_addr;
    uint32_t page = kmalloc(1000, 1, &phys_addr);
    char page_str[16] = "";
    hex_to_ascii(page, page_str);
    char phys_str[16] = "";
    hex_to_ascii(phys_addr, phys_str);
    kprint("Page: ");
    kprint(page_str);
    kprint(", physical address: ");
    kprint(phys_str);
    kprint("\n");
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        cmd_end();
        return;
    }
    if (strcmp(input, "PAGE") == 0) {
        cmd_page();
        return;
    }

    kprint("Command ");
    kprint(input);
    kprint(" unknown");

    kprint("\n> ");
}
