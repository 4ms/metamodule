cmake_minimum_required(VERSION 3.19)

add_library(CoreModules STATIC
  hub/hub_medium.cc
  moduleFactory.cc
)

target_link_libraries(CoreModules PRIVATE metamodule-core-interface cpputil)

target_include_directories(CoreModules
  PUBLIC
  ../ #so libs that link to this can do #include "CoreModules/moduleFactory.hh"
  ${FWDIR}/src
  ${FWDIR}/src/console
)
