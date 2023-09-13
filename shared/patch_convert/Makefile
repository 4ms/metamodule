RYMLDIR = ryml/rapidyaml
LVGLDIR = ../../firmware/lib/lvgl/lvgl
CXXFLAGS = 	-Wall \
		 	-std=gnu++2a \
			-Wdeprecated-anon-enum-enum-conversion \
			-Iryml \
			-I../\
			-I../etl/include \
			-I$(RYMLDIR)/src \
			-I$(RYMLDIR)/ext/c4core/src \			
			-I$(LVGLDIR)


SOURCES =
SOURCES += patch_convert.cc
SOURCES += ryml/ryml_serial.cc
SOURCES += patch_to_yaml.cc
SOURCES += $(wildcard $(RYMLDIR)/src/c4/yml/*.cpp)
SOURCES += $(wildcard $(RYMLDIR)/ext/c4core/src/c4/*.cpp)

BUILDDIR = build

CXX = clang++
LDFLAGS = -lstdc++
OBJECTS = $(addprefix $(BUILDDIR)/, $(subst ../,,$(addsuffix .o, $(basename $(SOURCES)))))
DEPDIR := $(BUILDDIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(subst ../,,$(basename $<).d)

.PHONY: all tests clean patch_convert

all: patch_convert

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

patch_convert: $(OBJECTS)
	@$(CXX) $(LDFLAGS) -o $@ $(OBJECTS)

clean:
	rm -rf $(BUILDDIR)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(addprefix $(DEPDIR)/, $(addsuffix .d, $(basename $(TEST_SOURCES))))
$(DEPFILES):

include $(wildcard $(DEPFILES))

