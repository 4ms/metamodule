include(modules.cmake)
# the above should define ${BEFACO_SOURCE_PATHS}, the list of sources to add to the BefacoLibrary OBJECT

add_library(BefacoLibrary OBJECT ${BEFACO_SOURCE_PATHS})

target_include_directories(BefacoLibrary PRIVATE ${BEFACO_DIR}/src .)
target_include_directories(BefacoLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../../) #For Befaco SpringReverb to find IR.h file

target_compile_options(BefacoLibrary PRIVATE -Wno-double-promotion $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>)

set_property(TARGET BefacoLibrary PROPERTY CXX_STANDARD 20)

