set(AUDIBLE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../AudibleInstruments)

add_library(
  AudibleInstrumentsModules OBJECT
  ${AUDIBLE_DIR}/src/Braids.cpp
  ${AUDIBLE_DIR}/eurorack/stmlib/utils/random.cc
  ${AUDIBLE_DIR}/eurorack/stmlib/dsp/atan.cc
  ${AUDIBLE_DIR}/eurorack/stmlib/dsp/units.cc
  ${AUDIBLE_DIR}/eurorack/braids/analog_oscillator.cc
  ${AUDIBLE_DIR}/eurorack/braids/digital_oscillator.cc
  ${AUDIBLE_DIR}/eurorack/braids/macro_oscillator.cc
  ${AUDIBLE_DIR}/eurorack/braids/resources.cc
)

target_include_directories(AudibleInstrumentsModules PRIVATE ${AUDIBLE_DIR}/src ${AUDIBLE_DIR}/eurorack)

target_compile_options(AudibleInstrumentsModules PRIVATE -Wno-double-promotion)
