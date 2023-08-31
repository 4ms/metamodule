include(modules.cmake)

# the above should define ${AUDIBLE_INSTRUMENTS_SOURCE_PATHS}, the list of sources to add to the BefacoModules library OBJECT

add_library(
  AudibleInstrumentsModules OBJECT
  ${AUDIBLEINSTRUMENTS_SOURCE_PATHS}
)

target_include_directories(AudibleInstrumentsModules PRIVATE ${AUDIBLE_DIR}/src ${AUDIBLE_DIR}/eurorack)

target_compile_options(AudibleInstrumentsModules PRIVATE -Wno-double-promotion -Wno-deprecated-enum-float-conversion)
