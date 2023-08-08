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
  ${MM_ROOT}/firmware/src/gui/images/4ms/modules/*.c
  ${MM_ROOT}/firmware/src/gui/images/4ms/components/*.c
  ${MM_ROOT}/firmware/src/gui/images/Befaco/modules/*.c
  ${MM_ROOT}/firmware/src/gui/images/Befaco/components/*.c
  ${MM_ROOT}/firmware/src/gui/images/AudibleInstruments/modules/*.c
  ${MM_ROOT}/firmware/src/gui/images/AudibleInstruments/components/*.c
  ${MM_ROOT}/firmware/src/gui/images/Rack/components/*.c
  ${MM_ROOT}/firmware/src/gui/fonts/MuseoSansRounded_*.c)

# #################### SLS Export ##################################

file(STRINGS ${MM_ROOT}/firmware/src/gui/slsexport/meta5/filelist.txt
     SLS_SOURCES)
list(TRANSFORM SLS_SOURCES
     PREPEND "${MM_ROOT}/firmware/src/gui/slsexport/meta5/")

# FIXME: SLS symbols not found when linking library to the executable:
# add_subdirectory(${MM_ROOT}/firmware/src/gui/slsexport/meta5
# ${CMAKE_CURRENT_BINARY_DIR}/meta5)

# target_include_directories(ui PRIVATE ./ ${LVGL_DIR})
# target_compile_options(ui PRIVATE -Wall -Og -g2 $<$<COMPILE_LANGUAGE:CXX>:
# -std=c++20>)

# #################### CoreModules ##################################
file(GLOB CORE_MODULES ${MM_ROOT}/shared/CoreModules/4ms/core/*Core.cc)

set(CORE_MODULES
    ${CORE_MODULES}
    ${MM_ROOT}/firmware/src/VCV_adaptor/plugin_instance.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/dynamic_data.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/data.cc
    #
    # Befaco
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/StereoStrip.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/SlewLimiter.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/SamplingModulator.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/STMix.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/Rampage.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/PonyVCO.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/Percall.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/MotionMTR.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/Morphader.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/Mixer.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/KickAll.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/HexMixVCA.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/ChoppingKinky.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/ABC.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/ADSR.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/SpringReverb.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/DualAtenuverter.cpp
    ${MM_ROOT}/firmware/vcv_ports/Befaco/src/EvenVCO.cpp
    # ${MM_ROOT}/firmware/vcv-ports/Befaco/src/NoisePlethora.cpp
    # ${MM_ROOT}/firmware/vcv-ports/Befaco/src/Muxslicer.cpp
    #
    # AudibleInstruments
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/src/Braids.cpp
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/stmlib/utils/random.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/stmlib/dsp/atan.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/stmlib/dsp/units.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/braids/analog_oscillator.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/braids/digital_oscillator.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/braids/macro_oscillator.cc
    ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack/braids/resources.cc
    #
    # support files
    ${MM_ROOT}/firmware/src/VCV_adaptor/pffft/pffft.c
    ${MM_ROOT}/shared/axoloti-wrapper/axoloti_math.cpp
    ${MM_ROOT}/shared/cpputil/util/math_tables.cc)

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

add_executable(
  simulator src/main.cc ${CORE_MODULES} ${GUI_IMAGES} ${SLS_SOURCES}
            ${MM_ROOT}/firmware/src/gui/pages/page_manager.cc)

target_include_directories(
  simulator
  PRIVATE src
          stubs
          lvgl_drv
          ${SDL2_INCLUDE_DIRS}
          ${MM_ROOT}/firmware
          ${MM_ROOT}/firmware/src
          ${MM_ROOT}/firmware/src/console
          ${MM_ROOT}/firmware/src/params
          ${MM_ROOT}/firmware/src/medium
          ${MM_ROOT}/shared
          ${MM_ROOT}/shared/cpputil
          ${MM_ROOT}/shared/patch
          ${MM_ROOT}/shared/CoreModules
          ${MM_ROOT}/shared/CoreModules/4ms
          ${MM_ROOT}/shared/CoreModules/Befaco
          ${MM_ROOT}/firmware/vcv_ports/AudibleInstruments/eurorack
          ${MM_ROOT}/firmware/src/VCV_adaptor
          ${MM_ROOT}/firmware/src/VCV_adaptor/pffft)

target_compile_options(
  simulator PRIVATE -Wall -Og -g2 $<$<COMPILE_LANGUAGE:CXX>: -std=c++20>
                    ${SDL2_CFLAGS_OTHER})
target_compile_options(simulator PRIVATE -Wno-missing-braces)

target_compile_definitions(simulator PRIVATE SIMULATOR TEST)
# Define TEST so braids dsp/dsp.h works (since it contains raw Cortex-M4
# assembly)

target_link_libraries(simulator PRIVATE ${SDL2_LIBRARIES} lvglsdl lvgl::lvgl
                                        ryml SDL2)

target_link_options(simulator PUBLIC LINKER:-map,simulator.map)
