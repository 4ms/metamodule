cmake_minimum_required(VERSION 3.24)

add_library(CoreModules STATIC
  ${SHARED}/CoreModules/hub/hub_medium.cc
  ${SHARED}/CoreModules/moduleFactory.cc
  ${SHARED}/CoreModules/modules_helpers.cc
)

target_link_libraries(CoreModules PRIVATE metamodule-core-interface cpputil)

target_include_directories(CoreModules
  PRIVATE
  ${SHARED}
  ${FWDIR}/src
  ${FWDIR}/src/console
)
