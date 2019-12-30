; print hex
org 0x7c00 ;directive so [Label] works
mov dx , 0x1fb6 ; store the value to print in dx
call print_hex ; call the function
jmp END
; prints the value of DX as hex.
print_hex:
    pusha
    ; TODO : manipulate chars at HEX_OUT to reflect dx
    mov bx , HEX_OUT ; pass a pointer to string buffer to save hex in bx
    call save_hex_to_string_buffer
    mov bx , HEX_OUT ; print the string pointed to
    call print_string ; by BX
    popa
    ret
    ; Funtions bellow
    save_hex_to_string_buffer:
        pusha
        mov cl , 0 ;set cl and ch index to 0
        mov al , "0" ; start string with 0x
        mov [bx], al
        add bx , 1 ; increment string pointer
        mov al , "x"
        mov [bx], al
        add bx , 1 ; increment string pointer
        mov ax , 0 ; hex temp
        convert_hex_to_string:
            cmp cl , 4 ; numcharacters to convert
            jge done
            mov ax,dx ;copy hex to temp to manipulate
            cmp cl , 0 ;apparently shl can only use 2 registers if using cl as count
            je ZERO
            cmp cl , 1
            je FOUR
            cmp cl , 2
            je EIGHT
            cmp cl , 3
            je TWELVE
            jmp END_IF
            ZERO:
            shl ax , 0
            jmp END_IF
            FOUR:
            shl ax , 4
            jmp END_IF
            EIGHT:
            shl ax , 8
            jmp END_IF
            TWELVE:
            shl ax , 12
            jmp END_IF
            END_IF:
            shr ax , 12
            add al , 48 ; offset to Digit ascii codes
            cmp al , 57 ;add 7 if al >  57
            jg ASCII_OFFSET
            jmp ASCII_DONE
            ASCII_OFFSET:
            add al , 7
            jmp ASCII_DONE
            ASCII_DONE:
            mov [bx], al
            add bx , 1 ; increment string pointer
            add cl , 1
            jmp convert_hex_to_string
        done:
        popa
        ret
    print_string: ; print string with pointer bx
        pusha ; Push all register values to the stack
        mov cl , 0 ;set index to 0
        Loop:
            cmp cl , 6 ;print 5 chars
            jge EndLoop
            mov al , [bx]; value to print
            add bx , 1 ; increment string pointer
            mov ah , 0x0e ; int =10/ ah =0x0e -> BIOS tele - type output
            int 0x10 ; print the character in al
            add cl , 1
            jmp Loop
        EndLoop:
        popa ; Restore original register values
        ret ;exit print string
HEX_OUT: db "0x0000" ,0
END:
jmp $ ; Jump forever.
; Padding and magic BIOS number.
times 510 -( $ - $$ ) db 0
dw 0xaa55