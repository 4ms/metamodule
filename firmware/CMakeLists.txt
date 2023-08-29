cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/ccache.cmake)

set(CMAKE_BUILD_TYPE "RelWithDebInfo")

project(
  MetaModule
  VERSION 0.1
  DESCRIPTION "MetaModule"
  LANGUAGES C CXX ASM
)

#
# LVGL
#
set(LV_CONF_PATH
    ${PROJECT_SOURCE_DIR}/lib/lvgl/lv_conf.h
    CACHE STRING "" FORCE
)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/lvgl)
target_link_libraries(lvgl PRIVATE mdrivlib_interface)
target_include_directories(lvgl PUBLIC ${PROJECT_SOURCE_DIR}/lib/printf)

#
# Main Application
#
add_subdirectory(src/core_m4 ${CMAKE_CURRENT_BINARY_DIR}/mp1corem4/medium)
add_subdirectory(src ${CMAKE_CURRENT_BINARY_DIR}/mp1corea7/medium)

#
# Bootloader (MP1-Boot)
#
add_custom_target(
  bootloader
  COMMAND make BOARD_CONF=../board_conf/mmp11_conf.hh
  COMMENT "Building MP1-Boot (FSBL)"
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bootloader/mp1-boot
  VERBATIM
)

#
# Tests
#
set(SHARED ${PROJECT_SOURCE_DIR}/../shared)

add_custom_target(
  tests ALL
  COMMAND cd ${PROJECT_SOURCE_DIR} && make --no-print-directory -f tests/Makefile -j8
  COMMAND cd ${SHARED}/patch_convert && make --no-print-directory -f tests/Makefile -j8
  COMMAND cd ${SHARED}/CoreModules && make --no-print-directory -f tests/Makefile -j8
  BYPRODUCTS ${PROJECT_SOURCE_DIR}/tests/build/*
  VERBATIM USES_TERMINAL
)

add_custom_target(
  dep_tests
  COMMAND cd ${SHARED}/cpputil && make --no-print-directory -f tests/Makefile -j8
  COMMAND cd ${PROJECT_SOURCE_DIR}/lib/mdrivlib && make --no-print-directory -f tests/Makefile -j8
  BYPRODUCTS ${PROJECT_SOURCE_DIR}/lib/mdrivlib/tests/build/* ${SHARED}/cpputil/tests/build/*
  VERBATIM USES_TERMINAL
)

set_property(
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  APPEND
  PROPERTY ADDITIONAL_CLEAN_FILES
           ${PROJECT_SOURCE_DIR}/tests/build
           ${PROJECT_SOURCE_DIR}/lib/mdrivlib/tests/build
           ${SHARED}/cpputil/tests/build
)

#
# Flashing/installing
#
include(flashing/flashing.cmake)

#
# Simulator shortcut
#
add_custom_target(
  simulate
  COMMAND make -C ${PROJECT_SOURCE_DIR}/../simulator run
  VERBATIM USES_TERMINAL
)

# TODO: use CMake for all targets below here:

#
# Helpers/generators
#
add_custom_target(
  gen_minblep
  COMMAND make --no-print-directory -C ${SHARED}/gen_minblep && ${SHARED}/gen_minblep/gen_minblep 16 32 >
          ${PROJECT_SOURCE_DIR}/src/VCV_adaptor/dsp/minblep_16_32.h
  VERBATIM USES_TERMINAL
)

add_custom_target(
  module-infos
  COMMAND make --no-print-directory -f ${PROJECT_SOURCE_DIR}/makefiles/makefile_moduleinfo.mk SHARED=${SHARED}
          module-infos
  COMMENT "Updating/creating CoreModule *_info.hh files from *_info.svg"
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  VERBATIM
)

add_custom_target(
  vcv-images
  COMMAND make --no-print-directory -f ${PROJECT_SOURCE_DIR}/makefiles/makefile_moduleinfo.mk SHARED=${SHARED}
          vcv-images
  COMMENT "Updating/creating 4ms VCV artwork SVGs files from *_info.svg files"
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  VERBATIM
)

add_custom_target(
  image-list
  COMMAND make --no-print-directory -f ${PROJECT_SOURCE_DIR}/makefiles/makefile_component_images.mk image-list
  COMMENT "Updating image_list.hh"
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
  VERBATIM USES_TERMINAL
)

# List of brands
set(brands
    4ms
    Befaco
    AudibleInstruments
    Rack
)
foreach(brand ${brands})

  # for components, we just want _all_ components so use a glob
  file(GLOB ${brand}_comp_svgs ${PROJECT_SOURCE_DIR}/../graphics/${brand}/components/*.svg)
  set(${brand}_comp_lvgls)

  # for each svg, add_custom_command (...) to convert to lvgl
  foreach(svg ${${brand}_comp_svgs})
    get_filename_component(svg_name ${svg} NAME_WE)
    set(c_name ${PROJECT_SOURCE_DIR}/src/gui/images/${brand}/components/${svg_name}.c)
    list(APPEND ${brand}_comp_lvgls ${c_name})
    add_custom_command(
      OUTPUT ${c_name}
      COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py convertSvgToLvgl ${svg} ${c_name}
      DEPENDS ${svg}
      COMMENT "Converting component: ${svg_name} to ${svg_name}.c"
    )
  endforeach()
  list(APPEND comp_lvgls ${${brand}_comp_lvgls})

  # for faceplates, we skip 4ms and Rack
  if(NOT ${brand} STREQUAL "4ms" AND NOT ${brand} STREQUAL "Rack")
    # each brand should define the faceplate paths in modules.cmake in ${brand}_faceplate_svgs
    include(${PROJECT_SOURCE_DIR}/vcv_ports/glue/${brand}/modules.cmake)
    # we modify this list to prepend the full path
    list(TRANSFORM ${brand}_faceplate_svgs PREPEND ${PROJECT_SOURCE_DIR}/vcv_ports/${brand}/)

    set(${brand}_faceplate_lvgls)
    foreach(svg ${${brand}_faceplate_svgs})
      get_filename_component(svg_name ${svg} NAME_WE)
      set(c240_name ${PROJECT_SOURCE_DIR}/src/gui/images/${brand}/modules/${svg_name}_240.c)
      list(APPEND ${brand}_faceplate_lvgls ${c240_name})
      add_custom_command(
        OUTPUT ${c240_name}
        COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py createLvglFaceplate ${svg} ${c240_name}
        DEPENDS ${svg}
        COMMENT "Creating faceplate: ${svg_name}_240.c"
      )
    endforeach()
    list(APPEND faceplate_lvgls ${${brand}_faceplate_lvgls})
  endif()
endforeach()

add_custom_target(comp-images DEPENDS ${comp_lvgls})
add_custom_target(faceplate-images DEPENDS ${faceplate_lvgls})
