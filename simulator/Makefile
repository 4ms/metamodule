BUILDDIR := build

all: | $(BUILDDIR)
	cmake --build $(BUILDDIR) 

$(BUILDDIR):
	cmake --fresh --preset Default -DLOG_LEVEL=DEBUG

clean:
	cmake --fresh --preset Default -DLOG_LEVEL=DEBUG

config-sim: clean

realclean:
	rm -rf $(BUILDDIR)

warnings: 
	cmake --fresh --preset gcc-warn -DLOG_LEVEL=TRACE

run: all
	build/simulator

debug:
	cmake --build ${BUILDDIR} --target debug
	

config-headless:
	cmake --fresh --preset headless -DLOG_LEVEL=DEBUG

config-headless-min:
	cmake --fresh --preset headless-min -DLOG_LEVEL=NONE
	

.PHONY: all clean warnings run
