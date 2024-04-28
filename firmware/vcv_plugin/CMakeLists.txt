cmake_minimum_required(VERSION 3.24)
project(VCV-Plugin)

#################################

add_subdirectory(interface)

# TODO: This needs to be removed eventually
set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../)

#################################

# Create library that holds the implementation of the interface defined by vcv_plugin_interface
add_library(vcv_plugin STATIC)

target_link_libraries(vcv_plugin PUBLIC vcv_plugin_interface)

target_sources(
  vcv_plugin
  PRIVATE 
         src/app/ModuleWidget.cpp
         src/app/ParamWidget.cc
         src/app/SvgKnob.cc
         src/app/SvgPort.cc
         src/app/SvgSlider.cc
         src/app/SvgSwitch.cc
         src/engine/Engine.cpp
         src/engine/Module.cpp
         src/engine/ParamQuantity.cpp
         src/plugin/Model.cpp
         src/plugin/Plugin.cpp
         src/widget/Widget.cc
         src/widget/SvgWidget.cc
         src/widget/FramebufferWidget.cc
         src/window/Svg.cpp

         src/Quantity.cpp
         src/VCV_module_wrapper.cc
         src/asset.cc
         src/context.cpp
         src/glfw3.c
         src/history.cpp
         src/logger.cpp
         src/make_element.cc
         src/settings.cpp
         src/string.cpp
         src/svg.cc
         src/roundevenf.c
)

add_subdirectory(jansson)
add_subdirectory(pffft)

target_link_libraries(vcv_plugin PUBLIC cpputil) 
target_link_libraries(vcv_plugin PRIVATE lvgl::lvgl)
target_link_libraries(vcv_plugin PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,jansson>")
target_link_libraries(vcv_plugin PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,pffft>")
target_link_libraries(vcv_plugin INTERFACE metamodule::rack-interface)

target_include_directories(
  vcv_plugin
  PUBLIC src
         ${MM_ROOT}/firmware/src #for svg.cc: gui/elements/..., and for console/pr_dbg.hh
)

set_property(TARGET vcv_plugin PROPERTY CXX_STANDARD 20)
target_compile_options(vcv_plugin PRIVATE -fno-function-sections -fno-data-sections)

set_source_files_properties(
  src/svg.cc
  PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;"
)


