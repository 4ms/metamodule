cmake_minimum_required(VERSION 3.19)

add_library(CoreModules STATIC
  hub/hub_medium.cc
  moduleFactory.cc
)

# add_subdirectory(4ms)
# target_link_libraries(CoreModules PUBLIC CoreModules-4ms)

target_link_libraries(CoreModules PRIVATE metamodule-core-interface cpputil)

target_include_directories(CoreModules
  PRIVATE
  ../
  ${FWDIR}/src
  ${FWDIR}/src/console
)
