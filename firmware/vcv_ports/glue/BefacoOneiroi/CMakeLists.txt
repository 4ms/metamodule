cmake_minimum_required(VERSION 3.22)

if (BUILD_DYN_PLUGIN)
    #FIXME: Improve setting this path?
    include(${CMAKE_CURRENT_LIST_DIR}/../../../metamodule-plugin-sdk/plugin.cmake)
endif()

project(BefacoOneiroiMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "BefacoOneiroi Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

include(modules.cmake)
# the above should define ${BEFACO_ONEIROI_SOURCE_PATHS}, the list of sources to add to the BefacoLibrary OBJECT

add_library(BefacoOneiroiLibrary STATIC ${BEFACO_ONEIROI_SOURCE_PATHS})


target_include_directories(BefacoOneiroiLibrary PRIVATE 
	${BEFACO_ONEIROI_DIR}/src 
    ${BEFACO_ONEIROI_DIR}/libs/OwlProgram/LibSource
    ${BEFACO_ONEIROI_DIR}/libs/OwlProgram/Source
    ${BEFACO_ONEIROI_DIR}/libs/OwlProgram/Libraries/KissFFT
    ${BEFACO_ONEIROI_DIR}/libs/OwlProgram/Libraries
    ${BEFACO_ONEIROI_DIR}/libs/Oneiroi
)

file(GLOB DSP_SOURCES 
    ${SOURCE_DIR}/libs/OwlProgram/LibSource/*.cpp
    ${SOURCE_DIR}/libs/OwlProgram/LibSource/*.c
    ${SOURCE_DIR}/libs/OwlProgram/Libraries/KissFFT/*.c
    libs/OwlProgram/LibSource/*.c
)



target_compile_options(BefacoOneiroiLibrary PRIVATE 
    -Wno-double-promotion 
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
    -Wno-asm-operand-widths
)

target_compile_definitions(BefacoOneiroiLibrary PRIVATE METAMODULE)

set_property(TARGET BefacoOneiroiLibrary PROPERTY CXX_STANDARD 23)

if (BUILD_DYN_PLUGIN)
    target_sources(BefacoOneiroiLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/plugin.cpp)

    create_plugin(
        SOURCE_LIB      BefacoOneiroiLibrary
        PLUGIN_NAME     BefacoOneiroi
        PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/../../BefacoOneiroi/plugin.json
        SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/../../../assets/BefacoOneiroi
        DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../../../build/metamodule-plugins/BefacoOneiroi
    )
endif()
