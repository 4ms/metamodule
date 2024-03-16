set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../)

add_library(VCV_adaptor STATIC)

target_sources(
  VCV_adaptor
  PRIVATE src/string.cpp
         src/plugin_instance.cc
         src/engine/Module.cpp
         ../dynload/keep-symbols.cc
         src/plugin/Plugin.cpp
		 src/VCV_module_wrapper.cc
         src/plugin/Model.cpp
         src/widget/Widget.cc
         src/app/ModuleWidget.cpp
         src/app/Widget.cc
         src/history.cpp
         src/svg.cc
)

# TODO: replace this with for example fetchContent later
# if (NOT TARGET jansson)
add_subdirectory(jansson)
# endif()
add_subdirectory(pffft)

# propagate these libraries (e.g. to vcv_ports/Befaco, etc)
target_link_libraries(VCV_adaptor PUBLIC pffft jansson cpputil)

target_link_libraries(VCV_adaptor PRIVATE lvgl::lvgl)

target_include_directories(
  VCV_adaptor
  PUBLIC include
         include/VCV_adaptor
         ${MM_ROOT}/firmware/src
         ${MM_ROOT}/firmware/src/console
         ${MM_ROOT}/firmware
         ${MM_ROOT}/shared
)

set_property(TARGET VCV_adaptor PROPERTY CXX_STANDARD 20)
