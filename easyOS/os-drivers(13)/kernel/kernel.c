/* This will force us to create a kernel entry function instead of jumping to kernel.c:0x00 */
/* First function is always called (by boot sector) so stack frame will auto return and prevent unwated code to be executed*/
#include "../drivers/port-IO.h"
#include "../drivers/screen.h"
#include "util.h"

void Do_Nothing() {
}

void start() {
    /* Screen cursor position: ask VGA control register (0x3d4) for bytes
     * 14 = high byte of cursor and 15 = low byte of cursor. */
    port_byte_out(0x3d4, 14); // Requesting byte 14: high byte of cursor pos
    int position = port_byte_in(0x3d5); // Data is returned in VGA data register (0x3d5) 
    position = position << 8; // high byte of cursor pos

    port_byte_out(0x3d4, 15); // Requesting byte 15: low byte of cursor pos
    position += port_byte_in(0x3d5);

    // VGA 'cells' are [byte char][byte color] hence * 2
    int offset_from_vga = position * 2;

    // Let's write on the current cursor position, we already know how
    char *vga = (char*) 0xb8000;
    vga[offset_from_vga] = 'X'; 
    vga[offset_from_vga+1] = 0x0f; /* White text on black background */ 
    

    char* video_memory = (char*) 0xb8006;
    *video_memory = 'Z';
    video_memory += 0x1;
    *video_memory = 0x0a; //green

    clear_screen();
    char msg1[] = "123456789123456789123456789123456789dasdasd89";
    kprint_at(msg1, 0, 6);
    char msg2[] = "There is a line\nbreak";
    kprint(msg2);
    char msg3[] = "What happens when we run out of space?";
    kprint_at(msg3, 2, 24); // " " is a const char []/*  not char * 

    /*clear_screen();
    // Fill up the screen*/
    for (int i = 0; i < 24; i++) {
        char str[255]; //buffer size
        int_to_ascii(i, str);
        kprint_at(str, 0, i);
    }
    
    char msg4[] = "And with this text the kernel will scroll again and see what ca"; //64 is max size of string allowed
    kprint(msg4); //kprint breaks when text goes off screen right side
     char msg6[] = "And with this text the kernel will scroll again and see what ca"; //64 is max size of string allowed
    kprint(msg6);
    char msg7[] = "And with this text the kernel will scroll again and see what ca"; //64 is max size of string allowed
    kprint(msg7);
    // Cursor is lost when bottom is reached
    //char msg5[] = "This text forces the kernel to scroll. Row 0 will disappear.";
    //kprint_at(msg5, 60, 24);

    clear_screen();

    /* Fill up the screen */
    for (int i = 0; i < 24; i++) {
        char str[255];
        int_to_ascii(i, str);
        kprint_at(str, 0, i);
    }
    char msg8[]="This text forces the kernel to scroll. Row 0 will disappear.";
    kprint_at(msg8, 60, 24);
    char msg9[]="And with this text, the kernel will scroll again, and row 1 will disappear too!";//max char size is 64 so this dosent work
    kprint(msg9);
}