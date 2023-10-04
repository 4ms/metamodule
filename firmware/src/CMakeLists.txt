include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/arch_mp15xa7.cmake)

set(FWDIR ${CMAKE_SOURCE_DIR})
set(SHARED ${FWDIR}/../shared)

#
# Driver interface
#
add_library(mdrivlib_interface INTERFACE)
target_link_libraries(mdrivlib_interface INTERFACE mp15xa7_arch)
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

#
# VCV Adaptor
#
add_subdirectory(VCV_adaptor)
target_link_libraries(VCV_adaptor PUBLIC mp15xa7_arch)
target_include_directories(VCV_adaptor PRIVATE console/) # For pr_dbg, etc
target_link_libraries(jansson PUBLIC mp15xa7_arch)

#
# Brands
#
include(${CMAKE_CURRENT_LIST_DIR}/../vcv_ports/brands.cmake)

foreach(brand ${brands})
  # Component artwork
  file(GLOB BRAND_ARTWORK_SOURCES ${FWDIR}/src/gui/images/${brand}/components/*.c)
  list(APPEND COMP_ARTWORK_SOURCES ${BRAND_ARTWORK_SOURCES})

  # Module Library
  add_subdirectory(${FWDIR}/vcv_ports/glue/${brand} ${CMAKE_CURRENT_BINARY_DIR}/${brand})
  target_link_libraries(${brand}Library PRIVATE mp15xa7_arch)
  target_include_directories(
    ${brand}Library
    PUBLIC ${FWDIR}/src/VCV_adaptor
           ${FWDIR}/src/VCV_adaptor/pffft
           ${FWDIR}/lib/jansson
           ${FWDIR}/lib/jansson/jansson/src
           ${FWDIR}/src
           ${FWDIR}
           ${SHARED}
           ${SHARED}/cpputil
  )
  target_compile_options(${brand}Library PRIVATE -Wno-attributes)

  # Faceplate artwork
  include(${FWDIR}/vcv_ports/glue/${brand}/modules.cmake)
  foreach(module IN LISTS ${brand}Modules)
    if(NOT DEFINED LIMITED_MODULES OR module IN_LIST LIMITED_MODULES)
      if(brand EQUAL "4ms")
        list(APPEND FACEPLATE_ARTWORK_SOURCES ${FWDIR}/src/gui/images/${brand}/modules/${module}_artwork_240.c)
      else()
        list(APPEND FACEPLATE_ARTWORK_SOURCES ${FWDIR}/src/gui/images/${brand}/modules/${module}_240.c)
      endif()
    endif()
  endforeach()

endforeach()

#
# RYML
#
set(RYMLDIR ${SHARED}/patch_convert/ryml/rapidyaml)
file(
  GLOB
  RYML_SOURCES
  ${RYMLDIR}/src/c4/yml/*.cpp
  ${RYMLDIR}/ext/c4core/src/c4/*.cpp
)
add_library(ryml OBJECT ${RYML_SOURCES})
target_link_libraries(ryml PUBLIC mp15xa7_arch)
target_include_directories(ryml PUBLIC ${RYMLDIR}/src ${RYMLDIR}/ext/c4core/src)

#
# SLS Exported GUI (meta5)
#
add_subdirectory(${FWDIR}/src/gui/slsexport/meta5)
target_link_libraries(ui PRIVATE lvgl::lvgl mp15xa7_arch)
# Fix for SLS generated files (See https://forum.squareline.io/t/unused-variable-target-warning-when-compiling/1610/3 )
target_compile_options(ui PRIVATE -Wno-unused-variable)

#
# Main App
#
add_executable(
  main.elf
  $<TARGET_FILE_DIR:main_m4.elf>/m4_rodata.ld
  $<TARGET_FILE_DIR:main_m4.elf>/firmware_m4.h
  $<TARGET_FILE_DIR:main_m4.elf>/firmware_m4_vectors.h
  ${FWDIR}/system/libc_stub.c
  ${FWDIR}/system/libcpp_stub.cc
  ${FWDIR}/system/new.cc
  ${FWDIR}/system/mmu_ca7.c
  ${FWDIR}/src/core_intercom/shared_memory.cc
  ${FWDIR}/src/console/uart_log.cc
  ${FWDIR}/src/core_a7/main.cc
  ${FWDIR}/src/audio/audio.cc
  ${FWDIR}/src/core_a7/aux_core_main.cc
  ${FWDIR}/src/ryml_tests/patchlist_ryml_tests.cc
  ${FWDIR}/src/fs/fatfs/diskio.cc
  ${FWDIR}/src/fs/fatfs/fattime.cc
  ${FWDIR}/src/fs/time_convert.cc
  #
  ${SHARED}/CoreModules/hub/hub_medium.cc
  ${SHARED}/patch_convert/yaml_to_patch.cc
  ${SHARED}/patch_convert/ryml/ryml_serial.cc
  ${SHARED}/cpputil/util/math_tables.cc
  #
  ${FWDIR}/lib/fatfs/source/ff.c
  ${FWDIR}/lib/fatfs/source/ffunicode.c
  #
  ${FWDIR}/lib/littlefs/lfs.c
  ${FWDIR}/lib/littlefs/lfs_util.c
  #
  ${FWDIR}/lib/printf/printf.c
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
  ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7/boot/startup_ca7.s
  #
  ${FWDIR}/src/VCV_adaptor/random.cpp
  #
  ${COMP_ARTWORK_SOURCES}
  ${FACEPLATE_ARTWORK_SOURCES}
)

# Fixup for compiler warning on files that include LVGL 8.3.4 headers:
set_source_files_properties(
  ${FWDIR}/src/core_a7/aux_core_main.cc
  PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;"
)

# Fixup for compiler warning for LittleFS
set_source_files_properties(${FWDIR}/lib/littlefs/lfs.c PROPERTIES COMPILE_OPTIONS "-Wno-unused-function")

target_include_directories(
  main.elf
  PRIVATE $<TARGET_FILE_DIR:main_m4.elf>
          ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/params
          ${FWDIR}/src/core_a7
          ${FWDIR}/src/medium
          ${FWDIR}/lib/mdrivlib
          ${FWDIR}/lib/mdrivlib/target/stm32mp1
          ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7
          ${SHARED}
          ${SHARED}/cpputil
          ${SHARED}/patch
          ${SHARED}/patch_convert
          ${FWDIR}/lib/fatfs/source
          ${FWDIR}/src/fs/fatfs
          ${FWDIR}/lib/cmsis-device/stm32mp157c/include
          #
          ${FWDIR}/lib/jansson
          ${FWDIR}/lib/jansson/jansson/src
)

target_link_libraries(
  main.elf
  PRIVATE lvgl::lvgl
          mp15xa7_arch
          mdrivlib_interface
          # core4ms
          ui
          ryml
          VCV_adaptor
)

foreach(brand ${brands})
  target_link_libraries(main.elf PRIVATE ${brand}Library)
endforeach()

add_dependencies(main.elf m4_firmware)

target_link_script(
  main
  ${FWDIR}/system/linker/stm32mp15xx_ca7.ld
  -L${FWDIR}
  -L$<TARGET_FILE_DIR:main_m4.elf>
  -Wl,--gc-sections
  -Wno-psabi
  -ffreestanding
  -nostartfiles
  -nostdlib
  -flto=auto
)

add_bin_hex_command(main)

add_custom_command(
  TARGET main.elf
  POST_BUILD
  COMMAND ${FWDIR}/flashing/uimg_header.py $<TARGET_FILE_DIR:main.elf>/main.bin $<TARGET_FILE_DIR:main.elf>/main.uimg
          0xC1FBFFC0 0xC2000040
  COMMAND ls -l $<TARGET_FILE_DIR:main.elf>/main.uimg
  COMMENT "Creating uimg file"
  VERBATIM
)

set_source_files_properties($<TARGET_FILE_DIR:main.elf>/main.uimg PROPERTIES GENERATED TRUE)
