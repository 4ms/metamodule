cmake_minimum_required(VERSION 3.22)

if (BUILD_DYN_PLUGIN)
    include(${CMAKE_CURRENT_LIST_DIR}/../../../metamodule-plugin-sdk/plugin.cmake)
endif()

project(ValleyMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Valley Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

add_library(ValleyLibrary STATIC)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../Valley)

target_sources(ValleyLibrary
    PRIVATE
    ${SOURCE_DIR}/src/Plateau/Plateau.cpp
    ${SOURCE_DIR}/src/Plateau/Dattorro.cpp

    ${SOURCE_DIR}/src/Topograph/TopographPatternGenerator.cpp
    ${SOURCE_DIR}/src/Topograph/Topograph.cpp
    ${SOURCE_DIR}/src/uGraph/uGraph.cpp

    ${SOURCE_DIR}/src/dsp/modulation/LinearEnvelope.cpp
    ${SOURCE_DIR}/src/dsp/filters/OnePoleFilters.cpp
    ${SOURCE_DIR}/src/timers/Metronome.cpp
    ${SOURCE_DIR}/src/timers/Oneshot.cpp
    ${SOURCE_DIR}/src/gui/ValleyChoiceMenu.cpp
    ${SOURCE_DIR}/src/gui/PlainText.cpp

    ${SOURCE_DIR}/src/utilities/math_lut.cc
)

if (BUILD_DYN_PLUGIN)
    target_sources(ValleyLibrary
        PRIVATE

        ${SOURCE_DIR}/src/Terrorform/Terrorform.cpp

        ${SOURCE_DIR}/src/Interzone/Interzone.cpp
        
        ${SOURCE_DIR}/src/Amalgam/Amalgam.cpp
        ${SOURCE_DIR}/src/Amalgam/VecAmalgam.cpp

        ${SOURCE_DIR}/src/Feline/Feline.cpp

        ${SOURCE_DIR}/src/dsp/filters/VecOnePoleFilters.cpp
        ${SOURCE_DIR}/src/dsp/filters/VecOTAFilter.cpp
        ${SOURCE_DIR}/src/dsp/filters/OTAFilter.cpp
        ${SOURCE_DIR}/src/dsp/modulation/VecLoopingADSR.cpp
        ${SOURCE_DIR}/src/dsp/fx/DiodeRingMod.cpp
        ${SOURCE_DIR}/src/dsp/fx/VecDiodeRingMod.cpp
        ${SOURCE_DIR}/src/gui/SteppedSlider.cpp
        ${SOURCE_DIR}/src/gui/DigitalDisplay.cpp
        ${SOURCE_DIR}/src/utilities/Utilities.cpp

        plugin.cpp 
    )

    target_compile_definitions(ValleyLibrary PRIVATE
        USE_SINGLE_FLOAT=1
    )
endif()

target_include_directories(ValleyLibrary PRIVATE 
	${SOURCE_DIR}/src 
)

set_property(TARGET ValleyLibrary PROPERTY CXX_STANDARD 23)

target_compile_options(ValleyLibrary PRIVATE 
	-Wno-double-promotion 
    -Wno-unused-variable
	$<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
)

target_compile_definitions(ValleyLibrary PRIVATE
    USE_SINGLE_FLOAT=1
)


if (BUILD_DYN_PLUGIN)
	create_plugin(
		SOURCE_LIB      ValleyLibrary                       # This is the cmake target name (defined in add_target)
		PLUGIN_NAME     Valley                              # This must match the brand "slug" used in VCV Rack
		SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
		DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/Valley
	)
endif()
