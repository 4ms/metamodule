set(BOARD_bootloader_conf "../board_conf/handheld-p1.hh")
set(BOARD_dfu_bootloader_conf "../../board_conf/dfu-handheld-p1.hh")

set(BOARD_a7_sources ${FWDIR}/lib/mdrivlib/drivers/codec_TAC5211.cc)

set(BOARD_m4_defines METAMODULE_USE_BATTERY_GUAGE=1)

unset(USE_WIFI_MODULE)
