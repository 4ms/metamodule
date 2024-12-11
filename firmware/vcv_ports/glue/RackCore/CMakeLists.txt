cmake_minimum_required(VERSION 3.22)

if (BUILD_DYN_PLUGIN)
    include(${CMAKE_CURRENT_LIST_DIR}/../../../metamodule-plugin-sdk/plugin.cmake)
endif()

project(RackCoreMetaModulePlugin 
    VERSION     0.1
    DESCRIPTION "Rack Core Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../RackCore)

add_library(RackCoreLibrary OBJECT
    ${SOURCE_DIR}/MIDI_CV.cpp
    ${SOURCE_DIR}/Scope.cpp
)

target_include_directories(RackCoreLibrary PRIVATE ${SOURCE_DIR})

# target_compile_options(RackCoreLibrary PRIVATE -Wno-double-promotion)

set_property(TARGET RackCoreLibrary PROPERTY CXX_STANDARD 23)

if (BUILD_DYN_PLUGIN)
    target_sources(RackCoreLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/plugin.cpp)

    create_plugin(
        SOURCE_LIB      RackCoreLibrary
        PLUGIN_NAME     RackCore
        PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/../../eightfold/plugin.json
        SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/../../../assets/RackCore
        DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../../../build/metamodule-plugins/RackCore
    )
endif()
