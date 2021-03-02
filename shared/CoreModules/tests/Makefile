#this is meant to be run from the shared/ dir
#and there should be shared/doctest/doctest/doctest.h


DOCTEST_DIR ?= doctest/doctest
ifeq (,$(wildcard $(DOCTEST_DIR)/doctest.h))
    $(error Tests require the file doctest.h installed at $(DOCTEST_DIR)/doctest.h)
endif

TEST_DIR ?= CoreModules/tests
TEST_SOURCES = $(TEST_DIR)/doctest.cc
TEST_SOURCES += $(wildcard util/*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cpp)

BUILDDIR = $(TEST_DIR)/build

.PHONY: tests clean 

CXX = clang++

CXXFLAGS = 	-Wall \
		 	-std=gnu++2a \
			-stdlib=libc++ \
			-I$(DOCTEST_DIR) \
			-I. \
			-ICoreModules \
			-I$(TEST_DIR) \
			-Wno-unused-const-variable \
			-DTESTPROJECT \

LDFLAGS = -lstdc++

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(TEST_SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(TEST_SOURCES))))
DEPFLAGS = -MMD -MF$(BUILDDIR)/$(basename $<).d

$(BUILDDIR)/%.o: %.c $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $<)
	$(CC) -c $(DEPFLAGS) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $<)
	$(CXX) -c $(DEPFLAGS) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cpp $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info Building $<)
	$(CXX) -c $(DEPFLAGS) $(CXXFLAGS) $< -o $@

%.d: ;

tests: $(BUILDDIR)/runtests
	$(BUILDDIR)/runtests

$(BUILDDIR)/runtests: $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS)

clean:
	rm -rf $(BUILDDIR)

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS)
