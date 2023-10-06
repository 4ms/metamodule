set(AUDIBLE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../AudibleInstruments)

# Add modules to be included
set(AudibleInstrumentsModules Braids
                              # Plaits etc
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
)
