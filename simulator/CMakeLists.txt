cmake_minimum_required(VERSION 3.14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mm_sim LANGUAGES C CXX)

set(FWDIR ${CMAKE_CURRENT_LIST_DIR}/../firmware)
set(SHARED ${CMAKE_CURRENT_LIST_DIR}/../shared)
set(LVGL_DIR ${FWDIR}/lib/lvgl/lvgl)

set(LV_CONF_PATH
    ${CMAKE_CURRENT_LIST_DIR}/lv_conf.h
    CACHE STRING "" FORCE)

add_compile_options(-O0 -g2)

# #################### cpputil #########################################

add_subdirectory(../shared/cpputil cpputil)

# #################### LVGL Simulator Driver #################################

add_subdirectory(lvgl_drv)

# #################### LVGL ############################################

get_filename_component(LV_CONF_DIR ${LV_CONF_PATH} DIRECTORY)
include(${LVGL_DIR}/CMakeLists.txt)
target_include_directories(lvgl PRIVATE 
          ${FWDIR}/lib/fatfs/source
          ${FWDIR}/src/fs/fatfs
)

# #################### RYML ##################################

add_subdirectory(${SHARED}/patch_convert/ryml/rapidyaml ${CMAKE_CURRENT_BINARY_DIR}/rapidyaml)

# #################### SLS Export ##################################

add_subdirectory(${FWDIR}/src/gui/slsexport/meta5 ${CMAKE_CURRENT_BINARY_DIR}/ui)
target_link_libraries(ui PRIVATE lvgl)

# #################### VCV Adaptor ##################################

add_subdirectory(${FWDIR}/vcv_plugin ${CMAKE_CURRENT_BINARY_DIR}/vcv_plugin)

# #################### Other brands ##################################
 
add_subdirectory(${FWDIR}/vcv_ports/ ${CMAKE_CURRENT_BINARY_DIR}/vcv_ports)
target_compile_options(vcv_ports INTERFACE -Wno-double-promotion)

# #################### Application ############################################

add_subdirectory(${SHARED}/CoreModules ${CMAKE_CURRENT_BINARY_DIR}/CoreModules)
target_compile_options(CoreModules INTERFACE -Wno-double-promotion)

add_executable(
	simulator 
	src/main.cc 
	src/ui.cc
    stubs/random.cpp
	${FWDIR}/src/gui/elements/element_name.cc
	${FWDIR}/src/gui/slsexport/ui_local.cc
    ${FWDIR}/src/fw_update/updater_proxy.cc
	${SHARED}/patch_convert/ryml/ryml_serial.cc
	${SHARED}/patch_convert/ryml/ryml_init.cc
	${SHARED}/patch_convert/yaml_to_patch.cc 
	${SHARED}/patch_convert/patch_to_yaml.cc

	#Fatfs:
	stubs/fattime.cc
	${FWDIR}/lib/fatfs/source/ff.c
	${FWDIR}/lib/fatfs/source/ffunicode.c
	${FWDIR}/src/fs/fatfs/diskio.cc
	${FWDIR}/src/fs/time_convert.cc
	#Tar:
	${FWDIR}/src/fs/asset_drive/untar.cc
	)

target_include_directories(
  simulator
  PRIVATE src
          stubs
          sdl_audio
          ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/params
          ${SHARED}/patch
          ${FWDIR}/src/medium
          ${FWDIR}/lib/fatfs/source
          ${FWDIR}/src/fs/fatfs
			.
          )

target_compile_options(simulator PRIVATE -Wall -Og)
target_compile_options(simulator PRIVATE -Wno-double-promotion)


target_link_libraries(simulator PRIVATE ${SDL2_LIBRARIES} lvglsdl ryml SDL2 ui vcv_ports CoreModules)
target_link_libraries(simulator PUBLIC vcv_plugin)

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

