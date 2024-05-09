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

bootloader tests dep_tests simulate gen_minblep module-infos vcv-images comp-images faceplate-images flash-bootloader-sd flash-app-sd flash-dfu jprog debug start-jlinkgdb start-openocd flash_loader flash_loader_dfu:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

# Forward any other arguments
%:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

.PHONY: configure all bootloader tests dep_tests simulate gen_minblep module-infos vcv-images comp-images faceplate-images flash-bootloader-sd flash-app-sd flash-dfu jprog debug start-jlinkgdb start-openocd flash_loader flash_loader_dfu
