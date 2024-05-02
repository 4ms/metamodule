set(AUDIBLE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../AudibleInstruments)

# Add modules to be included
set(
  AudibleInstrumentsModules
  Blinds
  Braids
  Branches
  Clouds #
  Elements
  Frames #
  Kinks
  Links
  Marbles
  Plaits #
  Rings
  Ripples
  Shades
  Shelves
  Stages #
  Streams #
  Tides #
  Tides2
  Veils
  Warps #
)

# svgs
list(TRANSFORM AudibleInstrumentsModules PREPEND ${AUDIBLE_DIR}/res/ OUTPUT_VARIABLE AUDIBLEINSTRUMENTS_FACEPLATE_SVGS)
list(TRANSFORM AUDIBLEINSTRUMENTS_FACEPLATE_SVGS APPEND .svg)

# core cpp source files
list(TRANSFORM AudibleInstrumentsModules PREPEND ${AUDIBLE_DIR}/src/ OUTPUT_VARIABLE AUDIBLEINSTRUMENTS_SOURCE_PATHS)
list(TRANSFORM AUDIBLEINSTRUMENTS_SOURCE_PATHS APPEND .cpp)

# extra cpp source files
file(GLOB PLAITS_SOURCES
  ${AUDIBLE_DIR}/eurorack/plaits/dsp/*.cc
  ${AUDIBLE_DIR}/eurorack/plaits/dsp/engine/*.cc
  ${AUDIBLE_DIR}/eurorack/plaits/dsp/speech/*.cc
  ${AUDIBLE_DIR}/eurorack/plaits/dsp/physical_modelling/*.cc
)

list(
  APPEND
  AUDIBLEINSTRUMENTS_SOURCE_PATHS
  ${AUDIBLE_DIR}/eurorack/stmlib/utils/random.cc
  ${AUDIBLE_DIR}/eurorack/stmlib/dsp/atan.cc
  ${AUDIBLE_DIR}/eurorack/stmlib/dsp/units.cc

  ${AUDIBLE_DIR}/eurorack/braids/analog_oscillator.cc
  ${AUDIBLE_DIR}/eurorack/braids/digital_oscillator.cc
  ${AUDIBLE_DIR}/eurorack/braids/macro_oscillator.cc
  ${AUDIBLE_DIR}/eurorack/braids/resources.cc

  ${PLAITS_SOURCES}
  ${AUDIBLE_DIR}/eurorack/plaits/resources.cc

  ${AUDIBLE_DIR}/eurorack/clouds/dsp/correlator.cc
  ${AUDIBLE_DIR}/eurorack/clouds/dsp/granular_processor.cc
  ${AUDIBLE_DIR}/eurorack/clouds/dsp/mu_law.cc
  ${AUDIBLE_DIR}/eurorack/clouds/dsp/pvoc/frame_transformation.cc
  ${AUDIBLE_DIR}/eurorack/clouds/dsp/pvoc/phase_vocoder.cc
  ${AUDIBLE_DIR}/eurorack/clouds/dsp/pvoc/stft.cc
  ${AUDIBLE_DIR}/eurorack/clouds/resources.cc


  ${AUDIBLE_DIR}/eurorack/elements/dsp/exciter.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/ominous_voice.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/resonator.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/tube.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/multistage_envelope.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/part.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/string.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/voice.cc
  ${AUDIBLE_DIR}/eurorack/elements/resources.cc

  ${AUDIBLE_DIR}/eurorack/rings/dsp/fm_voice.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/part.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/string_synth_part.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/string.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/resonator.cc
  ${AUDIBLE_DIR}/eurorack/rings/resources.cc

  ${AUDIBLE_DIR}/eurorack/tides/generator.cc
  ${AUDIBLE_DIR}/eurorack/tides/resources.cc

  ${AUDIBLE_DIR}/eurorack/tides2/poly_slope_generator.cc
  ${AUDIBLE_DIR}/eurorack/tides2/ramp_extractor.cc
  ${AUDIBLE_DIR}/eurorack/tides2/resources.cc

  ${AUDIBLE_DIR}/eurorack/warps/dsp/modulator.cc
  ${AUDIBLE_DIR}/eurorack/warps/dsp/oscillator.cc
  ${AUDIBLE_DIR}/eurorack/warps/dsp/vocoder.cc
  ${AUDIBLE_DIR}/eurorack/warps/dsp/filter_bank.cc
  ${AUDIBLE_DIR}/eurorack/warps/resources.cc

  ${AUDIBLE_DIR}/eurorack/frames/keyframer.cc
  ${AUDIBLE_DIR}/eurorack/frames/resources.cc
  ${AUDIBLE_DIR}/eurorack/frames/poly_lfo.cc

  ${AUDIBLE_DIR}/eurorack/peaks/processors.cc
  ${AUDIBLE_DIR}/eurorack/peaks/resources.cc
  ${AUDIBLE_DIR}/eurorack/peaks/drums/bass_drum.cc
  ${AUDIBLE_DIR}/eurorack/peaks/drums/fm_drum.cc
  ${AUDIBLE_DIR}/eurorack/peaks/drums/high_hat.cc
  ${AUDIBLE_DIR}/eurorack/peaks/drums/snare_drum.cc
  ${AUDIBLE_DIR}/eurorack/peaks/modulations/lfo.cc
  ${AUDIBLE_DIR}/eurorack/peaks/modulations/multistage_envelope.cc
  ${AUDIBLE_DIR}/eurorack/peaks/pulse_processor/pulse_shaper.cc
  ${AUDIBLE_DIR}/eurorack/peaks/pulse_processor/pulse_randomizer.cc
  ${AUDIBLE_DIR}/eurorack/peaks/number_station/number_station.cc

  ${AUDIBLE_DIR}/eurorack/stages/segment_generator.cc
  ${AUDIBLE_DIR}/eurorack/stages/ramp_extractor.cc
  ${AUDIBLE_DIR}/eurorack/stages/resources.cc

  ${AUDIBLE_DIR}/eurorack/marbles/random/t_generator.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/x_y_generator.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/output_channel.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/lag_processor.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/quantizer.cc
  ${AUDIBLE_DIR}/eurorack/marbles/ramp/ramp_extractor.cc
  ${AUDIBLE_DIR}/eurorack/marbles/resources.cc

  ${AUDIBLE_DIR}/eurorack/streams/resources.cc
  ${AUDIBLE_DIR}/eurorack/streams/processor.cc
  ${AUDIBLE_DIR}/eurorack/streams/follower.cc
  ${AUDIBLE_DIR}/eurorack/streams/lorenz_generator.cc
  ${AUDIBLE_DIR}/eurorack/streams/envelope.cc
  ${AUDIBLE_DIR}/eurorack/streams/svf.cc
  ${AUDIBLE_DIR}/eurorack/streams/vactrol.cc
  ${AUDIBLE_DIR}/eurorack/streams/compressor.cc

)
