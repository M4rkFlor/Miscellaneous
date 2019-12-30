;
; Functions using pusha popa
; Protects register values to prevent from incrementing such as line 12
; Allows al to remain G throughout the program
mov al , "G" ; pass G as arg
call my_print_function
call my_print_function
call my_print_function
jmp END
my_print_function:
pusha ; Push all register values to the stack
add al , 1 ;increment ASCII CODE G -> H
mov ah , 0x0e ; int =10/ ah =0x0e -> BIOS tele - type output
int 0x10 ; print the character in al
popa ; Restore original register values
ret
;
END:
jmp $ ;loop forever
; Padding and magic number.
times 510 -( $ - $$ ) db 0
dw 0xaa55