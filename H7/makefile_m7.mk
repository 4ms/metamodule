# Makefile by Dan Green <danngreen1@gmail.com>, public domain

$(info Building for M7 core)
BUILDDIR = $(BUILDDIR_M7)
LOADFILE	= stm32h755xx_flash_CM7.ld
MCU =  -mcpu=cortex-m7 -mfpu=fpv5-d16 -mthumb -mlittle-endian -mfloat-abi=hard
ARCH_CFLAGS = -DARM_MATH_CM7 -DCORE_CM7
CORE_SRC = src/m7
HAL_CONF_INC = src/m7

OPTFLAG = -O3
include makefile_opts.mk

MFDIR = $(LIBDIR)/mcufont/decoder
include $(LIBDIR)/mcufont/decoder/mcufont.mk

SOURCES  = $(DRIVERLIB)/drivers/$(STARTUP)
SOURCES  += $(DEVICE)/src/$(SYSTEM)
SOURCES  += $(wildcard $(PERIPH)/src/*.c)
SOURCES  += $(wildcard $(DRIVERLIB)/drivers/*.c)
SOURCES  += $(wildcard $(DRIVERLIB)/drivers/*.cc)
SOURCES  += $(wildcard $(DRIVERLIB)/drivers/*.cpp)
SOURCES  += $(wildcard $(CORE_SRC)/*.c)
SOURCES  += $(wildcard $(CORE_SRC)/*.cc)
SOURCES  += $(wildcard $(CORE_SRC)/*.cpp)
SOURCES  += $(wildcard src/*.c)
SOURCES  += $(wildcard src/*.cc)
SOURCES  += $(wildcard src/*.cpp)
SOURCES  += $(wildcard src/sys/*.c)
SOURCES  += $(wildcard src/sys/*.cc)
SOURCES  += $(wildcard src/sys/*.cpp)
SOURCES  += $(wildcard src/pages/*.cc)
SOURCES  += $(wildcard $(SHARED)/util/*.c)
SOURCES  += $(wildcard $(SHARED)/util/*.cc)
SOURCES  += $(wildcard $(SHARED)/util/*.cpp)
SOURCES  += $(wildcard $(SHARED)/CoreModules/*.cpp)
SOURCES  += $(LIBDIR)/printf/printf.c
SOURCES  += $(MFSRC)

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

INCLUDES = -I$(DEVICE)/include \
			-I$(CMSIS)/include \
			-I$(PERIPH)/include \
			-I$(DRIVERLIB) \
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

include makefile_common.mk

