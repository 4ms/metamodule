# If you want to use `make flash`, set this to the path to your JFlash executable:
JFLASHEXE ?= /Applications/SEGGER/JLink_V696/JFlash.app/Contents/MacOS/JFlashExe
ARM_NONE_EABI_PATH ?= arm-none-eabi-

export BUILDDIR_H7M7 	= build/h7corem7
export BUILDDIR_H7M4 	= build/h7corem4
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

export VALID_BOARDS = mini medium max pcmdev


.PHONY: all mp1-mini mp1-pcmdev mp1-med patches clean install_a7 flash_h7 tables tests hardware_tests core_tests util_tests proc_tests mdrivlib_tests simulate


all: patches mp1-med tests #mp1-mini h7 

# Binaries

mp1-mini:
	@$(MAKE) --no-print-directory -f makefile_mp1m4.mk mini
	@$(MAKE) --no-print-directory -f makefile_mp1a7.mk mini

mp1-med:
	@$(MAKE) --no-print-directory -f makefile_mp1m4.mk medium
	@$(MAKE) --no-print-directory -f makefile_mp1a7.mk medium 

mp1-pcmdev:
	@$(MAKE) --no-print-directory -f makefile_mp1a7.mk pcmdev 

h7:  #mini only
	@$(MAKE) --no-print-directory -f makefile_h7m4.mk
	@$(MAKE) --no-print-directory -f makefile_h7m7.mk




## Patches

PATCH_BINARIES = $(wildcard $(SHARED)/patch/*.mmpatch)
PATCH_BINARIES += $(wildcard $(SHARED)/patch/integration_tests/*.mmpatch)
PATCH_HEADERS = $(addsuffix .hh, $(basename $(PATCH_BINARIES)))

patches: $(PATCH_HEADERS)

%.hh : %.mmpatch 
	cd $(dir $<) && xxd -i -c 8 $(notdir $<) $(notdir $@)


## Module images
# MODULEIMG_SVGS = $(wildcard ../vcv/res/*-artwork.svg)
MODULEIMG_SVGS = $(wildcard $(SHARED)/CoreModules/svg/*_info.svg)
MODULEIMG_PNG240S = $(addprefix src/pages/images/,$(addsuffix _240.png, $(subst info,artwork,$(basename $(notdir $(MODULEIMG_SVGS))))))
MODULEIMG_C = $(MODULEIMG_PNG240S:.png=.c)

images: $(MODULEIMG_C)

# src/pages/images/%_artwork_240.c: ../vcv/res/%-artwork.svg
src/pages/images/%_artwork_240.c: $(SHARED)/CoreModules/svg/%_info.svg
	$(info Converting $<)
	@python3 $(SHARED)/svgextract/svgextract.py createlvimg $< $(subst .c,.png,$@)
	@python3 $(SHARED)/svgextract/svgextract.py appendimglist $*_artwork_240 src/pages/images/image_list.hh

.SECONDARY: $(MODULEIMG_PNG240S)

## Cleaning

clean:
	rm -rf $(BUILDDIR_H7M4)
	rm -rf $(BUILDDIR_H7M7)
	rm -rf $(BUILDDIR_MP1A7)
	rm -rf $(BUILDDIR_MP1M4)
	rm -f src/mini/firmware_m4*.h
	rm -f src/medium/firmware_m4*.h
	rm -f src/max/firmware_m4*.h
	rm -f src/pcmdev/firmware_m4*.h
	@$(MAKE) --no-print-directory -f tests/Makefile clean
	@cd $(DRIVERLIB) && $(MAKE) --no-print-directory -f tests/Makefile clean
	@cd $(SHARED)/util && $(MAKE) --no-print-directory -f tests/Makefile clean
	@cd $(SHARED)/CoreModules && $(MAKE) --no-print-directory -f tests/Makefile clean


clean_a7:
	$(MAKE) --no-print-directory clean -f makefile_mp1a7.mk

clean_uboot:
	$(MAKE) --no-print-directory clean_uboot -f makefile_mp1a7.mk


# $(BUILDDIR_H7M4)/$(BINARYNAME).hex:
# 	@$(MAKE) --no-print-directory -f makefile_m4.mk

# $(BUILDDIR_H7M7)/$(BINARYNAME).hex:
# 	@$(MAKE) --no-print-directory -f makefile_m7.mk

# $(BUILDDIR_MP1M4)/$(BINARYNAME).elf:
# 	@$(MAKE) --no-print-directory -f makefile_mp1m4.mk

## Flashing

# ifeq (,$(wildcard $(JFLASHEXE)))
#     $(error JFlashExe program not found at $(JFLASHEXE). Please edit this Makefile and enter the correct path)
# endif

# install_a7:
# 	$(info SD card must be mounted)
# 	cp $(BUILDDIR_MP1A7)/$(BINARYNAME).uimg /Volumes/BAREAPP/a7-main.uimg
# 	diskutil unmount /Volumes/BAREAPP

# flash_mp1m4:
# 	$(JFLASHEXE) -openprjflashing/metamodule-mp1-cm4.jflash -open$(BUILDDIR_MP1M4)/$(BINARYNAME).hex -auto -exit

flash_h7: h7
	$(JFLASHEXE) -openprjflashing/metamodule-h7-cm7.jflash -open$(BUILDDIR_H7M7)/main.hex -auto -open$(BUILDDIR_H7M4)/main.hex -auto -exit

start_gdb:
	JLinkGDBServer -select USB -device STM32MP15xx_M4_Bank1 -endian little -if SWD -speed 8000 -noir -nohalt


## Simulator

simulate:
	$(info Simulating screens...)
	@cd ../screen_simulator && cargo run

## Tests

tests: module_tests core_tests util_tests mdrivlib_tests #vcv_tests

module_tests:
	$(info ... Running firmware tests....)
	@$(MAKE) --no-print-directory -f tests/Makefile

mdrivlib_tests:
	$(info ... Running mdrivlib tests ...)
	@cd $(DRIVERLIB) && $(MAKE) --no-print-directory -f tests/Makefile

util_tests:
	$(info ... Running shared/util tests ...)
	@cd $(SHARED)/util && $(MAKE) --no-print-directory -f tests/Makefile

core_tests:
	$(info ... Running CoreModule tests ...)
	@cd $(SHARED)/CoreModules && $(MAKE) --no-print-directory -f tests/Makefile

## Support files

tables $(SHARED)/util/math_tables.cc: $(TABLEGEN)/main.cpp
	g++ -I../shared -std=c++17 $(TABLEGEN)/main.cpp -o $(TABLEGEN)/make_tables
	cd $(TABLEGEN) && ./make_tables

generate_compile_txt:
	arm-none-eabi-gcc -E -x c++ - -v < /dev/null 2>&1 | \
    awk '/End of search list./ { show=0 } { if (show) printf "-I%s\n",$1 }; /#include <...> search starts here:/ { show=1; }' > compile_flags.txt

compile_commands:
	compiledb make
	compdb -p ./ list > compile_commands.tmp 2>/dev/null
	rm compile_commands.json
	mv compile_commands.tmp compile_commands.json
