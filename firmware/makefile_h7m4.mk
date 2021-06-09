# Makefile by Dan Green <danngreen1@gmail.com>, public domain

$(info --------------------)
$(info Building for H7 M4 core)
BUILDDIR = $(BUILDDIR_H7M4)
LOADFILE = $(LINKSCRIPTDIR)/stm32h755xx_flash_CM4.ld
MCU = -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mlittle-endian -mfloat-abi=hard
ARCH_CFLAGS = -DARM_MATH_CM4 -DCORE_CM4
CORE_SRC = src/m4
HAL_CONF_INC = src/m4
HALDIR = $(HALBASE)/stm32h7x5
DEVICEDIR = $(DEVICEBASE)/stm32h7x5
TARGETDEVICEDIR = $(DRIVERLIB)/target/stm32h7x5
TARGETCOREDIR = $(DRIVERLIB)/target/stm32h7x5_m4

STARTUP_H7 = $(TARGETDEVICEDIR)/boot/startup_cm7.s
SYSTEM_H7 = system/system_stm32h7xx_dualcore_boot_cm4_cm7.c

OPTFLAG = -O3
include makefile_opts.mk

SOURCES  = $(STARTUP_H7)
SOURCES  += $(SYSTEM_H7)
SOURCES  += $(wildcard $(HALDIR)/src/*.c)
SOURCES  += $(wildcard $(CORE_SRC)/*.c)
SOURCES  += $(wildcard $(CORE_SRC)/*.cc)
SOURCES  += $(wildcard $(CORE_SRC)/*.cpp)
SOURCES  += system/libc_stub.c
SOURCES  += system/libcpp_stub.cc
SOURCES  += system/new.cc
SOURCES  += src/controls.cc
SOURCES  += $(DRIVERLIB)/drivers/hal_handlers.cc
SOURCES  += $(DRIVERLIB)/drivers/i2c.cc
SOURCES  += $(TARGETDEVICEDIR)/drivers/interrupt_handler.cc
SOURCES  += $(DRIVERLIB)/drivers/pin.cc
SOURCES  += $(DRIVERLIB)/drivers/rotary.cc
SOURCES  += $(DRIVERLIB)/drivers/tim.cc
SOURCES  += $(DRIVERLIB)/drivers/timekeeper.cc
SOURCES  += $(DRIVERLIB)/drivers/pca9685_led_driver.cc
SOURCES  += $(DRIVERLIB)/drivers/pca9685_led_driver_dma.cc

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

INCLUDES = -I$(DEVICEDIR)/include \
			-I$(CMSIS)/Include \
			-I$(HALDIR)/include \
			-I$(DRIVERLIB) \
			-I$(DRIVERLIB)/drivers \
			-I$(TARGETCOREDIR) \
			-I$(TARGETCOREDIR)/drivers \
			-I$(TARGETDEVICEDIR) \
			-I$(TARGETDEVICEDIR)/drivers \
			-I$(LIBDIR)/easiglib \
			-I. \
			-Isrc \
			-Isrc/conf \
			-Isrc/m4/conf \
			-I$(CORE_SRC) \
			-I$(HAL_CONF_INC) \
			-I$(SHARED) \
			-I$(SHARED)/processors \
			-I$(SHARED)/CoreModules \
			-I$(SHARED)/util \
			-I$(SHARED)/patch \

EXTRA_CFLAGS = 

EXTDEF ?= METAMODULE_NORMAL_MODE

ARCH_CFLAGS += -D'__FPU_PRESENT=1' \
			  -DUSE_HAL_DRIVER \
			  -DUSE_FULL_LL_DRIVER \
			  -DSTM32H745xx \
			  -DSTM32H7x5xx \
			  -DSTM32H7 \
			  -D$(EXTDEF)


include makefile_common.mk

