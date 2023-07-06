BUILDDIR := build

all: | $(BUILDDIR)
	cmake --build $(BUILDDIR) 

$(BUILDDIR):
	cmake -B $(BUILDDIR) -GNinja

clean:
	rm -rf $(BUILDDIR)

warnings: clean
	cmake --preset gcc-warn -B $(BUILDDIR)

run:
	build/simulator

.PHONY: all clean warnings run
