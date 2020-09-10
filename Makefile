# Makefile by Dan Green <danngreen1@gmail.com>
#

BINARYNAME 		= main

STARTUP 		= startup_stm32f732xx.s
SYSTEM 			= system_stm32f7xx.c
LOADFILE 		= STM32F732REx_FLASH.ld

DEVICE 			= stm32/device
CORE 			= stm32/core
PERIPH 			= stm32/periph

BUILDDIR 		= build

SOURCES  += $(wildcard $(PERIPH)/src/*.c)
SOURCES  += $(DEVICE)/src/$(STARTUP)
SOURCES  += $(DEVICE)/src/$(SYSTEM)
SOURCES  += $(wildcard src/*.c)
SOURCES  += $(wildcard src/*.cc)
SOURCES  += $(wildcard src/drivers/*.c)
SOURCES  += $(wildcard src/drivers/*.cc)

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

INCLUDES += -I$(DEVICE)/include \
			-I$(CORE)/include \
			-I$(PERIPH)/include \
			-Isrc \
			-Isrc/drivers \
			-Isrc/processors \
			-Isrc/util \

ELF 	= $(BUILDDIR)/$(BINARYNAME).elf
HEX 	= $(BUILDDIR)/$(BINARYNAME).hex
BIN 	= $(BUILDDIR)/$(BINARYNAME).bin

ARCH 	= arm-none-eabi
CC 		= $(ARCH)-gcc
CXX 	= $(ARCH)-g++
LD 		= $(ARCH)-g++
AS 		= $(ARCH)-as
OBJCPY 	= $(ARCH)-objcopy
OBJDMP 	= $(ARCH)-objdump
GDB 	= $(ARCH)-gdb
SZ 		= $(ARCH)-size

SZOPTS 	= -d

CPU = -mcpu=cortex-m7
FPU = -mfpu=fpv5-d16
FLOAT-ABI = -mfloat-abi=hard
MCU = $(CPU) -mthumb -mlittle-endian $(FPU) $(FLOAT-ABI)

ARCH_CFLAGS = -DARM_MATH_CM7 -D'__FPU_PRESENT=1' -DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER -DSTM32F732xx

OPTFLAG = -O3

CFLAGS = -g2 -fno-common \
	$(ARCH_CFLAGS) $(MCU) \
	-I. $(INCLUDES) \
	-fdata-sections -ffunction-sections \
	-lstdc++ \

CXXFLAGS=$(CFLAGS) \
	-std=c++17 \
	-fno-rtti \
	-fno-exceptions \
	-ffreestanding \
	-Werror=return-type \
	-Wdouble-promotion \
	-Wno-register \
	-fno-threadsafe-statics \
	-specs=nosys.specs \


AFLAGS = $(MCU)
#	-x assembler-with-cpp


LDSCRIPT = $(DEVICE)/$(LOADFILE)

LFLAGS =  -Wl,-Map,main.map,--cref \
	-Wl,--gc-sections \
	-lstdc++ \
	$(MCU) -specs=nosys.specs  -T $(LDSCRIPT) \


#----------------------------------
# Uncomment to compile unoptimized:
# build/src/main.o: OPTFLAG = -O0
# build/src/debug.o: OPTFLAG = -O0
# build/src/drivers/cap1203.o: OPTFLAG = -O0
# build/src/drivers/codec_i2sx2.o: OPTFLAG = -O0
# build/src/drivers/codec_i2c.o: OPTFLAG = -O0
# build/src/audio.o: OPTFLAG = -O0
# $(BUILDDIR)/$(PERIPH)/src/%.o: OPTFLAG = -O3

# rm compile_commands.json
# rm build/compile_commands.json
# compiledb -n make
# mv compile_commands.json build/

all: Makefile $(BIN) $(HEX)
# 	rm compile_commands.json
# 	rm build/compile_commands.json
# 	compiledb -n make
# 	mv compile_commands.json build/
# 	compdb -p build/ list > compile_commands.json 2>/dev/null

$(BIN): $(ELF)
	$(OBJCPY) -O binary $< $@
	$(OBJDMP) -x --syms $< > $(addsuffix .dmp, $(basename $<))
	ls -l $@ $<

$(HEX): $(ELF)
	$(OBJCPY) --output-target=ihex $< $@
	$(SZ) $(SZOPTS) $(ELF)

$(ELF): $(OBJECTS)
	$(LD) $(LFLAGS) -o $@ $(OBJECTS)

DEPFLAGS = -MMD -MP -MF $(BUILDDIR)/$(basename $<).d

$(BUILDDIR)/%.o: %.c $(BUILDDIR)/%.d
	mkdir -p $(dir $@)
	$(CC) -c $(DEPFLAGS) $(OPTFLAG) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc $(BUILDDIR)/%.d
	mkdir -p $(dir $@)
	$(CXX) -c $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@
# 	$(CXX) -c $(OPTFLAG) $(CXXFLAGS) -fverbose-asm -Wa,-adhln $< > $(BUILDDIR)/$(basename $<).lst

$(BUILDDIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(AS) $(AFLAGS) $< -o $@ > $(addprefix $(BUILDDIR)/, $(addsuffix .lst, $(basename $<)))

%.d: ;


tables:
	g++ tableGen/main.cpp -o tableGen/table
	tableGen/table

flash: $(BIN)
	st-flash write $(BIN) 0x8000000

clean:
	rm -rf build

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS) $(ELF)
.PHONY: all clean flash
