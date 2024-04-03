cmake_minimum_required(VERSION 3.24)
project(vcv_ports)

include(${CMAKE_CURRENT_LIST_DIR}/brands.cmake)

# Create library that combines all brands
# Link against this library from outside
add_library(_vcv_ports_internal STATIC)
target_sources(_vcv_ports_internal PRIVATE ${CMAKE_CURRENT_LIST_DIR}/glue/empty.cc)

if (CMAKE_CROSSCOMPILING)
  # Enable LTO for top level library
  set_property(TARGET _vcv_ports_internal PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
endif()

set_property(TARGET _vcv_ports_internal PROPERTY CXX_STANDARD 20)


# Create interface wrapper that whole-links the actual library
add_library(vcv_ports INTERFACE)
target_link_libraries(vcv_ports INTERFACE "$<LINK_LIBRARY:WHOLE_ARCHIVE,_vcv_ports_internal>")

foreach(brand ${brands})

  include(${CMAKE_CURRENT_LIST_DIR}/glue/${brand}/modules.cmake)
  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glue/${brand})

  target_compile_options(${brand}Library PRIVATE -Wno-attributes $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>)
  target_sources(${brand}Library PRIVATE ${CMAKE_CURRENT_LIST_DIR}/glue/empty.cc)
  target_compile_definitions(${brand}Library PRIVATE METAMODULE_INTERNAL_PLUGIN=1)
  target_link_libraries(${brand}Library PUBLIC VCV_mm_adaptor)

  if (CMAKE_CROSSCOMPILING)
    # Enable LTO for all brands
    set_property(TARGET ${brand}Library PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
  endif()

  target_link_libraries(_vcv_ports_internal PUBLIC ${brand}Library)

endforeach()

