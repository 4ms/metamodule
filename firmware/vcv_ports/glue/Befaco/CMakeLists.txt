include(modules.cmake)
# the above should define ${BEFACO_SOURCE_PATHS}, the list of sources to add to the BefacoLibrary OBJECT

set(FW_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../..)

add_library(BefacoLibrary OBJECT ${BEFACO_SOURCE_PATHS} ${FW_ROOT}/src/VCV_adaptor/pffft/pffft.c)

target_include_directories(BefacoLibrary PRIVATE ${BEFACO_DIR}/src ${FW_ROOT}/src/VCV_adaptor/pffft)

target_compile_options(BefacoLibrary PRIVATE -Wno-double-promotion -Wno-deprecated-enum-float-conversion)

# Fixup for pffft compiler warnings
set_source_files_properties(${FW_ROOT}/src/VCV_adaptor/pffft/pffft.c COMPILE_FLAGS -Wno-double-promotion)
