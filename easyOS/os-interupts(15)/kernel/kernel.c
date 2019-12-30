/*Made following tutorials from */
/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
/* First function is always called (by boot sector) so stack frame will auto return and prevent unwated code to be executed*/
#include "../drivers/port-IO.h"
#include "../drivers/screen.h"
#include "../drivers/keyboard.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "util.h"

void Do_Nothing() {
}

void start() {
    /*IMPORTANT WEIRD BEHAVIOR CAN BE CAUSE BY NOT READING ENOUGH SECTORS 50 x 512 = 25.6 KB*/
    clear_screen();

    isr_install();
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $4");
    asm volatile("sti");
    //init_timer(50);
    /* Comment out the timer IRQ handler to read
     * the keyboard IRQs easier */
    init_keyboard();
}