# Add wifi comm functionality
add_subdirectory(${FWDIR}/src/wifi/comm ${CMAKE_BINARY_DIR}/wifi_comm)

# Add wifi flashing
add_subdirectory(${FWDIR}/src/wifi/flasher ${CMAKE_BINARY_DIR}/wifi_flash)

set(BOARD_m4_libraries wifi_comm wifi_flasher)
