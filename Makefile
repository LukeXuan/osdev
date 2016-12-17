OUTPUT=build
SOURCE=src
VPATH=src:$(SOURCE)

CC = clang
CFLAGS = -m32 --target=i686-pc-none-elf -march=i386 -fno-stack-protector -fno-builtin -nostdlib -nostdinc -Wall -Wextra -Werror

AS = nasm
ASFLAGS = -f elf

LD = gnu-ld
LDFLAGS = -melf_i386

OBJECTS=loader.o kmain.o display/framebuffer.o util/io.o display/monitor.o

all: kernel.elf

kernel.elf: link.ld $(OBJECTS)
	@$(LD) -T $< $(LDFLAGS) $(addprefix $(OUTPUT)/, $(OBJECTS)) -o $(OUTPUT)/kernel.elf

%.o: %.c
	@mkdir -p $(dir $(OUTPUT)/$@)
	@$(CC) $(CFLAGS) -c $< -o $(OUTPUT)/$@

%.o: %.asm
	@mkdir -p $(dir $(OUTPUT)/$@)
	@$(AS) $(ASFLAGS) $< -o $(OUTPUT)/$@

iso: kernel.elf
	@cp $(OUTPUT)/kernel.elf iso/boot/kernel.elf
	@mkisofs -R \
	 		 -b boot/grub/stage2_eltorito \
			 -no-emul-boot \
			 -boot-load-size 4 \
			 -boot-info-table \
			 -o $(OUTPUT)/os.iso \
			 iso
	@rm iso/boot/kernel.elf

run: iso
	qemu-system-i386 -cdrom $(OUTPUT)/os.iso -m 512 -monitor stdio

clean:
	@find $(OUTPUT) -name '*.o' -delete
	@rm -rf $(OUTPUT)/kernel.elf $(OUTPUT)/os.iso
