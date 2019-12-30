;http://www.brokenthorn.com/Resources/OSDev8.html good documentation on each individual bit.
gdt_start: ; don't remove the labels, they're needed to compute sizes and jumps
    dq 0 ; the GDT starts with a null 8-byte

; GDT for code segment. base = 0x00000000, length = 0xfffff
gdt_code: ; cs should point to this descriptor with something like jmp 0x8:gdt_code
    dw 0xffff    ; Limit or segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10011010b ; flags (8 bits) , bit 3 is 1 for code selector
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

gdt_data:   ; GDT for data segment. base and length identical to code segment (overlap)
    dw 0xffff       ; limit low
    dw 0x0          ; base low
    db 0x0          ; base middle
    db 10010010b    ; access , bit 3 is 0 for data selector
    db 11001111b    ; granularity
    db 0x0          ; base high

gdt_end: ; label for size calculation
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; Limit (Size of GDT, 16 bits), always one less of its true size
    dd gdt_start ; base address of GDT (32 bit)

; define some constants for later use
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start