// Read/Write a byte/word from the specified port

/* Inline assembler syntax
Source and destination registers are switched from NASM
"=a" (result) , set (result) to the value of register e'a'x
"d" (port) , map (port) into e'd'x register
asm : output : inputs
The IN instruction reads from an I/O device, OUT writes to I/O device
 */
unsigned char port_byte_in (unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void port_byte_out (unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_word_in (unsigned short port) {
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return result;
}

void port_word_out (unsigned short port, unsigned short data) {
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}