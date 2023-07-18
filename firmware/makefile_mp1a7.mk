# Makefile by Dan Green <danngreen1@gmail.com>, public domain

USE_FEWER_MODULES ?= 1

#brands := 4ms Befaco AudibleInstruments

# First target of the make command is the board we should build for. Check if it's valid.
ifeq ($(MAKECMDGOALS),$(filter $(MAKECMDGOALS),$(VALID_BOARDS)))
target_board = $(word 1,$(MAKECMDGOALS))
$(info --------------------)
$(info Building for MP1 A7 core, target: $(target_board))

else ifeq ($(MAKECMDGOALS),uimg)
$(info Building uimg)
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

INCLUDES = 
SOURCES =

SOURCES += system/libc_stub.c
SOURCES += system/libcpp_stub.cc
SOURCES += system/new.cc
SOURCES += system/mmu_ca7.c
SOURCES += src/shared_memory.cc
SOURCES += src/uart_log.cc
SOURCES += $(main_source)
SOURCES += $(audio_source)
SOURCES += $(core_src)/aux_core_main.cc
SOURCES += src/patchlist.cc
SOURCES += src/patchlist_ryml_tests.cc
INCLUDES += -I.
INCLUDES += -Isrc
INCLUDES += -I$(core_src)
INCLUDES += -I$(target_src)
INCLUDES += -I$(target_chip_src)
INCLUDES += -I$(SHARED)
INCLUDES += -I$(SHARED)/patch


# Printf
SOURCES += $(LIBDIR)/printf/printf.c
INCLUDES += -I$(LIBDIR)/printf

# HAL
SOURCES += $(TARGETDEVICEDIR_CA7)/boot/system_ca7.c
SOURCES += $(TARGETDEVICEDIR_CA7)/boot/irq_ctrl.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_rcc.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_rcc_ex.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_mdma.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_usart.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_uart.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_dma.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_i2c.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_i2c_ex.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_sai.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_ltdc.c
SOURCES += $(HALDIR)/src/stm32mp1xx_ll_tim.c
SOURCES += $(HALDIR)/src/stm32mp1xx_ll_rcc.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_sd.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_sd_ex.c
SOURCES += $(HALDIR)/src/stm32mp1xx_ll_sdmmc.c
INCLUDES += -I$(HALDIR)/include
INCLUDES += -I$(CMSIS)/Core_A/Include
INCLUDES += -I$(CMSIS)/Include
INCLUDES += -I$(DEVICEDIR)/include

# mdrivlib
SOURCES += $(DRIVERLIB)/drivers/pin.cc
SOURCES += $(TARGETDEVICEDIR_CA7)/drivers/interrupt_handler.cc
SOURCES += $(DRIVERLIB)/drivers/timekeeper.cc
SOURCES += $(DRIVERLIB)/drivers/tim.cc
SOURCES += $(TARGETDEVICEDIR_CA7)/drivers/hal_handlers.cc
SOURCES += $(TARGETDEVICEDIR_CA7)/drivers/cycle_counter.cc
SOURCES += $(DRIVERLIB)/drivers/i2c.cc
SOURCES += $(TARGETDEVICEDIR)/drivers/sai_tdm.cc
SOURCES += $(DRIVERLIB)/drivers/codec_PCM3168.cc
INCLUDES += -I$(DRIVERLIB)
INCLUDES += -I$(DRIVERLIB)/drivers
INCLUDES += -I$(TARGETDEVICEDIR)
INCLUDES += -I$(TARGETDEVICEDIR)/drivers
INCLUDES += -I$(TARGETDEVICEDIR_CA7)
INCLUDES += -I$(TARGETDEVICEDIR_CA7)/drivers

# Util
SOURCES += $(SHARED)/cpputil/util/math_tables.cc
INCLUDES += -I$(SHARED)/cpputil

# GUI
SOURCES += $(wildcard src/pages/elements/*.cc)
SOURCES += src/pages/page_manager.cc

# Modules: CoreModules and faceplate artwork 
SOURCES += $(SHARED)/CoreModules/hub/hub_medium.cc
ifeq "$(USE_FEWER_MODULES)" "1"
modulesAudible := Braids

modulesBefaco := EvenVCO
modulesBefaco += DualAtenuverter
modulesBefaco += SpringReverb
modulesBefaco += ABC
modulesBefaco += ADSR
modulesBefaco += ChoppingKinky
modulesBefaco += HexmixVCA
modulesBefaco += Kickall
modulesBefaco += Mixer
modulesBefaco += Morphader
modulesBefaco += MotionMTR
# modulesBefaco += Muxlicer #can't change visibility dynamically
modulesBefaco += Percall
modulesBefaco += PonyVCO
modulesBefaco += Rampage
modulesBefaco += STMix
modulesBefaco += SamplingModulator
modulesBefaco += SlewLimiter
modulesBefaco += StereoStrip
# modulesBefaco += NoisePlethora

modules4ms := EnOsc ENVVCA 
modules4ms += Djembe StMix PEG SMR MultiLFO PitchShift
modules4ms += HPF InfOsc KPLS Freeverb Seq8

SOURCES += $(foreach m,$(modulesAudible),vcv-ports/AudibleInstruments/src/$(m).cpp)
SOURCES += $(foreach m,$(modulesBefaco),vcv-ports/Befaco/src/$(m).cpp)
SOURCES += $(foreach m,$(modules4ms),$(SHARED)/CoreModules/4ms/core/$(m)Core.cc)

SOURCES += $(foreach m,$(modulesAudible),src/pages/images/AudibleInstruments/modules/$(m)_artwork_240.c)
SOURCES += $(foreach m,$(modulesAudible),src/pages/images/AudibleInstruments/modules/$(m)_artwork_120.c)
SOURCES += $(foreach m,$(modulesBefaco),src/pages/images/Befaco/modules/$(m)_artwork_240.c)
SOURCES += $(foreach m,$(modulesBefaco),src/pages/images/Befaco/modules/$(m)_artwork_120.c)
SOURCES += $(foreach m,$(modules4ms),src/pages/images/4ms/modules/$(m)_artwork_240.c)
SOURCES += $(foreach m,$(modules4ms),src/pages/images/4ms/modules/$(m)_artwork_120.c)

else
SOURCES += $(wildcard $(SHARED)/CoreModules/4ms/core/*.cc)
SOURCES += $(wildcard vcv-ports/AudibleInstruments/src/*.cpp)
SOURCES += $(wildcard vcv-ports/Befaco/src/*.cpp)

SOURCES += $(wildcard src/pages/images/4ms/modules/*.c)
SOURCES += $(wildcard src/pages/images/Befaco/modules/*.c)
SOURCES += $(wildcard src/pages/images/AudibleInstruments/modules/*.c)
endif

INCLUDES += -I$(SHARED)/CoreModules
INCLUDES += -I$(SHARED)/CoreModules/4ms
INCLUDES += -Ivcv-ports/AudibleInstruments/src/
INCLUDES += -Ivcv-ports/AudibleInstruments/eurorack
INCLUDES += -Ivcv-ports/Befaco/src

SOURCES += vcv-ports/register_vcv_ports.cc
SOURCES += src/VCV-adaptor/pffft/pffft.c
INCLUDES += -Isrc/VCV-adaptor
INCLUDES += -Isrc/VCV-adaptor/pffft

# Component images
SOURCES += $(wildcard src/pages/images/4ms/components/*.c)
SOURCES += $(wildcard src/pages/images/Befaco/components/*.c)
SOURCES += $(wildcard src/pages/images/AudibleInstruments/components/*.c)

# Module support files
SOURCES += $(SHARED)/CoreModules/4ms/core/enosc/data.cc
SOURCES += $(SHARED)/CoreModules/4ms/core/enosc/dynamic_data.cc
SOURCES += $(SHARED)/CoreModules/AudibleInstruments/core/stmlib/utils/random.cc
SOURCES += $(SHARED)/CoreModules/AudibleInstruments/core/stmlib/dsp/atan.cc
SOURCES += $(SHARED)/CoreModules/AudibleInstruments/core/stmlib/dsp/units.cc
SOURCES += $(SHARED)/CoreModules/AudibleInstruments/core/braids/analog_oscillator.cc
SOURCES += $(SHARED)/CoreModules/AudibleInstruments/core/braids/digital_oscillator.cc
SOURCES += $(SHARED)/CoreModules/AudibleInstruments/core/braids/macro_oscillator.cc
SOURCES += $(SHARED)/CoreModules/AudibleInstruments/core/braids/resources.cc
SOURCES += $(SHARED)/axoloti-wrapper/axoloti_math.cpp

## LVGL / Gui-Guider
SOURCES += $(shell find -L $(LIBDIR)/lvgl/lvgl/src/extra/widgets -name \*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/extra/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/extra/libs/png/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/extra/layouts/flex/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/extra/layouts/grid/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/extra/others/gridnav/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/extra/themes/default/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/core/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/draw/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/draw/sw/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/widgets/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/font/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/misc/*.c)
SOURCES += $(wildcard $(LIBDIR)/lvgl/lvgl/src/hal/*.c)
INCLUDES +=	-I$(LIBDIR)/lvgl
INCLUDES +=	-I$(LIBDIR)/lvgl/lvgl

# Fonts
SOURCES += src/pages/fonts/MuseoSansRounded_500_12.c
SOURCES += src/pages/fonts/MuseoSansRounded_700_12.c
SOURCES += src/pages/fonts/MuseoSansRounded_700_14.c
SOURCES += src/pages/fonts/MuseoSansRounded_700_16.c
SOURCES += src/pages/fonts/MuseoSansRounded_700_18.c

# Generated:
SOURCES += src/pages/slsexport/patchsel/ui.c
SOURCES += src/pages/slsexport/patchsel/ui_helpers.c
SOURCES += $(wildcard src/pages/slsexport/patchsel/ui_font_*.c)
SOURCES += src/pages/slsexport/patchview/ui.c
#patchview
SOURCES += $(wildcard src/pages/slsexport/patchview/components/*.c)
SOURCES += $(wildcard src/pages/slsexport/patchview/images/*.c)
SOURCES += $(wildcard src/pages/slsexport/patchview/fonts/*.c)
SOURCES += $(wildcard src/pages/slsexport/patchview/screens/*.c)
INCLUDES += -Isrc/pages/slsexport

# Patch convert
SOURCES += $(SHARED)/patch_convert/yaml_to_patch.cc
SOURCES += $(SHARED)/patch_convert/ryml/ryml_serial.cc
INCLUDES += -I$(SHARED)/patch_convert
INCLUDES += -I$(SHARED)/patch_convert/ryml
## RapidYml
RYMLDIR = $(SHARED)/patch_convert/ryml/rapidyaml
SOURCES += $(wildcard $(RYMLDIR)/src/c4/yml/*.cpp)
SOURCES += $(wildcard $(RYMLDIR)/ext/c4core/src/c4/*.cpp)
INCLUDES += -I$(RYMLDIR)/src
INCLUDES += -I$(RYMLDIR)/ext/c4core/src

## FatFS, qspi flash

SOURCES += $(LIBDIR)/fatfs/source/ff.c
SOURCES += $(LIBDIR)/fatfs/source/ffunicode.c
SOURCES += src/fatfs/diskio.cc
SOURCES += src/fatfs/fattime.cc
SOURCES += src/patch_fileio.cc
SOURCES += src/time_convert.cc
SOURCES += $(LIBDIR)/littlefs/lfs.c
SOURCES += $(LIBDIR)/littlefs/lfs_util.c
SOURCES += $(HALDIR)/src/stm32mp1xx_hal_qspi.c
SOURCES += $(DRIVERLIB)/drivers/qspi_flash_driver.cc
INCLUDES += -I$(LIBDIR)/fatfs/source
INCLUDES += -Isrc/fatfs


#D-Cache L1: 32 KB, 128 Sets, 64 Bytes/Line, 4-Way
EXTRA_CFLAGS = --param l1-cache-size=32 \
	 		   --param l1-cache-line-size=64 \
			   --param l2-cache-size=256 \

				# -DNE10_ENABLE_DSP \
				# $(NE10_CFLAGS) \

ifeq "$(USE_FEWER_MODULES)" "1"
	EXTRA_CFLAGS += -D'USE_FEWER_MODULES=1'
endif

EXTRA_CPPFLAGS = $(LTOFLAG) -ffold-simple-inlines \
				-Wno-psabi -Wno-double-promotion 

$(BUILDDIR)/vcv-ports/Befaco/src/%.o: EXTRA_CPPFLAGS += -Wno-deprecated-enum-float-conversion
$(BUILDDIR)/vcv-ports/AudibleInstruments/src/%.o: EXTRA_CPPFLAGS += -Wno-deprecated-enum-float-conversion

EXTRA_LFLAGS = $(LTOFLAG) $(OPTFLAG) \
				-L$(BUILDDIR_MP1M4)/$(target_board) \
				-Wno-psabi

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
UIMG  		= $(BUILDDIR)/$(BINARYNAME).uimg

.PHONY: uimg
uimg: $(UIMG)

$(UIMG): $(BIN)
	python3 flashing/uimg_header.py $< $@ 0xC1FBFFC0 0xC2000040

#Used by norflash loader
%-uimg.h : %.uimg 
	cd $(dir $<) && xxd -i -c 8 $(notdir $<) $(notdir $@)

medium: all uimg

norflash-loader: uimg

