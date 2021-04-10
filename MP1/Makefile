# If you want to use `make flash`, set this to the path to your JFlash executable:
JFLASHEXE = /Applications/SEGGER/JLink_V696/JFlash.app/Contents/MacOS/JFlashExe

export BUILDDIR_M4 		= build/corem4
export BUILDDIR_M7 		= build/corem7
export BINARYNAME 		= main
export STARTUP 			= startup_cm7.s
export SYSTEM 			= system_stm32h7xx_dualcore_boot_cm4_cm7.c
export LIBDIR 			= lib
export DEVICE 			= $(LIBDIR)/stm32/device
export CMSIS 			= $(LIBDIR)/stm32/cmsis
export PERIPH 			= $(LIBDIR)/stm32/periph
export DRIVERLIB       	= $(LIBDIR)/mdrivlib
export SHARED  			= ../shared
export TABLEGEN 		= $(SHARED)/tableGen

all: 
	@$(MAKE) --no-print-directory -f makefile_m7.mk
	@$(MAKE) --no-print-directory -f makefile_m4.mk
	@$(MAKE) --no-print-directory tests

inttest: 
	touch src/patchlist.cc 
	touch src/patchlist.hh
	@$(MAKE) --no-print-directory EXTDEF=METAMODULE_INTEGRATION_TESTS all

clean:
	rm -rf $(BUILDDIR_M4)
	rm -rf $(BUILDDIR_M7)

$(BUILDDIR_M4)/$(BINARYNAME).hex:
	@$(MAKE) --no-print-directory -f makefile_m4.mk

$(BUILDDIR_M7)/$(BINARYNAME).hex:
	@$(MAKE) --no-print-directory -f makefile_m7.mk


# ifeq (,$(wildcard $(JFLASHEXE)))
#     $(error JFlashExe program not found at $(JFLASHEXE). Please edit this Makefile and enter the correct path)
# endif
flash_m7: $(BUILDDIR_M7)/$(BINARYNAME).hex
	$(JFLASHEXE) -openprjmetamodule-h7-cm7.jflash -open$(BUILDDIR_M7)/$(BINARYNAME).hex -auto -exit

flash_m4: $(BUILDDIR_M4)/$(BINARYNAME).hex
	$(JFLASHEXE) -openprjmetamodule-h7-cm7.jflash -open$(BUILDDIR_M4)/$(BINARYNAME).hex -auto -exit

flash: $(BUILDDIR_M7)/$(BINARYNAME).hex $(BUILDDIR_M4)/$(BINARYNAME).hex
	$(JFLASHEXE) -openprjmetamodule-h7-cm7.jflash -open$(BUILDDIR_M7)/$(BINARYNAME).hex -auto -open$(BUILDDIR_M4)/$(BINARYNAME).hex -auto -exit

tables $(SHARED)/util/math_tables.cc: $(TABLEGEN)/main.cpp
	g++ -I../shared -std=c++17 $(TABLEGEN)/main.cpp -o $(TABLEGEN)/make_tables
	cd $(TABLEGEN) && ./make_tables

simulate:
	$(info Simulating screens...)
	@cd ../screen_simulator && cargo run

.PHONY: all clean flash tables tests H7_tests core_tests util_tests proc_tests mdrivlib_tests simulate

tests: H7_tests core_tests util_tests mdrivlib_tests #proc_tests

H7_tests:
	$(info ... Running H7 tests....)
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

generate_compile_txt:
	arm-none-eabi-gcc -E -x c++ - -v < /dev/null 2>&1 | \
    awk '/End of search list./ { show=0 } { if (show) printf "-I%s\n",$1 }; /#include <...> search starts here:/ { show=1; }' > compile_flags.txt

#https://github.com/nickdiego/compiledb
compile_commands:
	compiledb make
	compdb -p ./ list > compile_commands.tmp 2>/dev/null
	rm compile_commands.json
	mv compile_commands.tmp compile_commands.json
