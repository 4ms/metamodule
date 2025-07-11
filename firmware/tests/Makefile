# This is meant to be run from the parent dir of this Makefile:
# make -f tests/Makefile

TEST_DIR ?= tests
DOCTESTHEADER_DIR = $(TEST_DIR)
BUILDDIR = $(TEST_DIR)/build
RYMLDIR = lib/patch-serial/ryml/rapidyaml

TEST_SOURCES = $(TEST_DIR)/doctest.cc
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_SOURCES += lib/patch-serial/yaml_to_patch.cc
TEST_SOURCES += lib/patch-serial/patch_to_yaml.cc
TEST_SOURCES += lib/patch-serial/ryml/ryml_serial.cc
TEST_SOURCES += lib/patch-serial/ryml/ryml_init.cc
TEST_SOURCES += $(wildcard $(RYMLDIR)/src/c4/yml/*.cpp)
TEST_SOURCES += $(wildcard $(RYMLDIR)/ext/c4core/src/c4/*.cpp)
TEST_SOURCES += src/fs/time_convert.cc
TEST_SOURCES += src/user_settings/settings_parse.cc
TEST_SOURCES += src/user_settings/settings_serialize.cc
TEST_SOURCES += src/fw_update/hash/md5_hash.h
TEST_SOURCES += src/fw_update/hash/hash_processor.cc
TEST_SOURCES += lib/CoreModules/moduleFactory.cc
TEST_SOURCES += tests/resampler_tests.cc
TEST_SOURCES += vcv_plugin/export/src/resampler.cc
TEST_SOURCES += tests/stubs/plugin_module.cc
TEST_SOURCES += src/params/expanders.cc
TEST_SOURCES += src/gui/elements/element_name.cc
TEST_SOURCES += src/gui/elements/panel_name.cc
TEST_SOURCES += $(TEST_DIR)/stubs/async_thread_control.cc

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
			-Ilib \
			-Ilib/lvgl/lvgl \
			-Ilib/cpputil \
			-Ilib/patch-serial \
			-Ilib/patch-serial/ryml \
			-Ilib/patch-serial/ryml/rapidyaml/src \
			-Ilib/CoreModules \
			-Imetamodule-plugin-sdk/metamodule-core-interface \
			-Imetamodule-plugin-sdk/metamodule-rack-interface/dep/include \
			-I$(RYMLDIR)/src \
			-I$(RYMLDIR)/ext/c4core/src \
			-isystem $(TEST_DIR) \
			-DTESTPROJECT \
			-g3 -O0 \

### Boilerplate below here:

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(TEST_SOURCES))))
DEPDIR := $(BUILDDIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(basename $<).d
TMPFILE = $(BUILDDIR)/runtests.out

.PHONY: all tests clean patches

all: patches tests

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

clean:
	rm -rf $(BUILDDIR)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(addprefix $(DEPDIR)/, $(addsuffix .d, $(basename $(TEST_SOURCES))))
$(DEPFILES):

include $(wildcard $(DEPFILES))

