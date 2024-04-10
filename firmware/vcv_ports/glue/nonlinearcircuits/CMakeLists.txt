include(modules.cmake)

set(EXTRA_SOURCES ${NONLINEARCIRCUITS_DIR}/src/NLCShared.cpp)

add_library(
  nonlinearcircuitsLibrary OBJECT
  ${NONLINEARCIRCUITS_SOURCE_PATHS}
  ${EXTRA_SOURCES}
)

target_include_directories(nonlinearcircuitsLibrary PRIVATE ${NONLINEARCIRCUITS_DIR}/src)

set_property(TARGET nonlinearcircuitsLibrary PROPERTY CXX_STANDARD 20)

target_compile_options(
    nonlinearcircuitsLibrary
  PRIVATE -fvisibility=hidden
          $<$<COMPILE_LANGUAGE:CXX>:-fvisibility-inlines-hidden>
          -Wno-double-promotion
          # # Fixes for warnings with Gamma:
          # -Wno-misleading-indentation
          # -Wno-unused-but-set-variable
          # -Wno-unused-function
          # # Fixes for warnings with DSP and main source:
          # -Wno-unused-variable
)

