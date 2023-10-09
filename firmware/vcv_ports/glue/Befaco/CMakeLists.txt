include(modules.cmake)

add_library(BefacoLibrary OBJECT ${BEFACO_SOURCE_PATHS})

target_include_directories(BefacoLibrary PRIVATE ${BEFACO_DIR}/src)

target_compile_options(BefacoLibrary PRIVATE -Wno-double-promotion -Wno-deprecated-enum-float-conversion)

set_property(TARGET BefacoLibrary PROPERTY CXX_STANDARD 20)

