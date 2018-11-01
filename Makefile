HEADERS =
OBJECTS = build/main.o build/cpu.o build/mem.o build/hardware.o build/keypad.o build/menu.o build/lang.o build/instructions.o build/irq.o build/exception.o
CPPFILES =
# SOURCES = src/main.c src/mem.c src/cpu.c src/hardware.c src/keypad.c
ASM =
CFLAGS = -DHRT_WITH_LIBHEART -Wall -Ofast -march=armv4t -Wno-switch -Wno-multichar -ffast-math -mlong-calls -mcpu=arm7tdmi -mtune=arm7tdmi -marm -faggressive-loop-optimizations -fverbose-asm 
ARCH = -mthumb -mthumb-interwork
SPECS = -specs=gba.specs
PREFIX = C:\devkitPro\devkitARM\bin\arm-none-eabi-

default: pocketmini.gba

build/%.o: src/%.c $(HEADERS)
	$(PREFIX)gcc $(CFLAGS) -Iinc $(ARCH) -c $< -o $@
	
build/%.o: src/%.cpp $(HEADERS)
	$(PREFIX)g++ $(CFLAGS) $(ARCH) -c $< -o $@
	
build/%.out: src/%.s
	$(PREFIX)as  -mthumb -mthumb-interwork -mcpu=arm7tdmi $< -o $@
	
build/main.elf: $(OBJECTS)
	$(PREFIX)gcc $(SPECS) $(ARCH) $(OBJECTS) -lheart -lm -o build/main.elf
	
pocketmini.gba: build/main.elf
	$(PREFIX)objcopy -O binary build/main.elf pocketmini.gba
	C:/devkitPro/devkitARM/bin/gbafix pocketmini.gba -tPOKEMONMINI -cPKMU -v1
	

clean:
	-rm build/*.o build/*.out build/main.elf
	-rm pocketmini.gba