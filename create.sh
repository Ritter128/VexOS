nasm -f elf64 src/multibooter.asm -o build/multibooter.o
nasm -f elf64 src/main.asm -o build/main.o
nasm -f elf64 src/main64.asm -o build/main64.o
gcc src/kernel/kernel.c src/kernel/kernel.h -ffreestanding -c
ld -n -o kernel.bin -T linker.ld build/multibooter.o build/main.o build/main64.o kernel.o
rm kernel.o
cp kernel.bin iso/boot
grub-mkrescue -o vexos.iso iso
qemu-system-x86_64 vexos.iso
