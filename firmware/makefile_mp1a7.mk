# Makefile by Dan Green <danngreen1@gmail.com>, public domain

$(info --------------------)
$(info Building for MP1 A7 core)
BUILDDIR = $(BUILDDIR_MP1A7)
LOADFILE = $(LINKSCRIPTDIR)/stm32mp15xx_ca7.ld
CORE_SRC = src/a7
HAL_CONF_INC = src/a7
HALDIR = $(HALBASE)/stm32mp1
DEVICEDIR = $(DEVICEBASE)/stm32mp157c
TARGETDEVICEDIR = $(DRIVERLIB)/target/stm32mp1
TARGETDEVICEDIR_CA7 = $(DRIVERLIB)/target/stm32mp1_ca7

STARTUP_CA7	= $(TARGETDEVICEDIR_CA7)/boot/startup_ca7.s
SHARED = src/shared

OPTFLAG = -O3
# LTOFLAG =
LTOFLAG = -flto=auto

include makefile_opts.mk

MFFONTDIR = $(LIBDIR)/mcufont/fonts
MFDIR = $(LIBDIR)/mcufont/decoder
include $(LIBDIR)/mcufont/decoder/mcufont.mk

NE10DIR = $(LIBDIR)/ne10/ne10

ASM_SOURCES = $(STARTUP_CA7)

SOURCES = \
		  system/libc_stub.c\
		  system/libcpp_stub.cc \
		  system/new.cc \
		  system/mmu_ca7.c \
		  $(TARGETDEVICEDIR_CA7)/boot/system_ca7.c \
		  $(TARGETDEVICEDIR_CA7)/boot/irq_ctrl.c \
		  $(HALDIR)/src/stm32mp1xx_hal.c \
		  $(HALDIR)/src/stm32mp1xx_hal_sai.c \
		  $(HALDIR)/src/stm32mp1xx_hal_dma.c \
		  $(HALDIR)/src/stm32mp1xx_hal_i2c.c \
		  $(HALDIR)/src/stm32mp1xx_hal_i2c_ex.c \
		  $(HALDIR)/src/stm32mp1xx_hal_rcc.c \
		  $(HALDIR)/src/stm32mp1xx_hal_rcc_ex.c \
		  $(HALDIR)/src/stm32mp1xx_ll_tim.c \
		  $(DRIVERLIB)/drivers/pin.cc \
		  $(DRIVERLIB)/drivers/timekeeper.cc \
		  $(DRIVERLIB)/drivers/tim.cc \
		  $(TARGETDEVICEDIR_CA7)/drivers/interrupt_handler.cc \
		  $(TARGETDEVICEDIR_CA7)/drivers/hal_handlers.cc \
		  $(TARGETDEVICEDIR_CA7)/drivers/cycle_counter.cc \
		  $(DRIVERLIB)/drivers/i2c.cc \
		  $(DRIVERLIB)/drivers/sai.cc \
		  $(DRIVERLIB)/drivers/codec_WM8731.cc \
		  $(SHARED)/util/math_tables.cc \
		  $(CORE_SRC)/main.cc\
		  $(CORE_SRC)/aux_core_main.cc\
		  src/patchlist.cc\
		  src/pages/page_manager.cc \
		  src/print.cc \
		  src/audio.cc \
		  $(wildcard $(SHARED)/CoreModules/*.cpp) \
		  $(LIBDIR)/printf/printf.c \
		  $(MFSRC) \
		  $(NE10DIR)/common/NE10_mask_table.c \
		  $(NE10DIR)/modules/dsp/NE10_fft.c \
		  $(NE10DIR)/modules/dsp/NE10_fft_float32.c \
		  $(NE10DIR)/modules/dsp/NE10_fft_generic_float32.c \
		  $(NE10DIR)/modules/dsp/NE10_fft_generic_int32.cpp \
		  $(NE10DIR)/modules/dsp/NE10_rfft_float32.c \
		  $(NE10DIR)/modules/dsp/NE10_fft_int32.c \
		  $(NE10DIR)/modules/dsp/NE10_fft_int16.c \
		  $(NE10DIR)/modules/dsp/NE10_fir.c \
		  $(NE10DIR)/modules/dsp/NE10_fir_init.c \
		  $(NE10DIR)/modules/dsp/NE10_iir.c \
		  $(NE10DIR)/modules/dsp/NE10_iir_init.c \
		  $(NE10DIR)/modules/dsp/NE10_fft_generic_float32.neonintrinsic.cpp \
		  $(NE10DIR)/modules/dsp/NE10_fft_generic_int32.neonintrinsic.cpp \
		  $(NE10DIR)/modules/dsp/NE10_init_dsp.c \

NE10_ASM_OPTIMIZATION = 1

ifneq ($(NE10_ASM_OPTIMIZATION),)
SOURCES += \
		  $(NE10DIR)/modules/dsp/NE10_fft_float32.neon.c \
		  $(NE10DIR)/modules/dsp/NE10_fft_int32.neon.c \
		  $(NE10DIR)/modules/dsp/NE10_fft_int16.neon.c \

ASM_SOURCES += \
		  $(NE10DIR)/modules/dsp/NE10_fft_float32.neon.s \
		  $(NE10DIR)/modules/dsp/NE10_fft_int32.neon.s \
		  $(NE10DIR)/modules/dsp/NE10_fft_int16.neon.s \

NE10_CFLAGS = -DNE10_UNROLL_LEVEL=0
else
SOURCES += \
	$(NE10DIR)/modules/dsp/NE10_fft_float32.neonintrinsic.c \
	$(NE10DIR)/modules/dsp/NE10_fft_int32.neonintrinsic.c \
	$(NE10DIR)/modules/dsp/NE10_fft_int16.neonintrinsic.c \
	$(NE10DIR)/modules/dsp/NE10_rfft_float32.neonintrinsic.c \

NE10_CFLAGS = -DNE10_UNROLL_LEVEL=1
endif

ASM_SOURCES += \
		  $(NE10DIR)/modules/dsp/NE10_fir.neon.s \
		  $(NE10DIR)/modules/dsp/NE10_iir.neon.s \
		  $(NE10DIR)/common/NE10header.s \
		  $(NE10DIR)/common/versionheader.s \

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
		   -I$(TARGETDEVICEDIR) \
		   -I$(TARGETDEVICEDIR)/drivers \
		   -I$(TARGETDEVICEDIR_CA7) \
		   -I$(TARGETDEVICEDIR_CA7)/drivers \
		   -I$(SHARED) \
		   -I$(SHARED)/CoreModules \
		   -I$(SHARED)/util \
		   -I$(SHARED)/patch \
		   -I$(LIBDIR)/printf \
		   -I$(MFINC) \
		   -I$(MFFONTDIR) \
		   -I$(NE10DIR)/inc \
		   -I$(NE10DIR)/common \
		   -I$(NE10DIR)/modules/dsp \

#D-Cache L1: 32 KB, 128 Sets, 64 Bytes/Line, 4-Way
EXTRA_CFLAGS = --param l1-cache-size=32 \
	 		   --param l1-cache-line-size=64 \
			   --param l2-cache-size=256 \
				-DNE10_ENABLE_DSP \
				$(NE10_CFLAGS) \

EXTRA_CPPFLAGS = $(LTOFLAG)

EXTRA_LFLAGS = $(LTOFLAG) $(OPTFLAG)

EXTDEF ?= METAMODULE_NORMAL_MODE

ARCH_CFLAGS += -DUSE_HAL_DRIVER \
			  -DUSE_FULL_LL_DRIVER \
			  -DSTM32MP157Cxx \
			  -DSTM32MP1 \
			  -DCORE_CA7 \
              -DENABLE_NE10_FIR_FLOAT_NEON \
              -DENABLE_NE10_FIR_DECIMATE_FLOAT_NEON \
              -DENABLE_NE10_FIR_INTERPOLATE_FLOAT_NEON \
              -DENABLE_NE10_FIR_LATTICE_FLOAT_NEON \
              -DENABLE_NE10_FIR_SPARSE_FLOAT_NEON \
              -DENABLE_NE10_IIR_LATTICE_FLOAT_NEON \
			  -D$(EXTDEF)

MCU = -mcpu=cortex-a7 \
	  -mlittle-endian \
	  -mfpu=neon-vfpv4 \
	  -mfloat-abi=hard \
	  -munaligned-access \
	  -mthumb-interwork \
	  -mtune=cortex-a7 \
	  -funsafe-math-optimizations \
	  -mvectorize-with-neon-quad \
	  -ffast-math \

AFLAGS = -mcpu=cortex-a7 \
		 -mlittle-endian \
		 -mfpu=neon-vfpv4 \
		 -mfloat-abi=hard \

#### U-BOOT
UIMG  		= $(BUILDDIR)/$(BINARYNAME).uimg
LOADADDR 	= 0xC2000040
ENTRYPOINT 	= $(LOADADDR)
UBOOTDIR 	= $(LIBDIR)/u-boot
UBOOTSRCDIR = $(UBOOTDIR)/u-boot-stm32mp1-baremetal
UBOOTBUILDDIR = $(UBOOTDIR)/build
UBOOT_MKIMAGE = $(UBOOTBUILDDIR)/tools/mkimage
#####

include makefile_common.mk

image: $(UIMG)

$(UBOOT_MKIMAGE): $(UBOOTSRCDIR)
	cd $(UBOOTSRCDIR) && make O=$(PWD)/$(UBOOTBUILDDIR) CROSS_COMPILE=arm-none-eabi- stm32mp15x_baremetal_defconfig
	cd $(UBOOTSRCDIR) && make -j16 O=$(PWD)/$(UBOOTBUILDDIR) CROSS_COMPILE=arm-none-eabi- all

$(UIMG): $(BIN) $(UBOOT_MKIMAGE)
	@$(UBOOT_MKIMAGE) -A arm -C none -T kernel -a $(LOADADDR) -e $(ENTRYPOINT) -d $(BIN) $@

clean_uboot:
	rm -rf $(UBOOTBUILDDIR)



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

