# Makefile by Dan Green <danngreen1@gmail.com>
#

BINARYNAME 		= main
LIBDIR 			= lib
STARTUP 		= startup_stm32f746xx.s
SYSTEM 			= system_stm32f7xx.c
LOADFILE 		= STM32F746ZGTx_FLASH.ld

DEVICE 			= $(LIBDIR)/stm32/device
CORE 			= $(LIBDIR)/stm32/core
PERIPH 			= $(LIBDIR)/stm32/periph
DRIVERLIB       = $(LIBDIR)/mdrivlib

BUILDDIR 		= build

SOURCES  += $(DEVICE)/src/$(STARTUP)
SOURCES  += $(DEVICE)/src/$(SYSTEM)
SOURCES  += $(wildcard $(PERIPH)/src/*.c)
SOURCES  += $(wildcard $(DRIVERLIB)/drivers/*.c)
SOURCES  += $(wildcard $(DRIVERLIB)/drivers/*.cc)
SOURCES  += $(wildcard $(DRIVERLIB)/drivers/*.cpp)
SOURCES  += $(wildcard src/*.c)
SOURCES  += $(wildcard src/*.cc)
SOURCES  += $(wildcard src/*.cpp)
SOURCES  += $(wildcard src/sys/*.c)
SOURCES  += $(wildcard src/sys/*.cc)
SOURCES  += $(wildcard src/sys/*.cpp)
SOURCES  += $(wildcard src/util/*.c)
SOURCES  += $(wildcard src/util/*.cc)
SOURCES  += $(wildcard src/util/*.cpp)
SOURCES  += $(wildcard src/processors/*.c)
SOURCES  += $(wildcard src/processors/*.cc)
SOURCES  += $(wildcard src/processors/*.cpp)

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

INCLUDES += -I$(DEVICE)/include \
			-I$(CORE)/include \
			-I$(PERIPH)/include \
			-I$(DRIVERLIB) \
			-I$(LIBDIR)/easiglib \
			-Isrc \
			-Isrc/processors \
			-Isrc/util \
			-Isrc/conf \

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

ARCH_CFLAGS = -DARM_MATH_CM7 \
			  -D'__FPU_PRESENT=1' \
			  -DUSE_HAL_DRIVER \
			  -DUSE_FULL_LL_DRIVER \
			  -DSTM32F746xx \
			  -DSTM32F7

OPTFLAG = -O3

CFLAGS = -g2 -fno-common \
	$(ARCH_CFLAGS) $(MCU) \
	-I. $(INCLUDES) \
	-fdata-sections -ffunction-sections \
	-nostdlib \
	-nostartfiles \

CXXFLAGS=$(CFLAGS) \
	-std=c++2a \
	-fno-rtti \
	-fno-exceptions \
	-fno-unwind-tables \
	-ffreestanding \
	-fno-threadsafe-statics \
	-Werror=return-type \
	-Wdouble-promotion \
	-Wno-register \
	-nostdlib \
	-nostartfiles \

AFLAGS = $(MCU)
#	-x assembler-with-cpp


LDSCRIPT = $(DEVICE)/$(LOADFILE)

LFLAGS =  -Wl,-Map,$(BUILDDIR)/main.map,--cref \
	-Wl,--gc-sections \
	-nostdlib \
	-nostartfiles \
	$(MCU) \
	-T $(LDSCRIPT) \


#----------------------------------
# Uncomment to compile unoptimized:
# build/src/main.o: OPTFLAG = -O0
# build/src/debug.o: OPTFLAG = -O0
# build/src/drivers/cap1203.o: OPTFLAG = -O0
# build/src/drivers/codec_i2sx2.o: OPTFLAG = -O0
# build/src/drivers/codec_i2c.o: OPTFLAG = -O0
# build/src/audio.o: OPTFLAG = -O0
# $(BUILDDIR)/$(PERIPH)/src/%.o: OPTFLAG = -O3

all: Makefile $(BIN) $(HEX)

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

$(BUILDDIR)/%.hh.gch: %.hh
	mkdir -p $(dir $@)
	$(CXX) -c -x c++-header $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.h.gch: %.h
	mkdir -p $(dir $@)
	$(CXX) -c -x c++-header $(CXXFLAGS) $< -o $@

%.d: ;

tables src/processors/wavefold_tables.h: tableGen/main.cpp
	g++ tableGen/main.cpp -o tableGen/make_tables
	tableGen/make_tables

flash: $(BIN)
	st-flash write $(BIN) 0x8000000

clean:
	rm -rf build

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS) $(ELF) $(PRECHDRS)
.PHONY: all clean flash

generate_compile_txt:
	arm-none-eabi-gcc -E -x c++ - -v < /dev/null 2>&1 | \
    awk '/End of search list./ { show=0 } { if (show) printf "-I%s\n",$1 }; /#include <...> search starts here:/ { show=1; }' > compile_flags.txt

# bear: brew install bear
# compdb: pip install compdb (https://github.com/Sarcasm/compdb)
generate_build_flags:
	rm -rf build
	bear make -j16 all
	compdb -p ./ list > compile_commands_with_headers.json 2>/dev/null
	rm compile_commands.json 
	mv compile_commands_with_headers.json compile_commands.json
