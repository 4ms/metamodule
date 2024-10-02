cmake_minimum_required(VERSION 3.24)
project(VCV-Plugin)

#################################

add_subdirectory(interface)

# TODO: This needs to be removed eventually
set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../)

#################################

# Create library that holds the implementation of the interface defined by vcv_plugin_interface
add_library(vcv_plugin_export STATIC)

target_link_libraries(vcv_plugin_export PUBLIC vcv_plugin_interface)

target_sources(
  vcv_plugin_export
  PRIVATE 
         src/app/Knob.cpp
         src/app/ModuleWidget.cpp
         src/app/ParamWidget.cc
         src/app/SvgKnob.cc
         src/app/SvgPanel.cpp
         src/app/SvgPort.cc
         src/app/SvgSlider.cc
         src/app/SvgSwitch.cc
         src/app/SvgButton.cc
         src/app/SvgScrew.cc
         src/engine/Engine.cpp
         src/engine/Module.cpp
         src/engine/ParamQuantity.cpp
         src/plugin/Model.cpp
         src/plugin/Plugin.cpp
         src/widget/Widget.cc
         src/widget/SvgWidget.cc
         src/widget/FramebufferWidget.cc
         src/widget/event.cpp
         src/window/Svg.cpp

         src/Quantity.cpp
         src/VCV_module_wrapper.cc
         src/asset.cc
         src/context.cpp
         src/glfw3.c
         src/history.cpp
         src/logger.cpp
         src/midi.cpp
         src/midi_input_queue.cpp
         src/settings.cpp
         src/string.cpp
         src/roundevenf.c
         src/color.cpp
         src/common.cpp
         src/resampler.cc
)

add_subdirectory(jansson)
add_subdirectory(pffft)

target_link_libraries(vcv_plugin_export PUBLIC cpputil) 
target_link_libraries(vcv_plugin_export PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,jansson>")
target_link_libraries(vcv_plugin_export PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,pffft>")
target_link_libraries(vcv_plugin_export INTERFACE metamodule::rack-interface)

target_include_directories( vcv_plugin_export PUBLIC
    src
    ${MM_ROOT}/firmware/src #for svg.cc to access gui/elements/..., and for console/pr_dbg.hh
    ${SHARED}
	${MM_ROOT}/firmware/lib
)

target_compile_definitions(vcv_plugin_export PRIVATE METAMODULE)

target_compile_options(vcv_plugin_export PRIVATE -fno-function-sections -fno-data-sections -Wno-double-promotion)

set_target_properties(vcv_plugin_export PROPERTIES CXX_STANDARD 23)
# set_target_properties(vcv_plugin_export PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vcv-export)


