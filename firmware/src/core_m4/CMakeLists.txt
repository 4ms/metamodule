include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/arch_mp15xm4.cmake)
set_arch_flags()

include(${CMAKE_SOURCE_DIR}/cmake/log_levels.cmake)
enable_logging()

set(M4DIR ${CMAKE_CURRENT_SOURCE_DIR}) # /firmware/src/core_m4
set(FWDIR ${CMAKE_SOURCE_DIR}) # /firmware

set(HALDIR ${FWDIR}/lib/stm32-hal/stm32mp1)
set(DRIVERLIB ${FWDIR}/lib/mdrivlib)

add_executable(
  main_m4.elf
  ${M4DIR}/controls.cc
  ${M4DIR}/main_m4.cc
  ${M4DIR}/write.cc
  ${M4DIR}/system_stm32mp1xx.c
  ${FWDIR}/src/console/uart_log.cc
  ${FWDIR}/src/core_intercom/shared_memory.cc
  ${FWDIR}/system/libc_stub.c
  ${M4DIR}/libc_stub.c
  ${M4DIR}/libcpp_stub.cc
  ${FWDIR}/system/new.cc
  ${FWDIR}/system/sbrk.cc
  ${FWDIR}/system/startup_stm32mp157cxx_cm4.s
  ${DRIVERLIB}/drivers/hal_handlers.cc
  ${DRIVERLIB}/drivers/i2c.cc
  ${DRIVERLIB}/drivers/pin.cc
  ${DRIVERLIB}/drivers/tim.cc
  ${DRIVERLIB}/drivers/timekeeper.cc
  ${DRIVERLIB}/target/stm32mp1_cm4/drivers/interrupt_handler.cc
  ${HALDIR}/src/stm32mp1xx_hal.c
  ${HALDIR}/src/stm32mp1xx_hal_adc.c
  ${HALDIR}/src/stm32mp1xx_hal_adc_ex.c
  ${HALDIR}/src/stm32mp1xx_hal_cortex.c
  ${HALDIR}/src/stm32mp1xx_hal_dma.c
  ${HALDIR}/src/stm32mp1xx_hal_i2c.c
  ${HALDIR}/src/stm32mp1xx_hal_i2c_ex.c
  ${HALDIR}/src/stm32mp1xx_hal_mdma.c
  ${HALDIR}/src/stm32mp1xx_hal_pwr_ex.c
  ${HALDIR}/src/stm32mp1xx_hal_rcc.c
  ${HALDIR}/src/stm32mp1xx_hal_rcc_ex.c
  ${HALDIR}/src/stm32mp1xx_hal_uart.c
  ${HALDIR}/src/stm32mp1xx_hal_usart.c
  ${HALDIR}/src/stm32mp1xx_ll_rcc.c
  ${HALDIR}/src/stm32mp1xx_ll_tim.c
)

target_include_directories(
  main_m4.elf
  PRIVATE ${FWDIR}/lib/cmsis-device/stm32mp157c/include
          ${FWDIR}/lib/cmsis/Include
          ${HALDIR}/include
          ${DRIVERLIB}
          ${DRIVERLIB}/target/stm32mp1
          ${DRIVERLIB}/target/stm32mp1_cm4
          ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/params
          ${FWDIR}/src/board
          ${M4DIR}
          ${FWDIR}
          ${FWDIR}/lib
          ${FWDIR}/system
)

set_property(TARGET main_m4.elf PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)

target_link_script(main_m4 ${FWDIR}/system/linker/stm32mp15xx_m4.ld -L${FWDIR})

target_link_libraries(main_m4.elf PRIVATE cpputil)
target_compile_definitions(main_m4.elf PRIVATE CPPUTIL_STATIC_STRING_USE_STD_STRING)
