
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

ELF 	= $(BUILDDIR)/$(BINARYNAME).elf
HEX 	= $(BUILDDIR)/$(BINARYNAME).hex
BIN 	= $(BUILDDIR)/$(BINARYNAME).bin

ARCH_CFLAGS += -D'__FPU_PRESENT=1' \
			  -DUSE_HAL_DRIVER \
			  -DUSE_FULL_LL_DRIVER \
			  -DSTM32H745xx \
			  -DSTM32H7x5xx \
			  -DSTM32H7 \
			  -D$(EXTDEF)

CFLAGS = -g2 -fno-common \
	$(ARCH_CFLAGS) $(MCU) \
	$(INCLUDES) \
	-fdata-sections -ffunction-sections \
	-nostdlib \
	-nostartfiles \
	--param l1-cache-size=16 \
	--param l1-cache-line-size=32 \

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
	-nostdlib \
	-nostartfiles \

AFLAGS = $(MCU)
#	-x assembler-with-cpp

LFLAGS = -Wl,--gc-sections \
	-Wl,-Map,$(BUILDDIR)/main.map,--cref \
	$(MCU)  \
	-T $(DEVICE)/$(LOADFILE) \
	-nostdlib \
	-nostartfiles \

DEPFLAGS = -MMD -MP -MF $(BUILDDIR)/$(basename $<).d

all: Makefile $(BIN) $(HEX)

$(BIN): $(ELF)
	$(OBJCPY) -O binary $< $@
	$(OBJDMP) -x --syms $< > $(addsuffix .dmp, $(basename $<))
	ls -l $@ $<

$(HEX): $(ELF)
	$(OBJCPY) --output-target=ihex $< $@
	$(SZ) $(SZOPTS) $(ELF)

$(ELF): $(OBJECTS) $(DEVICE)/$(LOADFILE)
	$(info Linking...)
	@$(LD) $(LFLAGS) -o $@ $(OBJECTS)

$(BUILDDIR)/%.o: %.c $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	@$(CC) -c $(DEPFLAGS) $(OPTFLAG) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	$(CXX) -c $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cpp $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	@$(CXX) -c $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	@$(AS) $(AFLAGS) $< -o $@ > $(addprefix $(BUILDDIR)/, $(addsuffix .lst, $(basename $<)))

%.d: ;

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS) $(ELF) $(PRECHDRS)
