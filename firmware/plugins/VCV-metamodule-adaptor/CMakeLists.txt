set(MM_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../../)

add_library(VCV_mm_adaptor STATIC)

target_sources(
  VCV_mm_adaptor
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

target_link_libraries(VCV_mm_adaptor PUBLIC cpputil) 
target_link_libraries(VCV_mm_adaptor PRIVATE lvgl::lvgl)
target_link_libraries(VCV_mm_adaptor PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,jansson>")
target_link_libraries(VCV_mm_adaptor PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,pffft>")

target_include_directories(
  VCV_mm_adaptor
  PUBLIC include
         src
         dep/include
         ${MM_ROOT}/firmware/src #for svg.cc: gui/elements/..., and for console/pr_dbg.hh
         ${MM_ROOT}/shared
)

set_property(TARGET VCV_mm_adaptor PROPERTY CXX_STANDARD 20)
target_compile_options(VCV_mm_adaptor PRIVATE -fno-function-sections -fno-data-sections)

add_library(VCV_mm_adaptor_interface INTERFACE)
set_property(TARGET VCV_mm_adaptor_interface PROPERTY CXX_STANDARD 20)
target_include_directories(
  VCV_mm_adaptor_interface
  INTERFACE include
         src
         dep/include
         ${MM_ROOT}/firmware/src #for svg.cc: gui/elements/..., and for console/pr_dbg.hh
         ${MM_ROOT}/shared
)
