cmake_minimum_required(VERSION 3.24)
project(VCV-Plugin)

# This library will have its symbols (API)
# made available (that is, "exported") to plugins.
# Any source files that are required for plugins 
# to work but should NOT have their API exported
# must go in the vcv_plugin/internal/ library.


add_subdirectory(interface)

set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../)

# Create library that holds the implementation of the interface defined by vcv_plugin_interface
add_library(vcv_plugin_export STATIC)

target_link_libraries(vcv_plugin_export PUBLIC vcv_plugin_interface)

target_sources(
  vcv_plugin_export
  PRIVATE 
		 src/app/CableWidget.cc
		 src/app/CircularShadow.cc
         src/app/Knob.cpp
         src/app/LedDisplay.cpp
         src/app/LightWidget.cpp
         src/app/MidiDisplay.cc
         src/app/ModuleWidget.cpp
         src/app/MultiLightWidget.cc
         src/app/ParamWidget.cc
         src/app/PortWidget.cc
         src/app/RackScrollWidget.cc
         src/app/RackWidget.cc
         src/app/RailWidget.cc
         src/app/RackWidget.cc
         src/app/Scene.cc
         src/app/SliderKnob.cc
         src/app/SvgButton.cc
         src/app/SvgKnob.cc
         src/app/SvgPanel.cpp
         src/app/SvgPort.cc
         src/app/SvgScrew.cc
         src/app/SvgSlider.cc
         src/app/SvgSwitch.cc
         src/app/Switch.cc

         src/engine/Engine.cpp
         src/engine/Module.cpp
         src/engine/ParamQuantity.cpp
         src/engine/LightInfo.cc
         src/engine/PortInfo.cc

         src/plugin/Model.cpp
         src/plugin/Plugin.cpp

		 src/ui/Button.cc
		 src/ui/ChoiceButton.cc
		 src/ui/common.cc
		 src/ui/Label.cc
		 src/ui/List.cc
         src/ui/Menu.cc
         src/ui/MenuItem.cc
         src/ui/MenuEntry.cc
         src/ui/MenuLabel.cc
         src/ui/MenuOverlay.cc
         src/ui/MenuSeparator.cc
         src/ui/OptionButton.cc
         src/ui/ProgressBar.cc
         src/ui/RadioButton.cc
         src/ui/Scrollbar.cc
         src/ui/ScrollWidget.cc
         src/ui/Slider.cc
         src/ui/TextField.cc


         src/widget/Widget.cc
         src/widget/SvgWidget.cc
         src/widget/FramebufferWidget.cc
         src/widget/event.cpp
         src/window/Svg.cpp
         src/window/Window.cpp

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
         src/midi_message.cc
         src/system.cc

		 src/blendish.c
)

add_subdirectory(jansson)
add_subdirectory(pffft)
add_subdirectory(osdialog)
add_subdirectory(libsamplerate)

target_link_libraries(vcv_plugin_export PUBLIC cpputil) 
target_link_libraries(vcv_plugin_export PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,jansson>")
target_link_libraries(vcv_plugin_export PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,pffft>")
target_link_libraries(vcv_plugin_export PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,osdialog>")
target_link_libraries(vcv_plugin_export PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,libsamplerate>")

if(NOT METAMODULE_HEADLESS)
	add_subdirectory(nanovg)
	target_include_directories(nanovg PRIVATE ${MM_ROOT}/firmware/src)
	target_link_libraries(nanovg PRIVATE metamodule::rack-interface)
	target_link_libraries(vcv_plugin_export PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,nanovg>")
endif()

target_include_directories( vcv_plugin_export PUBLIC
    src
    ${MM_ROOT}/firmware/src #for svg.cc to access gui/elements/..., and for console/pr_dbg.hh
    ${SHARED}
	${MM_ROOT}/firmware/lib
	${MM_ROOT}/firmware #for system/time.hh
)

target_compile_definitions(vcv_plugin_export PRIVATE METAMODULE)

target_compile_options(vcv_plugin_export PRIVATE -fno-function-sections -fno-data-sections -Wno-double-promotion)

set_target_properties(vcv_plugin_export PROPERTIES CXX_STANDARD 23)
# set_target_properties(vcv_plugin_export PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/vcv-export)


