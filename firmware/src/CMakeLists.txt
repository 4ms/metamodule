include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/arch_mp15xa7.cmake)

option(ENABLE_WIFI_BRIDGE        "Enable serial bridge to wifi module" ON)

set(FWDIR ${CMAKE_SOURCE_DIR})
set(LIBDIR ${FWDIR}/lib)

set_arch_flags()

#
# Driver interface
#
add_library(mdrivlib_interface INTERFACE)
target_include_directories(
  mdrivlib_interface
  INTERFACE ${FWDIR}/lib/cmsis-device/stm32mp157c/include
            ${FWDIR}/lib/cmsis/Core_A/Include
            ${FWDIR}/lib/cmsis/Include
            ${FWDIR}/lib/mdrivlib
            ${FWDIR}/lib/mdrivlib/target/stm32mp1
            ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7
            ${FWDIR}/lib/stm32-hal/stm32mp1/include
            ${FWDIR}/src/core_a7
)
target_compile_options(mdrivlib_interface INTERFACE $<$<COMPILE_LANGUAGE:CXX>:-Wno-register>)

#
# LVGL
#
set(LV_CONF_PATH
    ${FWDIR}/lib/lvgl/lv_conf.h
    CACHE STRING "" FORCE
)
add_subdirectory(${FWDIR}/lib/lvgl ${CMAKE_CURRENT_BINARY_DIR}/lvgl)
target_link_libraries(lvgl PRIVATE mdrivlib_interface)

target_include_directories(lvgl 
    PRIVATE ${PROJECT_SOURCE_DIR}/lib/fatfs/source 
            ${PROJECT_SOURCE_DIR}/src/fs/fatfs
)

target_sources(lvgl
    PRIVATE ${PROJECT_SOURCE_DIR}/lib/fatfs/source/ff.c
            ${PROJECT_SOURCE_DIR}/lib/fatfs/source/ffunicode.c
            ${PROJECT_SOURCE_DIR}/src/fs/fatfs/diskio.cc
            ${PROJECT_SOURCE_DIR}/src/fs/fatfs/delete_node.cc
)

#
# VCV Adaptor
#
add_subdirectory(../vcv_plugin ${CMAKE_BINARY_DIR}/vcv_plugin)
target_sources(vcv_plugin_export PRIVATE ../vcv_plugin/export/src/keep-symbols.cc)

#
# Brands
#
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/../vcv_ports ${CMAKE_BINARY_DIR}/vcv_ports)
add_subdirectory(${FWDIR}/lib/CoreModules/4ms ${CMAKE_CURRENT_BINARY_DIR}/CoreModules-4ms)

add_subdirectory(${LIBDIR}/patch-serial ${CMAKE_CURRENT_BINARY_DIR}/patch-serial)


#
# RYML
#
# if (NOT TARGET ryml)
#   add_subdirectory(${LIBDIR}/patch-serial/ryml/rapidyaml ${CMAKE_CURRENT_BINARY_DIR}/rapidyaml)
# endif()

#
# Jansson
#
# TODO: replace this with for example fetchContent later
if (NOT TARGET jansson)
  add_subdirectory(${FWDIR}/lib/jansson ${CMAKE_CURRENT_BINARY_DIR}/jansson)
endif()

#
# SLS Exported GUI (meta5)
#
add_subdirectory(${FWDIR}/src/gui/slsexport/meta5)
target_link_libraries(ui PRIVATE lvgl)

#
# Core Interface
#

if (NOT TARGET metamodule::core-interface)
  add_subdirectory(${FWDIR}/metamodule-plugin-sdk/metamodule-core-interface metamodule-core-interface)
endif()

#
# Main App
#
add_executable(
  main.elf
  ${FWDIR}/system/libc_stub.c
  ${FWDIR}/system/libcpp_stub.cc
  ${FWDIR}/system/new.cc
  ${FWDIR}/system/mmu_ca7.c
  ${FWDIR}/system/time.cc
  ${FWDIR}/system/startup_ca7.s
  ${FWDIR}/src/core_intercom/shared_memory.cc
  ${FWDIR}/src/core_a7/a7_shared_memory.cc
  ${FWDIR}/src/console/uart_log.cc
  ${FWDIR}/src/core_a7/main.cc
  ${FWDIR}/src/audio/audio.cc
  ${FWDIR}/src/core_a7/aux_core_main.cc
  ${FWDIR}/src/ryml_tests/patchlist_ryml_tests.cc
  ${FWDIR}/src/fs/fatfs/diskio.cc
  ${FWDIR}/src/fs/fatfs/fattime.cc
  ${FWDIR}/src/fs/time_convert.cc
  ${FWDIR}/src/fw_update/updater_proxy.cc
  ${FWDIR}/src/gui/elements/element_name.cc
  ${FWDIR}/src/gui/slsexport/ui_local.cc
  #
  ${FWDIR}/src/dynload/dynloader.cc
  ${FWDIR}/metamodule-plugin-sdk/version.cc
  #
  ${FWDIR}/src/fs/asset_drive/untar.cc
  ${FWDIR}/src/flash_loader/flash_loader.cc
  ${FWDIR}/src/fs/general_io.cc
  #
  ${FWDIR}/src/user_settings/settings_file.cc
  ${FWDIR}/src/user_settings/settings_parse.cc
  ${FWDIR}/src/user_settings/settings_serialize.cc
  #
  ${FWDIR}/lib/fatfs/source/ff.c
  ${FWDIR}/lib/fatfs/source/ffunicode.c
  #
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_rcc.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_rcc_ex.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_mdma.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_usart.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_usart_ex.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_uart.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_uart_ex.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_dma.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_i2c.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_i2c_ex.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_sai.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_ltdc.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_rng.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_ll_tim.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_ll_rcc.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_sd.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_sd_ex.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_ll_sdmmc.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_qspi.c
  #
  ${FWDIR}/lib/mdrivlib/drivers/pin.cc
  ${FWDIR}/lib/mdrivlib/drivers/tim.cc
  ${FWDIR}/lib/mdrivlib/drivers/timekeeper.cc
  ${FWDIR}/lib/mdrivlib/drivers/i2c.cc
  ${FWDIR}/lib/mdrivlib/drivers/qspi_flash_driver.cc
  ${FWDIR}/lib/mdrivlib/drivers/codec_PCM3168.cc
  ${FWDIR}/lib/mdrivlib/target/stm32mp1/drivers/sai_tdm.cc
  ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7/boot/system_ca7.c
  ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7/boot/irq_ctrl.c
  ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7/drivers/interrupt_handler.cc
  ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7/drivers/hal_handlers.cc
  ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7/drivers/cycle_counter.cc
  #
  ${FWDIR}/src/vcv_hardware/random.cpp
  ${FWDIR}/src/vcv_hardware/gettimeofday.cc
  #
  ${FWDIR}/src/patch_play/modules_helpers.cc
  #
  ${CMAKE_BINARY_DIR}/checkgit/git_version.cpp
)

# CoreModules sources
add_subdirectory(${FWDIR}/lib/CoreModules CoreModules)

# Fixup for compiler warning on files that include LVGL 8.3.4 headers:
set_source_files_properties(
  ${FWDIR}/src/core_a7/aux_core_main.cc
  ${FWDIR}/src/gui/elements/element_name.cc
  ${FWDIR}/src/gui/slsexport/ui_local.cc
  PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;"
)


target_include_directories(
  main.elf
  PRIVATE 
          ${FWDIR}
          ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/params
          ${FWDIR}/src/core_a7
          ${FWDIR}/src/medium
          ${FWDIR}/lib/mdrivlib
          ${FWDIR}/lib/mdrivlib/target/stm32mp1
          ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7
          ${LIBDIR}
          ${FWDIR}/lib/fatfs/source
          ${FWDIR}/src/fs/fatfs
          ${FWDIR}/lib/cmsis-device/stm32mp157c/include
          #
          ${CMAKE_BINARY_DIR}/checkgit
)

if (NOT TARGET cpputil::cpputil)
  add_subdirectory(${LIBDIR}/cpputil cpputil)
endif()


target_link_libraries(main.elf PRIVATE lvgl::lvgl mdrivlib_interface CoreModules ui metamodule::patch-serial cpputil vcv_ports)
target_link_libraries(main.elf PUBLIC vcv_plugin)
add_subdirectory(${FWDIR}/coreproc_plugin ${CMAKE_BINARY_DIR}/coreproc_plugin)
target_link_libraries(main.elf PUBLIC "$<LINK_LIBRARY:WHOLE_ARCHIVE,coreproc_plugin_export>")
target_link_libraries(main.elf PUBLIC "$<LINK_LIBRARY:WHOLE_ARCHIVE,CoreModules-4ms>")

if (METAMODULE_PCB_VERSION)
    target_compile_definitions(main.elf PRIVATE METAMODULE_PCB_VERSION=${METAMODULE_PCB_VERSION})
endif()

include(${CMAKE_CURRENT_LIST_DIR}/../vcv_ports/brands.cmake)
foreach(brand ${brands})
	if (DEFINED BUILD_DYN_PLUGIN_${brand})
	target_compile_definitions(main.elf PRIVATE -DBUILD_DYN_PLUGIN_${brand})
	endif()
endforeach()


target_link_script(
  main
  ${FWDIR}/system/linker/stm32mp15xx_ca7.ld
  -L${FWDIR}
  -Wl,--gc-sections
  -Wno-psabi
  -ffreestanding
  -nostartfiles
  # -flto=auto
)

