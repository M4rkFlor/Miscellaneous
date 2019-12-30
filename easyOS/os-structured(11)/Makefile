# $@ = target file
# $< = first dependency(Prerequisite)
# $^ = all dependencies

C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

#MakeFile using MinGW
# First rule is the one executed when no parameters are fed to the Makefile
all : os-image.img

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	gcc -Wall -pedantic-errors -ffreestanding -c $< -o $@ -nostdlib

%.o: %.asm
	nasm $< -f  elf -o $@

%.bin: %.asm
	nasm $< -f bin -I './boot/' -o $@

# Dependencies are built as needed
kernel.tmp: boot/kernel_entry.o ${OBJ}
	ld -T NUL -o $@ -Ttext 0x1000 -nostdlib $^

kernel.bin: kernel.tmp
	objcopy -O binary -j .text $< $@

os-image.img: boot/bootsect.bin kernel.bin
	copy /b ".\boot\bootsect.bin"+"$(word 2,$^)" os-image.img

clean:
	del /S *.bin *.o *.tmp *.dis