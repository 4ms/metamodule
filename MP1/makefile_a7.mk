# Makefile by Dan Green <danngreen1@gmail.com>, public domain

$(info Building for A7 core)
BUILDDIR = $(BUILDDIR_A7)
LOADFILE = $(DEVICE)/src/stm32mp15xx_ca7.ld
MCU =  -mcpu=cortex-a7 -mfpu=fpv5-d16 -mlittle-endian -mfloat-abi=hard
# MCU = -mcpu=cortex-a7 -mlittle-endian #-mthumb? -mfput=? -mfloat-abi=?
CORE_SRC = src/a7
HAL_CONF_INC = src/a7

OPTFLAG = -O0
include makefile_opts.mk

####
UIMG  		= $(BUILDDIR)/$(BINARYNAME).uimg
LOADADDR 	= 0xC2000040
ENTRYPOINT 	= $(LOADADDR)
UBOOTDIR 	= $(LIBDIR)/u-boot
UBOOTSRCDIR = $(UBOOTDIR)/u-boot-stm32mp1-baremetal
UBOOTBUILDDIR = $(UBOOTDIR)/build
UBOOT_MKIMAGE = $(UBOOTBUILDDIR)/tools/mkimage
#####

SOURCES = $(DRIVERLIB)/drivers/$(STARTUP_CA7) \
		  src/sys/syscpp.c\
		  src/a7/main.cc\
		  $(DRIVERLIB)/drivers/pin.cc \
		  $(DRIVERLIB)/drivers/i2c.cc \
		  $(PERIPH)/src/stm32mp1xx_hal.c \
		  $(PERIPH)/src/stm32mp1xx_hal_i2c.c \
		  $(PERIPH)/src/stm32mp1xx_hal_i2c_ex.c \

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

INCLUDES = -I. \
		   -Isrc \
		   -Isrc/a7 \
		   -Isrc/a7/conf \
		   -I$(PERIPH)/include \
		   -I$(CMSIS)/Core_A/Include \
		   -I$(CMSIS)/Core/Include \
		   -I$(CMSIS)/include \
		   -I$(DEVICE)/include \
		   -I$(DRIVERLIB) \
		   -I$(DRIVERLIB)/drivers \

AFLAGS = $(MCU)

ARCH_CFLAGS += -DUSE_HAL_DRIVER \
			  -DUSE_FULL_LL_DRIVER \
			  -DSTM32MP157Cxx \
			  -DSTM32MP1 \
			  -DCORE_CA7 \
#DARM_MATH_CA7

CFLAGS = -g2 \
		 -fno-common \
		 $(ARCH_CFLAGS) \
		 $(MCU) \
		 $(INCLUDES) \
		 -fdata-sections -ffunction-sections \
		 -nostartfiles \
		 -nostdlib \
		-ffreestanding

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

LFLAGS = -Wl,--gc-sections \
	-Wl,-Map,$(BUILDDIR)/$(BINARYNAME).map,--cref \
	$(MCU)  \
	-T $(LOADFILE) \
	-nostartfiles \
	-nostdlib \
	-ffreestanding

DEPFLAGS = -MMD -MP -MF $(BUILDDIR)/$(basename $<).d

# ARCH 	= /usr/local/Caskroom/gcc-arm-embedded/10-2020-q4-major/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi
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

all: Makefile $(ELF) $(UIMG)

$(UIMG): $(BIN) $(UBOOT_MKIMAGE)
	$(UBOOT_MKIMAGE) -A arm -C none -T kernel -a $(LOADADDR) -e $(ENTRYPOINT) -d $(BIN) $@

$(BUILDDIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	@$(AS) $(AFLAGS) $< -o $@ > $(addprefix $(BUILDDIR)/, $(addsuffix .lst, $(basename $<)))

$(BUILDDIR)/%.o: %.c $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	@$(CC) -c $(DEPFLAGS) $(OPTFLAG) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	@$(CXX) -c $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@

$(ELF): $(OBJECTS) $(LOADFILE)
	$(info Linking...)
	@$(LD) $(LFLAGS) -o $@ $(OBJECTS)

$(BIN): $(ELF)
	$(OBJCPY) -O binary $< $@

$(UBOOT_MKIMAGE): $(UBOOTSRCDIR)
	cd $(UBOOTSRCDIR) && make KBUILD_OUTPUT=$(PWD)/$(UBOOTBUILDDIR) CROSS_COMPILE=arm-none-eabi- stm32mp15x_baremetal_defconfig
	cd $(UBOOTSRCDIR) && make -j16 KBUILD_OUTPUT=$(PWD)/$(UBOOTBUILDDIR) CROSS_COMPILE=arm-none-eabi- all

uboot_clean:
	rm -rf $(UBOOTBUILDDIR)

%.d: ;

clean:
	rm -rf build
	rm $(UIMAGENAME)

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS) $(ELF)
.PHONY: all

#Todo: add card commands
#./create-sd.sh sdcard.img bare-arm.uimg
	
