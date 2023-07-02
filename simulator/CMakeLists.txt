cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mm_sim LANGUAGES C CXX)

set(MM_ROOT ${PROJECT_SOURCE_DIR}/..)
set(SIM_ROOT ${PROJECT_SOURCE_DIR})
set(LVGL_DIR ${MM_ROOT}/firmware/lib/lvgl/lvgl)

set(LV_CONF_PATH
    ${SIM_ROOT}/lv_conf.h
    CACHE STRING "" FORCE)

get_filename_component(LV_CONF_DIR ${LV_CONF_PATH} DIRECTORY)

# #################### LVGL Simulator Driver #################################

add_subdirectory(lvgl_drv)

# #################### LVGL ############################################

include(${LVGL_DIR}/CMakeLists.txt)

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
  ${MM_ROOT}/firmware/src/pages/slsexport/patchsel/*.c
  ${MM_ROOT}/firmware/src/pages/slsexport/patchsel/ui.c
  ${MM_ROOT}/firmware/src/pages/slsexport/patchsel/ui_helpers.c
  ${MM_ROOT}/firmware/src/pages/slsexport/patchview/screens/*.c
  ${MM_ROOT}/firmware/src/pages/slsexport/patchview/ui.c
  ${MM_ROOT}/firmware/src/pages/slsexport/patchview/components/*.c
  ${MM_ROOT}/firmware/src/pages/slsexport/patchview/images/*.c
  ${MM_ROOT}/firmware/src/pages/slsexport/patchview/fonts/*.c)

# #################### CoreModules ##################################
file(
  GLOB
  CORE_MODULES
  ${MM_ROOT}/shared/CoreModules/modules/*Core.cc
  ${MM_ROOT}/shared/CoreModules/Befaco/*Core.cc
  ${MM_ROOT}/shared/CoreModules/AudibleInstruments/*Core.cc
  ${MM_ROOT}/shared/CoreModules/modules/enosc/dynamic_data.cc
  ${MM_ROOT}/shared/CoreModules/modules/enosc/data.cc
  ${MM_ROOT}/shared/cpputil/util/math_tables.cc
  ${MM_ROOT}/shared/axoloti-wrapper/axoloti_math.cpp
  ${MM_ROOT}/shared/CoreModules/AudibleInstruments/stmlib/utils/random.cc
  ${MM_ROOT}/shared/CoreModules/AudibleInstruments/stmlib/dsp/atan.cc
  ${MM_ROOT}/shared/CoreModules/AudibleInstruments/stmlib/dsp/units.cc
  ${MM_ROOT}/shared/CoreModules/AudibleInstruments/braids/analog_oscillator.cc
  ${MM_ROOT}/shared/CoreModules/AudibleInstruments/braids/digital_oscillator.cc
  ${MM_ROOT}/shared/CoreModules/AudibleInstruments/braids/macro_oscillator.cc
  ${MM_ROOT}/shared/CoreModules/AudibleInstruments/braids/resources.cc)

# #################### RYML + Patch Convert ##################################

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

add_executable(simulator src/main.cc ${CORE_MODULES} ${GUI_IMAGES}
                         ${MM_ROOT}/firmware/src/pages/page_manager.cc)

target_include_directories(
  simulator
  PRIVATE src
          stubs
          lvgl_drv
          ${SDL2_INCLUDE_DIRS}
          ${MM_ROOT}/firmware/src
          ${MM_ROOT}/firmware/src/medium
          ${MM_ROOT}/shared
          ${MM_ROOT}/shared/cpputil
          ${MM_ROOT}/shared/patch
          ${MM_ROOT}/shared/CoreModules
          ${MM_ROOT}/shared/CoreModules/info
          ${MM_ROOT}/shared/CoreModules/modules
          ${MM_ROOT}/vcv/src # For sys/alloc_buffer.h
          ${MM_ROOT}/shared/CoreModules/AudibleInstruments)

target_compile_options(simulator PRIVATE -Wall -Og -g2)
target_compile_options(simulator PRIVATE $<$<COMPILE_LANGUAGE:CXX>: -std=c++20>
                                         ${SDL2_CFLAGS_OTHER})

target_compile_definitions(simulator PRIVATE SIMULATOR TEST)
# Define TEST so braids dsp/dsp.h works (avoids contains raw assembly)

target_link_libraries(simulator PRIVATE ${SDL2_LIBRARIES} lvglsdl lvgl::lvgl
                                        ryml SDL2)

target_link_options(simulator PUBLIC LINKER:-map,simulator.map)
