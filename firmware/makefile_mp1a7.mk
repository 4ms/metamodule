# Makefile by Dan Green <danngreen1@gmail.com>, public domain

#TODO: Once we have multiple a7 versions, build coreModules, HAL, NE10, font library, mdrivlib in a shared A7 dir
#so don't build it twice for mini/max/etc

USE_FEWER_MODULES ?= 1

# First target of the make command is the board we should build for. Check if it's valid.
ifeq ($(MAKECMDGOALS),$(filter $(MAKECMDGOALS),$(VALID_BOARDS)))
target_board = $(word 1,$(MAKECMDGOALS))
$(info --------------------)
$(info Building for MP1 A7 core, target: $(target_board))

else ifeq ($(MAKECMDGOALS),bootimg)
$(info Building img)
target_board = medium

else
$(error Board not supported)
endif

# target/chip/core specific source dirs
target_src := src/$(target_board)
target_chip_src := src/$(target_board)/mp1
core_src := src/a7
usb_src := src/usb

ifeq "$(target_board)" "pcmdev"
main_source = src/pcmdev/main.cc
audio_source = src/pcmdev/audio-dualcodec.cc
EXTDEF = DUAL_PCM3168_DEV
else ifeq "$(target_board)" "norflash-loader"
main_source = $(target_src)/main.cc
else
main_source = $(core_src)/main.cc
audio_source = src/audio.cc
endif

TAG := [MP1A7-$(target_board)]

BUILDDIR 			= $(BUILDDIR_MP1A7)/$(target_board)
LOADFILE 			= $(LINKSCRIPTDIR)/stm32mp15xx_ca7.ld
HALDIR 				= $(HALBASE)/stm32mp1
usbdev_libdir 		= $(LIBDIR)/stm32-usb-device-lib
usbhost_libdir 		= $(LIBDIR)/stm32-usb-host-lib
DEVICEDIR 			= $(DEVICEBASE)/stm32mp157c
TARGETDEVICEDIR 	= $(DRIVERLIB)/target/stm32mp1
TARGETDEVICEDIR_CA7 = $(DRIVERLIB)/target/stm32mp1_ca7
STARTUP_CA7			= $(TARGETDEVICEDIR_CA7)/boot/startup_ca7.s
SHARED 				= src/shared
ASM_SOURCES 		= $(STARTUP_CA7)
NE10DIR 			= $(LIBDIR)/ne10/ne10

OPTFLAG = -O3 
LTOFLAG = -flto=auto
# OPTFLAG = -O0
# LTOFLAG = 

SOURCES =
SOURCES += system/libc_stub.c
SOURCES += system/libcpp_stub.cc
SOURCES += system/new.cc
SOURCES += system/mmu_ca7.c
SOURCES += $(TARGETDEVICEDIR_CA7)/boot/system_ca7.c
SOURCES += $(TARGETDEVICEDIR_CA7)/boot/irq_ctrl.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_rcc.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_rcc_ex.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_mdma.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_uart.c
SOURCES += $(DRIVERLIB)/drivers/pin.cc
SOURCES += $(TARGETDEVICEDIR_CA7)/drivers/interrupt_handler.cc
SOURCES += $(LIBDIR)/printf/printf.c
SOURCES += src/uart_log.cc
SOURCES += $(main_source)

ifeq "$(target_board)" "norflash-loader"

else
# SOURCES += $(usb_src)/usbd_conf.cc
# SOURCES += $(usb_src)/usbd_desc.c
# SOURCES += $(usb_src)/usb_drive_device.cc
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_dma.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_i2c.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_i2c_ex.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_sai.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_ltdc.c
SOURCES += $(HALDIR)/src/stm32mp1xx_ll_tim.c
SOURCES += $(HALDIR)/src/stm32mp1xx_ll_rcc.c
# SOURCES += $(HALDIR)/src/stm32mp1xx_ll_usb.c
# SOURCES += $(HALDIR)/src/stm32mp1xx_hal_pcd.c
# SOURCES += $(HALDIR)/src/stm32mp1xx_hal_pcd_ex.c
# SOURCES += $(HALDIR)/src/stm32mp1xx_hal_hcd.c
# SOURCES += $(usbdev_libdir)/Class/MSC/Src/usbd_msc.c
# SOURCES += $(usbdev_libdir)/Class/MSC/Src/usbd_msc_bot.c
# SOURCES += $(usbdev_libdir)/Class/MSC/Src/usbd_msc_data.c
# SOURCES += $(usbdev_libdir)/Class/MSC/Src/usbd_msc_scsi.c
# SOURCES += $(usbdev_libdir)/Core/Src/usbd_core.c
# SOURCES += $(usbdev_libdir)/Core/Src/usbd_ctlreq.c
# SOURCES += $(usbdev_libdir)/Core/Src/usbd_ioreq.c

# SOURCES += $(usbhost_libdir)/Class/HUB/Src/usbh_hub.c
# SOURCES += $(usb_src)/usbh_conf.c
# SOURCES += $(usb_src)/usbh_MIDI.c
# SOURCES += $(usb_src)/midi_host.cc
# SOURCES += $(usbhost_libdir)/Core/Src/usbh_core.c
# SOURCES += $(usbhost_libdir)/Core/Src/usbh_ctlreq.c
# SOURCES += $(usbhost_libdir)/Core/Src/usbh_ioreq.c
# SOURCES += $(usbhost_libdir)/Core/Src/usbh_pipes.c

SOURCES += $(DRIVERLIB)/drivers/timekeeper.cc
SOURCES += $(DRIVERLIB)/drivers/tim.cc
SOURCES += $(TARGETDEVICEDIR_CA7)/drivers/hal_handlers.cc
SOURCES += $(TARGETDEVICEDIR_CA7)/drivers/cycle_counter.cc
SOURCES += $(DRIVERLIB)/drivers/i2c.cc
SOURCES += $(TARGETDEVICEDIR)/drivers/sai_tdm.cc
SOURCES += $(DRIVERLIB)/drivers/codec_PCM3168.cc
SOURCES += $(DRIVERLIB)/drivers/codec_WM8731.cc
SOURCES += $(SHARED)/cpputil/util/math_tables.cc
SOURCES += $(audio_source)
SOURCES += $(core_src)/aux_core_main.cc
SOURCES += src/patchlist.cc
SOURCES += src/patchlist_ryml_tests.cc
SOURCES += src/pages/page_manager.cc
ifeq "$(USE_FEWER_MODULES)" "1"
SOURCES += $(SHARED)/CoreModules/DjembeCore.cc
SOURCES += $(SHARED)/CoreModules/StMixCore.cc
SOURCES += $(SHARED)/CoreModules/PEGCore.cc
SOURCES += $(SHARED)/CoreModules/SMRCore.cc
SOURCES += $(SHARED)/CoreModules/MultiLFOCore.cc
SOURCES += $(SHARED)/CoreModules/PitchShiftCore.cc
SOURCES += $(SHARED)/CoreModules/HPFCore.cc
SOURCES += $(SHARED)/CoreModules/panel_medium.cc
SOURCES += $(SHARED)/CoreModules/InfOscCore.cc
SOURCES += $(SHARED)/CoreModules/KPLSCore.cc
SOURCES += $(SHARED)/CoreModules/FreeverbCore.cc
SOURCES += $(SHARED)/CoreModules/Seq8Core.cc
SOURCES += $(SHARED)/CoreModules/EnOscCore.cc
SOURCES += $(SHARED)/CoreModules/enosc/data.cc
SOURCES += $(SHARED)/CoreModules/enosc/dynamic_data.cc
else
SOURCES += $(wildcard $(SHARED)/CoreModules/*.cc)
endif
SOURCES += $(SHARED)/axoloti-wrapper/axoloti_math.cpp
SOURCES += $(SHARED)/patch_convert/yaml_to_patch.cc
SOURCES += $(SHARED)/patch_convert/ryml/ryml_serial.cc

## LVGL / Gui-Guider
LVGL_DIR=$(LIBDIR)/lvgl
LVGL_DIR_NAME=lvgl
SOURCES += $(shell find -L $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/widgets -name \*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/flex/*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/layouts/grid/*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/others/gridnav/*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/extra/themes/default/*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/core/*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/draw/*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/draw/sw/*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/widgets/*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/font/*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/misc/*.c)
# SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/gpu/*.c)
SOURCES += $(wildcard $(LVGL_DIR)/$(LVGL_DIR_NAME)/src/hal/*.c)
#SOURCES += $(wildcard src/pages/gui-guider/*.c)

# SOURCES += $(wildcard src/pages/fonts/*.c)
SOURCES += src/pages/fonts/MuseoSansRounded_500_12.c
SOURCES += src/pages/fonts/MuseoSansRounded_700_12.c
SOURCES += src/pages/fonts/MuseoSansRounded_700_14.c
SOURCES += src/pages/fonts/MuseoSansRounded_700_16.c
SOURCES += src/pages/fonts/MuseoSansRounded_700_18.c

ifeq "$(USE_FEWER_MODULES)" "1"
SOURCES += src/pages/images/Djembe_artwork_240.c
SOURCES += src/pages/images/StMix_artwork_240.c
SOURCES += src/pages/images/PEG_artwork_240.c
SOURCES += src/pages/images/SMR_artwork_240.c
SOURCES += src/pages/images/MultiLFO_artwork_240.c
SOURCES += src/pages/images/PitchShift_artwork_240.c
SOURCES += src/pages/images/HPF_artwork_240.c
SOURCES += src/pages/images/InfOsc_artwork_240.c
SOURCES += src/pages/images/KPLS_artwork_240.c
SOURCES += src/pages/images/Freeverb_artwork_240.c
SOURCES += src/pages/images/Seq8_artwork_240.c
SOURCES += src/pages/images/EnOsc_artwork_240.c

SOURCES += src/pages/images/Djembe_artwork_120.c
SOURCES += src/pages/images/StMix_artwork_120.c
SOURCES += src/pages/images/PEG_artwork_120.c
SOURCES += src/pages/images/MultiLFO_artwork_120.c
SOURCES += src/pages/images/SMR_artwork_120.c
SOURCES += src/pages/images/PitchShift_artwork_120.c
SOURCES += src/pages/images/HPF_artwork_120.c
SOURCES += src/pages/images/InfOsc_artwork_120.c
SOURCES += src/pages/images/KPLS_artwork_120.c
SOURCES += src/pages/images/Freeverb_artwork_120.c
SOURCES += src/pages/images/Seq8_artwork_120.c
SOURCES += src/pages/images/EnOsc_artwork_120.c
else
SOURCES += $(wildcard src/pages/images/*.c)
endif
# SOURCES += $(wildcard src/pages/images/ui/*.c)
SOURCES += $(wildcard src/pages/images/components/*.c)

## RapidYml

RYMLDIR = $(SHARED)/patch_convert/ryml/rapidyaml
SOURCES += $(wildcard $(RYMLDIR)/src/c4/yml/*.cpp)
SOURCES += $(wildcard $(RYMLDIR)/ext/c4core/src/c4/*.cpp)

## FatFS, qspi flash

SOURCES += $(LIBDIR)/fatfs/source/ff.c
SOURCES += $(LIBDIR)/fatfs/source/ffunicode.c
SOURCES += src/fatfs/diskio.cc
SOURCES += src/fatfs/fattime.cc
SOURCES += src/fatfs/ramdisk_fileio.cc
SOURCES += src/patchstorage.cc
SOURCES += src/time_convert.cc
# SOURCES += src/patchfileio.cc
SOURCES += $(LIBDIR)/littlefs/lfs.c
SOURCES += $(LIBDIR)/littlefs/lfs_util.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_qspi.c
SOURCES += $(DRIVERLIB)/drivers/qspi_flash_driver.cc


# SOURCES += $(NE10DIR)/common/NE10_mask_table.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_float32.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_generic_float32.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_generic_int32.cpp
# SOURCES += $(NE10DIR)/modules/dsp/NE10_rfft_float32.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_int32.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_int16.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fir.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fir_init.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_iir.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_iir_init.c
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_generic_float32.neonintrinsic.cpp
# SOURCES += $(NE10DIR)/modules/dsp/NE10_fft_generic_int32.neonintrinsic.cpp
# SOURCES += $(NE10DIR)/modules/dsp/NE10_init_dsp.c

# NE10_ASM_OPTIMIZATION = 1

# ifneq ($(NE10_ASM_OPTIMIZATION),)
# SOURCES += \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_float32.neon.c \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_int32.neon.c \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_int16.neon.c \

# ASM_SOURCES += \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_float32.neon.s \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_int32.neon.s \
# 		  $(NE10DIR)/modules/dsp/NE10_fft_int16.neon.s \

# NE10_CFLAGS = -DNE10_UNROLL_LEVEL=0
# else
# SOURCES += \
# 	$(NE10DIR)/modules/dsp/NE10_fft_float32.neonintrinsic.c \
# 	$(NE10DIR)/modules/dsp/NE10_fft_int32.neonintrinsic.c \
# 	$(NE10DIR)/modules/dsp/NE10_fft_int16.neonintrinsic.c \
# 	$(NE10DIR)/modules/dsp/NE10_rfft_float32.neonintrinsic.c \

# NE10_CFLAGS = -DNE10_UNROLL_LEVEL=1
# endif

# ASM_SOURCES += \
# 		  $(NE10DIR)/modules/dsp/NE10_fir.neon.s \
# 		  $(NE10DIR)/modules/dsp/NE10_iir.neon.s \
# 		  $(NE10DIR)/common/NE10header.s \
# 		  $(NE10DIR)/common/versionheader.s \

endif # ifneq "$(target_board)" "norflash-loader"

INCLUDES = 
INCLUDES += 	-I.
INCLUDES +=		-Isrc
INCLUDES +=		-I$(core_src)
INCLUDES +=		-I$(target_src)
INCLUDES +=		-I$(target_chip_src)
# INCLUDES +=		-I$(usb_src)
INCLUDES +=		-I$(HALDIR)/include
INCLUDES +=		-I$(CMSIS)/Core_A/Include
INCLUDES +=		-I$(CMSIS)/Include
INCLUDES +=		-I$(DEVICEDIR)/include
INCLUDES +=		-I$(DRIVERLIB)
INCLUDES +=		-I$(DRIVERLIB)/drivers
INCLUDES +=		-I$(TARGETDEVICEDIR)
INCLUDES +=		-I$(TARGETDEVICEDIR)/drivers
INCLUDES +=		-I$(TARGETDEVICEDIR_CA7)
INCLUDES +=		-I$(TARGETDEVICEDIR_CA7)/drivers
INCLUDES +=		-I$(SHARED)
INCLUDES +=		-I$(SHARED)/CoreModules
INCLUDES +=		-I$(SHARED)/cpputil
INCLUDES +=		-I$(SHARED)/patch
INCLUDES +=		-I$(LIBDIR)/lvgl
#INCLUDES +=		-I$(LIBDIR)/lvgl/lvgl/src/lv_font
INCLUDES +=		-I$(LIBDIR)/printf
# INCLUDES +=		-I$(usbdev_libdir)/Class/MSC/Inc
# INCLUDES +=		-I$(usbdev_libdir)/Core/Inc
# INCLUDES +=		-I$(usbdev_libdir)/Class/HUB/Inc
# INCLUDES +=		-I$(usbhost_libdir)/Core/Inc
INCLUDES += 	-I$(SHARED)/etl/include
INCLUDES += 	-I$(SHARED)/patch_convert
INCLUDES += 	-I$(SHARED)/patch_convert/ryml
# INCLUDES +=		-I$(NE10DIR)/inc
# INCLUDES +=		-I$(NE10DIR)/common
# INCLUDES +=		-I$(NE10DIR)/modules/dsp
INCLUDES += 	-I$(RYMLDIR)/src
INCLUDES += 	-I$(RYMLDIR)/ext/c4core/src
INCLUDES += 	-I$(LIBDIR)/fatfs/source
INCLUDES += 	-Isrc/fatfs

#D-Cache L1: 32 KB, 128 Sets, 64 Bytes/Line, 4-Way
EXTRA_CFLAGS = --param l1-cache-size=32 \
	 		   --param l1-cache-line-size=64 \
			   --param l2-cache-size=256 \
				# -DNE10_ENABLE_DSP \
				# $(NE10_CFLAGS) \

ifeq "$(USE_FEWER_MODULES)" "1"
	EXTRA_CFLAGS += -D'USE_FEWER_MODULES=1'
endif

EXTRA_CPPFLAGS = $(LTOFLAG) -ffold-simple-inlines

EXTRA_LFLAGS = $(LTOFLAG) $(OPTFLAG)

EXTDEF ?= METAMODULE_NORMAL_MODE

ARCH_CFLAGS += -DUSE_HAL_DRIVER \
			  -DUSE_FULL_LL_DRIVER \
			  -DSTM32MP157Cxx \
			  -DSTM32MP1 \
			  -DCORE_CA7 \
			  -D$(EXTDEF)
              # -DENABLE_NE10_FIR_FLOAT_NEON \
              # -DENABLE_NE10_FIR_DECIMATE_FLOAT_NEON \
              # -DENABLE_NE10_FIR_INTERPOLATE_FLOAT_NEON \
              # -DENABLE_NE10_FIR_LATTICE_FLOAT_NEON \
              # -DENABLE_NE10_FIR_SPARSE_FLOAT_NEON \
              # -DENABLE_NE10_IIR_LATTICE_FLOAT_NEON \

MCU = -mcpu=cortex-a7 \
	  -mlittle-endian \
	  -mfpu=neon-vfpv4 \
	  -mfloat-abi=hard \
	  -mthumb-interwork \
	  -mno-unaligned-access \
	  -mtune=cortex-a7 \
	  -mvectorize-with-neon-quad \
	  -funsafe-math-optimizations \
	  # -ffast-math \
	  # -mstrict-align \

	  # -fopt-info-vec-missed=vec.miss 
	  # -ftree-vectorizer-verbose=n -fdump-tree-vect
	  # -ffast-math \ # Karplus is silent

# Note: -funsafe-math-optimizations and/or -mno-unaligned-access 
# must be here or else we get alignment errors in some modules (e.g. Karplus)
#
# Example bad instruction: 
# VLD1.64 {D16, D17} [R1 :64] 
# where R1 is not aligned to 64-bits (ends in 0x4 for example)
# See: https://gcc.gnu.org/projects/tree-ssa/vectorization.html quote: 
# "To enable vectorization of floating point reductions use -ffast-math or -fassociative-math."
# (note that -funsafe-math-optimizations implies -fassociative-math: https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html )

AFLAGS = -mcpu=cortex-a7 \
		 -mlittle-endian \
		 -mfpu=neon-vfpv4 \
		 -mfloat-abi=hard \

## Build targets

include makefile_opts.mk
include makefile_common.mk


#### BOOT IMAGE
IMG  		= $(BUILDDIR)/$(BINARYNAME).img
LOADADDR 	= 0xC2000040
ENTRYPOINT 	= $(LOADADDR)


.PHONY: bootimg
bootimg: $(IMG)

$(IMG): $(BIN) $(MP1BOOT)
	# $(UBOOT_MKIMAGE) -A arm -C none -T firmware -a $(LOADADDR) -e $(ENTRYPOINT) -d $(BIN) $@
	# TODO: use MP1-Boot script to convert bin to img
	$(info sudo dd if=$(IMG) of=/dev/disk4s3)
	$(info Image created. Now copy image to sd card with this command (assumes /dev/disk4 is the sd card):)

#Used by norflash loader
%-uimg.h : %.uimg 
	cd $(dir $<) && xxd -i -c 8 $(notdir $<) $(notdir $@)

medium: all 

norflash-loader: bootimg

