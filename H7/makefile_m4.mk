# Makefile by Dan Green <danngreen1@gmail.com>, public domain

$(info Building for M4 core)
BUILDDIR = $(BUILDDIR_M4)
LOADFILE	= stm32h755xx_flash_CM4.ld
MCU =  -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mlittle-endian -mfloat-abi=hard
ARCH_CFLAGS = -DARM_MATH_CM4 -DCORE_CM4
CORE_SRC = src/m4
HAL_CONF_INC = src/m4

OPTFLAG = -O3
include makefile_opts.mk

SOURCES  = $(DRIVERLIB)/drivers/$(STARTUP)
SOURCES  += $(DEVICE)/src/$(SYSTEM)
SOURCES  += $(wildcard $(PERIPH)/src/*.c)
SOURCES  += $(wildcard $(CORE_SRC)/*.c)
SOURCES  += $(wildcard $(CORE_SRC)/*.cc)
SOURCES  += $(wildcard $(CORE_SRC)/*.cpp)
SOURCES  += $(wildcard src/sys/*.c)
SOURCES  += $(wildcard src/sys/*.cc)
SOURCES  += $(DRIVERLIB)/drivers/hal_handlers.cc
SOURCES  += $(DRIVERLIB)/drivers/i2c.cc
SOURCES  += $(DRIVERLIB)/drivers/interrupt.cc
SOURCES  += $(DRIVERLIB)/drivers/pin.cc
SOURCES  += $(DRIVERLIB)/drivers/rotary.cc
SOURCES  += $(DRIVERLIB)/drivers/system.cc
SOURCES  += $(DRIVERLIB)/drivers/tim.cc
SOURCES  += $(DRIVERLIB)/drivers/timekeeper.cc
SOURCES  += $(DRIVERLIB)/drivers/pca9685_led_driver.cc
SOURCES  += $(DRIVERLIB)/drivers/pca9685_led_driver_dma.cc

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
			-I$(LIBDIR)/adafruit_gfx/Adafruit_ST7735_and_ST7789_Library \
			-I$(LIBDIR)/adafruit_gfx/Adafruit_GFX_Library \
			-I$(LIBDIR)/adafruit_gfx/arduino \
			-I$(LIBDIR)/adafruit_gfx/SPI \
			-I$(LIBDIR)/adafruit_gfx \

include makefile_common.mk

