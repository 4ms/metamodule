# Makefile by Dan Green <danngreen1@gmail.com>
#

BINARYNAME 		= main

STARTUP 		= startup_stm32f730xx.s
SYSTEM 			= system_stm32f7xx.c
LOADFILE 		= STM32F730V8x_FLASH.ld

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

INCLUDES += -I$(DEVICE)/include \
			-I$(CORE)/include \
			-I$(PERIPH)/include \
			-I src \
			-I src/drivers \

ELF 	= $(BUILDDIR)/$(BINARYNAME).elf
HEX 	= $(BUILDDIR)/$(BINARYNAME).hex
BIN 	= $(BUILDDIR)/$(BINARYNAME).bin

ARCH 	= arm-none-eabi
CC 		= $(ARCH)-gcc
LD 		= $(ARCH)-gcc
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

ARCH_CFLAGS = -DARM_MATH_CM7 -D'__FPU_PRESENT=1' -DUSE_HAL_DRIVER -DSTM32F730xx

OPTFLAG = -O3

CFLAGS = -g2 -fno-common \
	$(ARCH_CFLAGS) $(MCU) \
	-I. $(INCLUDES) \
	-fdata-sections -ffunction-sections \
	-specs=nano.specs \

CXXFLAGS=$(CFLAGS) \
	-std=c++17 \
	-fno-rtti \
	-fno-exceptions \
	-ffreestanding \
	-Werror=return-type \
	-Wdouble-promotion \
	-Wno-register \


AFLAGS = $(MCU)
#	-x assembler-with-cpp


LDSCRIPT = $(DEVICE)/$(LOADFILE)

LFLAGS =  -Wl,-Map,build/main.map,--cref \
	-Wl,--gc-sections \
	$(MCU) -specs=nano.specs  -T $(LDSCRIPT)


#-----------------------------------
# Uncomment to compile unoptimized:

build/src/main.o: OPTFLAG = -O0
build/src/drivers/codec_i2sx2.o: OPTFLAG = -O0
build/src/drivers/codec_i2c.o: OPTFLAG = -O0
build/src/audio.o: OPTFLAG = -O0

$(BUILDDIR)/$(PERIPH)/src/%.o: OPTFLAG = -O0

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


$(BUILDDIR)/%.o: %.c $(wildcard src/*.h) $(wildcard src/drivers/*.h)
	mkdir -p $(dir $@)
	$(CC) -c $(OPTFLAG) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc $(wildcard src/*.h) $(wildcard src/drivers/*.h)
	mkdir -p $(dir $@)
	$(CC) -c $(OPTFLAG) $(CXXFLAGS) $< -o $@


$(BUILDDIR)/%.o: %.s
	mkdir -p $(dir $@)
	$(AS) $(AFLAGS) $< -o $@ > $(addprefix $(BUILDDIR)/, $(addsuffix .lst, $(basename $<)))


flash: $(BIN)
	st-flash write $(BIN) 0x8000000

clean:
	rm -rf build
