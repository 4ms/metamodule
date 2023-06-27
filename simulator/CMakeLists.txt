cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mm_sim LANGUAGES C CXX)

set(MM_ROOT ${PROJECT_SOURCE_DIR}/..)
set(SIM_ROOT ${PROJECT_SOURCE_DIR})
set(LVGL_DIR ${MM_ROOT}/firmware/lib/lvgl)

# #################### LVGL Simulator Driver #################################

add_subdirectory(lvgl_drv)

# #################### Gui Assets ############################################
file(
  GLOB
  GUI_IMAGES
  ${MM_ROOT}/firmware/src/pages/images/modules/*.c
  ${MM_ROOT}/firmware/src/pages/images/components/*.c
  ${MM_ROOT}/firmware/src/pages/images/ui/*.c
  ${MM_ROOT}/firmware/src/pages/images/Befaco/*.c
  ${MM_ROOT}/firmware/src/pages/images/Befaco/components/*.c
  ${MM_ROOT}/firmware/src/pages/images/AudibleInstruments/*.c
  ${MM_ROOT}/firmware/src/pages/images/AudibleInstruments/components/*.c
  ${MM_ROOT}/firmware/src/pages/fonts/MuseoSansRounded_*.c
  ${MM_ROOT}/firmware/src/pages/slsexport/ui_font_*.c)

add_library(gui_assets ${GUI_IMAGES})

target_compile_options(gui_assets PRIVATE -Wall -O2)
target_include_directories(gui_assets PRIVATE ${LVGL_DIR} ${LVGL_DIR}/lvgl)

# #################### CoreModules ##################################
file(
  GLOB
  CORE_MODULES
  ${MM_ROOT}/shared/CoreModules/modules/*Core.cc
  ${MM_ROOT}/shared/CoreModules/Befaco/*Core.cc
  ${MM_ROOT}/shared/CoreModules/AudibleInstruments/*Core.cc
  ${MM_ROOT}/shared/CoreModules/modules/enosc/dynamic_data.cc
  ${MM_ROOT}/shared/CoreModules/modules/enosc/data.cc)

add_library(core_modules ${CORE_MODULES})

target_compile_options(core_modules PRIVATE $<$<COMPILE_LANGUAGE:CXX>:
                                            -std=c++20> -Wall -O2)
target_include_directories(
  core_modules
  PRIVATE ${MM_ROOT}/shared/
          ${MM_ROOT}/shared/CoreModules
          ${MM_ROOT}/shared/CoreModules/info
          ${MM_ROOT}/firmware/src
          ${MM_ROOT}/shared/cpputil
          ${MM_ROOT}/vcv/src # For sys/alloc_buffer.h
          ${MM_ROOT}/shared/CoreModules/AudibleInstruments)

# #################### RYML + Patch Convert ##################################

target_compile_options(gui_assets PRIVATE -Wall -O2)
target_include_directories(gui_assets PRIVATE ${LVGL_DIR} ${LVGL_DIR}/lvgl)

file(GLOB RYML_SOURCES
     ${MM_ROOT}/shared/patch_convert/ryml/rapidyaml/src/c4/yml/*.cpp
     ${MM_ROOT}/shared/patch_convert/ryml/rapidyaml/ext/c4core/src/c4/*.cpp)

add_library(
  ryml ${MM_ROOT}/shared/patch_convert/ryml/ryml_serial.cc
       ${MM_ROOT}/shared/patch_convert/yaml_to_patch.cc ${RYML_SOURCES})

target_include_directories(
  ryml
  PRIVATE ${MM_ROOT}/shared/patch_convert
          ${MM_ROOT}/shared/patch_convert/ryml
          ${MM_ROOT}/shared/patch_convert/ryml/rapidyaml/src
          ${MM_ROOT}/shared/patch_convert/ryml/rapidyaml/ext/c4core/src
          ${MM_ROOT}/shared/cpputil
          ${MM_ROOT}/shared)

target_compile_options(ryml PRIVATE $<$<COMPILE_LANGUAGE:CXX>: -std=c++20>)

# #################### Application ############################################

add_executable(
  simulator
  src/main.cc ${MM_ROOT}/firmware/src/pages/slsexport/ui.c
  ${MM_ROOT}/firmware/src/pages/slsexport/ui_helpers.c
  ${MM_ROOT}/firmware/src/pages/page_manager.cc)

target_include_directories(
  simulator
  PRIVATE src
          stubs
          lvgl_drv
          ${LVGL_DIR}
          ${LVGL_DIR}/lvgl
          ${SDL2_INCLUDE_DIRS}
          ${MM_ROOT}/firmware/src
          ${MM_ROOT}/firmware/src/medium
          ${MM_ROOT}/shared
          ${MM_ROOT}/shared/cpputil
          ${MM_ROOT}/shared/patch)

target_compile_options(simulator PRIVATE -Wall -O0 -Og -g2)
target_compile_options(simulator PRIVATE $<$<COMPILE_LANGUAGE:CXX>: -std=c++20>
                                         ${SDL2_CFLAGS_OTHER})

target_compile_definitions(simulator PRIVATE SIMULATOR)
target_link_libraries(
  simulator
  PRIVATE ${SDL2_LIBRARIES}
          lvglsdl
          lvgl::lvgl
          gui_assets
          core_modules
          ryml
          SDL2)

target_link_options(simulator PUBLIC LINKER:-map,simulator.map)

include(${LVGL_DIR}/lvgl/CMakeLists.txt)
