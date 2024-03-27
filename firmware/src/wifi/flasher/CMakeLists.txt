#
# ESP Serial Flasher
#

set(ESP_SERIAL_FLASHER_PORT "CUSTOM")
set(ESP_SERIAL_FLASHER_ENABLE_MD5 ON CACHE INTERNAL "")
add_subdirectory(${FWDIR}/lib/esp-serial-flasher ${CMAKE_CURRENT_BINARY_DIR}/esp-serial-flasher)


# Sources

target_sources(main_m4.elf PRIVATE
    flasher.cpp
    flasher.h
    implementation.cpp
    BufferedUSART.h
    BufferedUSART.cpp
)

target_include_directories(main_m4.elf PRIVATE .)

target_link_libraries(main_m4.elf PUBLIC flasher)

