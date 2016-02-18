DEVICE        = atmega328p
CLOCK         = 16000000
PROGRAMMER    = -c arduino -b 115200 -P COM3
BUILD_DIR     = bin
SRC_DIR       = src
SRC_SUBDIRS   = $(wildcard $(SRC_DIR)/*/*)
BUILD_SUBDIRS = $(subst $(SRC_DIR),$(BUILD_DIR),$(SRC_SUBDIRS))
INCLUDES      = $(foreach include, $(wildcard $(SRC_DIR)/lib/*/), -I$(include))
SOURCES       = $(SRC_DIR)/main.c $(wildcard $(SRC_DIR)/lib/*/*.c)
OBJECTS       = $(subst $(SRC_DIR),$(BUILD_DIR),$(subst .c,.o,$(SOURCES)))
FUSES         = -U hfuse:w:0xde:m -U lfuse:w:0xff:m -U efuse:w:0x05:m

# Tune the lines below only if you know what you are doing:

AVRDUDE = avrdude $(PROGRAMMER) -p $(DEVICE)
COMPILE = avr-gcc -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE) $(INCLUDES)

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
	$(AVRDUDE) -U flash:w:main.hex:i

fuse:
	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

# if you use a bootloader, change the command below appropriately:
load: all
	bootloadHID main.hex

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
	$(COMPILE) -E main.c

test: test.hex
	$(AVRDUDE) -U flash:w:test.hex:i
