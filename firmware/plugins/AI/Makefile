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
SOURCES += $(SOURCEREPO)/eurorack/stmlib/utils/random.cc 
SOURCES += $(SOURCEREPO)/eurorack/stmlib/dsp/atan.cc 
SOURCES += $(SOURCEREPO)/eurorack/stmlib/dsp/units.cc 

SOURCES += $(SOURCEREPO)/eurorack/braids/analog_oscillator.cc 
SOURCES += $(SOURCEREPO)/eurorack/braids/digital_oscillator.cc 
SOURCES += $(SOURCEREPO)/eurorack/braids/macro_oscillator.cc 
SOURCES += $(SOURCEREPO)/eurorack/braids/resources.cc 

SOURCES += $(wildcard $(SOURCEREPO)/eurorack/plaits/dsp/*.cc)
SOURCES += $(wildcard $(SOURCEREPO)/eurorack/plaits/dsp/engine/*.cc)
SOURCES += $(wildcard $(SOURCEREPO)/eurorack/plaits/dsp/speech/*.cc)
SOURCES += $(wildcard $(SOURCEREPO)/eurorack/plaits/dsp/physical_modelling/*.cc)
SOURCES += $(SOURCEREPO)/eurorack/plaits/resources.cc

SOURCES += $(SOURCEREPO)/eurorack/clouds/dsp/correlator.cc
SOURCES += $(SOURCEREPO)/eurorack/clouds/dsp/granular_processor.cc
SOURCES += $(SOURCEREPO)/eurorack/clouds/dsp/mu_law.cc
SOURCES += $(SOURCEREPO)/eurorack/clouds/dsp/pvoc/frame_transformation.cc
SOURCES += $(SOURCEREPO)/eurorack/clouds/dsp/pvoc/phase_vocoder.cc
SOURCES += $(SOURCEREPO)/eurorack/clouds/dsp/pvoc/stft.cc
SOURCES += $(SOURCEREPO)/eurorack/clouds/resources.cc

SOURCES += $(SOURCEREPO)/eurorack/elements/dsp/exciter.cc 
SOURCES += $(SOURCEREPO)/eurorack/elements/dsp/ominous_voice.cc 
SOURCES += $(SOURCEREPO)/eurorack/elements/dsp/resonator.cc 
SOURCES += $(SOURCEREPO)/eurorack/elements/dsp/tube.cc 
SOURCES += $(SOURCEREPO)/eurorack/elements/dsp/multistage_envelope.cc 
SOURCES += $(SOURCEREPO)/eurorack/elements/dsp/part.cc 
SOURCES += $(SOURCEREPO)/eurorack/elements/dsp/string.cc 
SOURCES += $(SOURCEREPO)/eurorack/elements/dsp/voice.cc 
SOURCES += $(SOURCEREPO)/eurorack/elements/resources.cc 

SOURCES += $(SOURCEREPO)/eurorack/rings/dsp/fm_voice.cc 
SOURCES += $(SOURCEREPO)/eurorack/rings/dsp/part.cc 
SOURCES += $(SOURCEREPO)/eurorack/rings/dsp/string_synth_part.cc 
SOURCES += $(SOURCEREPO)/eurorack/rings/dsp/string.cc 
SOURCES += $(SOURCEREPO)/eurorack/rings/dsp/resonator.cc 
SOURCES += $(SOURCEREPO)/eurorack/rings/resources.cc 

SOURCES += $(SOURCEREPO)/eurorack/tides/generator.cc
SOURCES += $(SOURCEREPO)/eurorack/tides/resources.cc

SOURCES += $(SOURCEREPO)/eurorack/tides2/poly_slope_generator.cc 
SOURCES += $(SOURCEREPO)/eurorack/tides2/ramp_extractor.cc 
SOURCES += $(SOURCEREPO)/eurorack/tides2/resources.cc 

SOURCES += $(SOURCEREPO)/eurorack/warps/dsp/modulator.cc
SOURCES += $(SOURCEREPO)/eurorack/warps/dsp/oscillator.cc
SOURCES += $(SOURCEREPO)/eurorack/warps/dsp/vocoder.cc
SOURCES += $(SOURCEREPO)/eurorack/warps/dsp/filter_bank.cc
SOURCES += $(SOURCEREPO)/eurorack/warps/resources.cc

SOURCES += $(SOURCEREPO)/eurorack/frames/keyframer.cc
SOURCES += $(SOURCEREPO)/eurorack/frames/resources.cc
SOURCES += $(SOURCEREPO)/eurorack/frames/poly_lfo.cc

SOURCES += $(SOURCEREPO)/eurorack/peaks/processors.cc
SOURCES += $(SOURCEREPO)/eurorack/peaks/resources.cc
SOURCES += $(SOURCEREPO)/eurorack/peaks/drums/bass_drum.cc
SOURCES += $(SOURCEREPO)/eurorack/peaks/drums/fm_drum.cc
SOURCES += $(SOURCEREPO)/eurorack/peaks/drums/high_hat.cc
SOURCES += $(SOURCEREPO)/eurorack/peaks/drums/snare_drum.cc
SOURCES += $(SOURCEREPO)/eurorack/peaks/modulations/lfo.cc
SOURCES += $(SOURCEREPO)/eurorack/peaks/modulations/multistage_envelope.cc
SOURCES += $(SOURCEREPO)/eurorack/peaks/pulse_processor/pulse_shaper.cc
SOURCES += $(SOURCEREPO)/eurorack/peaks/pulse_processor/pulse_randomizer.cc
SOURCES += $(SOURCEREPO)/eurorack/peaks/number_station/number_station.cc

SOURCES += $(SOURCEREPO)/eurorack/stages/segment_generator.cc
SOURCES += $(SOURCEREPO)/eurorack/stages/ramp_extractor.cc
SOURCES += $(SOURCEREPO)/eurorack/stages/resources.cc

SOURCES += $(SOURCEREPO)/eurorack/marbles/random/t_generator.cc 
SOURCES += $(SOURCEREPO)/eurorack/marbles/random/x_y_generator.cc 
SOURCES += $(SOURCEREPO)/eurorack/marbles/random/output_channel.cc 
SOURCES += $(SOURCEREPO)/eurorack/marbles/random/lag_processor.cc 
SOURCES += $(SOURCEREPO)/eurorack/marbles/random/quantizer.cc 
SOURCES += $(SOURCEREPO)/eurorack/marbles/ramp/ramp_extractor.cc 
SOURCES += $(SOURCEREPO)/eurorack/marbles/resources.cc 

SOURCES += $(SOURCEREPO)/eurorack/streams/resources.cc
SOURCES += $(SOURCEREPO)/eurorack/streams/processor.cc
SOURCES += $(SOURCEREPO)/eurorack/streams/follower.cc
SOURCES += $(SOURCEREPO)/eurorack/streams/lorenz_generator.cc
SOURCES += $(SOURCEREPO)/eurorack/streams/envelope.cc
SOURCES += $(SOURCEREPO)/eurorack/streams/svf.cc
SOURCES += $(SOURCEREPO)/eurorack/streams/vactrol.cc
SOURCES += $(SOURCEREPO)/eurorack/streams/compressor.cc


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
