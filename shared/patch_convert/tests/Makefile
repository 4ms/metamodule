# This is meant to be run from the patch_convert/ dir
# make -f tests/Makefile

TEST_DIR ?= tests
DOCTESTHEADER_DIR ?= $(TEST_DIR)

RYMLDIR = ryml/rapidyaml

TEST_SOURCES = $(TEST_DIR)/doctest.cc
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_SOURCES += ../ryml/ryml_serial.cc
TEST_SOURCES += ../ryml/ryml_init.cc
TEST_SOURCES += ../patch_to_yaml.cc
TEST_SOURCES += ../yaml_to_patch.cc
TEST_SOURCES += $(wildcard $(RYMLDIR)/src/c4/yml/*.cpp)
TEST_SOURCES += $(wildcard $(RYMLDIR)/ext/c4core/src/c4/*.cpp)

BUILDDIR = $(TEST_DIR)/build/obj

CXXFLAGS = 	-Wall \
		 	-std=gnu++2a \
			-I$(DOCTEST_DIR) \
			-I \
			-Iryml \
			-I../../firmware/src/medium \
			-I.. \
			-I../cpputil \
			-I$(RYMLDIR)/src \
			-I$(RYMLDIR)/ext/c4core/src \
			-I$(TEST_DIR) \
			-DTESTPROJECT \

### Boilerplate below here:

OBJECTS = $(addprefix $(BUILDDIR)/, $(subst ../,,$(addsuffix .o, $(basename $(TEST_SOURCES)))))
DEPDIR := $(BUILDDIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(subst ../,,$(basename $<).d)

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
	rm -rf $(TEST_DIR)/build

$(DEPDIR): ; @mkdir -p $@

DEPFILES =  $(addprefix $(DEPDIR)/, $(subst ../,,$(addsuffix .d, $(basename $(TEST_SOURCES)))))
$(DEPFILES):

include $(DEPFILES)

