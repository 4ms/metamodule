# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

SHARED_DIR = src/shared
SHARED = $(SHARED_DIR)

# FLAGS will be passed to both the C and C++ compiler
FLAGS += -std=c++2a -Isrc -I$(SHARED_DIR)/util -I$(SHARED_DIR)/processors -I$(SHARED_DIR)/CoreModules -I$(SHARED_DIR)/patch -I$(SHARED_DIR) -I$(SHARED_DIR)/axoloti-wrapper
CFLAGS +=
CXXFLAGS += 

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

# Add .cpp files to the build
SOURCES += $(wildcard src/*.cpp)
SOURCES += $(wildcard $(SHARED_DIR)/CoreModules/*.cpp)
SOURCES += $(wildcard $(SHARED_DIR)/util/*.cc)
SOURCES += $(SHARED_DIR)/axoloti-wrapper/axoloti_math.cpp

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk

all: $(TARGET)
	@$(MAKE) --no-print-directory tests

run: install
	$(shell $(RACK_DIR)/Rack &)
	
compile_commands:
	rm -rf build
	compiledb make -j16 all
	compdb -p ./ list > compile_commands_with_headers.json 2>/dev/null
	rm compile_commands.json 
	mv compile_commands_with_headers.json compile_commands.json

tests: core_tests util_tests vcv_tests axo_tests

core_tests:
	$(info ... Running CoreModule tests ...)
	@cd $(SHARED)/CoreModules && $(MAKE) --no-print-directory -f tests/Makefile

util_tests:
	$(info ... Running shared/util tests ...)
	@cd $(SHARED)/util && $(MAKE) --no-print-directory -f tests/Makefile

vcv_tests:
	$(info ... Running vcv plugin tests ...)
	@$(MAKE) --no-print-directory -f tests/Makefile

axo_tests:
	$(info ... Running Axoloti-wrapper tests ...)
	@cd $(SHARED)/axoloti-wrapper && $(MAKE) --no-print-directory -f tests/Makefile

win_dist:
	CC=x86_64-w64-mingw32-gcc CXX=x86_64-w64-mingw32-g++ STRIP=x86_64-w64-mingw32-strip RACK_DIR=../../Rack-SDK make -j16 dist

.PHONY: tests core_tests vcv_tests util_tests axo_tests

