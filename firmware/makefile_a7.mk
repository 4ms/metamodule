# Makefile by Dan Green <danngreen1@gmail.com>, public domain

$(info Building for A7 core)
BUILDDIR = $(BUILDDIR_A7)

LOADFILE = $(LINKSCRIPTDIR)/stm32mp15xx_ca7.ld
STARTUP_CA7	= $(DRIVERLIB)/drivers/startup_ca7.s

MCU =  -mcpu=cortex-a7 -mfpu=fpv5-d16 -mlittle-endian -mfloat-abi=hard
CORE_SRC = src/a7
HAL_CONF_INC = src/a7
HALDIR = $(HALBASE)/stm32mp1
DEVICEDIR = $(DEVICEBASE)/stm32mp157c
TARGETDRIVERS = $(DRIVERLIB)/drivers/target/stm32mp1

SHARED = src/a7/shared

OPTFLAG = -O0
include makefile_opts.mk

SOURCES = $(STARTUP_CA7) \
		  system/libc_stub.c\
		  system/libcpp_stub.cc \
		  system/new.cc \
		  system/system_ca7.c \
		  system/irq_ctrl.c \
		  $(HALDIR)/src/stm32mp1xx_hal.c \
		  $(HALDIR)/src/stm32mp1xx_hal_sai.c \
		  $(HALDIR)/src/stm32mp1xx_hal_dma.c \
		  $(HALDIR)/src/stm32mp1xx_hal_i2c.c \
		  $(HALDIR)/src/stm32mp1xx_hal_i2c_ex.c \
		  $(HALDIR)/src/stm32mp1xx_hal_rcc.c \
		  $(HALDIR)/src/stm32mp1xx_hal_rcc_ex.c \
		  $(DRIVERLIB)/drivers/pin.cc \
		  $(TARGETDRIVERS)/drivers/interrupt.cc \
		  $(TARGETDRIVERS)/drivers/hal_handlers.cc \
		  $(TARGETDRIVERS)/drivers/cycle_counter.cc \
		  $(TARGETDRIVERS)/drivers/pinchange.cc \
		  $(DRIVERLIB)/drivers/i2c.cc \
		  $(DRIVERLIB)/drivers/sai.cc \
		  $(DRIVERLIB)/drivers/codec_WM8731.cc \
		  $(SHARED)/util/math_tables.cc \
		  $(CORE_SRC)/main.cc\
		  src/patchlist.cc\
		  src/audio.cc\
		  $(wildcard $(SHARED)/CoreModules/*.cpp) \

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

INCLUDES = -I. \
		   -Isrc \
		   -Isrc/a7 \
		   -Isrc/a7/conf \
		   -I$(HALDIR)/include \
		   -I$(CMSIS)/Core_A/Include \
		   -I$(CMSIS)/Include \
		   -I$(DEVICEDIR)/include \
		   -I$(DRIVERLIB) \
		   -I$(DRIVERLIB)/drivers \
		   -I$(DRIVERLIB)/drivers/target/stm32mp1 \
		   -I$(DRIVERLIB)/drivers/target/stm32mp1/drivers \
		   -I$(SHARED) \
		   -I$(SHARED)/CoreModules \
		   -I$(SHARED)/util \
		   -I$(SHARED)/patch \

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

#### U-BOOT
UIMG  		= $(BUILDDIR)/$(BINARYNAME).uimg
LOADADDR 	= 0xC2000040
ENTRYPOINT 	= $(LOADADDR)
UBOOTDIR 	= $(LIBDIR)/u-boot
UBOOTSRCDIR = $(UBOOTDIR)/u-boot-stm32mp1-baremetal
UBOOTBUILDDIR = $(UBOOTDIR)/build
UBOOT_MKIMAGE = $(UBOOTBUILDDIR)/tools/mkimage
#####

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

$(BUILDDIR)/%.o: %.cpp $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	@$(CXX) -c $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@


$(ELF): $(OBJECTS) $(LOADFILE)
	$(info Linking...)
	@$(LD) $(LFLAGS) -o $@ $(OBJECTS)

$(BIN): $(ELF)
	$(OBJCPY) -O binary $< $@

$(UBOOT_MKIMAGE): $(UBOOTSRCDIR)
	cd $(UBOOTSRCDIR) && make O=$(PWD)/$(UBOOTBUILDDIR) CROSS_COMPILE=arm-none-eabi- stm32mp15x_baremetal_defconfig
	cd $(UBOOTSRCDIR) && make -j16 O=$(PWD)/$(UBOOTBUILDDIR) CROSS_COMPILE=arm-none-eabi- all

$(UIMG): $(BIN) $(UBOOT_MKIMAGE)
	$(UBOOT_MKIMAGE) -A arm -C none -T kernel -a $(LOADADDR) -e $(ENTRYPOINT) -d $(BIN) $@

%.d: ;

clean:
	rm -rf $(BUILDDIR)

clean_uboot:
	rm -rf $(UBOOTBUILDDIR)


ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS) $(ELF)
.PHONY: all


# Todo: get this working:
# install-uboot:
	# $(info Please enter the sd card device node:)
	# ls -l /dev/disk*  #if macOS
	# ls -l /dev/sd*    #if linux
	# getinput(devXX)  #How to do this?
	# scripts/format-sdcard.sh $(devXX)
	# scripts/partition-sdcard.sh $(devXX)
	# scripts/copy-bootloader.sh $(devXX) $(UBOOTBUILDDIR)/
	# scripts/copy-app-to-sdcard.sh $(UIMG) $(devXX)

