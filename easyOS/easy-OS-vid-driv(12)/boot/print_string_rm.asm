print_string_rm:
    pusha
    start:
        mov al, [bx] ; 'bx' is the base address for the string
        cmp al, 0 
        je done
        mov ah, 0x0e
        int 0x10 ; 'al' already contains the char
        add bx, 1 ; inc string pointer
        jmp start
    done:
        popa
        ret

print_NL_rm:
    pusha
    mov ah, 0x0e
    mov al, 0x0a ; newline char
    int 0x10
    mov al, 0x0d ; carriage return
    int 0x10
    popa
    ret