; A simple boot sector program that outputs text.
; need interrupt 0x10 and to set ah to 0x0e (to indicate tele-type mode) and
; al to the ASCII code of the character we wish to print.
org 0x7c00
mov ah , 0x0e ; int 10/ ah = 0eh -> scrolling teletype BIOS routine
;
; First attempt
mov al , my_string ;adress value of label not value of string
int 0x10 ; Does this print an X? NO
;
; Second attempt
mov al , [my_string] ;contents of adress
int 0x10 ; Does this print an X? YES only with org directive
;
; Third attempt
mov bx , my_string
add bx , 0x7c00;bootsector starts at this adress
mov al , [bx]
int 0x10 ; Does this print an X? Yes without org directive
;
; Fourth attempt
mov al , [0x7c1e]
int 0x10 ; Does this print an X? Yes without org directive, needs to be manualy changed depending on instriction count.
;
jmp $ ; Jump forever.
my_string: db "Booting The OS...",0;the convention is to declare strings as 'null-terminating', which means we always declare the last byte of the string as 0
times 510 -( $ - $$ ) db 0 ; When compiled , our program must fit into 512 bytes ,
; 510th byte here.
dw 0xaa55 ; Last two bytes ( one word ) form the magic number, so BIOS knows we are a boot sector.
;Bocsh.exe to run boot_sect.bin