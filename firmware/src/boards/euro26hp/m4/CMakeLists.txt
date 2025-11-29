# Todo: move all wifi stuff to separate files, e.g. main() calls board_process() which is defined in
# boards/euro26hp/wifi.cc to process Wifi set(BOARD_a7_defines METAMODULE_ENABLE_WIFI=1) set(BOARD_m4_defines
# METAMODULE_ENABLE_WIFI=1)
set(BOARD_USE_WIFI_MODULE
    1
    PARENT_SCOPE
)
