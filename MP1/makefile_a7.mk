# Makefile by Dan Green <danngreen1@gmail.com>, public domain

$(info Building for A7 core)
BUILDDIR = $(BUILDDIR_A7)
LOADFILE = stm32mp15xx_ca7.ld
MCU = #-mcpu=cortex-a7 -mfpu=? -mthumb -mlittle-endian -mfloat-abi=?
ARCH_CFLAGS = -DCORE_CA7 -DSTM32MP157Cxx #-DARM_MATH_CA7
CORE_SRC = src/a7
HAL_CONF_INC = src/a7

OPTFLAG = -O0
include makefile_opts.mk

####
BINARYNAME = app
UIMAGENAME = bare-arm.uimg
LOADADDR 	= 0xC2000040
ENTRYPOINT 	= $(LOADADDR)
UBOOTDIR =../u-boot-stm32mp-2020.01-r0/build_baremetal
#####

SOURCES = $(DRIVERLIB)/drivers/$(STARTUP_CA7) \
		  app.c

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

INCLUDES = -I. \
		   -IDrivers/STM32MP1xx_HAL_Driver/Inc \
		   -IDrivers/CMSIS/Core_A/Include \
		   -IDrivers/CMSIS/Device/ST/STM32MP1xx/Include \

AFLAGS = $(MCU)

CFLAGS = -g2 \
		 -nostdlib \
		 -nostartfiles \
		 $(ARCH_CFLAGS) \
		 $(MCU) \
		 $(INCLUDES) \
		 -fno-common \
		 -fdata-sections -ffunction-sections \

CXXFLAGS = $(CFLAGS) \
		-std=c++2a \
		-fno-rtti \
		-fno-exceptions \
		-fno-unwind-tables \
		-ffreestanding \
		-fno-threadsafe-statics \
		-Werror=return-type \
		-Wdouble-promotion \
		-Wno-register \
		-Wno-volatile \

LFLAGS = -T $(DEVICE)/$(LOADFILE) \
	-Wl,--gc-sections \
	-Wl,-Map,$(BUILDDIR)/$(BINARYNAME).map,--cref \
	$(MCU)  \
	-nostdlib \
	-nostartfiles \

DEPFLAGS = -MMD -MP -MF $(BUILDDIR)/$(basename $<).d

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

ELF 	= $(BUILDDIR)/$(BINARYNAME).elf
HEX 	= $(BUILDDIR)/$(BINARYNAME).hex
BIN 	= $(BUILDDIR)/$(BINARYNAME).bin

PHONY: all

all: Makefile $(ELF) $(UIMAGENAME)

$(UIMAGENAME): $(BIN)
	$(UBOOTDIR)/tools/mkimage -A arm -C none -T kernel -a $(LOADADDR) -e $(ENTRYPOINT) -d $< $@

$(BUILDDIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	$(AS) $(AFLAGS) $< -o $@ > $(addprefix $(BUILDDIR)/, $(addsuffix .lst, $(basename $<)))

$(BUILDDIR)/%.o: %.c $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	$(CC) -c $(DEPFLAGS) $(OPTFLAG) $(CFLAGS) $< -o $@

$(ELF): $(OBJECTS) $(DEVICE)/$(LOADFILE)
	$(info Linking...)
	$(LD) $(LFLAGS) -o $@ $(OBJECTS)

$(BIN): $(ELF)
	$(OBJCPY) -O binary $< $@

%.d: ;

clean:
	rm -rf build
	rm $(UIMAGENAME)

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS) $(ELF)

#Todo: add card commands
#./create-sd.sh sdcard.img bare-arm.uimg
	
