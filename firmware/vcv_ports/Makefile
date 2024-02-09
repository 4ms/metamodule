BINARYNAME := Befaco
BUILDDIR := build

SHAREDDIR := ../../../shared
SCRIPTDIR := ../../../scripts
LIBDIR := ../lib

SOURCES = plugin/libc_stub.c \
		Befaco/src/plugin.cpp \
		Befaco/src/EvenVCO.cpp \
		Befaco/src/DualAtenuverter.cpp \
		Befaco/src/SpringReverb.cpp \
		Befaco/src/ABC.cpp \
		Befaco/src/ADSR.cpp \
		Befaco/src/ChoppingKinky.cpp \
		Befaco/src/HexmixVCA.cpp \
		Befaco/src/Kickall.cpp \
		Befaco/src/Mixer.cpp \
		Befaco/src/Morphader.cpp \
		Befaco/src/MotionMTR.cpp \
		Befaco/src/Percall.cpp \
		Befaco/src/PonyVCO.cpp \
		Befaco/src/Rampage.cpp \
		Befaco/src/STMix.cpp \
		Befaco/src/SamplingModulator.cpp \
		Befaco/src/SlewLimiter.cpp \
		Befaco/src/StereoStrip.cpp \

INCLUDES := -IBefaco/src \
			-I../src \
			-I../src/VCV_adaptor \
			-I../src/VCV_adaptor/pffft \
			-I$(LIBDIR)/jansson \
			-I$(LIBDIR)/jansson/jansson/src \
			-I../../shared \
			-I../../shared/cpputil \
			-I..

LINKSCR := linkscript.ld

ARCH_CFLAGS := -DSTM32MP157Cxx -DSTM32MP1 -DCORE_CA7

LFLAGS = $(MCU)  \
		 -Wl,-Map,$(BUILDDIR)/$(BINARYNAME).map,--cref \
		 -Wl,--gc-sections \
		 -nostartfiles -nostdlib

%.diss : %.so
	arm-none-eabi-objdump -CDz --source $^ > $@

%.nm : %.so
	arm-none-eabi-nm -CA $^ > $@

%.readelf : %.so
	arm-none-eabi-readelf --demangle=auto -a -W $^ > $@


#### Shared lib (-shared), multiple files ##################

EXTRACFLAGS = -fPIC -c -Wno-double-promotion \
		 -nostartfiles \
		 -nostdlib \
		 -shared \

	# @mkdir -p $(OBJDIR)
	# $(CXX) $(DEPFLAGS) -PIC -c $(CXXFLAGS) plugin-extcall-multifile1.cc -o $(BUILDDIR)/plugin-extcall-multifile1.o
	# $(CXX) $(DEPFLAGS) -PIC -c $(CXXFLAGS) plugin-extcall-multifile2.cc -o $(BUILDDIR)/plugin-extcall-multifile2.o

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

OPTFLAG ?= -O2

AFLAGS = $(MCU)

EXTRACFLAGS ?= -c

CFLAGS ?= -g2 \
		 -fno-common \
		 $(ARCH_CFLAGS) \
		 $(MCU) \
		 $(INCLUDES) \
		 -fdata-sections -ffunction-sections \
		 $(EXTRACFLAGS)\

CXXFLAGS ?= $(CFLAGS) \
		-std=c++2a \
		-fno-rtti \
		-fno-exceptions \
		-fno-unwind-tables \
		-fno-threadsafe-statics \
		-mno-unaligned-access \
		-Werror=return-type \
		-Wno-register \
		-Wno-volatile \
		 $(EXTRACXXFLAGS) \

LINK_STDLIB ?= -nostdlib

# LFLAGS ?= -Wl,--gc-sections \
# 		 -Wl,-Map,$(BUILDDIR)/$(BINARYNAME).map,--cref \
# 		 $(MCU)  \
# 		 -T $(LINKSCR) \
# 		 $(LINK_STDLIB) \
# 		 -nostartfiles \
# 		 -ffreestanding \
# 		 $(EXTRALDFLAGS) \

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

SO 	    = $(BUILDDIR)/$(BINARYNAME).so
ELF 	= $(BUILDDIR)/$(BINARYNAME).elf
HEX 	= $(BUILDDIR)/$(BINARYNAME).hex
BIN 	= $(BUILDDIR)/$(BINARYNAME).bin

all: Makefile $(SO) 

$(OBJDIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	$(AS) $(AFLAGS) $< -o $@ 

$(OBJDIR)/%.o: %.c $(OBJDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	$(CC) $(DEPFLAGS) $(OPTFLAG) $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: %.c[cp]* $(OBJDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	$(CXX) $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@


$(SO): $(OBJECTS)
	$(info Linking shared library...)
	$(LD) -shared $(LFLAGS) -o $@ $(OBJECTS)

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


