# Makefile by Dan Green <danngreen1@gmail.com>, public domain

$(info Building for M7 core)
BUILDDIR = $(BUILDDIR_M7)
LOADFILE = $(LINKSCRIPTDIR)/stm32h755xx_flash_CM7.ld
MCU = -mcpu=cortex-m7 -mfpu=fpv5-d16 -mthumb -mlittle-endian -mfloat-abi=hard
ARCH_CFLAGS = -DARM_MATH_CM7 -DCORE_CM7
CORE_SRC = src/m7
HAL_CONF_INC = src/m7
HALDIR = $(HALBASE)/stm32h7x5
DEVICEDIR = $(DEVICEBASE)/stm32h7x5
TARGETDEVICEDIR = $(DRIVERLIB)/drivers/target/stm32h7x5

OPTFLAG = -O3
include makefile_opts.mk

MFFONTDIR = $(LIBDIR)/mcufont/fonts
MFDIR = $(LIBDIR)/mcufont/decoder
include $(LIBDIR)/mcufont/decoder/mcufont.mk

SOURCES  = $(STARTUP_H7)
SOURCES  += $(SYSTEM_H7)
SOURCES  += $(wildcard $(HALDIR)/src/*.c)
SOURCES  += $(wildcard $(DRIVERLIB)/drivers/*.cc)
SOURCES  += $(wildcard $(TARGETDEVICEDIR)/drivers/*.cc)
SOURCES  += $(wildcard $(CORE_SRC)/*.c)
SOURCES  += $(wildcard $(CORE_SRC)/*.cc)
SOURCES  += $(wildcard $(CORE_SRC)/*.cpp)
SOURCES  += $(wildcard src/*.c)
SOURCES  += $(wildcard src/*.cc)
SOURCES  += $(wildcard src/*.cpp)
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

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

INCLUDES = -I$(DEVICEDIR)/include \
			-I$(CMSIS)/Include \
			-I$(HALDIR)/include \
			-I$(DRIVERLIB) \
			-I$(DRIVERLIB)/drivers \
			-I$(DRIVERLIB)/drivers/target/stm32h7x5 \
			-I$(DRIVERLIB)/drivers/target/stm32h7x5/drivers \
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

include makefile_common.mk

