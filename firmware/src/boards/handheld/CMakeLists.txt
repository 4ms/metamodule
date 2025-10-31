set(BOARD_bootloader_conf "../board_conf/devboard-v0.2.hh")
set(BOARD_dfu_bootloader_conf "../../board_conf/dfu-devboard-v0.2.hh")

set(BOARD_a7_sources
    ${FWDIR}/lib/mdrivlib/drivers/codec_PCM3060.cc
    ${BOARD_SUPPORT_DIR}/gui/file_browser_adaptor.cc
    ${BOARD_SUPPORT_DIR}/gui/fonts/fonts.cc
    ${BOARD_SUPPORT_DIR}/gui/fonts/ttf.cc
    ${BOARD_SUPPORT_DIR}/gui/4ms-logo-black-h200px.c
)

unset(USE_WIFI_MODULE)
