TEST_SOURCES = doctest.cc
TEST_SOURCES += $(wildcard *_test.cc)
TEST_SOURCES += $(wildcard *_test.cpp)
TEST_SOURCES += $(wildcard *_tests.cc)
TEST_SOURCES += $(wildcard *_tests.cpp)
TEST_SOURCES += $(wildcard test_*.cc)
TEST_SOURCES += $(wildcard test_*.cpp)

BUILDDIR = build

.PHONY: tests clean

CXXFLAGS = 	-Wall \
		 	-std=gnu++2a \
			-stdlib=libc++

tests: $(BUILDDIR)/runtests
	$(BUILDDIR)/runtests

$(BUILDDIR)/runtests: $(TEST_SOURCES) $(wildcard ../*.hh)
	@mkdir -p $(@D)
	clang++ $(CXXFLAGS) $(TEST_SOURCES) -o $(BUILDDIR)/runtests

clean:
	rm -rf $(BUILDDIR)

