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
# Only build a limited set of modules, defined in an external file
#
include(vcv_ports/glue/filter.cmake)

unset(USE_LIMITED_MODULES)
if(DEFINED LIMITED_MODULES_FILE)
  validate_limited_modules_file(${LIMITED_MODULES_FILE})
endif()

#
# Git commit hash
#
include(cmake/CheckGit.cmake)
CheckGitSetup()

#
# Main Application
#
set(M4_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR}/mp1corem4/medium)
set(A7_BIN_PATH ${CMAKE_CURRENT_BINARY_DIR}/mp1corea7/medium)

add_subdirectory(src/core_m4 ${M4_BIN_PATH})
add_subdirectory(src ${A7_BIN_PATH})

#
# Symbol table
#

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/a7_symbols.yaml
  #TODO: fix hard-coded dirs
  COMMAND flashing/dump_syms.py
  			--objdir ${CMAKE_BINARY_DIR}/mp1corea7/medium/CMakeFiles/main.elf.dir/Users/dann/4ms/stm32/meta-module/shared/CoreModules/
			--objdir ${CMAKE_BINARY_DIR}/mp1corea7/medium/VCV_adaptor/CMakeFiles/VCV_adaptor.dir/
			--elf $<TARGET_FILE:main.elf>
			--yaml ${CMAKE_CURRENT_BINARY_DIR}/a7_symbols.yaml \
			-v

  COMMAND flashing/dump_syms.py
          --m4 $<TARGET_FILE:main_m4.elf>
          --a7 $<TARGET_FILE:main.elf>
          ${MAIN_FW_FILENAME}
  COMMAND cp ${MAIN_FW_FILENAME} ${CMAKE_CURRENT_BINARY_DIR}/main-uimg.bin #Jlink and Ozone require .bin extension
  COMMAND ls -l ${MAIN_FW_FILENAME}
  DEPENDS main.elf main_m4.elf
  COMMENT "Creating combined uimg file"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  VERBATIM USES_TERMINAL
)

#
# Package Release
#
set(RELEASE_TARGET_DIR   ${CMAKE_CURRENT_BINARY_DIR}/metamodule-firmware)
set(RELEASE_ARCHIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/metamodule-${GIT_FIRMWARE_VERSION_TAG}-all.zip)
set(RELEASE_FW_ONLY_ARCHIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/metamodule-${GIT_FIRMWARE_VERSION_TAG}-main.zip)
set(MANIFEST_FILENAME    metamodule.json)
set(MAIN_FW_FILENAME  ${CMAKE_CURRENT_BINARY_DIR}/main.uimg)

add_custom_command(
  OUTPUT ${MAIN_FW_FILENAME}
  COMMAND flashing/elf_to_uimg.py
          --m4 $<TARGET_FILE:main_m4.elf>
          --a7 $<TARGET_FILE:main.elf>
          ${MAIN_FW_FILENAME}
  COMMAND cp ${MAIN_FW_FILENAME} ${CMAKE_CURRENT_BINARY_DIR}/main-uimg.bin #Jlink and Ozone require .bin extension
  COMMAND ls -l ${MAIN_FW_FILENAME}
  DEPENDS main.elf main_m4.elf ${CMAKE_CURRENT_BINARY_DIR}/a7_symbols.yaml #TODO: Is this the best way to be sure dump_syms is always run first?
  COMMENT "Creating combined uimg file"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  VERBATIM USES_TERMINAL
)

add_custom_command(
  OUTPUT ${RELEASE_ARCHIVE_PATH} ${RELEASE_FW_ONLY_ARCHIVE_PATH}

  COMMAND ${CMAKE_CURRENT_LIST_DIR}/flashing/manifest_generator.py
           --version         "${GIT_FIRMWARE_VERSION_TAG}"
           --app             "${MAIN_FW_FILENAME}"
           "${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME}"
  COMMAND ${CMAKE_COMMAND} -E tar cvf ${RELEASE_FW_ONLY_ARCHIVE_PATH} --format=zip -- ${RELEASE_TARGET_DIR}/main.uimg ${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME} && rm -rf ${RELEASE_TARGET_DIR}

  COMMAND ${CMAKE_CURRENT_LIST_DIR}/flashing/manifest_generator.py
           --version         "${GIT_FIRMWARE_VERSION_TAG}"
           --fsbl            "${CMAKE_CURRENT_LIST_DIR}/bootloader/mp1-boot/build/fsbl.stm32"
           --dfu             "${CMAKE_CURRENT_LIST_DIR}/bootloader/mp1-usb-dfu/build/usbdfu.uimg"
           --app             "${MAIN_FW_FILENAME}"
           --wifi_bootloader "${CMAKE_CURRENT_LIST_DIR}/src/wifi/flasher/images/bootloader.bin"
           --wifi_app        "${CMAKE_CURRENT_LIST_DIR}/src/wifi/flasher/images/application.bin"
           --wifi_filesystem "${CMAKE_CURRENT_LIST_DIR}/src/wifi/flasher/images/filesystem.img"
           "${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME}"
  COMMAND ${CMAKE_COMMAND} -E tar cvf ${RELEASE_ARCHIVE_PATH} --format=zip -- ${RELEASE_TARGET_DIR} && rm -rf ${RELEASE_TARGET_DIR}

  DEPENDS ${MAIN_FW_FILENAME} bootloader bootloader-dfu
  COMMENT "Creating release at ${RELEASE_ARCHIVE_PATH}"
  VERBATIM USES_TERMINAL
)

add_custom_target(
  combined-uimg ALL
  DEPENDS ${MAIN_FW_FILENAME} ${RELEASE_ARCHIVE_PATH}
)


#
# Flash loader
#
add_subdirectory(src/flash_loader)

#
# Bootloader (MP1-Boot)
#
if ("${TOOLCHAIN_BASE_DIR}" STREQUAL "")
	set(BOOTLOADER_TOOLCHAIN_OPT "")
else()
	set(BOOTLOADER_TOOLCHAIN_OPT "TOOLCHAIN_DIR=${TOOLCHAIN_BASE_DIR}/")
endif()

add_custom_target(
  bootloader
  COMMAND make --no-print-directory BOARD_CONF=../board_conf/mmp11_conf.hh ${BOOTLOADER_TOOLCHAIN_OPT}
  COMMENT "Building MP1-Boot (FSBL)"
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bootloader/mp1-boot
  VERBATIM
)

add_custom_target(
  bootloader-dfu
  COMMAND make --no-print-directory BOARD_CONF=board_conf/mmp11_conf.hh ${BOOTLOADER_TOOLCHAIN_OPT}
  COMMENT "Building DFU Bootloader"
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bootloader/mp1-usb-dfu
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
  VERBATIM USES_TERMINAL
)
file(
  GLOB
  tests_clean_files
  CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/tests/build/*"
  "${SHARED}/patch_convert/tests/build/*"
  "${SHARED}/CoreModules/tests/build/*"
  "${SHARED}/axoloti-wrapper/tests/build/*"
)
set_target_properties(tests PROPERTIES ADDITIONAL_CLEAN_FILES "${tests_clean_files}")

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
  VERBATIM USES_TERMINAL
)

add_custom_command(
  OUTPUT faceplate-cmd
  COMMAND ${CMAKE_COMMAND} -E echo "Generated LVGL image files for faceplates (all brands)"
  VERBATIM USES_TERMINAL
)

add_custom_command(
  OUTPUT vcvimages-cmd
  COMMAND ${CMAKE_COMMAND} -E echo "Updating/creating 4ms VCV artwork SVGs files from *_info.svg files"
  VERBATIM USES_TERMINAL
)

add_custom_command(
  OUTPUT moduleinfos-cmd
  COMMAND ${CMAKE_COMMAND} -E echo "Updating/creating CoreModule *_info.hh files from *_info.svg"
  VERBATIM USES_TERMINAL
)

add_custom_target(comp-images DEPENDS comp-cmd)
add_custom_target(faceplate-images DEPENDS faceplate-cmd)
add_custom_target(vcv-images DEPENDS vcvimages-cmd)
add_custom_target(module-infos DEPENDS moduleinfos-cmd)

# meta command to do all processing
add_custom_target(
  regenerate-all
  DEPENDS comp-images
          faceplate-images
          vcv-images
          module-infos
)

# List of brands
include(vcv_ports/brands.cmake)

foreach(brand ${brands})
  string(TOUPPER ${brand} BRAND)

  add_custom_command(
    OUTPUT faceplate-cmd-${brand}
    COMMAND ${CMAKE_COMMAND} -E echo "Generating LVGL image files for ${brand} faceplates"
    VERBATIM USES_TERMINAL
  )
  add_custom_target(faceplate-images-${brand} DEPENDS faceplate-cmd-${brand})
  add_dependencies(faceplate-images faceplate-images-${brand})

  # for components, we just want _all_ components so use a glob
  file(GLOB ${brand}_comp_svgs ${PROJECT_SOURCE_DIR}/../graphics/${brand}/components/*.svg)

  # for each component svg, add_custom_command (...) to convert to lvgl
  foreach(svg ${${brand}_comp_svgs})
    get_filename_component(svg_name ${svg} NAME_WE)
    set(outpath ${PROJECT_SOURCE_DIR}/src/gui/images/${brand}/components/)
    add_custom_command(
      OUTPUT comp-cmd
      APPEND
      COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py convertSvgToLvgl ${svg} ${outpath}
      DEPENDS ${svg}
      COMMENT "Converting component: ${svg_name} to ${svg_name}.c"
    )
  endforeach()

  # For faceplates, we get branded lists from glue/BRAND/modules.cmake. In this file, each brand should set
  # ${BRAND}_FACEPLATE_SVGS to be the paths to all the faceplate SVGs
  include(${PROJECT_SOURCE_DIR}/vcv_ports/glue/${brand}/modules.cmake)

  if(NOT DEFINED ${BRAND}_FACEPLATE_SVGS)
    message(
      FATAL_ERROR
        "No faceplate svgs for ${BRAND}, make sure vcv_ports/glue/${brand}/modules.cmake defines ${BRAND}_FACEPLATE_SVGS!"
    )
  endif()

  # generation script will fail if this folder doesn't exist
  file(MAKE_DIRECTORY ${PROJECT_SOURCE_DIR}/src/gui/images/${brand}/modules)

  foreach(svg ${${BRAND}_FACEPLATE_SVGS})
    get_filename_component(svg_name ${svg} NAME_WE)
    set(c240_name ${PROJECT_SOURCE_DIR}/src/gui/images/${brand}/modules/${svg_name}_240.c)

    # for each module svg, convert to .c version
    add_custom_command(
      OUTPUT faceplate-cmd-${brand}
      APPEND
      COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py createLvglFaceplate ${svg} ${c240_name}
      DEPENDS ${svg}
      COMMENT "Creating 240px-height lvgl img from full-sized svg artwork: ${svg_name}_240.c"
    )
  endforeach() # loop over faceplates

endforeach() # loop over brands

# 4ms Info SVGs for each info svg, add_custom_command (...) to convert get the VCV svg and generate the _info.hh
foreach(info_svg ${4MS_INFO_SVGS})
  get_filename_component(slug ${info_svg} NAME_WE) # e.g. Verb_info

  string(
    REPLACE "_info"
            "_artwork"
            svg_name_artwork
            ${slug}
  )
  set(vcv_svg ${PROJECT_SOURCE_DIR}/../vcv/res/modules/${svg_name_artwork}.svg)

  add_custom_command(
    OUTPUT vcvimages-cmd
    APPEND
    COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py createVcvSvg ${info_svg} ${vcv_svg}
    DEPENDS ${info_svg}
    COMMENT "Creating VCV SVG: ${slug}"
  )

  add_custom_command(
    OUTPUT moduleinfos-cmd
    APPEND
    COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py createInfo ${info_svg}
            ${PROJECT_SOURCE_DIR}/../shared/CoreModules/4ms/info
    DEPENDS ${info_svg}
    COMMENT "Creating info header: ${slug}"
  )
endforeach()

set_source_files_properties(comp-cmd PROPERTIES SYMBOLIC "true")
set_source_files_properties(faceplate-cmd PROPERTIES SYMBOLIC "true")
set_source_files_properties(vcvimages-cmd PROPERTIES SYMBOLIC "true")
set_source_files_properties(moduleinfos-cmd PROPERTIES SYMBOLIC "true")

add_custom_target(
  gen_minblep
  COMMAND cd ${PROJECT_SOURCE_DIR}/../shared/gen_minblep && cmake -B build -GNinja && cmake --build build --target
          generate_minblep_files
  COMMENT "Regenerating minBlep tables"
  VERBATIM USES_TERMINAL
)
