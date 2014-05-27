CC = arm-none-eabi-gcc
CFLAGS = -g -std=c99 -nostdlib -nostdinc -mthumb -mcpu=cortex-m4
LDFLAGS = -T startup.ld -Wl,--gc-sections

.SECONDARY:

.PHONY: all flash clean
all: image.bin

flash: image.bin
	@echo "reset halt\nflash write_image erase image.bin 0x08000000\nreset\nexit\n" | nc localhost 4444

image.elf: startup.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm *.o *.elf *.bin

%.bin: %.elf
	arm-none-eabi-objcopy -O binary $< $@
