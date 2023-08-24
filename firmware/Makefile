BUILDDIR := build

all: | $(BUILDDIR)
	cmake --build $(BUILDDIR) 

# Detect MinGW and use Make
ifdef SYSTEMROOT
GEN := Unix Makefiles
else
GEN := Ninja
endif

$(BUILDDIR):
	cmake -B $(BUILDDIR) -G"$(GEN)"

# Forward arguments to cmake
%: | $(BUILDDIR)
	cmake --build build -- $(MAKECMDGOALS)

.PHONY: all
