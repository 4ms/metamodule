set(MM_ROOT ${PROJECT_SOURCE_DIR}/..)

file(GLOB RACKARTWORK_SOURCES ${MM_ROOT}/firmware/src/gui/images/Rack/components/*.c)

add_library(
  VCV_adaptor OBJECT
  plugin_instance.cc
  pffft/pffft.c
  engine/ParamQuantity.cpp
  ${RACKARTWORK_SOURCES}
)

target_link_libraries(VCV_adaptor PUBLIC lvgl::lvgl)

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
