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
          -fvisibility-inlines-hidden
          # Fixes for warnings with Gamma:
          -Wno-misleading-indentation
          -Wno-unused-but-set-variable
          -Wno-unused-function
          # Fixes for warnings with DSP and main source:
          -Wno-unused-variable
)

target_compile_definitions(hetrickcvLibrary PRIVATE GAMMA_EMBEDDED_COMPILE)
