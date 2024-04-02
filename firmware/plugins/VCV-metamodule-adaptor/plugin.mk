ARCH_CFLAGS := -DSTM32MP157Cxx -DSTM32MP1 -DCORE_CA7

MCU :=  -mcpu=cortex-a7 -march=armv7ve -mfpu=neon-vfpv4 -mlittle-endian -mfloat-abi=hard

LFLAGS := $(MCU)  \
		 -Wl,-Map,$(BUILDDIR)/$(BINARYNAME).map,--cref \
		 -Wl,--gc-sections \
		 -nostartfiles -nostdlib

OPTFLAG ?= -O2

AFLAGS = $(MCU)

CFLAGS ?= -g2 \
		 -fno-common \
		 $(ARCH_CFLAGS) \
		 $(MCU) \
		 $(INCLUDES) \
		 -fdata-sections -ffunction-sections \
		 -fPIC \
		 -nostartfiles \
		 -nostdlib \
		 -shared \
		 -c \
		 -Wno-double-promotion \
		 -Wno-attributes \

CXXFLAGS ?= $(CFLAGS) \
		-std=c++2a \
		-fno-exceptions \
		-fno-unwind-tables \
		-fno-threadsafe-statics \
		-mno-unaligned-access \
		-Werror=return-type \
		-Wno-register \
		-Wno-volatile \
		-fno-rtti \
		$(EXTRA_CPPFLAGS) \
		

OBJECTS   = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
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

SO 	    = $(BUILDDIR)/$(BINARYNAME).so
SOSTRIP = $(BUILDDIR)/$(BINARYNAME)-strip.so
SOSTRIP_H = $(BUILDDIR)/$(BINARYNAME)-strip-so.h

all: Makefile $(SOSTRIP) 

$(OBJDIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(info Building $<)
	$(AS) $(AFLAGS) $< -o $@ 

$(OBJDIR)/%.o: %.c $(OBJDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CC) $(DEPFLAGS) $(OPTFLAG) $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: %.c[cp]* $(OBJDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CXX) $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@

$(SO): $(OBJECTS)
	$(info Linking shared library...)
	@$(LD) -shared $(LFLAGS) -o $@ $(OBJECTS)

$(SOSTRIP): $(SO)
	$(STRIP) -g -v -o $@ $<

# $(SOSTRIP_H): $(SOSTRIP)
# 	cd build && xxd -i $(BINARYNAME)-strip.so > $(BINARYNAME)-strip-so.h

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



