BUILDDIR := build

all: | $(BUILDDIR)
	cmake --build $(BUILDDIR) 

$(BUILDDIR):
	cmake --fresh --preset Default

clean:
	cmake --fresh --preset Default

realclean:
	rm -rf $(BUILDDIR)

warnings: 
	cmake --fresh --preset gcc-warn

run: all
	build/simulator

.PHONY: all clean warnings run
