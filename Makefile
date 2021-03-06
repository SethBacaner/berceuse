C_SOURCES = $(wildcard kern/*.c drivers/*.c lib/*.c arch_i386/cpu/*.c)
INCLUDE_DIR = include/
OBJ = ${C_SOURCES:.c=.o arch_i386/cpu/interrupt.o}

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
CFLAGS = -g
LINKER = /usr/local/i386elfgcc/bin/i386-elf-ld

GDB = /usr/local/i386elfgcc/bin/i386-elfgdb
QEMU = /usr/bin/qemu-system-i386

os-image.bin: arch_i386/boot/boot_sect.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: arch_i386/boot/start_kernel.o ${OBJ}
	${LINKER} -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: arch_i386/boot/start_kernel.o ${OBJ}
	${LINKER} -o $@ -Ttext 0x1000 $^

# Starts qemu in the background and waits for instruction from GDB.
# -S starts qemu and waits for instruction.
# -s is equivalent to -gdb tcp::1234.
debug: os-image.bin kernel.elf
	${QEMU} -S -s -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -I${INCLUDE_DIR} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -rf *.bin *.o os-image.bin *.elf
	rm -rf kern/*.o arch_i386/boot/*.bin drivers/*.o arch_i386/boot/*.o lib/*.o
