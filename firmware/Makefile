PRESET := base

# Detect MinGW and use Make
ifdef SYSTEMROOT
GEN := "Unix Makefiles"
else
GEN := Ninja
endif

configure:
	cmake --fresh --preset ${PRESET} -G ${GEN}

all:
	cmake --build --preset ${PRESET} 

bootloader tests dep_tests simulate gen_minblep module-infos vcv-images comp-images faceplate-images image-list flash-bootloader-sd flash-app-sd flash-dfu jprog:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

# Forward any other arguments
%:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

.PHONY: configure all bootloader tests dep_tests simulate gen_minblep module-infos vcv-images comp-images faceplate-images image-list flash-bootloader-sd flash-app-sd flash-dfu jprog
