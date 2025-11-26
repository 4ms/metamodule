set(BOARD_bootloader_conf "../board_conf/mmp11_with_expanders_conf.hh")
set(BOARD_dfu_bootloader_conf "board_conf/mmp11_conf.hh")

set(BOARD_a7_sources
    ${FWDIR}/lib/mdrivlib/drivers/codec_PCM3168.cc
    ${BOARD_SUPPORT_DIR}/gui/elements/element_name.cc
    ${BOARD_SUPPORT_DIR}/gui/elements/panel_name.cc
    ${BOARD_SUPPORT_DIR}/gui/ui_lvgl/ui_local.cc
    ${BOARD_SUPPORT_DIR}/gui/fonts/fonts.cc
    ${BOARD_SUPPORT_DIR}/gui/fonts/ttf.cc
    ${BOARD_SUPPORT_DIR}/gui/pages/file_browser/file_browser_adaptor.cc
    ${BOARD_SUPPORT_DIR}/params/expanders.cc
    ${BOARD_SUPPORT_DIR}/gui/pages/module_view/element_roller.cc
    ${BOARD_SUPPORT_DIR}/gui/pages/module_view/draw_module.cc
    ${BOARD_SUPPORT_DIR}/gui/pages/module_view/quick_assign.cc
)

set_source_files_properties(
  ${BOARD_SUPPORT_DIR}/gui/elements/element_name.cc
  ${BOARD_SUPPORT_DIR}/gui/ui_lvgl/ui_local.cc
  ${BOARD_SUPPORT_DIR}/gui/pages/module_view/draw_module.cc
  ${BOARD_SUPPORT_DIR}/gui/pages/module_view/element_roller.cc
  ${BOARD_SUPPORT_DIR}/gui/pages/module_view/quick_assign.cc
  ${BOARD_SUPPORT_DIR}/gui/fonts/fonts.cc
  ${BOARD_SUPPORT_DIR}/gui/fonts/ttf.cc
  ${BOARD_SUPPORT_DIR}/gui/pages/file_browser/file_browser_adaptor.cc
  PROPERTIES COMPILE_OPTIONS "-Wno-deprecated-enum-enum-conversion;-Wno-deprecated-anon-enum-enum-conversion;"
)

set(USE_WIFI_MODULE 1)

set(BOARD_a7_defines METAMODULE_ENABLE_WIFI=1)
set(BOARD_m4_defines METAMODULE_ENABLE_WIFI=1)

add_subdirectory(${BOARD_SUPPORT_DIR}/gui/ui_lvgl)
