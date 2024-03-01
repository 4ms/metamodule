set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../)

# TODO: replace this with for example fetchContent later
if (NOT TARGET jansson)
  add_subdirectory(${MM_ROOT}/shared/jansson jansson)
endif()
if (NOT TARGET pffft)
  add_subdirectory(${MM_ROOT}/shared/pffft pffft)
endif()
if (NOT TARGET cpputil)
  add_subdirectory(${MM_ROOT}/shared/cpputil cpputil)
endif()
if (NOT TARGET modules)
  add_subdirectory(${MM_ROOT}/shared/modules modules)
endif()
if (NOT TARGET gcem)
  add_subdirectory(${MM_ROOT}/shared/gcem gcem)
endif()


add_library(VCV_adaptor STATIC)

set_property(TARGET VCV_adaptor PROPERTY CXX_STANDARD 20)

target_include_directories(
  VCV_adaptor
  PUBLIC .
         ${MM_ROOT}/firmware/src
         ${MM_ROOT}/firmware/src/console
)

target_sources(
  VCV_adaptor
  PRIVATE string.cpp
         plugin_instance.cc
         engine/Module.cpp
)


# TODO: is this really meant to be propagated
target_link_libraries(VCV_adaptor PUBLIC pffft jansson cpputil modules gcem)

target_link_libraries(VCV_adaptor PRIVATE lvgl::lvgl jansson)

