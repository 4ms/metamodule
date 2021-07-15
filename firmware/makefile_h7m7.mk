# Makefile by Dan Green <danngreen1@gmail.com>, public domain

$(info --------------------)
$(info Building for H7 M7 core)
BUILDDIR = $(BUILDDIR_H7M7)
LOADFILE = $(LINKSCRIPTDIR)/stm32h755xx_flash_CM7.ld
MCU = -mcpu=cortex-m7 -mfpu=fpv5-d16 -mthumb -mlittle-endian -mfloat-abi=hard
ARCH_CFLAGS = -DARM_MATH_CM7 -DCORE_CM7
CORE_SRC = src/m7
HAL_CONF_INC = src/m7
HALDIR = $(HALBASE)/stm32h7x5
DEVICEDIR = $(DEVICEBASE)/stm32h7x5
TARGETDEVICEDIR = $(DRIVERLIB)/target/stm32h7x5
TARGETCOREDIR = $(DRIVERLIB)/target/stm32h7x5_m7

STARTUP_H7 = $(TARGETDEVICEDIR)/boot/startup_cm7.s
SYSTEM_H7 = system/system_stm32h7xx_dualcore_boot_cm4_cm7.c

OPTFLAG = -O3
include makefile_opts.mk

MFFONTDIR = $(LIBDIR)/mcufont/fonts
MFDIR = $(LIBDIR)/mcufont/decoder
include $(LIBDIR)/mcufont/decoder/mcufont.mk

ASM_SOURCES  = $(STARTUP_H7)
SOURCES  = $(SYSTEM_H7)
SOURCES  += $(wildcard $(HALDIR)/src/*.c)
SOURCES  += $(wildcard $(DRIVERLIB)/drivers/*.cc)
SOURCES  += $(wildcard $(TARGETDEVICEDIR)/drivers/*.cc)
SOURCES  += $(wildcard $(TARGETCOREDIR)/drivers/*.cc)
SOURCES  += $(wildcard $(CORE_SRC)/*.c)
SOURCES  += $(wildcard $(CORE_SRC)/*.cc)
SOURCES  += $(wildcard $(CORE_SRC)/*.cpp)
SOURCES  += src/audio.cc
SOURCES  += src/patchlist.cc
SOURCES  += src/print.cc
SOURCES  += $(wildcard system/libc_stub.c)
SOURCES  += $(wildcard system/libcpp_stub.cc)
SOURCES  += $(wildcard system/new.cc)
SOURCES  += $(wildcard src/pages/*.cc)
SOURCES  += $(wildcard $(SHARED)/util/*.c)
SOURCES  += $(wildcard $(SHARED)/util/*.cc)
SOURCES  += $(wildcard $(SHARED)/util/*.cpp)
SOURCES  += $(wildcard $(SHARED)/CoreModules/*.cpp)
SOURCES  += $(LIBDIR)/printf/printf.c
SOURCES  += $(MFSRC)

INCLUDES = -I$(DEVICEDIR)/include \
			-I$(CMSIS)/Include \
			-I$(HALDIR)/include \
			-I$(DRIVERLIB) \
			-I$(DRIVERLIB)/drivers \
			-I$(TARGETDEVICEDIR) \
			-I$(TARGETDEVICEDIR)/drivers \
			-I$(TARGETCOREDIR) \
			-I$(TARGETCOREDIR)/drivers \
			-I$(LIBDIR)/easiglib \
			-I. \
			-Isrc \
			-Isrc/conf \
			-I$(CORE_SRC) \
			-I$(HAL_CONF_INC) \
			-I$(SHARED) \
			-I$(SHARED)/processors \
			-I$(SHARED)/CoreModules \
			-I$(SHARED)/util \
			-I$(SHARED)/patch \
			-I$(LIBDIR)/printf \
			-I$(MFINC) \
			-I$(MFFONTDIR) \


EXTRA_CFLAGS = --param l1-cache-size=16 \
	 		   --param l1-cache-line-size=32 \

EXTDEF ?= METAMODULE_NORMAL_MODE

ARCH_CFLAGS += -D'__FPU_PRESENT=1' \
			  -DUSE_HAL_DRIVER \
			  -DUSE_FULL_LL_DRIVER \
			  -DSTM32H745xx \
			  -DSTM32H7x5xx \
			  -DSTM32H7 \
			  -D$(EXTDEF)


include makefile_common.mk

