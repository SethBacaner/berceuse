C_SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJ = $(wildcard *.o)

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
GDB = /usr/local/i386elfgcc/bin/i386-elfgdb
LINKER = /usr/local/i386elfgcc/bin/i386-elf-ld

CFLAGS = -g

QEMU = /usr/bin/qemu-system-i386

os-image.bin: boot_sect.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: start_kernel.o ${OBJ}
	${LINKER} -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: start_kernel.o ${OBJ}
	${LINKER} -o $@ -Ttext 0x1000 $^
# -S starts and waits for instruction.
# -s is equivalent to -gdb tcp::1234
debug: os-image.bin kernel.elf
	${QEMU} -S -s -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.o os-bin.bin *.elf
