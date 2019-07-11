// main.c -- Определяет точку входа Cи-кода ядра

#include "monitor.h"
#include "multiboot.h"
#include "descriptor_tables.h"
#include "timer.h"


int main(struct multiboot *mboot_ptr)
{
    // Initialise all the ISRs and segmentation
    init_descriptor_tables();
    // Initialise the screen (by clearing it)
    monitor_clear();
    // Write out a sample string
    monitor_write("Hello, world!\n");

    asm volatile("int $0x3");
    asm volatile("int $0x4");

    asm volatile("sti");
    init_timer(10);

    return 0;
}