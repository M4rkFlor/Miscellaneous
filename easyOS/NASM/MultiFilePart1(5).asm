;
; Functions using multi File
; Protects register values to prevent from incrementing such as line 12
; Allows al to remain G throughout the program
mov al , "A" ; pass A as arg
call my_print_function
call my_print_function
call my_print_function
jmp END
%include "MultiFilePart2(5).asm"
; print function from other file
;
END:
jmp $ ;loop forever
; Padding and magic number.
times 510 -( $ - $$ ) db 0
dw 0xaa55