set(AUDIBLE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../AudibleInstruments)

# Add modules to be included
set(
  AudibleInstrumentsModules
  Blinds
  Braids
  Branches
  # Clouds
  Elements
  # Frames
  Kinks
  Links
  Marbles
  # Plaits
  Rings
  Ripples
  Shades
  Shelves
  # Stages
  # Streams
  # Tides
  Tides2
  Veils
  # Warps
  # Edges, Grids, and Peaks don't have Audible Instruments equivalents
)

include(${CMAKE_CURRENT_LIST_DIR}/../filter.cmake)
limit_modules_built("AudibleInstruments" AudibleInstrumentsModules)

# svgs
list(TRANSFORM AudibleInstrumentsModules PREPEND ${AUDIBLE_DIR}/res/ OUTPUT_VARIABLE AUDIBLEINSTRUMENTS_FACEPLATE_SVGS)
list(TRANSFORM AUDIBLEINSTRUMENTS_FACEPLATE_SVGS APPEND .svg)

# core cpp source files
list(TRANSFORM AudibleInstrumentsModules PREPEND ${AUDIBLE_DIR}/src/ OUTPUT_VARIABLE AUDIBLEINSTRUMENTS_SOURCE_PATHS)
list(TRANSFORM AUDIBLEINSTRUMENTS_SOURCE_PATHS APPEND .cpp)

# extra cpp source files
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

  ${AUDIBLE_DIR}/eurorack/elements/dsp/exciter.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/ominous_voice.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/resonator.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/tube.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/multistage_envelope.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/part.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/string.cc
  ${AUDIBLE_DIR}/eurorack/elements/dsp/voice.cc
  ${AUDIBLE_DIR}/eurorack/elements/resources.cc

  ${AUDIBLE_DIR}/eurorack/marbles/random/t_generator.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/x_y_generator.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/output_channel.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/lag_processor.cc
  ${AUDIBLE_DIR}/eurorack/marbles/random/quantizer.cc
  ${AUDIBLE_DIR}/eurorack/marbles/ramp/ramp_extractor.cc
  ${AUDIBLE_DIR}/eurorack/marbles/resources.cc

  ${AUDIBLE_DIR}/eurorack/rings/dsp/fm_voice.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/part.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/string_synth_part.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/string.cc
  ${AUDIBLE_DIR}/eurorack/rings/dsp/resonator.cc
  ${AUDIBLE_DIR}/eurorack/rings/resources.cc

  ${AUDIBLE_DIR}/eurorack/tides2/poly_slope_generator.cc
  ${AUDIBLE_DIR}/eurorack/tides2/ramp_extractor.cc
  ${AUDIBLE_DIR}/eurorack/tides2/resources.cc
)
