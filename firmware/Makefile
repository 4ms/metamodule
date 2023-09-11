PRESET := base

# Detect MinGW and use Make
ifdef SYSTEMROOT
GEN := "Unix Makefiles"
else
GEN := Ninja
endif

all: | build/cmake-ok
	cmake --build --preset ${PRESET} 

build/cmake-ok:
	cmake --fresh --preset ${PRESET} -G ${GEN}

configure: 
	cmake --fresh --preset ${PRESET} -G ${GEN}

bootloader clean tests dep_tests simulate gen_minblep module-infos vcv-images comp-images faceplate-images image-list flash-bootloader-sd flash-app-sd flash-dfu jprog:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

.PHONY: all configure bootloader clean tests dep_tests simulate gen_minblep module-infos vcv-images comp-images faceplate-images image-list flash-bootloader-sd flash-app-sd flash-dfu jprog
.INTERMEDIATE: build/
