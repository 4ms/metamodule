BUILDDIR := build

all: | $(BUILDDIR)
	cmake --build $(BUILDDIR) 

$(BUILDDIR):
	cmake -B $(BUILDDIR) -GNinja

# Forward arguments to cmake
%: | $(BUILDDIR)
	cmake --build build -- $(MAKECMDGOALS)

.PHONY: all
