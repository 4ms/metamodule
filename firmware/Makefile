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
	cmake --fresh --preset ${PRESET} -G ${GEN} -DLOG_LEVEL=DEBUG

# Auto-complete these targets:
bootloader tests dep_tests simulate gen_minblep flash-bootloader-sd flash-app-sd flash-dfu jprog debug start-jlinkgdb start-openocd flash_loader flash_loader_dfu new-api-sym-list:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

# Forward any other arguments
%:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

.PHONY: configure all bootloader tests dep_tests simulate gen_minblep flash-bootloader-sd flash-app-sd flash-dfu jprog debug start-jlinkgdb start-openocd flash_loader flash_loader_dfu new-api-sym-list
