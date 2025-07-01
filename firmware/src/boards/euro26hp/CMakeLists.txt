set(BOARD_bootloader_conf "../board_conf/mmp11_with_expanders_conf.hh")
set(BOARD_dfu_bootloader_conf "board_conf/mmp11_conf.hh")

set(BOARD_a7_sources ${FWDIR}/lib/mdrivlib/drivers/codec_PCM3168.cc)

set(USE_WIFI_MODULE 1)

set(BOARD_a7_defines METAMODULE_ENABLE_WIFI=1)
set(BOARD_m4_defines METAMODULE_ENABLE_WIFI=1)
