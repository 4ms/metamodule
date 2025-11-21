set(BOARD_bootloader_conf "../board_conf/devboard-v0.2.hh")
set(BOARD_dfu_bootloader_conf "../../board_conf/dfu-devboard-v0.2.hh")

set(BOARD_a7_sources
    ${FWDIR}/lib/mdrivlib/drivers/codec_PCM3060.cc
    ${BOARD_SUPPORT_DIR}/gui/file_browser_adaptor.cc
    ${BOARD_SUPPORT_DIR}/gui/fonts/fonts.cc
    ${BOARD_SUPPORT_DIR}/gui/fonts/ttf.cc
    ${BOARD_SUPPORT_DIR}/gui/4ms-logo-black-h200px.c
    ${BOARD_SUPPORT_DIR}/sketch/api.cc
    ${BOARD_SUPPORT_DIR}/sketch/api/framebuffer.cc
    ${BOARD_SUPPORT_DIR}/sketch/api/color_convert.cc
    ${BOARD_SUPPORT_DIR}/sketch/api/color_mode.cc
    ${BOARD_SUPPORT_DIR}/sketch/api/rect.cc
    ${BOARD_SUPPORT_DIR}/sketch/api/ellipse.cc
    ${BOARD_SUPPORT_DIR}/sketch/api/shape.cc
    ${BOARD_SUPPORT_DIR}/sketch/api/matrix.cc
)

unset(USE_WIFI_MODULE)
