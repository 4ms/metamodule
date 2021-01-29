# Makefile by Dan Green <danngreen1@gmail.com>
#
CORE ?= M7

ifeq ($(CORE), M7)
$(info Building for M7 core)
LOADFILE	= STM32H745IGTX_FLASH_CM7.ld
BUILDDIR = build/corem7
MCU =  -mcpu=cortex-m7 -mfpu=fpv5-d16 -mthumb -mlittle-endian -mfloat-abi=hard
ARCH_CFLAGS = -DARM_MATH_CM7 -DCORE_CM7
HAL_CONF_INC = src/m7
else

ifeq ($(CORE), M4)
$(info Building for M4 core)
LOADFILE	= STM32H745IGTX_FLASH_CM4.ld
BUILDDIR = build/corem4
MCU =  -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mlittle-endian -mfloat-abi=hard
ARCH_CFLAGS = -DARM_MATH_CM4 -DCORE_CM4
HAL_CONF_INC = src/m4

else
$(error You must specify a CORE. Valid values are M4 or M7)
endif
endif



BINARYNAME 		= main
# STARTUP 		= startup_stm32h745igtx.s
STARTUP 		= startup_cm7.s
SYSTEM 			= system_stm32h7xx_dualcore_boot_cm4_cm7.c

LIBDIR 			= lib
DEVICE 			= $(LIBDIR)/stm32/device
CMSIS 			= $(LIBDIR)/stm32/cmsis
PERIPH 			= $(LIBDIR)/stm32/periph
DRIVERLIB       = $(LIBDIR)/mdrivlib
SHARED  		= src/shared
TABLEGEN 		= $(SHARED)/tableGen

# SOURCES  += $(DEVICE)/src/$(STARTUP)
SOURCES  += $(DRIVERLIB)/drivers/$(STARTUP)
SOURCES  += $(DEVICE)/src/$(SYSTEM)
SOURCES  += $(wildcard $(PERIPH)/src/*.c)
SOURCES  += $(wildcard $(DRIVERLIB)/drivers/*.c)
SOURCES  += $(wildcard $(DRIVERLIB)/drivers/*.cc)
SOURCES  += $(wildcard $(DRIVERLIB)/drivers/*.cpp)
SOURCES  += $(wildcard src/*.c)
SOURCES  += $(wildcard src/*.cc)
SOURCES  += $(wildcard src/*.cpp)
SOURCES  += $(wildcard src/sys/*.c)
SOURCES  += $(wildcard src/sys/*.cc)
SOURCES  += $(wildcard src/sys/*.cpp)
SOURCES  += $(wildcard $(SHARED)/util/*.c)
SOURCES  += $(wildcard $(SHARED)/util/*.cc)
SOURCES  += $(wildcard $(SHARED)/util/*.cpp)
SOURCES  += $(wildcard $(SHARED)/CoreModules/*.cpp)

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

INCLUDES += -I$(DEVICE)/include \
			-I$(CMSIS)/include \
			-I$(PERIPH)/include \
			-I$(DRIVERLIB) \
			-I$(LIBDIR)/easiglib \
			-I. \
			-Isrc \
			-Isrc/conf \
			-I$(HAL_CONF_INC) \
			-I$(SHARED) \
			-I$(SHARED)/processors \
			-I$(SHARED)/CoreModules \
			-I$(SHARED)/util \
			-I$(SHARED)/patch \

ELF 	= $(BUILDDIR)/$(BINARYNAME).elf
HEX 	= $(BUILDDIR)/$(BINARYNAME).hex
BIN 	= $(BUILDDIR)/$(BINARYNAME).bin

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
#From CubeIDE: 
#linker: -mcpu=cortex-m7 -T"/Users/dann/4ms_local/stm32/meta-module/H7/cubemx/H745/STM32CubeIDE/CM7/STM32H745IGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="${ProjName}.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
#gcc: -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DCORE_CM7 -DDEBUG -DSTM32H745xx -c -I../../../CM7/Core/Inc -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb

#gcc(m4): -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DCORE_CM4 -DDEBUG -DSTM32H745xx -c -I../../../CM4/Core/Inc -I../../../Drivers/STM32H7xx_HAL_Driver/Inc -I../../../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../../../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../../../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb 
#Todo: separate cm4 and cm7 builds




ARCH_CFLAGS += -D'__FPU_PRESENT=1' \
			  -DUSE_HAL_DRIVER \
			  -DUSE_FULL_LL_DRIVER \
			  -DSTM32H745xx \
			  -DSTM32H7x5xx \
			  -DSTM32H7

OPTFLAG = -O3

#----------------------------------
# Uncomment to compile unoptimized:
# $(BUILDDIR)/src/main.o: OPTFLAG = -O0
# $(BUILDDIR)/src/audio.o: OPTFLAG = -O0
# $(BUILDDIR)/$(PERIPH)/src/%.o: OPTFLAG = -O3
# $(BUILDDIR)/$(PERIPH)/src/stm32h7xx_hal_qspi.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/sdram.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/system.o: OPTFLAG = -O0
# $(BUILDDIR)/$(PERIPH)/src/stm32h7xx_hal_i2c.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/pca9685_led_driver_dma.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/pca9685_led_driver.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/i2c.o: OPTFLAG = -O0
# $(BUILDDIR)/$(DRIVERLIB)/drivers/qspi_flash_driver.o: OPTFLAG = -O0

CFLAGS = -g2 -fno-common \
	$(ARCH_CFLAGS) $(MCU) \
	$(INCLUDES) \
	-fdata-sections -ffunction-sections \
	-nostdlib \
	-nostartfiles \

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



all: Makefile $(BIN) $(HEX)

$(BIN): $(ELF)
	$(OBJCPY) -O binary $< $@
	$(OBJDMP) -x --syms $< > $(addsuffix .dmp, $(basename $<))
	ls -l $@ $<

$(HEX): $(ELF)
	$(OBJCPY) --output-target=ihex $< $@
	$(SZ) $(SZOPTS) $(ELF)

$(ELF): $(OBJECTS)
	$(info Linking...)
	@$(LD) $(LFLAGS) -o $@ $(OBJECTS)

DEPFLAGS = -MMD -MP -MF $(BUILDDIR)/$(basename $<).d

$(BUILDDIR)/%.o: %.c $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	@$(CC) -c $(DEPFLAGS) $(OPTFLAG) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	@$(CXX) -c $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cpp $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	@$(CXX) -c $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.s
	@mkdir -p $(dir $@)
	$(info Building $< at $(OPTFLAG))
	@$(AS) $(AFLAGS) $< -o $@ > $(addprefix $(BUILDDIR)/, $(addsuffix .lst, $(basename $<)))

%.d: ;

tables $(SHARED)/processors/math_tables.h: $(TABLEGEN)/main.cpp
	g++ $(TABLEGEN)/main.cpp -o $(TABLEGEN)/make_tables
	cd $(TABLEGEN) && ./make_tables

flash: $(BIN)
	st-flash write $(BIN) 0x8000000

clean:
	rm -rf build

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS) $(ELF) $(PRECHDRS)
.PHONY: all clean flash tables tests H7_tests core_tests util_tests proc_tests mdrivlib_tests

tests: H7_tests core_tests util_tests mdrivlib_tests #proc_tests 

H7_tests:
	@echo
	@echo "----------------------------"
	@echo "Running H7 tests...."
	@echo "----------------------------"
	make -f tests/Makefile

mdrivlib_tests:
	@echo
	@echo "----------------------------"
	@echo "Running mdrivlib tests...."
	@echo "----------------------------"
	cd $(DRIVERLIB) && make -f tests/Makefile

util_tests:
	@echo
	@echo "----------------------------"
	@echo "Running shared/util tests...."
	@echo "----------------------------"
	cd $(SHARED)/util/tests && make tests

core_tests:
	@echo
	@echo "----------------------------"
	@echo "Running CoreModule tests...."
	@echo "----------------------------"
	$(MAKE) -f $(SHARED)/CoreModules/tests/Makefile

# proc_tests:
# 	cd $(SHARED)/processors/tests && make tests

generate_compile_txt:
	arm-none-eabi-gcc -E -x c++ - -v < /dev/null 2>&1 | \
    awk '/End of search list./ { show=0 } { if (show) printf "-I%s\n",$1 }; /#include <...> search starts here:/ { show=1; }' > compile_flags.txt

compile_commands:
	rm -rf build
	bear make -j16 all
	compdb -p ./ list > compile_commands_with_headers.json 2>/dev/null
	rm compile_commands.json 
	mv compile_commands_with_headers.json compile_commands.json
