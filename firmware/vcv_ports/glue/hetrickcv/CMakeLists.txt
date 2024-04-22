cmake_minimum_required(VERSION 3.22)

if (BUILD_DYN_PLUGIN)
    include(${CMAKE_CURRENT_LIST_DIR}/../../../metamodule-plugin-sdk/plugin.cmake)
endif()

project(hetrickcvMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "hetrickcv Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

include(modules.cmake)

file(
  GLOB
  DSP_SOURCES
  ${HETRICKCV_DIR}/src/DSP/*.cpp
  ${HETRICKCV_DIR}/src/DSP/Phasors/*.cpp
)

set(EXTRA_SOURCES ${HETRICKCV_DIR}/src/HetrickUtilities.cpp)

set(GAMMA_SOURCES
    ${HETRICKCV_DIR}/Gamma/src/arr.cpp
    ${HETRICKCV_DIR}/Gamma/src/DFT.cpp
    ${HETRICKCV_DIR}/Gamma/src/Domain.cpp
    ${HETRICKCV_DIR}/Gamma/src/FFT_fftpack.cpp
    ${HETRICKCV_DIR}/Gamma/src/fftpack++1.cpp
    ${HETRICKCV_DIR}/Gamma/src/fftpack++2.cpp
    ${HETRICKCV_DIR}/Gamma/src/scl.cpp
)

add_library(
  hetrickcvLibrary OBJECT
  ${HETRICKCV_SOURCE_PATHS}
  ${DSP_SOURCES}
  ${EXTRA_SOURCES}
  ${GAMMA_SOURCES}
)

target_include_directories(hetrickcvLibrary PRIVATE ${HETRICKCV_DIR}/Gamma ${HETRICKCV_DIR}/src)

set_property(TARGET hetrickcvLibrary PROPERTY CXX_STANDARD 20)

target_compile_options(
  hetrickcvLibrary
  PRIVATE -fvisibility=hidden
          $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>
          # Fixes for warnings with Gamma:
          -Wno-misleading-indentation
          -Wno-unused-but-set-variable
          -Wno-unused-function
          # Fixes for warnings with DSP and main source:
          -Wno-unused-variable
)

if (BUILD_DYN_PLUGIN)
    target_sources(hetrickcvLibrary PRIVATE ${CMAKE_CURRENT_LIST_DIR}/HetrickCV.cpp)

    create_plugin(
        SOURCE_LIB      hetrickcvLibrary
        PLUGIN_NAME     hetrickcv
        SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/../../../assets/hetrickcv
        DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../../../build/metamodule-plugins/hetrickcv
    )
endif()
