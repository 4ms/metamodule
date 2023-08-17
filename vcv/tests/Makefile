# This is meant to be run from the vcv/ dir
# make -f tests/Makefile

TEST_DIR ?= tests
DOCTESTHEADER_DIR ?= $(TEST_DIR)
OUTERBUILDDIR = $(TEST_DIR)/build
BUILDDIR = $(OUTERBUILDDIR)/build

SHARED_DIR = ../shared
RYMLDIR = $(SHARED_DIR)/patch_convert/ryml/rapidyaml


TEST_SOURCES = $(TEST_DIR)/doctest.cc
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_SOURCES += $(SHARED_DIR)/patch_convert/patch_to_yaml.cc
TEST_SOURCES += $(SHARED_DIR)/patch_convert/ryml/ryml_serial.cc
TEST_SOURCES += src/mapping/patch_writer.cc
TEST_SOURCES += $(wildcard $(RYMLDIR)/src/c4/yml/*.cpp)
TEST_SOURCES += $(wildcard $(RYMLDIR)/ext/c4core/src/c4/*.cpp)


CXXFLAGS = 	-Wall \
		 	-std=gnu++2a \
			-I$(DOCTEST_DIR) \
			-I../src\
			-Isrc\
			-Isrc/hub\
			-Isrc/mapping\
			-I$(SHARED_DIR) \
			-I$(SHARED_DIR)/cpputil \
			-I$(SHARED_DIR)/patch_convert/ryml \
			-I$(SHARED_DIR)/etl/include \
			-I$(TEST_DIR) \
			-I$(RYMLDIR)/src \
			-I$(RYMLDIR)/ext/c4core/src \
			-DTESTPROJECT \
			-Wno-missing-braces \

### Boilerplate below here:

LDFLAGS = -lstdc++
OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(TEST_SOURCES))))
DEPDIR := $(BUILDDIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(basename $<).d

.PHONY: all tests clean

TMPFILE = $(BUILDDIR)/runtests.out

all: $(DOCTESTHEADER_DIR)/doctest.h tests

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
	@$(CXX) $(LDFLAGS) -o $@ $(OBJECTS)

$(DOCTESTHEADER_DIR)/doctest.h:
	wget https://raw.githubusercontent.com/onqtam/doctest/master/doctest/doctest.h -P $(DOCTESTHEADER_DIR)/

clean:
	rm -rf $(OUTERBUILDDIR)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(addprefix $(DEPDIR)/, $(addsuffix .d, $(basename $(TEST_SOURCES))))
$(DEPFILES):

include $(wildcard $(DEPFILES))

