# This is meant to be run from the CoreModules/ dir
# make -f tests/Makefile

TEST_DIR ?= tests
DOCTESTHEADER_DIR = $(TEST_DIR)
RYMLDIR = ../../shared/patch-serial/ryml
TEST_SOURCES = $(TEST_DIR)/doctest.cc
TEST_SOURCES += moduleFactory.cc
TEST_SOURCES += $(wildcard ../cpputil/util/*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_SOURCES += 4ms/core/axoloti-wrapper/axoloti_math.cpp
TEST_SOURCES += $(RYMLDIR)/ryml_serial.cc
TEST_SOURCES += $(RYMLDIR)/ryml_init.cc
TEST_SOURCES += $(wildcard $(RYMLDIR)/rapidyaml/src/c4/yml/*.cpp)
TEST_SOURCES += $(wildcard $(RYMLDIR)/rapidyaml/ext/c4core/src/c4/*.cpp)

BUILDDIR = $(TEST_DIR)/build/obj/obj

CXXFLAGS = 	-Wall \
		 	-std=gnu++20 \
			-I. \
			-I.. \
			-I../../firmware/metamodule-plugin-sdk/metamodule-core-interface \
			-I../../shared/cpputil \
			-I../../shared/patch-serial \
			-I$(RYMLDIR) \
			-I$(RYMLDIR)/rapidyaml/src \
			-I$(RYMLDIR)/rapidyaml/ext/c4core/src \
			-I$(TEST_DIR) \
			-Wno-unused-const-variable \
			-Wno-missing-braces \
			-DTESTPROJECT \

### Boilerplate below here:

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(TEST_SOURCES))))
DEPDIR := $(BUILDDIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(basename $<).d

TMPFILE = $(BUILDDIR)/runtests.out

.PHONY: all tests clean

all: $(DOCTESTHEADER_DIR)/doctest.h tests

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CC) -c $(DEPFLAGS) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CXX) -c $(DEPFLAGS) $(CXXFLAGS) $< -o $@

#FixMe: This kludge lets us build util/%.o, but it's not pretty or general
$(BUILDDIR)/%.o: ../%.cc
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CXX) -c $(DEPFLAGS) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.o: ../%.cpp
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
	rm -rf $(BUILDDIR)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(addprefix $(DEPDIR)/, $(addsuffix .d, $(basename $(TEST_SOURCES))))
$(DEPFILES):

include $(wildcard $(DEPFILES))

