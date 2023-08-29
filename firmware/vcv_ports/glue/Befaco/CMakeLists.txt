set(BEFACO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../Befaco)

include(modules.cmake)

list(TRANSFORM BefacoModules PREPEND ${BEFACO_DIR}/src/ 
     OUTPUT_VARIABLE BEFACO_SOURCE_PATHS)

list(TRANSFORM BEFACO_SOURCE_PATHS APPEND .cpp)

# add the above list of sources to the BefacoModules library OBJECT
add_library(BefacoModules OBJECT ${BEFACO_SOURCE_PATHS})

target_include_directories(BefacoModules PRIVATE ${BEFACO_DIR}/src ${PROJECT_SOURCE_DIR}/src/VCV_adaptor/pffft)

target_compile_options(BefacoModules PRIVATE -Wno-double-promotion -Wno-deprecated-enum-float-conversion)
