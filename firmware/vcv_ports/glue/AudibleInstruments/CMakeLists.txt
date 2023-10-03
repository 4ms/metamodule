include(modules.cmake)

# the above should define ${AUDIBLE_INSTRUMENTS_SOURCE_PATHS}, the list of sources to add to the
# AudibleInstrumentsLibrary OBJECT

add_library(AudibleInstrumentsLibrary OBJECT ${AUDIBLEINSTRUMENTS_SOURCE_PATHS})

target_include_directories(AudibleInstrumentsLibrary PRIVATE ${AUDIBLE_DIR}/src ${AUDIBLE_DIR}/eurorack)

target_compile_options(AudibleInstrumentsLibrary PRIVATE -Wno-double-promotion -Wno-deprecated-enum-float-conversion)

# Fixups for compiler warnings in AudibleInstruments:
set_source_files_properties(
  ${AUDIBLE_DIR}/eurorack/braids/digital_oscillator.cc
  PROPERTIES COMPILE_OPTIONS "-Wno-unused-const-variable;-Wno-unused-but-set-variable"
)

set_source_files_properties(
  ${AUDIBLE_DIR}/eurorack/stmlib/dsp/units.cc PROPERTIES COMPILE_OPTIONS "-Wno-asm-operand-widths"
)

# Define TEST so braids dsp/dsp.h works (since it contains raw Cortex-M4 assembly)
target_compile_definitions(AudibleInstrumentsLibrary PRIVATE TEST)

set_property(TARGET AudibleInstrumentsLibrary PROPERTY CXX_STANDARD 20)
