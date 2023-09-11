include(modules.cmake)

# the above should define ${AUDIBLE_INSTRUMENTS_SOURCE_PATHS}, the list of sources to add to the
# AudibleInstrumentsLibrary OBJECT

add_library(AudibleInstrumentsLibrary OBJECT ${AUDIBLEINSTRUMENTS_SOURCE_PATHS})

target_include_directories(AudibleInstrumentsLibrary PRIVATE ${AUDIBLE_DIR}/src ${AUDIBLE_DIR}/eurorack)

target_compile_options(AudibleInstrumentsLibrary PRIVATE -Wno-double-promotion -Wno-deprecated-enum-float-conversion)

set_property(TARGET AudibleInstrumentsLibrary PROPERTY CXX_STANDARD 20)
