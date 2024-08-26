cmake_minimum_required(VERSION 3.22)

if (BUILD_DYN_PLUGIN)
    #FIXME: Improve setting this path?
    include(${CMAKE_CURRENT_LIST_DIR}/../../../metamodule-plugin-sdk/plugin.cmake)
endif()

project(BefacoMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Befaco Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

include(modules.cmake)
# the above should define ${BEFACO_SOURCE_PATHS}, the list of sources to add to the BefacoLibrary OBJECT

add_library(BefacoLibrary STATIC ${BEFACO_SOURCE_PATHS})

target_include_directories(BefacoLibrary PRIVATE ${BEFACO_DIR}/src .)
target_include_directories(BefacoLibrary PRIVATE ${BEFACO_DIR}/../../) #For Befaco SpringReverb to find IR.h file

target_sources(BefacoLibrary PRIVATE 
    ${BEFACO_DIR}/src/noise-plethora/plugins/Banks.cpp
    ${BEFACO_DIR}/src/noise-plethora/teensy/effect_bitcrusher.cpp
    ${BEFACO_DIR}/src/noise-plethora/teensy/effect_combine.cpp
    ${BEFACO_DIR}/src/noise-plethora/teensy/effect_flange.cpp
    ${BEFACO_DIR}/src/noise-plethora/teensy/effect_freeverb.cpp
    ${BEFACO_DIR}/src/noise-plethora/teensy/effect_granular.cpp
    ${BEFACO_DIR}/src/noise-plethora/teensy/effect_multiply.cpp
    ${BEFACO_DIR}/src/noise-plethora/teensy/effect_wavefolder.cpp
    ${BEFACO_DIR}/src/noise-plethora/teensy/filter_variable.cpp
    ${BEFACO_DIR}/src/noise-plethora/teensy/synth_pinknoise.cpp
    ${BEFACO_DIR}/src/noise-plethora/teensy/synth_pwm.cpp
    ${BEFACO_DIR}/src/noise-plethora/teensy/synth_whitenoise.cpp
)


target_compile_options(BefacoLibrary PRIVATE 
    -Wno-double-promotion 
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
    -Wno-asm-operand-widths
)

set_property(TARGET BefacoLibrary PROPERTY CXX_STANDARD 23)

if (BUILD_DYN_PLUGIN)
    target_sources(BefacoLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/plugin.cpp)

    create_plugin(
        SOURCE_LIB      BefacoLibrary
        PLUGIN_NAME     Befaco
        PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/../../Befaco/plugin.json
        SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/../../../assets/Befaco
        DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../../../build/metamodule-plugins/Befaco
    )
endif()
