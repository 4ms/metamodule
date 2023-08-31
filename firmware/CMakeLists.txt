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
  COMMAND cd ${SHARED}/axoloti-wrapper && make --no-print-directory -f tests/Makefile -j8
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


add_custom_command(
  OUTPUT comp-cmd
  COMMAND ${CMAKE_COMMAND} -E echo "Generating LVGL image files for components"
)

add_custom_command(
  OUTPUT faceplate-cmd
  COMMAND ${CMAKE_COMMAND} -E echo "Generating LVGL image files for faceplates"
)

add_custom_command(
  OUTPUT imagelist-cmd
  COMMAND ${CMAKE_COMMAND} -E echo "Updating image_list.hh"
)

add_custom_command(
  OUTPUT vcvimages-cmd
  COMMAND ${CMAKE_COMMAND} -E echo "Updating/creating 4ms VCV artwork SVGs files from *_info.svg files"
)

add_custom_command(
  OUTPUT moduleinfos-cmd
  COMMAND ${CMAKE_COMMAND} -E echo "Updating/creating CoreModule *_info.hh files from *_info.svg"
)

add_custom_target(comp-images DEPENDS comp-cmd)
add_custom_target(faceplate-images DEPENDS faceplate-cmd)
add_custom_target(image-list DEPENDS imagelist-cmd)
add_custom_target(vcv-images DEPENDS vcvimages-cmd)
add_custom_target(module-infos DEPENDS moduleinfos-cmd)
# meta command to do all processing
add_custom_target(regenerate-all DEPENDS comp-images faceplate-images image-list vcv-images module-infos)

# List of brands
set(brands
    4ms
    Befaco
    AudibleInstruments
    Rack
)
foreach(brand ${brands})
  string(TOUPPER ${brand} BRAND)

  # for components, we just want _all_ components so use a glob
  file(GLOB ${brand}_comp_svgs ${PROJECT_SOURCE_DIR}/../graphics/${brand}/components/*.svg)

  # for each component svg, add_custom_command (...) to convert to lvgl
  foreach(svg ${${brand}_comp_svgs})
    get_filename_component(svg_name ${svg} NAME_WE)
    set(c_name ${PROJECT_SOURCE_DIR}/src/gui/images/${brand}/components/${svg_name}.c)
    add_custom_command(
      OUTPUT comp-cmd APPEND
      COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py convertSvgToLvgl ${svg} ${c_name}
      DEPENDS ${svg}
      COMMENT "Converting component: ${svg_name} to ${svg_name}.c"
    )
  endforeach()

  # for faceplates, we get branded lists from glue cmake files
  if(NOT ${brand} STREQUAL "4ms" AND NOT ${brand} STREQUAL "Rack")
    # each brand should define the faceplate paths in modules.cmake in ${BRAND}_FACEPLATE_SVGS
    include(${PROJECT_SOURCE_DIR}/vcv_ports/glue/${brand}/modules.cmake)

    if(NOT DEFINED ${BRAND}_FACEPLATE_SVGS)
      message(FATAL_ERROR "No faceplate svgs for ${BRAND}, make sure vcv_ports/glue/${brand}/modules.cmake defines ${BRAND}_FACEPLATE_SVGS!")
    endif()

  elseif(${brand} STREQUAL "4ms")
    file(GLOB ${BRAND}_FACEPLATE_SVGS ${PROJECT_SOURCE_DIR}/../vcv/res/modules/*.svg)
    # The Hub is only needed in VCV Rack, not Meta Module so remove from firmware
    list(REMOVE_ITEM ${BRAND}_FACEPLATE_SVGS ${PROJECT_SOURCE_DIR}/../vcv/res/modules/HubMedium_artwork.svg)

  elseif(${brand} STREQUAL "Rack")    
    message(STATUS "Rack modules not yet supported, skipping!")
    set(${BRAND}_FACEPLATE_SVGS)
  endif()

  foreach(svg ${${BRAND}_FACEPLATE_SVGS})
    get_filename_component(svg_name ${svg} NAME_WE)
    set(c240_name ${PROJECT_SOURCE_DIR}/src/gui/images/${brand}/modules/${svg_name}_240.c)

    # for each module svg, convert to .c version
    add_custom_command(
      OUTPUT faceplate-cmd APPEND
      COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py createLvglFaceplate ${svg} ${c240_name}
      DEPENDS ${svg}
      COMMENT "Creating 240px-height lvgl img from full-sized svg artwork: ${svg_name}_240.c"
    )

    # for each module, append to imagelist
    add_custom_command(
      OUTPUT imagelist-cmd APPEND
      COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py appendImgList ${svg_name} ${PROJECT_SOURCE_DIR}/src/gui/images/faceplate_images.hh
      DEPENDS ${svg}
      COMMENT "Adding to image-list: ${svg_name}_240.c"
    )

  endforeach() # loop over faceplates
 
endforeach() # loop over brands


 # for processing 4ms info svgs, we assume we want all modules so use a glob
 file(GLOB 4ms_info_svgs ${PROJECT_SOURCE_DIR}/../shared/CoreModules/4ms/svg/*.svg)

 # for each info svg, add_custom_command (...) to convert get the VCV svg and generate the _info.hh
 foreach(svg ${4ms_info_svgs})
   get_filename_component(svg_name ${svg} NAME_WE)
   STRING(REPLACE "_info" "_artwork" svg_name_artwork ${svg_name})   
   set(svg_name ${PROJECT_SOURCE_DIR}/../vcv/res/modules/${svg_name_artwork}.svg)
   
   add_custom_command(
     OUTPUT vcvimages-cmd APPEND
     COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py createVcvSvg ${svg} ${svg_name}
     DEPENDS ${svg}
     COMMENT "Converting component: ${svg_name} to ${svg_name}.c"
   )

   add_custom_command(
    OUTPUT moduleinfos-cmd APPEND
    COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py createInfo ${svg} ${PROJECT_SOURCE_DIR}/../shared/CoreModules/4ms/info
    DEPENDS ${svg}
    COMMENT "Converting component: ${svg_name} to ${svg_name}.c"
  )
 endforeach()

set_source_files_properties(comp-cmd PROPERTIES SYMBOLIC "true")
set_source_files_properties(faceplate-cmd PROPERTIES SYMBOLIC "true")
set_source_files_properties(imagelist-cmd PROPERTIES SYMBOLIC "true")
set_source_files_properties(vcvimages-cmd PROPERTIES SYMBOLIC "true")
set_source_files_properties(moduleinfos-cmd PROPERTIES SYMBOLIC "true")

# TODO: minblep generation, following doesn't work as needs a different compiler (non-arm)
# add_subdirectory(${SHARED}/gen_minblep ${SHARED}/gen_minblep/build)
