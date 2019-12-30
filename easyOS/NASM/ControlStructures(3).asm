;mov bx , 30
;if (bx <= 4) {
;mov al , ’A ’
;} 
;else if (bx < 40) {
;mov al , ’B ’
;} 
;else {
;mov al , ’C ’
;}
;//////////
;//Converted C code///
;//////////
mov bx , 40
cmp bx , 4
jle IF ; if bx <= 4
cmp bx , 40
jl ELSE_IF ; else if bx < 40
mov al , "C" ; else here
jmp END
IF: mov al , "A"
jmp END
ELSE_IF: mov al , "B"
END:
mov ah , 0x0e ; int =10/ ah =0x0e -> BIOS tele - type output
int 0x10 ; print the character in al
jmp $ ;loop forever
; Padding and magic number.
times 510 -( $ - $$ ) db 0
dw 0xaa55