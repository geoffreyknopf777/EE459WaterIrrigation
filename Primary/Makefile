DEVICE        = atmega328p
CLOCK         = 7372800
PROGRAMMER    = -c usbtiny -P usb
BUILD_DIR     = bin
SRC_DIR       = src
SRC_SUBDIRS   = $(wildcard $(SRC_DIR)/*)
BUILD_SUBDIRS = $(subst $(SRC_DIR),$(BUILD_DIR),$(SRC_SUBDIRS))
INCLUDES      = $(foreach include, $(wildcard $(SRC_DIR)/*/), -I$(include))
SOURCES       = $(wildcard $(SRC_DIR)/*/*.c)
OBJECTS       = $(subst $(SRC_DIR),$(BUILD_DIR),$(subst .c,.o, $(SOURCES))) 
$(info $(OBJECTS))
FUSES         = -U hfuse:w:0xd9:m -U lfuse:w:0xe0:m

# Fuse Low Byte = 0xe0   Fuse High Byte = 0xd9   Fuse Extended Byte = 0xff
# Bit 7: CKDIV8  = 1     Bit 7: RSTDISBL  = 1    Bit 7:
#     6: CKOUT   = 1         6: DWEN      = 1        6:
#     5: SUT1    = 1         5: SPIEN     = 0        5:
#     4: SUT0    = 0         4: WDTON     = 1        4:
#     3: CKSEL3  = 0         3: EESAVE    = 1        3:
#     2: CKSEL2  = 0         2: BOOTSIZ1  = 0        2: BODLEVEL2 = 1
#     1: CKSEL1  = 0         1: BOOTSIZ0  = 0        1: BODLEVEL1 = 1
#     0: CKSEL0  = 0         0: BOOTRST   = 1        0: BODLEVEL0 = 1
# External clock source, start-up time = 14 clks + 65ms
# Don't output clock on PORTB0, don't divide clock by 8,
# Boot reset vector disabled, boot flash size 2048 bytes,
# Preserve EEPROM disabled, watch-dog timer off
# Serial program downloading enabled, debug wire disabled,
# Reset enabled, brown-out detection disabled

# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-g++ -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) $(INCLUDES)
#COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) $(INCLUDES)

# Define a newline character to separate operations in a foreach loop
define \n


endef

# symbolic targets:
all:	main.hex

# Map source files in the SRC_DIR to object files in the BUILD_DIR
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	@$(foreach dir, $(BUILD_SUBDIRS), @mkdir -p $(dir)${\n}) 
	$(COMPILE) -c $< -o $@
	
.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:$(BUILD_DIR)/main.hex:i
	
	#open up a uart terminal
	echo screen "$(ls /dev/tty.usb*)" 9600 > uart.command; chmod +x uart.command; open uart.command

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID $(BUILD_DIR)/main.hex

clean:
	rm -rf $(BUILD_DIR)

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o $(BUILD_DIR)/main.elf $(OBJECTS)

main.hex: main.elf
	rm -f $(BUILD_DIR)/main.hex
	avr-objcopy -j .text -j .data -O ihex $(BUILD_DIR)/main.elf $(BUILD_DIR)/main.hex
	avr-size --format=avr --mcu=$(DEVICE) $(BUILD_DIR)/main.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
disasm:	main.elf
	avr-objdump -d $(BUILD_DIR)/main.elf

cpp:
	$(COMPILE) -E $(SRC_DIR)/main/main.c

test: test.hex
	$(AVRDUDE) -U flash:w:test.hex:i
