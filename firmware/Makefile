# If you want to use `make flash`, set this to the path to your JFlash executable:
JFLASHEXE ?= /Applications/SEGGER/JLink_V720a/JFlash.app/Contents/MacOS/JFlashExe
ARM_NONE_EABI_PATH ?= arm-none-eabi-

export BUILDDIR_MP1A7 	= build/mp1corea7
export BUILDDIR_MP1M4 	= build/mp1corem4
export BINARYNAME  		= main
export LIBDIR 			= lib
export DEVICEBASE		= $(LIBDIR)/cmsis-device
export CMSIS 			= $(LIBDIR)/cmsis
export HALBASE 			= $(LIBDIR)/stm32-hal
export DRIVERLIB       	= $(LIBDIR)/mdrivlib
export LINKSCRIPTDIR   	= system/linker
export SHARED  			= ../shared
export TABLEGEN 		= $(SHARED)/tableGen

export VALID_BOARDS = medium norflash-loader


.PHONY: all mp1-med simulate tables norflash-loader clean

.PHONY: tests hardware_tests core_tests util_tests proc_tests mdrivlib_tests patch_convert_tests


all: mp1-med tests #images

# Binaries

mp1-med:
	@$(MAKE) --no-print-directory -f makefile_mp1m4.mk medium
	@$(MAKE) --no-print-directory -f makefile_mp1a7.mk medium 

norflash-loader: mp1-med
	$(MAKE) --no-print-directory -f makefile_mp1a7.mk norflash-loader

uimg:
	@$(MAKE) --no-print-directory -f makefile_mp1a7.mk uimg

.PHONY: bootloader format-sd flash-bootloader-sd 
SD_DISK_DEV ?= /dev/disk4

bootloader:
	cd bootloader/mp1-boot && make clean && make BOARD_CONF=../board_conf/mmp11_conf.hh

include makefile_moduleinfo.mk

format-sd:
	@read -p "What is the disk device to format (Enter for $(SD_DISK_DEV)): " DISK && \
	DISK=$${DISK:-$(SD_DISK_DEV)} && \
	echo "Formatting $${DISK}" && \
	echo "./flashing/format-partition-sdcard.sh $${DISK}" && \
	./flashing/format-partition-sdcard.sh $${DISK}

flash-bootloader-sd: 
	cd bootloader/mp1-boot && make load

flash-app-sd: uimg
	@read -p "What is the disk device and partition to flash to (Enter for $(SD_DISK_DEV)s4): " DISK && \
	DISK=$${DISK:-$(SD_DISK_DEV)s4} && \
	echo "Copying app to $${DISK}" && \
	echo "sudo dd if=./build/mp1corea7/medium/main.uimg of=$${DISK}" && \
	sudo dd if=./build/mp1corea7/medium/main.uimg of=$${DISK}

jprog: uimg
	$(info This only works after a hard reset with the Freeze jumper installed)
	@time JLinkExe -device STM32MP15XX_A7 -if JTAG -speed 25000 -jtagconf -1,-1 -nogui 1 -AutoConnect 1 -CommandFile flashing/program.jlink | tee /dev/tty | grep -q "failed" && \
	echo "FAILED!!! Did you do a hard reset with the Freeze jumper installed?" || echo "Programmed OK"


## Cleaning

clean:
	rm -rf $(BUILDDIR_MP1A7)
	rm -rf $(BUILDDIR_MP1M4)
	rm -f src/medium/firmware_m4*.h
	@$(MAKE) --no-print-directory -f tests/Makefile clean
	@cd $(DRIVERLIB) && $(MAKE) --no-print-directory -f tests/Makefile clean
	@cd $(SHARED)/cpputil && $(MAKE) --no-print-directory -f tests/Makefile clean
	@cd $(SHARED)/CoreModules && $(MAKE) --no-print-directory -f tests/Makefile clean
	@cd $(SHARED)/patch_convert && $(MAKE) --no-print-directory -f tests/Makefile clean


clean_a7:
	$(MAKE) --no-print-directory clean -f makefile_mp1a7.mk

start_gdb:
	JLinkGDBServer -select USB -device STM32MP15xx_M4_Bank1 -endian little -if SWD -speed 8000 -noir -nohalt

## Simulator

simulate:
	$(info Building and running simulation...)
	@cd ../simulator && make && build/simulator 

## Tests

tests: patch_convert_tests module_tests core_tests util_tests mdrivlib_tests  #vcv_tests

module_tests:
	$(info ... Running firmware tests....)
	@$(MAKE) --no-print-directory -f tests/Makefile

patch_convert_tests:
	$(info ... Running patch_convert tests....)
	@cd $(SHARED)/patch_convert && $(MAKE) --no-print-directory -f tests/Makefile

mdrivlib_tests:
	$(info ... Running mdrivlib tests ...)
	@cd $(DRIVERLIB) && $(MAKE) --no-print-directory -f tests/Makefile

util_tests:
	$(info ... Running shared/cpputil tests ...)
	@cd $(SHARED)/cpputil && $(MAKE) --no-print-directory -f tests/Makefile

core_tests:
	$(info ... Running CoreModule tests ...)
	@cd $(SHARED)/CoreModules && $(MAKE) --no-print-directory -f tests/Makefile

## Support files

tables $(SHARED)/cpputil/math_tables.cc: $(TABLEGEN)/main.cpp
	g++ -I../shared/cpputil -std=c++20 $(TABLEGEN)/main.cpp -o $(TABLEGEN)/make_tables
	cd $(TABLEGEN) && ./make_tables

gen_minblep:
	make -C ../shared/gen_minblep
	../shared/gen_minblep/gen_minblep 16 32 > ./src/VCV-adaptor/dsp/minblep_16_32.h

generate_compile_txt:
	arm-none-eabi-gcc -E -x c++ - -v < /dev/null 2>&1 | \
    awk '/End of search list./ { show=0 } { if (show) printf "-I%s\n",$1 }; /#include <...> search starts here:/ { show=1; }' > compile_flags.txt

compile_commands:
	compiledb make
	compdb -p ./ list > compile_commands.tmp 2>/dev/null
	rm compile_commands.json
	mv compile_commands.tmp compile_commands.json
