#
# Embedded images
#

add_subdirectory(images ${CMAKE_BINARY_DIR}/wifi_images)

#
# ESP Serial Flasher
#

set(ESP_SERIAL_FLASHER_PORT "CUSTOM")
set(ESP_SERIAL_FLASHER_ENABLE_MD5 ON)
add_subdirectory(${FWDIR}/lib/esp-serial-flasher ${CMAKE_CURRENT_BINARY_DIR}/esp-serial-flasher)
target_link_libraries(flasher PRIVATE mp15xm4_arch)

# Sources

target_sources(main_m4.elf PRIVATE
    ${WIFI_DIR}/flasher/wifi_update.cc
    ${WIFI_DIR}/flasher/flasher.cpp
    ${WIFI_DIR}/flasher/flasher.h
    ${WIFI_DIR}/flasher/implementation.cpp
    ${WIFI_DIR}/flasher/BufferedUSART.h
    ${WIFI_DIR}/flasher/BufferedUSART.cpp
)

target_link_libraries(main_m4.elf PUBLIC lockfree flasher wifi_images)

