cmake_minimum_required(VERSION 3.24)
project(vcv_ports)

include(${CMAKE_CURRENT_LIST_DIR}/brands.cmake)

# Create library that combines all brands
# Link against this library from outside
add_library(vcv_ports STATIC)
target_sources(vcv_ports PRIVATE ${CMAKE_CURRENT_LIST_DIR}/glue/empty.cc)

if (CMAKE_CROSSCOMPILING)
  # Enable LTO for top level library
  set_property(TARGET vcv_ports PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set_property(TARGET vcv_ports PROPERTY CXX_STANDARD 20)


# Create interface wrapper that whole-links the actual library
# add_library(vcv_ports INTERFACE)
# target_link_libraries(vcv_ports INTERFACE "$<LINK_LIBRARY:WHOLE_ARCHIVE,vcv_ports>")

foreach(brand ${brands})

  include(${CMAKE_CURRENT_LIST_DIR}/glue/${brand}/modules.cmake)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glue/${brand})

  target_compile_options(${brand}Library PRIVATE -Wno-attributes $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>)
  target_sources(${brand}Library PRIVATE ${CMAKE_CURRENT_LIST_DIR}/glue/empty.cc)

  # Link against the interface to vcv_plugin because it's linked to the main.elf with WHOLE_ARCHIVE
  target_link_libraries(${brand}Library PRIVATE vcv_plugin_interface)

  target_link_libraries(${brand}Library PRIVATE cpputil)

  if (CMAKE_CROSSCOMPILING)
    # Enable LTO for all brands
    set_property(TARGET ${brand}Library PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()

  target_link_libraries(vcv_ports PUBLIC ${brand}Library)

endforeach()

