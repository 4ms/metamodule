#this is meant to be run from PROJECT_ROOT/vcv/ or PROJECT_ROOT/F7/, 
#and there should be PROJECT_ROOT/shared/doctest/doctest/doctest.h

DOCTEST_DIR ?= ../shared/doctest/doctest
TEST_DIR ?= ../shared/CoreModules/tests
TEST_SOURCES = $(TEST_DIR)/doctest.cc
TEST_SOURCES += $(wildcard ../shared/util/*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cpp)

BUILDDIR = build

.PHONY: tests clean FORCE

CXXFLAGS = 	-Wall \
		 	-std=gnu++2a \
			-stdlib=libc++ \
			-I$(DOCTEST_DIR) \
			-I../shared \
			-I../shared/CoreModules \

tests: $(BUILDDIR)/runtests
	$(BUILDDIR)/runtests

#Todo: build test sources individually into .o files, and use -MM -MF -MMD to check dependencies
$(BUILDDIR)/runtests: $(TEST_SOURCES) FORCE
	@mkdir -p $(@D)
	clang++ $(CXXFLAGS) $(TEST_SOURCES) -o $(BUILDDIR)/runtests

clean:
	rm -rf $(BUILDDIR)


