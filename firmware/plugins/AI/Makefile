# Set the plugin name
PLUGINNAME := AudibleInstruments

# Point to the SDK
ADAPTORDIR := ../VCV-metamodule-adaptor

# Helper variable to point to original source files
SOURCEREPO := ../../vcv_ports/AudibleInstruments

SOURCES :=\
  $(SOURCEREPO)/src/Blinds.cpp \
  $(SOURCEREPO)/src/Braids.cpp \
  $(SOURCEREPO)/src/Branches.cpp \
  $(SOURCEREPO)/src/Elements.cpp \
  $(SOURCEREPO)/src/Kinks.cpp \
  $(SOURCEREPO)/src/Links.cpp \
  $(SOURCEREPO)/src/Marbles.cpp \
  $(SOURCEREPO)/src/Rings.cpp \
  $(SOURCEREPO)/src/Ripples.cpp \
  $(SOURCEREPO)/src/Shades.cpp \
  $(SOURCEREPO)/src/Shelves.cpp \
  $(SOURCEREPO)/src/Tides2.cpp \
  $(SOURCEREPO)/src/Veils.cpp \
  $(SOURCEREPO)/src/Clouds.cpp \
  $(SOURCEREPO)/src/Frames.cpp \
  $(SOURCEREPO)/src/Plaits.cpp \
  $(SOURCEREPO)/src/Stages.cpp \
  $(SOURCEREPO)/src/Streams.cpp \
  $(SOURCEREPO)/src/Tides.cpp \
  $(SOURCEREPO)/src/Warps.cpp \


#Helpers
SOURCES += \
  $(SOURCEREPO)/eurorack/stmlib/utils/random.cc \
  $(SOURCEREPO)/eurorack/stmlib/dsp/atan.cc \
  $(SOURCEREPO)/eurorack/stmlib/dsp/units.cc \
  $(SOURCEREPO)/eurorack/braids/analog_oscillator.cc \
  $(SOURCEREPO)/eurorack/braids/digital_oscillator.cc \
  $(SOURCEREPO)/eurorack/braids/macro_oscillator.cc \
  $(SOURCEREPO)/eurorack/braids/resources.cc \
  $(SOURCEREPO)/eurorack/elements/dsp/exciter.cc \
  $(SOURCEREPO)/eurorack/elements/dsp/ominous_voice.cc \
  $(SOURCEREPO)/eurorack/elements/dsp/resonator.cc \
  $(SOURCEREPO)/eurorack/elements/dsp/tube.cc \
  $(SOURCEREPO)/eurorack/elements/dsp/multistage_envelope.cc \
  $(SOURCEREPO)/eurorack/elements/dsp/part.cc \
  $(SOURCEREPO)/eurorack/elements/dsp/string.cc \
  $(SOURCEREPO)/eurorack/elements/dsp/voice.cc \
  $(SOURCEREPO)/eurorack/elements/resources.cc \
  $(SOURCEREPO)/eurorack/marbles/random/t_generator.cc \
  $(SOURCEREPO)/eurorack/marbles/random/x_y_generator.cc \
  $(SOURCEREPO)/eurorack/marbles/random/output_channel.cc \
  $(SOURCEREPO)/eurorack/marbles/random/lag_processor.cc \
  $(SOURCEREPO)/eurorack/marbles/random/quantizer.cc \
  $(SOURCEREPO)/eurorack/marbles/ramp/ramp_extractor.cc \
  $(SOURCEREPO)/eurorack/marbles/resources.cc \
  $(SOURCEREPO)/eurorack/rings/dsp/fm_voice.cc \
  $(SOURCEREPO)/eurorack/rings/dsp/part.cc \
  $(SOURCEREPO)/eurorack/rings/dsp/string_synth_part.cc \
  $(SOURCEREPO)/eurorack/rings/dsp/string.cc \
  $(SOURCEREPO)/eurorack/rings/dsp/resonator.cc \
  $(SOURCEREPO)/eurorack/rings/resources.cc \
  $(SOURCEREPO)/eurorack/tides2/poly_slope_generator.cc \
  $(SOURCEREPO)/eurorack/tides2/ramp_extractor.cc \
  $(SOURCEREPO)/eurorack/tides2/resources.cc




# If you can't build all the modules, then copy the plugin.cpp file from the source repo, 
# and remove the calls to plugin->addModel() for the modules you don't want to build.
SOURCES += ./plugin.cpp
		
INCLUDES := -I. \
			-I$(SOURCEREPO)/src \
			-I$(SOURCEREPO)/eurorack \

# Any extra flags needed can go here:
EXTRA_CFLAGS := \
			   -DTEST

EXTRA_CPPFLAGS := \
			   -Wno-deprecated-enum-float-conversion \
			   -Wno-misleading-indentation \
			   -Wno-unused-but-set-variable \
			   -Wno-unused-function \
			   -Wno-unused-variable \
			   -Wno-unused-local-typedefs \
			   -Wno-unused-const-variable \
			   -Wno-unused-but-set-variable \
			   -Wno-asm-operand-widths \
			   -Wno-stringop-overflow \
			   -DTEST


include $(ADAPTORDIR)/plugin.mk
