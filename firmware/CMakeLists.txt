cmake_minimum_required(VERSION 3.22)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(${CMAKE_CURRENT_LIST_DIR}/cmake/ccache.cmake)

set(CMAKE_BUILD_TYPE "RelWithDebInfo")

project(
  MetaModule
  VERSION 0.10
  DESCRIPTION "MetaModule"
  LANGUAGES C CXX ASM
)

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

set(SYMBOLS_FILE ${CMAKE_CURRENT_BINARY_DIR}/a7_symbols.yaml)
set(API_SYMBOL_NAMES_FILE ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugin-sdk/api-symbols.txt)
get_target_property(VcvPluginBinDir vcv_plugin_export BINARY_DIR)
set(SYMBOLS_BINFILE_DIRS
  --objdir ${VcvPluginBinDir} 
  --objdir ${CMAKE_BINARY_DIR}/mp1corea7/medium/CMakeFiles/main.elf.dir/vcv_hardware/
)

add_custom_command(
  OUTPUT ${API_SYMBOL_NAMES_FILE}
  COMMAND echo "vcv export dir is ${VcvPluginBinDir}"
  COMMAND scripts/dump_syms.py
          ${SYMBOLS_BINFILE_DIRS}
          --text-out ${API_SYMBOL_NAMES_FILE}
		  -v
  DEPENDS main.elf
  COMMENT "Creating new API symbol list file in the SDK directory ${API_SYMBOL_NAMES_FILE}"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/metamodule-plugin-sdk
  VERBATIM USES_TERMINAL
)

add_custom_target(new-api-sym-list DEPENDS ${API_SYMBOL_NAMES_FILE})

add_custom_command(
  OUTPUT ${SYMBOLS_FILE}
  COMMAND scripts/find_syms.py
          --symbols ${API_SYMBOL_NAMES_FILE}
          --elf $<TARGET_FILE:main.elf>
          --out ${SYMBOLS_FILE}
          # -v
  COMMAND ${CMAKE_OBJCOPY} --update-section .symlist=${SYMBOLS_FILE} $<TARGET_FILE:main.elf> $<TARGET_FILE:main.elf> 
  DEPENDS main.elf 
  COMMENT "Generating table of API symbol addresses and installing in firmware binary"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/metamodule-plugin-sdk
  VERBATIM USES_TERMINAL
)

#
# Asset Dir
#

set(ASSET_DIR  ${CMAKE_CURRENT_SOURCE_DIR}/assets)
set(ASSET_IMG_FILENAME  assets.uimg)
set(ASSET_IMG_PATH  ${CMAKE_CURRENT_BINARY_DIR}/${ASSET_IMG_FILENAME})

add_custom_command(
  OUTPUT ${ASSET_IMG_PATH} _always_force_refresh_
  #TODO how to make this run only if any file in the directory is modified, added, or deleted?
  COMMAND tar -cf ${ASSET_IMG_PATH}.tar -C ${ASSET_DIR} --strip-component=1 .
  COMMAND flashing/uimg_header.py --name Assets ${ASSET_IMG_PATH}.tar ${ASSET_IMG_PATH}
  COMMENT "Creating assets uimg file"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  VERBATIM USES_TERMINAL
)

add_custom_target(asset-image ALL DEPENDS ${ASSET_IMG_PATH})


#
# Package Release
#
set(RELEASE_TARGET_DIR   ${CMAKE_CURRENT_BINARY_DIR}/metamodule-firmware)
set(RELEASE_ARCHIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/metamodule-${GIT_FIRMWARE_VERSION_TAG}-all.zip)
set(RELEASE_FW_ONLY_ARCHIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/metamodule-${GIT_FIRMWARE_VERSION_TAG}-main.zip)
set(RELEASE_ASSETS_ARCHIVE_PATH ${CMAKE_CURRENT_BINARY_DIR}/metamodule-${GIT_FIRMWARE_VERSION_TAG}-assets.zip)
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
  DEPENDS main.elf main_m4.elf ${SYMBOLS_FILE}
  COMMENT "Creating combined uimg file"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  VERBATIM USES_TERMINAL
)

add_custom_command(
  OUTPUT ${RELEASE_ARCHIVE_PATH} ${RELEASE_FW_ONLY_ARCHIVE_PATH}

  COMMAND ${CMAKE_CURRENT_LIST_DIR}/flashing/manifest_generator.py
           --version         "${GIT_FIRMWARE_VERSION_TAG}"
           --assets          "${ASSET_IMG_PATH}"
           "${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME}"
  COMMAND ${CMAKE_COMMAND} -E tar cf ${RELEASE_ASSETS_ARCHIVE_PATH} --format=zip -- ${RELEASE_TARGET_DIR}/${ASSET_IMG_FILENAME} ${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME} && rm -rf ${RELEASE_TARGET_DIR}

  COMMAND ${CMAKE_CURRENT_LIST_DIR}/flashing/manifest_generator.py
           --version         "${GIT_FIRMWARE_VERSION_TAG}"
           --assets          "${ASSET_IMG_PATH}"
           --app             "${MAIN_FW_FILENAME}"
           "${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME}"
  COMMAND ${CMAKE_COMMAND} -E tar cf ${RELEASE_FW_ONLY_ARCHIVE_PATH} --format=zip -- ${RELEASE_TARGET_DIR}/main.uimg ${RELEASE_TARGET_DIR}/${ASSET_IMG_FILENAME} ${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME} && rm -rf ${RELEASE_TARGET_DIR}

  COMMAND ${CMAKE_CURRENT_LIST_DIR}/flashing/manifest_generator.py
           --version         "${GIT_FIRMWARE_VERSION_TAG}"
           --fsbl            "${CMAKE_CURRENT_LIST_DIR}/bootloader/mp1-boot/build/fsbl.stm32"
           --dfu             "${CMAKE_CURRENT_LIST_DIR}/bootloader/mp1-usb-dfu/build/usbdfu.uimg"
           --assets          "${ASSET_IMG_PATH}"
           --app             "${MAIN_FW_FILENAME}"
           --wifi_bootloader "${CMAKE_CURRENT_LIST_DIR}/src/wifi/flasher/images/bootloader.bin"
           --wifi_app        "${CMAKE_CURRENT_LIST_DIR}/src/wifi/flasher/images/application.bin"
           --wifi_filesystem "${CMAKE_CURRENT_LIST_DIR}/src/wifi/flasher/images/filesystem.img"
           "${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME}"
  COMMAND ${CMAKE_COMMAND} -E tar cf ${RELEASE_ARCHIVE_PATH} --format=zip -- ${RELEASE_TARGET_DIR} && rm -rf ${RELEASE_TARGET_DIR}

  DEPENDS ${MAIN_FW_FILENAME} ${ASSET_IMG_PATH} bootloader bootloader-dfu
  COMMENT "Creating release at ${RELEASE_ARCHIVE_PATH}"
  VERBATIM USES_TERMINAL
)

add_custom_target(
  combined-uimg ALL
  DEPENDS ${MAIN_FW_FILENAME} ${RELEASE_ARCHIVE_PATH}
)


#
# Bootloaders: MP1-Boot and MP1-DFU-USB
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
  COMMAND cd ${SHARED}/CoreModules/4ms/core/axoloti-wrapper && make --no-print-directory -f tests/Makefile -j8
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


#
# Process 4ms info files
#

add_custom_command(
  OUTPUT moduleinfos-cmd
  COMMAND ${CMAKE_COMMAND} -E echo "Updating/creating CoreModule *_info.hh files from *_info.svg"
  VERBATIM USES_TERMINAL
)


# 4ms Info SVGs for each info svg, add_custom_command (...) to to generate the _info.hh
include(vcv_ports/glue/4ms/modules.cmake)
foreach(info_svg ${4MS_INFO_SVGS})
  get_filename_component(slug ${info_svg} NAME_WE) # e.g. Verb_info

  add_custom_command(
    OUTPUT moduleinfos-cmd
    APPEND
    COMMAND python3 ${PROJECT_SOURCE_DIR}/../shared/svgextract/svgextract.py createInfo ${info_svg}
            ${PROJECT_SOURCE_DIR}/../shared/CoreModules/4ms/info
    DEPENDS ${info_svg}
    COMMENT "Creating info header: ${slug}"
  )
endforeach()

set_source_files_properties(moduleinfos-cmd PROPERTIES SYMBOLIC "true")

add_custom_target(module-infos DEPENDS moduleinfos-cmd)

#
# minBlep tables for vcv modules
#

add_custom_target(
  gen_minblep
  COMMAND cd ${PROJECT_SOURCE_DIR}/../shared/gen_minblep && cmake -B build -GNinja && cmake --build build --target
          generate_minblep_files
  COMMENT "Regenerating minBlep tables"
  VERBATIM USES_TERMINAL
)
