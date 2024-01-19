include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)

set(M4DIR ${CMAKE_CURRENT_SOURCE_DIR}) # /firmware/src/core_m4
set(FWDIR ${CMAKE_SOURCE_DIR}) # /firmware
set(SHARED ${FWDIR}/../shared) # /shared

set(HALDIR ${FWDIR}/lib/stm32-hal/stm32mp1)
set(DRIVERLIB ${FWDIR}/lib/mdrivlib)
set(USBHOST_LIBDIR ${FWDIR}/lib/stm32-usb-host-lib)
set(USBDEV_LIBDIR ${FWDIR}/lib/stm32-usb-device-lib)
set(WIFI_DIR ${FWDIR}/src/wifi)

add_executable(
  main_m4.elf
  ${M4DIR}/controls.cc
  ${M4DIR}/main_m4.cc
  ${M4DIR}/system_stm32mp1xx.c
  ${FWDIR}/src/console/uart_log.cc
  ${FWDIR}/src/core_intercom/shared_memory.cc
  ${FWDIR}/src/fs/fatfs/diskio.cc
  ${FWDIR}/src/fs/fatfs/fattime.cc
  ${FWDIR}/src/fs/time_convert.cc
  ${FWDIR}/src/usb/usb_drive_device.cc
  ${FWDIR}/src/usb/usbd_conf.cc
  ${FWDIR}/src/usb/usbd_desc.c
  ${FWDIR}/src/usb/usbh_conf.cc
  ${FWDIR}/src/usb/usbh_midi.cc
  ${FWDIR}/lib//fatfs/source/ff.c
  ${FWDIR}/lib//fatfs/source/ffunicode.c
  ${FWDIR}/lib//littlefs/lfs.c
  ${FWDIR}/lib//littlefs/lfs_util.c
  ${FWDIR}/system/libc_stub.c
  ${FWDIR}/system/libcpp_stub.cc
  ${FWDIR}/system/new.cc
  ${FWDIR}/system/startup_stm32mp157cxx_cm4.s
  ${DRIVERLIB}/drivers/hal_handlers.cc
  ${DRIVERLIB}/drivers/i2c.cc
  ${DRIVERLIB}/drivers/pin.cc
  ${DRIVERLIB}/drivers/qspi_flash_driver.cc
  ${DRIVERLIB}/drivers/tim.cc
  ${DRIVERLIB}/drivers/timekeeper.cc
  ${DRIVERLIB}/target/stm32mp1_cm4/drivers/interrupt_handler.cc
  ${HALDIR}/src/stm32mp1xx_hal.c
  ${HALDIR}/src/stm32mp1xx_hal_adc.c
  ${HALDIR}/src/stm32mp1xx_hal_adc_ex.c
  ${HALDIR}/src/stm32mp1xx_hal_cortex.c
  ${HALDIR}/src/stm32mp1xx_hal_dma.c
  ${HALDIR}/src/stm32mp1xx_hal_hcd.c
  ${HALDIR}/src/stm32mp1xx_hal_i2c.c
  ${HALDIR}/src/stm32mp1xx_hal_i2c_ex.c
  ${HALDIR}/src/stm32mp1xx_hal_mdma.c
  ${HALDIR}/src/stm32mp1xx_hal_pcd.c
  ${HALDIR}/src/stm32mp1xx_hal_pcd_ex.c
  ${HALDIR}/src/stm32mp1xx_hal_pwr_ex.c
  ${HALDIR}/src/stm32mp1xx_hal_qspi.c
  ${HALDIR}/src/stm32mp1xx_hal_rcc.c
  ${HALDIR}/src/stm32mp1xx_hal_rcc_ex.c
  ${HALDIR}/src/stm32mp1xx_hal_sd.c
  ${HALDIR}/src/stm32mp1xx_hal_sd_ex.c
  ${HALDIR}/src/stm32mp1xx_hal_uart.c
  ${HALDIR}/src/stm32mp1xx_hal_usart.c
  ${HALDIR}/src/stm32mp1xx_ll_rcc.c
  ${HALDIR}/src/stm32mp1xx_ll_sdmmc.c
  ${HALDIR}/src/stm32mp1xx_ll_tim.c
  ${HALDIR}/src/stm32mp1xx_ll_usb.c
  ${HALDIR}/src/stm32mp1xx_ll_usb_phy.c
  ${USBDEV_LIBDIR}/Class/MSC/Src/usbd_msc.c
  ${USBDEV_LIBDIR}/Class/MSC/Src/usbd_msc_bot.c
  ${USBDEV_LIBDIR}/Class/MSC/Src/usbd_msc_data.c
  ${USBDEV_LIBDIR}/Class/MSC/Src/usbd_msc_scsi.c
  ${USBDEV_LIBDIR}/Core/Src/usbd_core.c
  ${USBDEV_LIBDIR}/Core/Src/usbd_ctlreq.c
  ${USBDEV_LIBDIR}/Core/Src/usbd_ioreq.c
  ${USBHOST_LIBDIR}/Class/MSC/Src/usbh_msc.c
  ${USBHOST_LIBDIR}/Class/MSC/Src/usbh_msc_bot.c
  ${USBHOST_LIBDIR}/Class/MSC/Src/usbh_msc_scsi.c
  ${USBHOST_LIBDIR}/Core/Src/usbh_core.c
  ${USBHOST_LIBDIR}/Core/Src/usbh_ctlreq.c
  ${USBHOST_LIBDIR}/Core/Src/usbh_ioreq.c
  ${USBHOST_LIBDIR}/Core/Src/usbh_pipes.c
)

target_include_directories(
  main_m4.elf
  PRIVATE ${FWDIR}/lib/cmsis-device/stm32mp157c/include
          ${FWDIR}/lib/cmsis/Include
          ${HALDIR}/include
          ${DRIVERLIB}
          ${DRIVERLIB}/target/stm32mp1
          ${DRIVERLIB}/target/stm32mp1_cm4
          ${FWDIR}/lib/easiglib
          ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/params
          ${FWDIR}/src/medium
          ${M4DIR}
          ${FWDIR}
          ${FWDIR}/system
          ${SHARED}
          ${SHARED}/processors
          ${SHARED}/CoreModules
          ${SHARED}/cpputil
          ${SHARED}/patch
          ${FWDIR}/lib/fatfs/source
          ${FWDIR}/src/fs/fatfs
          ${FWDIR}/src/usb
          ${USBHOST_LIBDIR}/Core/Inc
          ${USBHOST_LIBDIR}/Class/MSC/Inc
          ${USBDEV_LIBDIR}/Core/Inc
          ${USBDEV_LIBDIR}/Class/MSC/Inc
)

set(MCU_FLAGS
    -mcpu=cortex-m4
    -mfpu=fpv4-sp-d16
    -mthumb
    -mlittle-endian
    -mfloat-abi=hard
)

add_library(mp15xm4_arch INTERFACE)
target_compile_options(mp15xm4_arch INTERFACE ${MCU_FLAGS})

target_compile_features(main_m4.elf PUBLIC cxx_std_23)

target_compile_options(
  main_m4.elf
  PRIVATE ${MCU_FLAGS}
          $<$<CONFIG:Debug>:-O0
          -g3>
          $<$<CONFIG:Release>:-O3>
          $<$<CONFIG:RelWithDebInfo>:-O3
          -g3>
          -fno-common
          -fdata-sections
          -ffunction-sections
          -nostartfiles
          -ffreestanding
          -fno-unwind-tables
          -Wall
          -Werror=return-type
          -Wsign-compare
          -Wdouble-promotion
          -flto=auto
          $<$<COMPILE_LANGUAGE:CXX>:
          -ffold-simple-inlines
          -Wno-psabi
          -fno-rtti
          -fno-exceptions
          -Wno-register
          -Wno-volatile
          -fno-threadsafe-statics
          >
)

target_compile_definitions(
  main_m4.elf
  PRIVATE USE_HAL_DRIVER
          USE_FULL_LL_DRIVER
          STM32MP157Cxx
          STM32MP1
          CORE_CM4
          ARM_MATH_CM4
)

target_link_script(
  main_m4
  ${FWDIR}/system/linker/stm32mp15xx_m4.ld
  -L${FWDIR}
  -Wl,--gc-sections
  -ffreestanding
  -nostartfiles
  -flto=auto
  ${MCU_FLAGS}
)

# Fixup for compiler warning for LittleFS
set_source_files_properties(${FWDIR}/lib/littlefs/lfs.c PROPERTIES COMPILE_OPTIONS "-Wno-unused-function")

if (ENABLE_WIFI_BRIDGE)

  target_compile_definitions(main_m4.elf PRIVATE
    ENABLE_WIFI_BRIDGE=1
  )

  # Add comm functionality
  add_subdirectory(${FWDIR}/src/wifi/comm ${CMAKE_BINARY_DIR}/wifi_comm)

endif()

# Always add wifi flashing
add_subdirectory(${FWDIR}/src/wifi/flasher ${CMAKE_BINARY_DIR}/wifi_flash)




set(GEN_PATH ${CMAKE_CURRENT_BINARY_DIR})

