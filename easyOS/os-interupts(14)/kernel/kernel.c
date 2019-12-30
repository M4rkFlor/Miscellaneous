/*Made following tutorials from */
/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
/* First function is always called (by boot sector) so stack frame will auto return and prevent unwated code to be executed*/
#include "../drivers/port-IO.h"
#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "util.h"

void Do_Nothing() {
}

void start() {
    clear_screen();

    /* Fill up the screen */
/*    for (int i = 0; i < 24; i++) {
        char str[255];
        int_to_ascii(i, str);
        kprint_at(str, 0, i);
    }
    char msg8[]="This text forces the kernel to scroll. Row 0 will disappear.";
    kprint_at(msg8, 60, 24);
    //char msg9[]="And with this text, the kernel will scroll again, and row 1 will disappear too!";//max char size is 64 so this dosent work
    //kprint(msg9);
*/
    isr_install();
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $4");
}