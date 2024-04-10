
add_library(vcv_plugin STATIC)

target_sources(
  vcv_plugin
  PRIVATE 
         src/app/ModuleWidget.cpp
         src/app/ParamWidget.cc
         src/app/SvgKnob.cc
         src/app/SvgPort.cc
         src/app/SvgSlider.cc
         src/app/SvgSwitch.cc
         src/engine/Module.cpp
         src/engine/ParamQuantity.cpp
         src/plugin/Model.cpp
         src/plugin/Plugin.cpp
         src/widget/Widget.cc
         src/widget/SvgWidget.cc
         src/widget/FramebufferWidget.cc

         src/Quantity.cpp
         src/VCV_module_wrapper.cc
         src/asset.cc
         src/context.cpp
         src/history.cpp
         src/keep-symbols.cc
         src/make_element.cc
         src/plugin_instance.cc
         src/settings.cpp
         src/string.cpp
         src/svg.cc
)

add_subdirectory(jansson)
add_subdirectory(pffft)

include(metamodule-rack-interface/interface.cmake)

target_link_libraries(vcv_plugin PUBLIC metamodule-rack-interface)
target_link_libraries(vcv_plugin PUBLIC cpputil) 
target_link_libraries(vcv_plugin PRIVATE lvgl::lvgl)
target_link_libraries(vcv_plugin PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,jansson>")
target_link_libraries(vcv_plugin PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,pffft>")

set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../)
target_include_directories(
  vcv_plugin
  PUBLIC src
         ${MM_ROOT}/firmware/src #for svg.cc: gui/elements/..., and for console/pr_dbg.hh
         ${MM_ROOT}/shared
)

set_property(TARGET vcv_plugin PROPERTY CXX_STANDARD 20)
target_compile_options(vcv_plugin PRIVATE -fno-function-sections -fno-data-sections)


# Create interface library for use by vcv_ports (built-in vcv modules)
add_library(vcv_ports_interface INTERFACE)
target_include_directories(vcv_ports_interface INTERFACE ${MM_ROOT}/shared)
target_link_libraries(vcv_ports_interface INTERFACE metamodule-rack-interface)
