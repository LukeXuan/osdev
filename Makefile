OUTPUT=build
SOURCE=src

CC = clang
CFLAGS = -m32 --target=i686-pc-none-elf -march=i386 -fno-stack-protector -fno-builtin -nostdlib -nostdinc -Wall -Wextra -Werror

AS = nasm
ASFLAGS = -f elf

LD = gnu-ld
LDFLAGS = -T $(SOURCE)/link.ld -melf_i386

OBJECTS=loader.o kmain.o display/framebuffer.o util/io.o display/monitor.o

all: kernel.elf

kernel.elf: $(addprefix $(OUTPUT)/, $(OBJECTS))
	$(LD) $(LDFLAGS) $(addprefix $(OUTPUT)/, $(OBJECTS)) -o $(OUTPUT)/kernel.elf

$(OUTPUT)/%.o: $(SOURCE)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OUTPUT)/%.o: $(SOURCE)/%.asm
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

iso: kernel.elf
	@cp $(OUTPUT)/kernel.elf iso/boot/kernel.elf
	mkisofs -R \
			-b boot/grub/stage2_eltorito \
			-no-emul-boot \
			-boot-load-size 4 \
			-boot-info-table \
			-o $(OUTPUT)/os.iso \
			iso

run: iso
	qemu-system-i386 -cdrom $(OUTPUT)/os.iso -m 512 -monitor stdio

clean:
	find $(OUTPUT) -name '*.o' -delete
	rm -rf $(OUTPUT)/kernel.elf $(OUTPUT)/os.iso
