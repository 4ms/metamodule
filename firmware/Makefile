## Example:
## make config-board BOARD=handheld
## make all

PRESET ?= full

BOARD ?= 

# Detect MinGW and use Make
ifdef SYSTEMROOT
GEN := "Unix Makefiles"
else
GEN := Ninja
endif

all:
	cmake --build build

config-board:
	cmake --fresh --preset min-brands -G ${GEN} -DLOG_LEVEL=DEBUG -DBOARD=src/boards/$(BOARD)

configure:
	cmake --fresh --preset ${PRESET} -G ${GEN} -DLOG_LEVEL=DEBUG

# Auto-complete these targets:
bootloader tests dep_tests simulate gen_minblep flash-bootloader-sd flash-app-sd flash-dfu jprog debug start-jlinkgdb start-openocd flash_loader flash_loader_dfu new-api-sym-list:
	cmake --build build -- $(MAKECMDGOALS)

# Forward any other arguments
%:
	cmake --build build -- $(MAKECMDGOALS)

.PHONY: configure all bootloader tests dep_tests simulate gen_minblep flash-bootloader-sd flash-app-sd flash-dfu jprog debug start-jlinkgdb start-openocd flash_loader flash_loader_dfu new-api-sym-list
