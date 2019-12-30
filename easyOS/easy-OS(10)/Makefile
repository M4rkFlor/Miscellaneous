# $@ = target file
# $< = first dependency(Prerequisite)
# $^ = all dependencies

#MakeFile using MinGW
# First rule is the one executed when no parameters are fed to the Makefile
all: run

# Notice how dependencies are built as needed
kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel.c
	gcc -Wall -pedantic-errors -ffreestanding -c $< -o $@ -nostdlib

bootsect.bin: daMain_boot_secctor(10).asm
	nasm $< -f bin -o $@

kernel.tmp: kernel_entry.o kernel.o
	ld -T NUL -o $@ -Ttext 0x1000 -nostdlib $^

kernel.bin: kernel.tmp
	objcopy -O binary -j .text $< $@

os-image.img: bootsect.bin kernel.bin
	copy /b $<+$(word 2,$^) os-image.img

run: os-image.img
	make32 clean
	bochs

clean:
	del *.bin *.o *.dis