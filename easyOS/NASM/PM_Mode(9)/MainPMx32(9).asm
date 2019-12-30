[org 0x7c00] ; bootloader offset
    mov bp, 0x9000 ; set the stack to not conflict with IVT
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print_string_rm ; This will be written after the BIOS messages

    call switch_to_pm ; may want to switch to long mode if able to https://wiki.osdev.org/Entering_Long_Mode_Directly#Notes_about_the_above_code.
    ;jumps to BEGIN_PM

%include "GDT.asm"
%include "print_string_rm.asm"
%include "print_string_pm.asm"
%include "switch_to_pm.asm"

[bits 32]
BEGIN_PM: ; switch_to_pm calls here at the end
    mov ebx, MSG_PROT_MODE
    call print_string_pm ; Note that this will be written at the top left corner
    jmp $

MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
; bootsector padding
times 510-($-$$) db 0
dw 0xaa55