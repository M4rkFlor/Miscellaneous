;CS	Code Segment
;DS	Data Segment
;SS	Stack Segment
;ES	Extra Segment
;FS	General Purpose Segments
;GS General Purpose Segments
mov ah, 0x0e ; int 10h/ ah = 0eh -> scrolling teletype BIOS routine

mov al, [the_secret]
int 0x10 ; correct offset to secret but is from the start of memory(memory accsesd absolutley), should be from the start of the boot sector

mov bx, 0x7c0 ; remember, the segment is automatically bx << 4 == bx * 16 == 0x7c00
mov ds, bx
; WARNING: from now on all memory references will be offset by 'ds' implicitly
mov al, [the_secret]
int 0x10 ;start of boot sector + ofset to secret

mov al, [es:the_secret]
int 0x10 ; doesn't look right... isn't 'es' currently 0x000? only one segment is applied (es), same as [the_secret] wont work

mov bx, 0x7c0
mov es, bx
mov al, [es:the_secret]
int 0x10 ;explicity use es segment instead of ds, works

jmp $

the_secret: db "X"

times 510 - ($-$$) db 0
dw 0xaa55