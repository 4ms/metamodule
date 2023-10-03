set(MM_ROOT ${PROJECT_SOURCE_DIR}/..)

add_library(VCV_adaptor STATIC)

# These sources are used by other libraries indirectly linked to VCV_adaptor, so they need to be public
target_sources(
  VCV_adaptor
  PUBLIC string.cpp
         plugin_instance.cc
         pffft/pffft.c
         engine/Module.cpp
)

add_subdirectory(${MM_ROOT}/firmware/lib/jansson ${CMAKE_CURRENT_BINARY_DIR}/jansson)

target_link_libraries(VCV_adaptor PUBLIC lvgl::lvgl jansson)

target_include_directories(
  VCV_adaptor
  PUBLIC ${MM_ROOT}/firmware/src/VCV_adaptor
         ${MM_ROOT}/firmware/src/VCV_adaptor/pffft
         ${MM_ROOT}/firmware/src
         ${MM_ROOT}/firmware
         ${MM_ROOT}/shared
         ${MM_ROOT}/shared/cpputil
)

# Fixup for pffft compiler warnings
set_source_files_properties(pffft/pffft.c PROPERTIES COMPILE_OPTIONS "-Wno-double-promotion;-Wno-pointer-to-int-cast")

set_property(TARGET VCV_adaptor PROPERTY CXX_STANDARD 20)
