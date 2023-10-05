PRESET := base

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

bootloader tests dep_tests simulate gen_minblep module-infos vcv-images comp-images faceplate-images image-list flash-bootloader-sd flash-app-sd flash-dfu jprog:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

# Forward any other arguments
%:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

.PHONY: configure all bootloader tests dep_tests simulate gen_minblep module-infos vcv-images comp-images faceplate-images image-list flash-bootloader-sd flash-app-sd flash-dfu jprog
