# This is meant to be run from the parent dir of this Makefile:
# make -f tests/Makefile

TEST_DIR ?= tests
DOCTESTHEADER_DIR = $(TEST_DIR)
BUILDDIR = $(TEST_DIR)/build
RYMLDIR = ../shared/patch_convert/ryml/rapidyaml

TEST_SOURCES = $(TEST_DIR)/doctest.cc
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_SOURCES += ../shared/patch_convert/yaml_to_patch.cc
TEST_SOURCES += ../shared/patch_convert/ryml/ryml_serial.cc
TEST_SOURCES += $(wildcard $(RYMLDIR)/src/c4/yml/*.cpp)
TEST_SOURCES += $(wildcard $(RYMLDIR)/ext/c4core/src/c4/*.cpp)
TEST_SOURCES += src/fs/time_convert.cc
TEST_SOURCES += src/fw_update/hash/md5_hash.h
TEST_SOURCES += src/fw_update/hash/hash_processor.cc

CXXFLAGS = 	-Wall \
		 	-std=gnu++2b \
			-I$(DOCTEST_DIR) \
			-I$(TEST_DIR) \
			-I$(TEST_DIR)/stubs \
			-I../$(TEST_DIR)/stubs \
			-I../stubs \
			-I. \
			-I.. \
			-Isrc \
			-Isrc/medium \
			-I../src \
			-I../shared \
			-I../shared/cpputil \
			-I../shared/patch \
			-I../shared/modules \
			-I../shared/modules/CoreModules \
			-I../shared/modules/CoreModules/elements \
			-I../shared/CoreModules \
			-I../shared/patch_convert \
			-I../shared/patch_convert/ryml \
			-I../shared/CoreModules \
			-I$(RYMLDIR)/src \
			-I$(RYMLDIR)/ext/c4core/src \
			-DTESTPROJECT \

### Boilerplate below here:

#CXX = clang++
#LDFLAGS = -lstdc++
OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(TEST_SOURCES))))
DEPDIR := $(BUILDDIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(basename $<).d
TMPFILE = $(BUILDDIR)/runtests.out

.PHONY: all tests clean patches

all: $(DOCTESTHEADER_DIR)/doctest.h patches tests

$(BUILDDIR)/tests/DualAtenCore_tests.o: CXXFLAGS += -Wno-missing-braces

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CC) -c $(DEPFLAGS) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CXX) -c $(DEPFLAGS) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CXX) -c $(DEPFLAGS) $(CXXFLAGS) $< -o $@


tests: $(BUILDDIR)/runtests 
	@$(BUILDDIR)/runtests --out=$(TMPFILE) && echo "[√] Unit tests passed: $(notdir $(PWD))" || cat $(TMPFILE)

$(BUILDDIR)/runtests: $(OBJECTS)
	$(info Building $(BUILDDIR)/runtests) 
	@$(CXX) $(LDFLAGS) -o $@ $(OBJECTS)

$(DOCTESTHEADER_DIR)/doctest.h:
	wget https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h -P $(DOCTESTHEADER_DIR)/

clean:
	rm -rf $(BUILDDIR)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(addprefix $(DEPDIR)/, $(addsuffix .d, $(basename $(TEST_SOURCES))))
$(DEPFILES):

include $(wildcard $(DEPFILES))

