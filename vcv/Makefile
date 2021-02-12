# If RACK_DIR is not defined when calling the Makefile, default to two directories above
RACK_DIR ?= ../..

SHARED_DIR = src/shared

# FLAGS will be passed to both the C and C++ compiler
FLAGS += -std=c++17 -Isrc -I$(SHARED_DIR)/util -I$(SHARED_DIR)/processors -I$(SHARED_DIR)/CoreModules -I$(SHARED_DIR)/patch -I$(SHARED_DIR)
CFLAGS +=
CXXFLAGS += 

# Careful about linking to shared libraries, since you can't assume much about the user's environment and library search path.
# Static libraries are fine, but they should be added to this plugin's build system.
LDFLAGS +=

# Add .cpp files to the build
SOURCES += $(wildcard src/*.cpp)
SOURCES += $(wildcard $(SHARED_DIR)/CoreModules/*.cpp)
SOURCES += $(wildcard $(SHARED_DIR)/util/*.cc)

# Add files to the ZIP package when running `make dist`
# The compiled plugin and "plugin.json" are automatically added.
DISTRIBUTABLES += res
DISTRIBUTABLES += $(wildcard LICENSE*)

# Include the Rack plugin Makefile framework
include $(RACK_DIR)/plugin.mk

compile_commands:
	rm -rf build
	bear make -j16 all
	compdb -p ./ list > compile_commands_with_headers.json 2>/dev/null
	rm compile_commands.json 
	mv compile_commands_with_headers.json compile_commands.json

tests: core_tests vcv_tests

core_tests:
	@echo
	@echo "----------------------------"
	@echo "Running CoreModule tests...."
	@echo "----------------------------"
	$(MAKE) -f $(SHARED_DIR)/CoreModules/tests/Makefile

vcv_tests:
	@echo
	@echo "----------------------------"
	@echo "Running vcv plugin tests...."
	@echo "----------------------------"
	$(MAKE) -f tests/Makefile

.PHONY: tests core_tests vcv_tests

