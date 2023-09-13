# If RACK_DIR is not defined when calling the Makefile, default to two directories above
#RACK_DIR ?= ../..

SHARED_DIR = ../shared
SHARED = $(SHARED_DIR)
RYMLDIR = $(SHARED)/patch_convert/ryml/rapidyaml
LGVLDIR = ../firmware/lib/lvgl/lvgl

INCLUDES = -Isrc
INCLUDES += -I$(SHARED_DIR)/cpputil
INCLUDES += -I$(SHARED_DIR)/processors
INCLUDES += -I$(SHARED_DIR)/patch
INCLUDES += -I$(SHARED_DIR)/patch_convert/ryml
INCLUDES += -I$(SHARED_DIR)
INCLUDES += -I$(SHARED_DIR)/axoloti-wrapper
INCLUDES += -I$(SHARED_DIR)/etl/include
INCLUDES += -I$(RYMLDIR)/src
INCLUDES += -I$(RYMLDIR)/ext/c4core/src
INCLUDES += -I$(LGVLDIR)
INCLUDES += -I$(LGVLDIR)/src/misc


# FLAGS will be passed to both the C and C++ compiler
FLAGS += -std=c++2a 
FLAGS += $(INCLUDES)
FLAGS += -g2

CFLAGS +=
CXXFLAGS += -DVCVRACK -Wno-missing-braces

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

INCLUDES += -I$(SHARED_DIR)/CoreModules/4ms
SOURCES += $(wildcard $(SHARED_DIR)/CoreModules/4ms/core/*Core.cc)
SOURCES += $(SHARED_DIR)/CoreModules/4ms/core/enosc/data.cc
SOURCES += $(SHARED_DIR)/CoreModules/4ms/core/enosc/dynamic_data.cc
SOURCES += $(SHARED_DIR)/CoreModules/4ms/core/enosc/easiglib/numtypes.cc

# plugin
SOURCES += $(wildcard src/*.cpp)
SOURCES += $(wildcard src/*.cc)
SOURCES += $(wildcard src/hub/*.cc)
SOURCES += $(wildcard src/comm/*.cc)
SOURCES += $(wildcard src/mapping/*.cc)
SOURCES += $(wildcard src/models/*.cc)

SOURCES += $(wildcard $(SHARED_DIR)/cpputil/util/*.cc)
SOURCES += $(SHARED_DIR)/axoloti-wrapper/axoloti_math.cpp
SOURCES += $(SHARED_DIR)/patch_convert/ryml/ryml_serial.cc
SOURCES += $(SHARED_DIR)/patch_convert/patch_to_yaml.cc

SOURCES += $(wildcard $(RYMLDIR)/src/c4/yml/*.cpp)
SOURCES += $(wildcard $(RYMLDIR)/ext/c4core/src/c4/*.cpp)


# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
CXXFLAGS += -mmacosx-version-min=10.15 
endif

./build/src/plugin.cc.o: CXXFLAGS+=-Wno-missing-braces
./build/src/hub/hub_medium.cc.o: CXXFLAGS+=-Wno-missing-braces
./build/src/shared/CoreModules/%Core.cc.o: CXXFLAGS+=-Wno-missing-braces
./build/src/shared/CoreModules/enosc/dynamic_data.cc.o: CXXFLAGS+=-Wno-unknown-pragmas

all: plugin res

include make-models.mk

plugin: $(TARGET)

run: install
	$(shell $(RACK_DIR)/Rack &)
	
compile_commands:
	rm -rf build
	compiledb make -j16 all
	compdb -p ./ list > compile_commands_with_headers.json 2>/dev/null
	rm compile_commands.json 
	mv compile_commands_with_headers.json compile_commands.json

tests: core_tests util_tests vcv_tests axo_tests patch_convert_tests

core_tests:
	$(info ... Running CoreModule tests ...)
	@cd $(SHARED)/CoreModules && $(MAKE) --no-print-directory -f tests/Makefile

util_tests:
	$(info ... Running shared/cpputil tests ...)
	@cd $(SHARED)/cpputil && $(MAKE) --no-print-directory -f tests/Makefile

vcv_tests:
	$(info ... Running vcv plugin tests ...)
	@$(MAKE) --no-print-directory -f tests/Makefile

axo_tests:
	$(info ... Running Axoloti-wrapper tests ...)
	@cd $(SHARED)/axoloti-wrapper && $(MAKE) --no-print-directory -f tests/Makefile

patch_convert_tests:
	$(info ... Running patch convert (yaml<-->patch) tests ...)
	@cd $(SHARED)/patch_convert && $(MAKE) --no-print-directory -f tests/Makefile

win_dist:
	CC=x86_64-w64-mingw32-gcc CXX=x86_64-w64-mingw32-g++ STRIP=x86_64-w64-mingw32-strip RACK_DIR=../../Rack-SDK make -j16 dist

.PHONY: all plugin tests core_tests vcv_tests util_tests axo_tests patch_convert_tests compile_commands run

