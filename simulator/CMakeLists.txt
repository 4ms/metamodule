cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mm_sim LANGUAGES C CXX)

set(FWDIR ${CMAKE_CURRENT_LIST_DIR}/../firmware)
set(SHARED ${CMAKE_CURRENT_LIST_DIR}/../shared)
set(LVGL_DIR ${FWDIR}/lib/lvgl/lvgl)

set(LV_CONF_PATH
    ${CMAKE_CURRENT_LIST_DIR}/lv_conf.h
    CACHE STRING "" FORCE)

add_compile_options(-g2)

# #################### cpputil #########################################

add_subdirectory(../shared/cpputil cpputil)

# #################### LVGL Simulator Driver #################################

add_subdirectory(lvgl_drv)

# #################### LVGL ############################################

get_filename_component(LV_CONF_DIR ${LV_CONF_PATH} DIRECTORY)
include(${LVGL_DIR}/CMakeLists.txt)

# #################### RYML ##################################

add_subdirectory(${SHARED}/patch_convert/ryml/rapidyaml ${CMAKE_CURRENT_BINARY_DIR}/rapidyaml)

# #################### SLS Export ##################################

add_subdirectory(${FWDIR}/src/gui/slsexport/meta5 ${CMAKE_CURRENT_BINARY_DIR}/ui)
target_link_libraries(ui PRIVATE lvgl)

# #################### VCV Adaptor ##################################

add_subdirectory(${FWDIR}/src/VCV_adaptor
                 ${CMAKE_CURRENT_BINARY_DIR}/VCV_adaptor)

# #################### Other brands ##################################
 
# Only build a limited set of modules, defined in an external file  
include(${FWDIR}/vcv_ports/glue/filter.cmake)  
unset(USE_LIMITED_MODULES)  
if(DEFINED LIMITED_MODULES_FILE)  
  validate_limited_modules_file(${LIMITED_MODULES_FILE})  
endif()  
 
add_subdirectory(${FWDIR}/vcv_ports/ ${CMAKE_CURRENT_BINARY_DIR}/vcv_ports)

# #################### Application ############################################

add_executable(
    simulator 
    src/main.cc 
    src/ui.cc
    stubs/random.cpp
    ${FWDIR}/src/gui/elements/element_name.cc
    ${FWDIR}/src/fw_update/updater_proxy.cc
    ${SHARED}/patch_convert/ryml/ryml_serial.cc
    ${SHARED}/patch_convert/ryml/ryml_init.cc
    ${SHARED}/patch_convert/yaml_to_patch.cc 
    ${SHARED}/patch_convert/patch_to_yaml.cc
    ${SHARED}/CoreModules/hub/hub_medium.cc
    )

target_include_directories(
  simulator
  PRIVATE src
          stubs
          sdl_audio
          ${FWDIR}/src/console
          ${FWDIR}/src/params
          ${SHARED}/patch
          ${FWDIR}/src/medium
          )

target_compile_options(simulator PRIVATE -Wall -Og -Wno-double-promotion)

target_link_libraries(simulator PRIVATE ${SDL2_LIBRARIES} lvglsdl ryml SDL2 ui vcv_ports)

set_property(TARGET simulator PROPERTY CXX_STANDARD 20)

# Arch-dependent Link options:
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


## Debugging
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang") 
  find_program(CMAKE_DEBUGGER_BINARY lldb)
  set(DEBUG_COMMAND ${CMAKE_DEBUGGER_BINARY} $<TARGET_FILE:simulator> -- -p ${CMAKE_CURRENT_LIST_DIR}/patches)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  find_program(CMAKE_DEBUGGER_BINARY gdb)
  set(DEBUG_COMMAND ${CMAKE_DEBUGGER_BINARY} -q
    -ex \"set debuginfod enabled off\"
    -ex \"set pagination off\" 
    -ex \"run\"
    --args $<TARGET_FILE:simulator> -p ${CMAKE_CURRENT_LIST_DIR}/patches
  )
else ()
  set(DEBUG_COMMAND echo "Compiler is ${CMAKE_CXX_COMPILER_ID}, but must be Clang, AppleClang, or GNU to debug")
endif()

add_custom_target(
  debug
  DEPENDS simulator
  COMMAND ${DEBUG_COMMAND}
  USES_TERMINAL
)

