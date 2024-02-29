include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/arch_mp15xa7.cmake)
set_arch_flags()

set(FWDIR ${CMAKE_SOURCE_DIR})
set(SHARED ${FWDIR}/../shared)

#
# cpputil
#
add_subdirectory(${SHARED}/cpputil ${CMAKE_CURRENT_BINARY_DIR}/cpputil)

add_executable(
  flash_loader.elf
  ${FWDIR}/system/libc_stub.c
  ${FWDIR}/system/libcpp_stub.cc
  ${FWDIR}/system/new.cc
  ${FWDIR}/system/mmu_ca7.c
  ${FWDIR}/system/startup_ca7.s
  ${FWDIR}/src/console/uart_log.cc
  ${FWDIR}/src/flash_loader/flash_loader.cc
  ${FWDIR}/src/flash_loader/flash_loader_main.cc
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
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_ll_rcc.c
  ${FWDIR}/lib/stm32-hal/stm32mp1/src/stm32mp1xx_hal_qspi.c
  #
  ${FWDIR}/lib/mdrivlib/drivers/pin.cc
  ${FWDIR}/lib/mdrivlib/drivers/qspi_flash_driver.cc
  ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7/boot/system_ca7.c
  ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7/boot/irq_ctrl.c
  ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7/drivers/interrupt_handler.cc
  ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7/drivers/hal_handlers.cc
  #
)

target_include_directories(
  flash_loader.elf
  PRIVATE ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/core_a7
          ${FWDIR}/src/flash_loader
          ${FWDIR}/src/medium
          ${FWDIR}/lib/mdrivlib
          ${FWDIR}/lib/mdrivlib/target/stm32mp1
          ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7
          ${SHARED}
          ${FWDIR}/lib/cmsis-device/stm32mp157c/include
          ${FWDIR}/lib/cmsis/Core_A/Include
          ${FWDIR}/lib/cmsis/Include
          ${FWDIR}/lib/stm32-hal/stm32mp1/include
)

target_compile_options(flash_loader.elf PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-Wno-register>)

target_link_script(
  flash_loader
  ${FWDIR}/system/linker/stm32mp15xx_ca7_flashloader.ld
  -L${FWDIR}
  -Wl,--gc-sections
  -nostdlib
)

target_link_libraries(flash_loader.elf PRIVATE cpputil)

add_bin_hex_command(flash_loader)

add_custom_command(
  TARGET flash_loader.elf
  POST_BUILD
  COMMAND ${FWDIR}/flashing/uimg_header.py $<TARGET_FILE_DIR:flash_loader.elf>/flash_loader.bin $<TARGET_FILE_DIR:flash_loader.elf>/flash_loader.uimg --load_addr 0xC2000000 --entry_point_offset 0x40
  COMMAND ${FWDIR}/flashing/uimg_header.py $<TARGET_FILE_DIR:flash_loader.elf>/flash_loader.bin $<TARGET_FILE_DIR:flash_loader.elf>/flash_loader_nonlegacy.uimg --bootable --load_addr 0xC2000040 --entry_point_offset 0x0
  COMMAND ls -l $<TARGET_FILE_DIR:flash_loader.elf>/flash_loader.uimg
  COMMENT "Creating uimg file"
  VERBATIM
)

set_property(TARGET flash_loader.elf PROPERTY EXCLUDE_FROM_ALL TRUE)

add_custom_target(
  flash_loader_dfu
  DEPENDS flash_loader.elf
  COMMAND echo "---------------------------------------------------"
  COMMAND echo "|        Flashing MetaModule via DFU USB          |"
  COMMAND echo "| You must power-up with the Encoder pushed down. |"
  COMMAND echo "|      Connect a USB cable to the MetaModule      |"
  COMMAND echo "---------------------------------------------------"
  COMMAND dfu-util -a 0 -s 0x70080000 -D $<TARGET_FILE_DIR:flash_loader.elf>/flash_loader.uimg
  VERBATIM USES_TERMINAL
)

add_custom_target(flash_loader DEPENDS flash_loader.elf)
