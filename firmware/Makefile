PRESET ?= full

# Detect MinGW and use Make
ifdef SYSTEMROOT
GEN := "Unix Makefiles"
else
GEN := Ninja
endif

all:
	cmake --build --preset ${PRESET} 

configure:
	cmake --fresh --preset ${PRESET} -G ${GEN}

# "make limit filename.txt" --> only build modules whose names are in the text file
ifeq (limit,$(firstword $(MAKECMDGOALS)))
LIMITFILE := $(filter-out limit,$(MAKECMDGOALS))
# silence messages about filename.txt target
.PHONY: $(LIMITFILE)
$(LIMITFILE): 
	@echo ""
endif

limit:
	cmake --fresh --preset ${PRESET} -G ${GEN} -DLIMITED_MODULES_FILE=$(LIMITFILE)

dyn:
	cmake --build --preset ${PRESET} 
	flashing/dump_syms.py \
			--objdir ./build/mp1corea7/medium/CMakeFiles/main.elf.dir/Users/dann/4ms/stm32/meta-module/shared/CoreModules/ \
			--objdir ./build/mp1corea7/medium/VCV_adaptor/CMakeFiles/VCV_adaptor.dir/ \
			--elf ./build/mp1corea7/medium/main.elf --out src/dynload/host_sym_list.hh -v
	cmake --build --preset ${PRESET} 

plugin:
	cd vcv_ports && make
	cp ./vcv_ports/build/Befaco-strip-so.h ./src/dynload/befaco-strip-so.h


bootloader tests dep_tests simulate gen_minblep module-infos vcv-images comp-images faceplate-images flash-bootloader-sd flash-app-sd flash-dfu jprog debug start-jlinkgdb start-openocd flash_loader flash_loader_dfu:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

# Forward any other arguments
%:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

.PHONY: configure all bootloader tests dep_tests simulate gen_minblep module-infos vcv-images comp-images faceplate-images flash-bootloader-sd flash-app-sd flash-dfu jprog debug start-jlinkgdb start-openocd flash_loader flash_loader_dfu
