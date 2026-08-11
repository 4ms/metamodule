cmake_minimum_required(VERSION 3.22)

project(
  BefacoMetaModulePlugin
  VERSION 0.1
  DESCRIPTION "Befaco Plugin for MetaModule"
  LANGUAGES C CXX ASM
)

# Path to the VCV Rack plugin submodule
set(BEFACO_DIR ${CMAKE_CURRENT_LIST_DIR}/../../Befaco)

add_library(BefacoLibrary STATIC)

file(GLOB BEFACO_MODULE_SOURCES CONFIGURE_DEPENDS
  ${BEFACO_DIR}/src/*.cpp
)

list(REMOVE_ITEM BEFACO_MODULE_SOURCES
  ${BEFACO_DIR}/src/plugin.cpp
  ${BEFACO_DIR}/src/Bypass.cpp
  ${BEFACO_DIR}/src/MidiThing.cpp
)

file(GLOB_RECURSE BEFACO_NOISE_PLETHORA_SOURCES CONFIGURE_DEPENDS
  ${BEFACO_DIR}/src/noise-plethora/*/*.cpp
)

file(GLOB BEFACO_OWLPROGRAM_SOURCES CONFIGURE_DEPENDS
  ${BEFACO_DIR}/libs/OwlProgram/LibSource/*.cpp
  ${BEFACO_DIR}/libs/OwlProgram/LibSource/*.c
  ${BEFACO_DIR}/libs/OwlProgram/Libraries/KissFFT/*.c
)

list(REMOVE_ITEM BEFACO_OWLPROGRAM_SOURCES
  ${BEFACO_DIR}/libs/OwlProgram/LibSource/ColourScreenPatch.cpp
  ${BEFACO_DIR}/libs/OwlProgram/LibSource/MonochromeScreenPatch.cpp
  ${BEFACO_DIR}/libs/OwlProgram/LibSource/PatchParameter.cpp
)

target_sources(
  BefacoLibrary
  PRIVATE ${BEFACO_MODULE_SOURCES}
          ${BEFACO_NOISE_PLETHORA_SOURCES}
          ${BEFACO_OWLPROGRAM_SOURCES}
)

target_include_directories(
  BefacoLibrary
  PRIVATE ${BEFACO_DIR}/src
          ${BEFACO_DIR}/../../ # For Befaco SpringReverb to find IR.h file
          ${BEFACO_DIR}/libs/Iroi
          ${BEFACO_DIR}/libs/OwlProgram/LibSource
          ${BEFACO_DIR}/libs/OwlProgram/Source
          ${BEFACO_DIR}/libs/OwlProgram/Libraries/KissFFT
          ${BEFACO_DIR}/libs/OwlProgram/Libraries
          .
)

target_compile_options(
  BefacoLibrary PRIVATE -Wno-double-promotion $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
                        -Wno-asm-operand-widths
                        -include ${CMAKE_CURRENT_LIST_DIR}/OwlProgramMetaModuleCompat.h
)

target_compile_definitions(BefacoLibrary PRIVATE METAMODULE VCV)

# set_property(TARGET BefacoLibrary PROPERTY METAMODULE_DISABLE_IPO TRUE)
set_property(TARGET BefacoLibrary PROPERTY CXX_STANDARD 23)
