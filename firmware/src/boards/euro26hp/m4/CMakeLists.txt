# Todo: move all wifi stuff to separate files, e.g. main() calls board_process() which is defined in
# boards/euro26hp/wifi.cc to process Wifi set(BOARD_a7_defines METAMODULE_ENABLE_WIFI=1) set(BOARD_m4_defines
# METAMODULE_ENABLE_WIFI=1)

# Add wifi comm functionality
add_subdirectory(${FWDIR}/src/wifi/comm ${CMAKE_BINARY_DIR}/wifi_comm)

# Add wifi flashing
add_subdirectory(${FWDIR}/src/wifi/flasher ${CMAKE_BINARY_DIR}/wifi_flash)

set(BOARD_m4_libraries wifi_comm wifi_flasher)
