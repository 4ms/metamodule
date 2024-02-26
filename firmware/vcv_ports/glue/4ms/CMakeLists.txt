include(modules.cmake)

add_library(
  4msLibrary OBJECT
  ${4MS_SOURCE_PATHS}
  ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/data.cc
  ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/dynamic_data.cc
  ${MM_ROOT}/shared/CoreModules/4ms/core/axoloti-wrapper/axoloti_math.cpp
)

target_include_directories(
  4msLibrary
  PUBLIC ${MM_ROOT}/shared
         ${MM_ROOT}/shared/CoreModules/4ms
)

set_property(TARGET 4msLibrary PROPERTY CXX_STANDARD 20)

target_link_libraries(4msLibrary PRIVATE cpputil)
