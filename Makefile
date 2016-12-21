OUTPUT=build
SOURCE=src
VPATH=src:$(SOURCE)

CC = clang
CFLAGS = -m32 --target=i686-pc-none-elf -march=i686 -fno-stack-protector -fno-builtin -nostdlib -nostdinc -Wall -Wextra -Werror -g

AS = nasm
ASFLAGS = -f elf

LD = gnu-ld
LDFLAGS = -melf_i386

OBJECTS=loader.o kmain.o \
		devices/framebuffer.o devices/serial.o \
		utils/io.o utils/monitor.o utils/log.o \
		memory/gdt_s.o memory/gdt.o

all: kernel.elf

kernel: link.ld $(OBJECTS)
	@$(LD) -T $< $(LDFLAGS) $(addprefix $(OUTPUT)/, $(OBJECTS)) -o $(OUTPUT)/kernel.elf

%.o: %.c
	@mkdir -p $(dir $(OUTPUT)/$@)
	@$(CC) $(CFLAGS) -c $< -o $(OUTPUT)/$@

%.o: %.asm
	@mkdir -p $(dir $(OUTPUT)/$@)
	@$(AS) $(ASFLAGS) $< -o $(OUTPUT)/$@

iso: kernel
	@cp $(OUTPUT)/kernel.elf iso/boot/kernel.elf
	@mkisofs -R \
			 -quiet \
	 		 -b boot/grub/stage2_eltorito \
			 -no-emul-boot \
			 -boot-load-size 4 \
			 -boot-info-table \
			 -o $(OUTPUT)/os.iso \
			 iso
	@rm iso/boot/kernel.elf

run: iso
	@qemu-system-i386 -cdrom $(OUTPUT)/os.iso -m 512 -serial stdio -serial vc -monitor vc

clean:
	@find $(OUTPUT) -name '*.o' -delete
	@rm -rf $(OUTPUT)/kernel.* $(OUTPUT)/os.iso
