BUILDDIR := build

all: | $(BUILDDIR)
	cmake --build $(BUILDDIR) 

$(BUILDDIR):
	cmake --fresh --preset Default -DLOG_LEVEL=DEBUG

clean:
	cmake --fresh --preset Default -DLOG_LEVEL=DEBUG

realclean:
	rm -rf $(BUILDDIR)

warnings: 
	cmake --fresh --preset gcc-warn -DLOG_LEVEL=TRACE

run: all
	build/simulator

debug:
	cmake --build ${BUILDDIR} --target debug -DLOG_LEVEL=DEBUG
	
.PHONY: all clean warnings run
