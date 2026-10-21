cmake_minimum_required(VERSION 3.22)

# Cortex-M33 (CPU2) firmware for the MetaModule MP2 ("pro").
# Built as an ExternalProject of cmake/mp2.cmake (it needs the arm-none-eabi
# toolchain, so it can't be a target of the A35 project). The A35 embeds main_m33.bin
# and loads it to M33_LOAD_ADDR.

set(FWDIR ${CMAKE_CURRENT_LIST_DIR}/../..)

if(NOT CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE ${FWDIR}/cmake/arm-none-eabi-gcc.cmake)
endif()

set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "")

project(
  MetaModuleMP2_M33
  VERSION 0.1
  DESCRIPTION "MetaModule MP2 (pro) Cortex-M33"
  LANGUAGES C CXX ASM
)

set(M33_LOAD_ADDR "" CACHE STRING "Address the A35 loads the M33 image to (set by the parent project)")
set(M33_REGION_SIZE "" CACHE STRING "Size of the M33 memory region (set by the parent project)")
set(SHAREDMEM_ADDR "" CACHE STRING "Address of the memory shared with the A35 (set by the parent project)")
set(SHAREDMEM_SIZE "" CACHE STRING "Size of the memory shared with the A35 (set by the parent project)")
if(NOT M33_LOAD_ADDR OR NOT M33_REGION_SIZE OR NOT SHAREDMEM_ADDR OR NOT SHAREDMEM_SIZE)
  message(FATAL_ERROR "M33_LOAD_ADDR, M33_REGION_SIZE, SHAREDMEM_ADDR, SHAREDMEM_SIZE must be set (build this via cmake --preset mp2)")
endif()

add_compile_definitions(
  M33_LOAD_ADDR=${M33_LOAD_ADDR} M33_REGION_SIZE=${M33_REGION_SIZE} SHAREDMEM_ADDR=${SHAREDMEM_ADDR}
  SHAREDMEM_SIZE=${SHAREDMEM_SIZE}
)

option(MP2_TEST_CARRIER "Build for the mp2-devboard test carrier instead of the pro p1 board" OFF)
if(MP2_TEST_CARRIER)
  add_compile_definitions(MP2_TEST_CARRIER)
endif()

# The DWC3 HAL sends a control transfer's data stage as one transfer, and reports it once (when the
# host moves on to the status stage), so the USB device library must not split it into packets
add_compile_definitions(USBD_AVOID_PACKET_SPLIT_MPS)

set(MDRIVLIB ${FWDIR}/lib/mdrivlib)
set(USBDEV_LIBDIR ${FWDIR}/lib/stm32-usb-device-lib)
set(USBHOST_LIBDIR ${FWDIR}/lib/stm32-usb-host-lib)

include(${FWDIR}/cmake/log_levels.cmake)
enable_logging()

include(${FWDIR}/cmake/arch_mp25xm33.cmake)
set_arch_flags()

# ST HAL (only the modules used here: see stm32mp2xx_hal_conf.h)
set(M33_HAL_MODULES
  hal_dcache
  hal_ospi
  hal_rcc
  hal_rcc_ex
  hal_sd
  hal_sd_ex
  ll_sdmmc
  ll_tim
  # USB device, DWC3 flavor (the generic hal_pcd.c etc only pick these for MP257C)
  hal_pcd_drd
  hal_pcd_drd_ex
  ll_usb_drd
)
list(TRANSFORM M33_HAL_MODULES PREPEND ${FWDIR}/lib/stm32-hal/stm32mp2/Src/stm32mp2xx_)
list(TRANSFORM M33_HAL_MODULES APPEND .c)
set_source_files_properties(${M33_HAL_MODULES} PROPERTIES COMPILE_OPTIONS "-Wno-unused-variable")

add_executable(
  main_m33.elf
  main.cc
  fault_handlers.cc
  panel_controls.cc
  system_init.cc
  write.cc
  ${M33_HAL_MODULES}
  ${MDRIVLIB}/target/stm32mp2_cm33/boot/startup_cm33.s
  ${MDRIVLIB}/target/stm32mp2_cm33/drivers/interrupt_handler.cc
  ${MDRIVLIB}/target/stm32mp2_cm33/drivers/hal_tick_stgen.cc
  ${MDRIVLIB}/drivers/pin.cc
  ${MDRIVLIB}/drivers/tim.cc
  ${MDRIVLIB}/drivers/timekeeper.cc
  ${MDRIVLIB}/target/stm32mp2/drivers/ospi_flash_driver.cc
  ${FWDIR}/lib/fatfs/source/ff.c
  ${FWDIR}/lib/fatfs/source/ffunicode.c
  ${FWDIR}/lib/littlefs/lfs.c
  ${FWDIR}/lib/littlefs/lfs_util.c
  ${FWDIR}/src/fs/fatfs/diskio.cc
  ${FWDIR}/src/fs/fatfs/delete_node.cc
  ${FWDIR}/src/fs/fatfs/fattime.cc
  ${FWDIR}/src/fs/helpers.cc
  ${FWDIR}/src/fs/time_convert.cc
  ${FWDIR}/system/sbrk_mp2.cc
  ${FWDIR}/system/libc_stub.c
  # USB device: MP1's classes and device manager, on our usbd_conf.cc
  usbd_conf.cc
  ${FWDIR}/src/usb/device_cdc/usb_serial_device.cc
  ${FWDIR}/src/usb/device_composite/usbd_composite.c
  ${FWDIR}/src/usb/device_composite/usbd_composite_desc.c
  ${FWDIR}/src/usb/device_msc/usb_drive_device.cc
  ${FWDIR}/src/usb/device_video/usb_video_device.cc
  ${FWDIR}/src/usb/device_video/usbd_video_desc.c
  ${FWDIR}/src/usb/device_midi/usbd_midi.c
  ${FWDIR}/src/usb/usb_midi_device.cc
  ${USBDEV_LIBDIR}/Core/Src/usbd_core.c
  ${USBDEV_LIBDIR}/Core/Src/usbd_ctlreq.c
  ${USBDEV_LIBDIR}/Core/Src/usbd_ioreq.c
  ${USBDEV_LIBDIR}/Class/MSC/Src/usbd_msc.c
  ${USBDEV_LIBDIR}/Class/MSC/Src/usbd_msc_bot.c
  ${USBDEV_LIBDIR}/Class/MSC/Src/usbd_msc_data.c
  ${USBDEV_LIBDIR}/Class/MSC/Src/usbd_msc_scsi.c
  ${USBDEV_LIBDIR}/Class/CDC/Src/usbd_cdc.c
  ${USBDEV_LIBDIR}/Class/VIDEO/Src/usbd_video.c
)

target_include_directories(
  main_m33.elf
  PRIVATE ${CMAKE_CURRENT_LIST_DIR}
          ${FWDIR}/src/mp2-stubs
          ${FWDIR}/src/pro # before src, so pro's conf/ headers are found before the shared ones in src/conf/
          ${FWDIR}/src
          ${FWDIR}
          ${FWDIR}/src/console
          ${FWDIR}/src/params
          ${FWDIR}/lib
          ${FWDIR}/lib/patch-serial
          ${FWDIR}/metamodule-plugin-sdk/core-interface
          ${FWDIR}/lib/fatfs/source
          ${FWDIR}/src/fs/fatfs
          ${FWDIR}/src/usb
          ${FWDIR}/src/usb/device_composite
          ${USBHOST_LIBDIR}/Core/Inc
          ${USBHOST_LIBDIR}/Class/MSC/Inc
          ${USBDEV_LIBDIR}/Core/Inc
          ${USBDEV_LIBDIR}/Class/MSC/Inc
          ${USBDEV_LIBDIR}/Class/CDC/Inc
          ${USBDEV_LIBDIR}/Class/VIDEO/Inc
          ${MDRIVLIB}
          ${MDRIVLIB}/target/stm32mp2
          ${MDRIVLIB}/target/stm32mp2_cm33
          ${FWDIR}/lib/cpputil
          ${FWDIR}/lib/stm32-hal/stm32mp2/Inc
          ${FWDIR}/lib/cmsis/Include
          ${FWDIR}/lib/cmsis-device/stm32mp257d/Include
)

set(LINKER_SCRIPT ${FWDIR}/system/linker/stm32mp2xx_cm33.ld)
target_link_options(
  main_m33.elf PRIVATE
  -T${LINKER_SCRIPT}
  -Wl,--defsym=M33_LOAD_ADDR=${M33_LOAD_ADDR}
  -Wl,--defsym=M33_REGION_SIZE=${M33_REGION_SIZE}
  -Wl,--defsym=SHAREDMEM_ADDR=${SHAREDMEM_ADDR}
  -Wl,--defsym=SHAREDMEM_SIZE=${SHAREDMEM_SIZE}
  -Wl,-Map,main_m33.map,--cref
  --specs=nano.specs
  --specs=nosys.specs
)
set_target_properties(main_m33.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

set_source_files_properties(${FWDIR}/lib/littlefs/lfs.c PROPERTIES COMPILE_OPTIONS "-Wno-unused-function")

add_custom_command(
  TARGET main_m33.elf
  POST_BUILD
  COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:main_m33.elf> main_m33.bin
  COMMAND ${CMAKE_SIZE_UTIL} $<TARGET_FILE:main_m33.elf>
  BYPRODUCTS main_m33.bin
  COMMENT "Creating main_m33.bin"
)
