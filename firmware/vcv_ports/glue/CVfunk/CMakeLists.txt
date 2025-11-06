cmake_minimum_required(VERSION 3.22)


if (BUILD_DYN_PLUGIN)
if(NOT "${METAMODULE_SDK_DIR}" STREQUAL "")
	message("METAMODULE_SDK_DIR set by CMake variable ${METAMODULE_SDK_DIR}")
elseif (DEFINED ENV{METAMODULE_SDK_DIR})
    set(METAMODULE_SDK_DIR "$ENV{METAMODULE_SDK_DIR}")
	message("METAMODULE_SDK_DIR set by environment variable ${METAMODULE_SDK_DIR}")
else()
    set(METAMODULE_SDK_DIR "${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk")
	message("METAMODULE_SDK_DIR set to default: ${METAMODULE_SDK_DIR}")
endif()

include(${METAMODULE_SDK_DIR}/plugin.cmake)
endif()

project(CVfunkMetaModulePlugin 
    DESCRIPTION "CVfunk Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

add_library(CVfunkLibrary STATIC)

# set(CVFUNK_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)
set(CVFUNK_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../../../../metamodule-plugin-examples/CVfunk)

target_sources(CVfunkLibrary
    PRIVATE
    ${CVFUNK_SOURCE_DIR}/src/Alloy.cpp
    ${CVFUNK_SOURCE_DIR}/src/Arrange.cpp
    ${CVFUNK_SOURCE_DIR}/src/CVfunkBlank.cpp
    ${CVFUNK_SOURCE_DIR}/src/CVfunkBlank4HP.cpp
	${CVFUNK_SOURCE_DIR}/src/Cartesia.cpp
    ${CVFUNK_SOURCE_DIR}/src/Clpy.cpp
    ${CVFUNK_SOURCE_DIR}/src/Collatz.cpp
    ${CVFUNK_SOURCE_DIR}/src/Count.cpp
    ${CVFUNK_SOURCE_DIR}/src/Decima.cpp
    ${CVFUNK_SOURCE_DIR}/src/EnvelopeArray.cpp
    ${CVFUNK_SOURCE_DIR}/src/FlowerPatch.cpp
    ${CVFUNK_SOURCE_DIR}/src/Hammer.cpp
    ${CVFUNK_SOURCE_DIR}/src/HexMod.cpp
    ${CVFUNK_SOURCE_DIR}/src/Hub.cpp
    ${CVFUNK_SOURCE_DIR}/src/ImpulseController.cpp
    ${CVFUNK_SOURCE_DIR}/src/JunkDNA.cpp
    ${CVFUNK_SOURCE_DIR}/src/Magnets.cpp
    ${CVFUNK_SOURCE_DIR}/src/Morta.cpp
    ${CVFUNK_SOURCE_DIR}/src/Node.cpp
    ${CVFUNK_SOURCE_DIR}/src/Nona.cpp
    ${CVFUNK_SOURCE_DIR}/src/Onion.cpp
    ${CVFUNK_SOURCE_DIR}/src/Ouros.cpp
    ${CVFUNK_SOURCE_DIR}/src/PentaSequencer.cpp
    ${CVFUNK_SOURCE_DIR}/src/Picus.cpp
    ${CVFUNK_SOURCE_DIR}/src/PreeeeeeeeeeessedDuck.cpp
	${CVFUNK_SOURCE_DIR}/src/PressedDuck.cpp
	${CVFUNK_SOURCE_DIR}/src/Ranges.cpp
    ${CVFUNK_SOURCE_DIR}/src/Rat.cpp
	${CVFUNK_SOURCE_DIR}/src/Signals.cpp
	${CVFUNK_SOURCE_DIR}/src/StepWave.cpp
	${CVFUNK_SOURCE_DIR}/src/Steps.cpp
	${CVFUNK_SOURCE_DIR}/src/Strings.cpp
	${CVFUNK_SOURCE_DIR}/src/Syncro.cpp
	${CVFUNK_SOURCE_DIR}/src/Tatami.cpp
	${CVFUNK_SOURCE_DIR}/src/TriDelay.cpp
    ${CVFUNK_SOURCE_DIR}/src/Tuner.cpp
    ${CVFUNK_SOURCE_DIR}/src/Weave.cpp
    ${CVFUNK_SOURCE_DIR}/src/Wonk.cpp

	# ${CVFUNK_SOURCE_DIR}/src/plugin.cpp
)

target_include_directories(CVfunkLibrary PRIVATE ${CVFUNK_SOURCE_DIR}/src )

set_property(TARGET CVfunkLibrary PROPERTY CXX_STANDARD 20)

if (BUILD_DYN_PLUGIN)
if("${INSTALL_DIR}" STREQUAL "")
    set(INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins)
endif()

create_plugin(
    SOURCE_LIB      CVfunkLibrary                                         # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     CVfunk                                         # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${CVFUNK_SOURCE_DIR}/plugin.json                      # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets               # Path to the assets/ dir containing the PNGs
    DESTINATION     ${INSTALL_DIR}  # Dir where plugin .mmplugin file should be put
)
endif()
