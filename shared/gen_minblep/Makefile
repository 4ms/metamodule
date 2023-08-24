SOURCES = minblep_main.cpp \
          minblep.cpp \
          ../../firmware/src/VCV_adaptor/pffft/pffft.c \
          ../cpputil/util/math_tables.cc

BUILDDIR = build
DEPFLAGS = -MMD -MP -MF $(BUILDDIR)/$(basename $<).d
OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))
DEPS   	  = $(addprefix $(BUILDDIR)/, $(addsuffix .d, $(basename $(SOURCES))))

CFLAGS = -I../../firmware/src/ \
         -I.. \
         -I../cpputil

CXXFLAGS = $(CFLAGS) \
		   -std=c++20

$(BUILDDIR)/%.o: %.c $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info $(TAG) Building $< at $(OPTFLAG))
	@$(CC) -c $(DEPFLAGS) $(OPTFLAG) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info $(TAG) Building $< at $(OPTFLAG))
	@$(CXX) -c $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cpp $(BUILDDIR)/%.d
	@mkdir -p $(dir $@)
	$(info $(TAG) Building $< at $(OPTFLAG))
	@$(CXX) -c $(DEPFLAGS) $(OPTFLAG) $(CXXFLAGS) $< -o $@


all: Makefile gen_minblep

gen_minblep: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)

%.d: ;

clean:
	rm -rf $(BUILDDIR)

ifneq "$(MAKECMDGOALS)" "clean"
-include $(DEPS)
endif

.PRECIOUS: $(DEPS) $(OBJECTS) $(ELF) $(PRECHDRS)

.PHONY: all
