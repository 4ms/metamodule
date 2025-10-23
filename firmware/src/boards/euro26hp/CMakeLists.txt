set(BOARD_bootloader_conf "../board_conf/mmp11_with_expanders_conf.hh")
set(BOARD_dfu_bootloader_conf "board_conf/mmp11_conf.hh")

set(BOARD_a7_sources
    ${FWDIR}/lib/mdrivlib/drivers/codec_PCM3168.cc
    ${FWDIR}/src/gui/elements/element_name.cc
    ${FWDIR}/src/gui/elements/panel_name.cc
    ${FWDIR}/src/gui/slsexport/ui_local.cc
    ${FWDIR}/src/gui/fonts/fonts.cc
    ${FWDIR}/src/gui/fonts/ttf.cc
    ${FWDIR}/src/gui/pages/file_browser/file_browser_adaptor.cc
    ${FWDIR}/src/params/expanders.cc
)

set(USE_WIFI_MODULE 1)

set(BOARD_a7_defines METAMODULE_ENABLE_WIFI=1)
set(BOARD_m4_defines METAMODULE_ENABLE_WIFI=1)
