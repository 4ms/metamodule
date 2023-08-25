PRESET := base

# Detect MinGW and use Make
ifdef SYSTEMROOT
GEN := Unix Makefiles
else
GEN := Ninja
endif

configure:
	cmake --fresh --preset ${PRESET} -G ${GEN}

$(BUILDDIR):
	cmake -B $(BUILDDIR) -G"$(GEN)"
all:
	cmake --build --preset ${PRESET} 

# Forward arguments to cmake
%:
	cmake --build --preset ${PRESET} -- $(MAKECMDGOALS)

.PHONY: all