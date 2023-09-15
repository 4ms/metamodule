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

file(GLOB GUI_IMAGES ${MM_ROOT}/firmware/src/gui/images/4ms/modules/*.c
     ${MM_ROOT}/firmware/src/gui/images/4ms/components/*.c)

# #################### SLS Export ##################################

file(STRINGS ${MM_ROOT}/firmware/src/gui/slsexport/meta5/filelist.txt
     SLS_SOURCES)
list(TRANSFORM SLS_SOURCES
     PREPEND "${MM_ROOT}/firmware/src/gui/slsexport/meta5/")

# Fixup for compiler warning in LVGL 8.3.4:
set_source_files_properties(${MM_ROOT}/firmware/src/gui/slsexport/meta5/ui.c
                            PROPERTIES COMPILE_FLAGS -Wno-unused-variable)

# #################### CoreModules ##################################

file(GLOB CORE_MODULES ${MM_ROOT}/shared/CoreModules/4ms/core/*Core.cc)

set(CORE_MODULES
    ${CORE_MODULES}
    ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/dynamic_data.cc
    ${MM_ROOT}/shared/CoreModules/4ms/core/enosc/data.cc
    #
    # support files
    ${MM_ROOT}/shared/axoloti-wrapper/axoloti_math.cpp
    ${MM_ROOT}/shared/cpputil/util/math_tables.cc)

# #################### VCV Adaptor ##################################

add_subdirectory(${MM_ROOT}/firmware/src/VCV_adaptor
                 ${CMAKE_CURRENT_BINARY_DIR}/VCV_adaptor)

# #################### Other brands ##################################

include(${MM_ROOT}/firmware/vcv_ports/brands.cmake)
# following is only for custom modules (not 4ms or Rack)
list(REMOVE_ITEM brands 4ms Rack)

foreach(brand ${brands})

  add_subdirectory(${MM_ROOT}/firmware/vcv_ports/glue/${brand}
                   ${CMAKE_CURRENT_BINARY_DIR}/${brand})
  target_link_libraries(${brand}Library PUBLIC VCV_adaptor)

  file(GLOB BRAND_GUI_IMAGES
       ${MM_ROOT}/firmware/src/gui/images/${brand}/components/*.c
       ${MM_ROOT}/firmware/src/gui/images/${brand}/modules/*.c)
  list(APPEND GUI_IMAGES ${BRAND_GUI_IMAGES})
endforeach()

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
          ${MM_ROOT}/simulator/stubs
          ${MM_ROOT}/shared)

target_compile_options(ryml PRIVATE $<$<COMPILE_LANGUAGE:CXX>: -std=c++20>)

# #################### Application ############################################

add_executable(simulator src/main.cc src/ui.cc ${CORE_MODULES} ${GUI_IMAGES}
                         ${SLS_SOURCES})

target_include_directories(
  simulator
  PRIVATE src
          stubs
          lvgl_drv
          sdl_audio
          ${SDL2_INCLUDE_DIRS}
          ${MM_ROOT}
          ${MM_ROOT}/firmware
          ${MM_ROOT}/firmware/src
          ${MM_ROOT}/firmware/src/console
          ${MM_ROOT}/firmware/src/params
          ${MM_ROOT}/firmware/src/medium
          ${MM_ROOT}/shared
          ${MM_ROOT}/shared/cpputil
          ${MM_ROOT}/shared/patch
          ${MM_ROOT}/shared/CoreModules
          ${MM_ROOT}/shared/CoreModules/4ms)

target_compile_options(simulator PRIVATE -Wall -Og -g2 ${SDL2_CFLAGS_OTHER})

target_link_libraries(simulator PRIVATE ${SDL2_LIBRARIES} lvglsdl lvgl::lvgl
                                        ryml SDL2 VCV_adaptor)

foreach(brand ${brands})
  target_link_libraries(simulator PRIVATE ${brand}Library)
endforeach()

set_property(TARGET simulator PROPERTY CXX_STANDARD 20)

message("CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_options(simulator PUBLIC "-Wl,-map,simulator.map")
  else()
    target_link_options(simulator PUBLIC LINKER:-Map,simulator.map)
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_options(simulator PUBLIC LINKER:-Map,simulator.map)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_link_options(simulator PRIVATE "/MAP:simulator.map")
endif()
