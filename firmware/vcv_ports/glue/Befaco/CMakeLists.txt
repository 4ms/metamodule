
include(modules.cmake)

# the above should define ${BEFACO_SOURCE_PATHS}, the list of sources to add to the BefacoModules library OBJECT
add_library(BefacoModules OBJECT ${BEFACO_SOURCE_PATHS})

target_include_directories(BefacoModules PRIVATE ${BEFACO_DIR}/src ${PROJECT_SOURCE_DIR}/src/VCV_adaptor/pffft)

target_compile_options(BefacoModules PRIVATE -Wno-double-promotion -Wno-deprecated-enum-float-conversion)
