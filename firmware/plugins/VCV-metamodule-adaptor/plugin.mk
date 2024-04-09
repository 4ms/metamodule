ARCH_CFLAGS :=  -DSTM32MP157Cxx -DSTM32MP1 -DCORE_CA7 \
				-DUSE_HAL_DRIVER -DUSE_FULL_LL_DRIVER \
				--param l1-cache-size=32 \
				--param l1-cache-line-size=64 \
				--param l2-cache-size=256 \

MCU := \
    -fno-exceptions \
    -fno-math-errno \
    -mcpu=cortex-a7 \
    -mlittle-endian \
    -mfpu=neon-vfpv4 \
    -mfloat-abi=hard \
    -mthumb-interwork \
    -mno-unaligned-access \
    -mtune=cortex-a7 \
    -mvectorize-with-neon-quad \
    -funsafe-math-optimizations \

BINARYNAME := $(PLUGINNAME)
BUILDDIR := build
OBJDIR := $(BUILDDIR)/obj/obj

LFLAGS := $(MCU)  \
		 -Wl,-Map,$(BUILDDIR)/$(BINARYNAME).map,--cref \
		 -Wl,--gc-sections \
		 -nostartfiles -nostdlib

OPTFLAG ?= -O3

AFLAGS = $(MCU)

CFLAGS ?= \
		-g2 \
		$(ARCH_CFLAGS) \
		$(MCU) \
		$(INCLUDES) \
		-fno-common \
		-fdata-sections -ffunction-sections \
		-fno-unwind-tables \
		-fPIC \
		-nostartfiles \
		-nostdlib \
		-shared \
		-c \
		-Wno-double-promotion \
		-Wno-attributes \
		-Wno-psabi

CXXFLAGS ?= $(CFLAGS) \
		-std=c++2a \
		-fno-exceptions \
		-fno-threadsafe-statics \
		-fno-rtti \
		-ffold-simple-inlines \
		-Werror=return-type \
		-Wno-register \
		-Wno-volatile \
		$(EXTRA_CPPFLAGS) \

		
SOURCES += $(ADAPTORDIR)/libc_stub.c 
INCLUDES += \
			-I$(ADAPTORDIR)/include \
			-I$(ADAPTORDIR)/dep/include \
			-I$(ADAPTORDIR)/dep/include/cpputil


OBJECTS   = $(addprefix $(OBJDIR)/, $(addsuffix .obj, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(OBJDIR)/, $(addsuffix .d, $(basename $(SOURCES))))
DEPFLAGS = -MMD -MP -MF $(OBJDIR)/$(basename $<).d

ARCH 	= arm-none-eabi
CC 		= $(ARCH)-gcc
CXX 	= $(ARCH)-g++
LD 		= $(ARCH)-g++
AS 		= $(ARCH)-as
OBJCPY 	= $(ARCH)-objcopy
OBJDMP 	= $(ARCH)-objdump
GDB 	= $(ARCH)-gdb
SZ 		= $(ARCH)-size
STRIP	= $(ARCH)-strip

SO 	    = $(BUILDDIR)/$(BINARYNAME)-debug.so
SOSTRIP = $(BUILDDIR)/$(BINARYNAME).so

all: Makefile $(SOSTRIP) 

$(OBJDIR)/%.obj: %.s
	@mkdir -p $(dir $@)
	$(info Building $<)
	$(AS) $(AFLAGS) $< -o $@ 

$(OBJDIR)/%.obj: %.c $(OBJDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CC) $(DEPFLAGS) $(OPTFLAG) $(CFLAGS) $< -o $@

$(OBJDIR)/%.obj: %.c[cp]* $(OBJDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CXX) $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@

$(SO): $(OBJECTS)
	$(info Linking shared library...)
	@$(LD) -shared $(LFLAGS) -o $@ $(OBJECTS)

$(SOSTRIP): $(SO)
	$(STRIP) -g -v -o $@ $<
	@ls -l $@

%.diss : %.so
	arm-none-eabi-objdump -CDz --source $^ > $@

%.nm : %.so
	arm-none-eabi-nm -CA $^ > $@

%.readelf : %.so
	arm-none-eabi-readelf --demangle=auto -a -W $^ > $@

%.d: ;

clean:
	rm -rf build

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS) $(SO) $(SOSTRIP) $(SOSTRIP_H)
.PHONY: all clean 



