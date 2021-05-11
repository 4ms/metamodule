# Makefile by Dan Green <danngreen1@gmail.com>, public domain

$(info --------------------)
$(info Building for MP1 M4 core)
BUILDDIR = $(BUILDDIR_MP1M4)
LOADFILE = $(LINKSCRIPTDIR)/stm32mp15xx_m4.ld
CORE_SRC = src/mp1m4
HAL_CONF_INC = src/mp1m4
HALDIR = $(HALBASE)/stm32mp1
DEVICEDIR = $(DEVICEBASE)/stm32mp157c
TARGETDEVICEDIR = $(DRIVERLIB)/target/stm32mp1
TARGETDEVICEDIR_CM4 = $(DRIVERLIB)/target/stm32mp1_cm4

STARTUP = $(TARGETDEVICEDIR_CM4)/boot/startup_stm32mp157cxx_cm4.s
SYSTEM = $(DEVICEBASE)/stm32mp157c/templates/system_stm32mp1xx.c

OPTFLAG = -O0
include makefile_opts.mk

SOURCES  = $(STARTUP)
SOURCES  += $(SYSTEM)
SOURCES  += $(HALDIR)/src/stm32mp1xx_hal.c)
SOURCES  += $(HALDIR)/src/stm32mp1xx_hal_i2c.c)
SOURCES  += $(HALDIR)/src/stm32mp1xx_hal_i2c_ex.c)
SOURCES  += $(HALDIR)/src/stm32mp1xx_hal_rcc.c)
SOURCES  += $(HALDIR)/src/stm32mp1xx_ll_tim.c)
SOURCES  += $(HALDIR)/src/stm32mp1xx_hal_dma.c)
SOURCES  += $(HALDIR)/src/stm32mp1xx_hal_cortex.c)
SOURCES  += $(wildcard $(CORE_SRC)/*.c)
SOURCES  += $(wildcard $(CORE_SRC)/*.cc)
SOURCES  += $(wildcard $(CORE_SRC)/*.cpp)
SOURCES  += src/controls.cc
SOURCES  += system/libc_stub.c
SOURCES  += system/libcpp_stub.cc
SOURCES  += system/new.cc
SOURCES  += $(DRIVERLIB)/drivers/hal_handlers.cc
SOURCES  += $(DRIVERLIB)/drivers/i2c.cc
SOURCES  += $(TARGETDEVICEDIR_CM4)/drivers/interrupt_handler.cc
SOURCES  += $(DRIVERLIB)/drivers/pin.cc
SOURCES  += $(DRIVERLIB)/drivers/rotary.cc
SOURCES  += $(DRIVERLIB)/drivers/tim.cc
SOURCES  += $(DRIVERLIB)/drivers/timekeeper.cc
# SOURCES  += $(DRIVERLIB)/drivers/pca9685_led_driver.cc
# SOURCES  += $(DRIVERLIB)/drivers/pca9685_led_driver_dma.cc

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

INCLUDES = -I$(DEVICEDIR)/include \
			-I$(CMSIS)/Include \
			-I$(HALDIR)/include \
			-I$(DRIVERLIB) \
			-I$(DRIVERLIB)/drivers \
			-I$(TARGETDEVICEDIR) \
			-I$(TARGETDEVICEDIR)/drivers \
			-I$(TARGETDEVICEDIR_CM4) \
			-I$(TARGETDEVICEDIR_CM4)/drivers \
			-I$(LIBDIR)/easiglib \
			-I. \
			-Isrc \
			-Isrc/conf \
			-Isrc/mp1m4/conf \
			-Isystem \
			-I$(CORE_SRC) \
			-I$(HAL_CONF_INC) \
			-I$(SHARED) \
			-I$(SHARED)/processors \
			-I$(SHARED)/CoreModules \
			-I$(SHARED)/util \
			-I$(SHARED)/patch \

MCU = -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mlittle-endian -mfloat-abi=hard

ARCH_CFLAGS = -DUSE_HAL_DRIVER \
			  -DUSE_FULL_LL_DRIVER \
			  -DSTM32MP157Cxx \
			  -DSTM32MP1 \
			  -DCORE_CM4 \
			  -DARM_MATH_CM4 \

include makefile_common.mk

