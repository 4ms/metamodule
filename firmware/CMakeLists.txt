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
get_target_property(CoreProcPluginBinDir coreproc_plugin_export BINARY_DIR)
set(SYMBOLS_BINFILE_DIRS
  --objdir ${VcvPluginBinDir} 
  --objdir ${CoreProcPluginBinDir} 
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

set_property(TARGET new-api-sym-list PROPERTY ADDITIONAL_CLEAN_FILES "")

#
# Asset Dir
#

cmake_path(SET ASSET_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSET_IMG_FILENAME  assets.uimg)
cmake_path(APPEND ASSET_IMG_PATH  "${CMAKE_CURRENT_BINARY_DIR}" "${ASSET_IMG_FILENAME}")

add_custom_command(
  #TODO how to make this run only if any file in the directory is modified, added, or deleted?
  OUTPUT ${ASSET_IMG_PATH} _always_force_refresh_
  COMMAND ${CMAKE_COMMAND} -E tar -cf ${ASSET_IMG_PATH}.tar .
  COMMAND cd ${CMAKE_CURRENT_SOURCE_DIR} && flashing/uimg_header.py --name Assets ${ASSET_IMG_PATH}.tar ${ASSET_IMG_PATH}
  COMMENT "Creating assets uimg file"
  WORKING_DIRECTORY ${ASSET_DIR}
  VERBATIM USES_TERMINAL
)

add_custom_target(asset-image ALL DEPENDS ${ASSET_IMG_PATH})


#
# Package Release
#
set(RELEASE_TARGET_DIR   ${CMAKE_CURRENT_BINARY_DIR}/metamodule-firmware)

set(RELEASE_AS_ARCHIVE             ${CMAKE_CURRENT_BINARY_DIR}/metamodule-${GIT_FIRMWARE_VERSION_TAG}-assets.zip)
set(RELEASE_FW_AS_ARCHIVE          ${CMAKE_CURRENT_BINARY_DIR}/metamodule-${GIT_FIRMWARE_VERSION_TAG}-firmware-assets.zip)
set(RELEASE_FW_AS_BL_ARCHIVE       ${CMAKE_CURRENT_BINARY_DIR}/metamodule-${GIT_FIRMWARE_VERSION_TAG}-firmware-assets-bl.zip)
set(RELEASE_FW_AS_BL_WIFI_ARCHIVE  ${CMAKE_CURRENT_BINARY_DIR}/metamodule-${GIT_FIRMWARE_VERSION_TAG}-firmware-assets-bl-wifi.zip)

set(MANIFEST_FILENAME metamodule.json)
set(MAIN_FW_FILENAME ${CMAKE_CURRENT_BINARY_DIR}/main.uimg)

add_custom_command(
  OUTPUT ${MAIN_FW_FILENAME}
  COMMAND flashing/elf_to_uimg.py
          --m4 $<TARGET_FILE:main_m4.elf>
          --a7 $<TARGET_FILE:main.elf>
          ${MAIN_FW_FILENAME}
  COMMAND cp ${MAIN_FW_FILENAME} ${CMAKE_CURRENT_BINARY_DIR}/main-uimg.bin #Jlink and Ozone require .bin extension
  COMMAND ls -l ${MAIN_FW_FILENAME}
  DEPENDS main.elf main_m4.elf ${SYMBOLS_FILE} AlwaysCheckGit
  COMMENT "Creating combined uimg file"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  VERBATIM USES_TERMINAL
)

add_custom_command(
  OUTPUT ${RELEASE_AS_ARCHIVE} ${RELEASE_FW_AS_ARCHIVE} ${RELEASE_FW_AS_BL_ARCHIVE} ${RELEASE_FW_AS_BL_WIFI_ARCHIVE}

  # Assets
  COMMAND ${CMAKE_CURRENT_LIST_DIR}/flashing/manifest_generator.py
                                   --version         "${GIT_FIRMWARE_VERSION_TAG}"
                                   --assets          "${ASSET_IMG_PATH}"
                                   "${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME}"
  COMMAND ${CMAKE_COMMAND} -E tar cf ${RELEASE_AS_ARCHIVE} --format=zip -- 
                                    ${RELEASE_TARGET_DIR}/${ASSET_IMG_FILENAME} 
                                    ${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME} 
                                    && rm -rf ${RELEASE_TARGET_DIR}

  # Firmware+Assets
  COMMAND ${CMAKE_CURRENT_LIST_DIR}/flashing/manifest_generator.py
                                   --version         "${GIT_FIRMWARE_VERSION_TAG}"
                                   --assets          "${ASSET_IMG_PATH}"
                                   --app             "${MAIN_FW_FILENAME}"
                                   "${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME}"
  COMMAND ${CMAKE_COMMAND} -E tar cf ${RELEASE_FW_AS_ARCHIVE} --format=zip -- 
                                        ${RELEASE_TARGET_DIR}/main.uimg 
                                        ${RELEASE_TARGET_DIR}/${ASSET_IMG_FILENAME} 
                                        ${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME} 
                                        && rm -rf ${RELEASE_TARGET_DIR}

  # Firmware+Assets+Bootloaders
  COMMAND ${CMAKE_CURRENT_LIST_DIR}/flashing/manifest_generator.py
                                   --version         "${GIT_FIRMWARE_VERSION_TAG}"
                                   --fsbl            "${CMAKE_CURRENT_LIST_DIR}/bootloader/mp1-boot/build/fsbl.stm32"
                                   --dfu             "${CMAKE_CURRENT_LIST_DIR}/bootloader/mp1-usb-dfu/build/usbdfu.uimg"
                                   --assets          "${ASSET_IMG_PATH}"
                                   --app             "${MAIN_FW_FILENAME}"
                                   "${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME}"
  COMMAND ${CMAKE_COMMAND} -E tar cf ${RELEASE_FW_AS_BL_ARCHIVE} --format=zip -- 
                                        ${RELEASE_TARGET_DIR}/main.uimg 
                                        ${RELEASE_TARGET_DIR}/${ASSET_IMG_FILENAME} 
                                        ${RELEASE_TARGET_DIR}/fsbl.stm32
                                        ${RELEASE_TARGET_DIR}/usbdfu.uimg
                                        ${RELEASE_TARGET_DIR}/${MANIFEST_FILENAME} 
                                        && rm -rf ${RELEASE_TARGET_DIR}

  # Firmware+Assets+Bootloaders+Wifi
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
  COMMAND ${CMAKE_COMMAND} -E tar cf ${RELEASE_FW_AS_BL_WIFI_ARCHIVE} --format=zip -- 
                                        ${RELEASE_TARGET_DIR} 
                                        && rm -rf ${RELEASE_TARGET_DIR}

  DEPENDS ${MAIN_FW_FILENAME} ${ASSET_IMG_PATH} bootloader bootloader-dfu AlwaysCheckGit
  COMMENT "Creating releases at ${CMAKE_CURRENT_BINARY_DIR}/metamodule-${GIT_FIRMWARE_VERSION_TAG}-*.zip"
  VERBATIM USES_TERMINAL
)

add_custom_target(
  combined-uimg ALL
  DEPENDS ${MAIN_FW_FILENAME} ${RELEASE_AS_ARCHIVE} ${RELEASE_FW_AS_ARCHIVE} ${RELEASE_FW_AS_BL_ARCHIVE} ${RELEASE_FW_AS_BL_WIFI_ARCHIVE}
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
set(LIBDIR ${PROJECT_SOURCE_DIR}/lib)

add_custom_target(
  tests ALL
  COMMAND cd ${PROJECT_SOURCE_DIR} && make --no-print-directory -f tests/Makefile -j8
  COMMAND cd ${LIBDIR}/patch-serial && make --no-print-directory -f tests/Makefile -j8
  COMMAND cd ${PROJECT_SOURCE_DIR}/lib/CoreModules/4ms/core/axoloti-wrapper && make --no-print-directory -f tests/Makefile -j8
  COMMAND cd ${PROJECT_SOURCE_DIR}/lib/CoreModules/tests && make all
  COMMAND cd ${PROJECT_SOURCE_DIR}/lib/CoreModules/4ms/tests && make all
  COMMENT "Running unit tests"
  VERBATIM USES_TERMINAL
)
file(
  GLOB
  tests_clean_files
  CONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/tests/build/*"
  "${LIBDIR}/patch-serial/tests/build/*"
  "${PROJECT_SOURCE_DIR}/lib/CoreModules/tests/build"
  "${PROJECT_SOURCE_DIR}/lib/CoreModules/4ms/tests/build"
  "${PROJECT_SOURCE_DIR}/lib/CoreModules/4ms/core/axoloti-wrapper/tests/build/*"
)
set_target_properties(tests PROPERTIES ADDITIONAL_CLEAN_FILES "${tests_clean_files}")

add_custom_target(
  dep_tests
  COMMAND cd ${LIBDIR}/cpputil && make --no-print-directory -f tests/Makefile -j8
  COMMAND cd ${PROJECT_SOURCE_DIR}/lib/mdrivlib && make --no-print-directory -f tests/Makefile -j8
  BYPRODUCTS ${PROJECT_SOURCE_DIR}/lib/mdrivlib/tests/build/* ${LIBDIR}/cpputil/tests/build/*
  VERBATIM USES_TERMINAL
)

set_property(
  DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  APPEND
  PROPERTY ADDITIONAL_CLEAN_FILES
           ${PROJECT_SOURCE_DIR}/tests/build
           ${PROJECT_SOURCE_DIR}/lib/mdrivlib/tests/build
           ${LIBDIR}/cpputil/tests/build
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
# minBlep tables for vcv modules
#

add_custom_target(
  gen_minblep
  COMMAND cd ${PROJECT_SOURCE_DIR}/../shared/gen_minblep && cmake -B build -GNinja && cmake --build build --target
          generate_minblep_files
  COMMENT "Regenerating minBlep tables"
  VERBATIM USES_TERMINAL
)
