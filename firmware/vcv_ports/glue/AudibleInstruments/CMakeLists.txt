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

# Fix for stmlib STATIC_ASSERT creating typedefs that aren't used
target_compile_options(AudibleInstrumentsLibrary PRIVATE -Wno-unused-local-typedefs)

set_source_files_properties(
  ${AUDIBLE_DIR}/eurorack/stmlib/dsp/units.cc PROPERTIES COMPILE_OPTIONS "-Wno-asm-operand-widths"
)

# Silence warning for synth_string_part.cc (used by Rings.cc) which writes 8B into a 4B space.
# Must be PUBLIC to propagate upwards into linkage of main.elf.
# TODO: fix this somehow, so we don't silence this useful warning in other projects.
target_link_options(AudibleInstrumentsLibrary PUBLIC -Wno-stringop-overflow)

# Define TEST so braids dsp/dsp.h works (since it contains raw Cortex-M4 assembly)
target_compile_definitions(AudibleInstrumentsLibrary PRIVATE TEST)

set_property(TARGET AudibleInstrumentsLibrary PROPERTY CXX_STANDARD 20)
