[org 0x7c00] ; bootloader offset
    KERNEL_OFFSET equ 0x1000 ; The same one we used when linking the kernel*
    mov [BOOT_DRIVE], dl ; BIOS sets us the boot drive in 'dl' on boot
    mov bp, 0x9000 ; set the stack to not conflict with IVT
    mov sp, bp

    mov bx, MSG_REAL_MODE
    call print_string_rm ; This will be written after the BIOS messages
    call print_NL_rm

    call load_kernel ; read the kernel from disk
    call switch_to_pm ; may want to switch to long mode if able to https://wiki.osdev.org/Entering_Long_Mode_Directly#Notes_about_the_above_code.
    ;jumps to BEGIN_PM

%include "GDT.asm"
%include "print_string_rm.asm"
%include "print_string_pm.asm"
%include "switch_to_pm.asm"
%include "disk_load.asm"
;print hex?
[bits 16]
load_kernel:
    mov bx, KERNEL_OFFSET ; Read from disk and store in 0x1000
    mov dh, 2 ; load 2 sectors to bx
    mov dl, [BOOT_DRIVE] ; the drive to read
    call disk_load

    mov bx, MSG_LOAD_KERNEL
    call print_string_rm
    

    ret
[bits 32]
BEGIN_PM: ; switch_to_pm calls here at the end
    mov ebx, MSG_PROT_MODE
    call print_string_pm ; Note that this will be written at the top left corner
    call KERNEL_OFFSET ; Go to the kernel
    jmp $

BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit real mode", 0
MSG_LOAD_KERNEL db "Loaded kernel into memory", 0
MSG_PROT_MODE db "Loaded 32-bit protected mode", 0
; bootsector padding , each sector is 512 bytes
times 510-($-$$) db 0
dw 0xaa55