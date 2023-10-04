include(modules.cmake)

add_library(
  4msLibrary OBJECT
  ${4MS_SOURCE_PATHS}
  ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/data.cc
  ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/dynamic_data.cc
  ${MM_ROOT}/shared/axoloti-wrapper/axoloti_math.cpp
  ${MM_ROOT}/shared/cpputil/util/math_tables.cc
)

target_include_directories(
  4msLibrary
  PUBLIC ${MM_ROOT}/shared
         ${MM_ROOT}/shared/CoreModules/4ms
         ${MM_ROOT}/shared/cpputil
         ${MM_ROOT}/firmware/src
         ${MM_ROOT}/firmware/src/medium
)

set_property(TARGET 4msLibrary PROPERTY CXX_STANDARD 20)
