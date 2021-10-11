ARCH 	?= $(ARM_NONE_EABI_PATH)
CC 		= $(ARCH)-gcc
CXX 	= $(ARCH)-g++
LD 		= $(ARCH)-g++
AS 		= $(ARCH)-as
OBJCPY 	= $(ARCH)-objcopy
OBJDMP 	= $(ARCH)-objdump
GDB 	= $(ARCH)-gdb
SZ 		= $(ARCH)-size

SZOPTS 	= -d

ELF 	= $(BUILDDIR)/$(BINARYNAME).elf
HEX 	= $(BUILDDIR)/$(BINARYNAME).hex
BIN 	= $(BUILDDIR)/$(BINARYNAME).bin
TAG ?=

EXTRA_CFLAGS ?= 
EXTRA_CPPFLAGS ?=
EXTRA_LFLAGS ?=

CFLAGS = -ggdb3 -fno-common \
	$(ARCH_CFLAGS) $(MCU) \
	$(INCLUDES) \
	-fdata-sections -ffunction-sections \
	-nostdlib \
	-nostartfiles \
	$(EXTRA_CFLAGS)

CXXFLAGS = $(CFLAGS) \
	-std=c++2a \
	-fno-rtti \
	-fno-exceptions \
	-fno-unwind-tables \
	-ffreestanding \
	-fno-threadsafe-statics \
	-Werror=return-type \
	-Wdouble-promotion \
	-Wno-register \
	-Wno-volatile \
	$(EXTRA_CPPFLAGS)

AFLAGS ?= $(MCU)

LFLAGS = -Wl,--gc-sections \
	-Wl,-Map,$(BUILDDIR)/$(BINARYNAME).map,--cref \
	$(MCU)  \
	-T $(LOADFILE) \
	-nostdlib \
	-nostartfiles \
	-ffreestanding \
	$(EXTRA_LFLAGS)

DEPFLAGS = -MMD -MP -MF $(BUILDDIR)/$(basename $<).d

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))
OBJECTS   += $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(addsuffix _s, $(basename $(ASM_SOURCES)))))
DEPS      += $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(addsuffix _s, $(basename $(ASM_SOURCES)))))

all: Makefile $(BIN) $(HEX)

$(BIN): $(ELF)
	@$(OBJCPY) -O binary $< $@
	@$(OBJDMP) -x --syms $< > $(addsuffix .dmp, $(basename $<))
	ls -l $@ $<

$(HEX): $(ELF)
	@$(OBJCPY) --output-target=ihex $< $@
	@$(SZ) $(SZOPTS) $(ELF)

$(ELF): $(OBJECTS) $(LOADFILE)
	$(info $(TAG) Linking...)
	@$(LD) $(LFLAGS) -o $@ $(OBJECTS)

$(BUILDDIR)/%.o: %.c $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info $(TAG) Building $< at $(OPTFLAG))
	@$(CC) -c $(DEPFLAGS) $(OPTFLAG) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info $(TAG) Building $< at $(OPTFLAG))
	@$(CXX) -c $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cpp $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info $(TAG) Building $< at $(OPTFLAG))
	@$(CXX) -c $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%_s.o: %.s
	@mkdir -p $(dir $@)
	$(info $(TAG) Building $<)
	@$(AS) $(AFLAGS) $< -o $@ > $(addprefix $(BUILDDIR)/, $(addsuffix .lst, $(basename $<)))

%.d: ;

clean:
	rm -rf $(BUILDDIR)


ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS) $(ELF) $(PRECHDRS)

.PHONY: all
