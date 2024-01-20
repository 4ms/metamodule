BINARYNAME := testbrand
BUILDDIR := build

SHAREDDIR := ../../../shared
LIBDIR := ../../lib

# RACK_DIR = ./Rack-SDK
# VCVINCLUDES := -I$(RACK_DIR)/include \
# 			   -I$(RACK_DIR)/dep/include

# VCVINCLUDES := -IVCV_adaptor -I.

VCVINCLUDES := -I../../src/VCV_adaptor -I../../src

# VCVINCLUDES := -Iplugin



SOURCES = test_brand/src/test_module.cpp \
		  test_brand/src/plugin.cpp \
		  plugin/libc_stub.c

INCLUDES := -Itest_brand/src \
			-Itest_brand \
			-I$(LIBDIR)/jansson \
			-I$(LIBDIR)/jansson/jansson/src \
			-I$(SHAREDDIR) \
			-I$(SHAREDDIR)/cpputil \
			$(VCVINCLUDES)

# LINKSCR := linkscript.ld

ARCH_CFLAGS := -DSTM32MP157Cxx -DSTM32MP1 -DCORE_CA7

LFLAGS = $(MCU)  \
		 -Wl,-Map,$(BUILDDIR)/$(BINARYNAME).map,--cref \
		 -Wl,--gc-sections \
		 -nostdlib \
		 -shared
		#-nostartfiles -ffreestanding

%.diss : %.elf
	arm-none-eabi-objdump -CDz --source $^ > $@

%.nm : %.elf
	arm-none-eabi-nm -CA $^ > $@

%.readelf : %.elf
	arm-none-eabi-readelf --demangle=auto -a -W $^ > $@


#### Shared lib (-shared), multiple files ##################

EXTRACFLAGS = -fPIC -c

####################################################################
####################################################################
####################################################################

OBJDIR = $(BUILDDIR)/obj/obj

OBJECTS   = $(addprefix $(OBJDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(OBJDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

MCU ?=  -mcpu=cortex-a7 -march=armv7ve -mfpu=neon-vfpv4 -mlittle-endian -mfloat-abi=hard

EXTRA_ARCH_CFLAGS ?= 

ARCH_CFLAGS ?= -DUSE_FULL_LL_DRIVER \
			   -DSTM32MP157Cxx \
			   -DSTM32MP1 \
			   -DCORE_CA7 \
			   $(EXTRA_ARCH_CFLAGS) \

OPTFLAG ?= -O0

AFLAGS = $(MCU)

EXTRACFLAGS ?= -c

CFLAGS ?= -g2 \
		 -fno-common \
		 $(ARCH_CFLAGS) \
		 $(MCU) \
		 $(INCLUDES) \
		 -fdata-sections -ffunction-sections \
		 $(EXTRACFLAGS)\

		 # -nostartfiles \
		 # -ffreestanding \

CXXFLAGS ?= $(CFLAGS) \
		-std=c++2a \
		-fno-exceptions \
		-fno-unwind-tables \
		-fno-threadsafe-statics \
		-mno-unaligned-access \
		-Werror=return-type \
		-Wdouble-promotion \
		-Wno-register \
		-Wno-volatile \
		 $(EXTRACXXFLAGS) \
		-fno-rtti \

LINK_STDLIB ?= -nostdlib

# LFLAGS ?= -Wl,--gc-sections \
# 		 -Wl,-Map,$(BUILDDIR)/$(BINARYNAME).map,--cref \
# 		 $(MCU)  \
# 		 $(LINK_STDLIB) \
# 		 -nostartfiles \
# 		 -ffreestanding \
# 		 $(EXTRALDFLAGS)

ifneq ("$(LINKSCR)","")
LFLAGS += -T $(LINKSCR)
endif

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

SZOPTS 	= -d

# SO 	    = $(BUILDDIR)/$(BINARYNAME).so
ELF 	= $(BUILDDIR)/$(BINARYNAME).elf
HEX 	= $(BUILDDIR)/$(BINARYNAME).hex
BIN 	= $(BUILDDIR)/$(BINARYNAME).bin

all: Makefile $(ELF) 

dis: all $(BUILDDIR)/$(BINARYNAME).nm $(BUILDDIR)/$(BINARYNAME).readelf $(BUILDDIR)/$(BINARYNAME).diss 

$(OBJDIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(info)# Building $<)
	$(AS) $(AFLAGS) $< -o $@ 

$(OBJDIR)/%.o: %.c $(OBJDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	$(CC) $(DEPFLAGS) $(OPTFLAG) $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: %.c[cp]* $(OBJDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	$(CXX) $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@


# $(SO): $(OBJECTS)
# 	$(info Linking shared library...)
# 	$(LD) -shared $(LFLAGS) -o $@ $(OBJECTS)

$(ELF): $(OBJECTS) $(LINKSCR)
	$(info Linking...)
	$(LD) $(LFLAGS) -o $@ $(OBJECTS) 

$(BIN): $(ELF)
	$(OBJCPY) -O binary $< $@

$(HEX): $(ELF)
	@$(OBJCPY) --output-target=ihex $< $@
	@$(SZ) $(SZOPTS) $(ELF)

%.d: ;

clean:
	rm -rf build

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS) $(ELF)
.PHONY: all clean install install-mp1-boot

