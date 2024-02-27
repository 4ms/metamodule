set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../)

add_library(VCV_adaptor STATIC)

# These sources are used by other libraries indirectly linked to VCV_adaptor, so they need to be public
target_sources(
  VCV_adaptor
  PRIVATE string.cpp
         plugin_instance.cc
         engine/Module.cpp
)

# TODO: replace this with for example fetchContent later
if (NOT TARGET jansson)
  add_subdirectory(${MM_ROOT}/firmware/lib/jansson ${CMAKE_CURRENT_BINARY_DIR}/jansson)
endif()
add_subdirectory(pffft)

# TODO: is this really meant to be propagated
target_link_libraries(VCV_adaptor PUBLIC pffft jansson cpputil)

target_link_libraries(VCV_adaptor PRIVATE lvgl::lvgl jansson)

target_include_directories(
  VCV_adaptor
  PUBLIC ${MM_ROOT}/firmware/src/VCV_adaptor
         ${MM_ROOT}/firmware/src
         ${MM_ROOT}/firmware/src/console
         ${MM_ROOT}/firmware
         ${MM_ROOT}/shared
)

set_property(TARGET VCV_adaptor PROPERTY CXX_STANDARD 20)
