#
# ESP Serial Flasher
#

set(ESP_SERIAL_FLASHER_PORT "CUSTOM")
set(ESP_SERIAL_FLASHER_ENABLE_MD5
    ON
    CACHE INTERNAL ""
)
add_subdirectory(${FWDIR}/lib/esp-serial-flasher ${CMAKE_CURRENT_BINARY_DIR}/esp-serial-flasher)

# Sources

add_library(
  wifi_flasher STATIC
  flasher.cpp
  flasher.h
  implementation.cpp
  BufferedUSART.h
  BufferedUSART.cpp
)

target_include_directories(
  wifi_flasher
  PRIVATE .
          ${BOARD_SUPPORT_DIR}
          ${FWDIR}/src
          ${FWDIR}/lib
          ${FWDIR}/system
          ${FWDIR}/lib/patch-serial
          ${FWDIR}/src/core_m4
          ${HALDIR}/include
          ${DRIVERLIB}
          ${DRIVERLIB}/target/stm32mp1
          ${DRIVERLIB}/target/stm32mp1_cm4
          ${FWDIR}/lib/cmsis-device/stm32mp157c/include
          ${FWDIR}/lib/cmsis/Include
)

target_link_libraries(wifi_flasher PUBLIC flasher metamodule::core-interface cpputil)
