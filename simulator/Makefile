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
	
# "make limit filename.txt" --> only build modules whose names are in the text file
ifeq (limit,$(firstword $(MAKECMDGOALS)))
LIMITFILE := $(filter-out limit,$(MAKECMDGOALS))
# silence messages about filename.txt target
.PHONY: $(LIMITFILE)
$(LIMITFILE): 
	@echo ""
endif

limit:
	cmake --fresh --preset Default -DLIMITED_MODULES_FILE=$(LIMITFILE)

.PHONY: all clean warnings run
