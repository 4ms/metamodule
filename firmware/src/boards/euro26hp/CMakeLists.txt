#
# LVGL
#
set(LV_CONF_PATH
    ${FWDIR}/lib/lvgl/lv_conf.h
    CACHE STRING "" FORCE
)

add_subdirectory(${FWDIR}/lib/lvgl ${CMAKE_CURRENT_BINARY_DIR}/lvgl)

target_link_libraries(lvgl PRIVATE mdrivlib_interface)

target_include_directories(
  lvgl
  PRIVATE ${FWDIR}/lib/lvgl
          ${FWDIR}/lib
          ${FWDIR}/lib/fatfs/source
          ${FWDIR}/src/fs/fatfs
          ${BOARD_SUPPORT_DIR}
)

target_include_directories(lvgl PUBLIC ${FWDIR}/lib/lvgl/lvgl)

target_sources(
  lvgl
  PRIVATE ${PROJECT_SOURCE_DIR}/lib/fatfs/source/ff.c
          ${PROJECT_SOURCE_DIR}/lib/fatfs/source/ffunicode.c
          ${PROJECT_SOURCE_DIR}/src/fs/fatfs/diskio.cc
          ${PROJECT_SOURCE_DIR}/src/fs/fatfs/delete_node.cc
)

set(BOARD_a7_libraries
    lvgl::lvgl ui_lvgl
    PARENT_SCOPE
)

add_subdirectory(${BOARD_SUPPORT_DIR}/gui/ui_lvgl)

#
# Board
#

set(BOARD_a7_sources
    ${FWDIR}/lib/mdrivlib/drivers/codec_PCM3168.cc
    ${BOARD_SUPPORT_DIR}/gui/elements/element_name.cc
    ${BOARD_SUPPORT_DIR}/gui/elements/panel_name.cc
    ${BOARD_SUPPORT_DIR}/gui/ui_lvgl/ui_local.cc
    ${BOARD_SUPPORT_DIR}/gui/fonts/fonts.cc
    ${BOARD_SUPPORT_DIR}/gui/fonts/ttf.cc
    ${BOARD_SUPPORT_DIR}/gui/pages/file_browser/file_browser_adaptor.cc
    ${BOARD_SUPPORT_DIR}/gui/pages/module_view/element_roller.cc
    ${BOARD_SUPPORT_DIR}/gui/pages/module_view/draw_module.cc
    ${BOARD_SUPPORT_DIR}/gui/pages/module_view/quick_assign.cc
    ${BOARD_SUPPORT_DIR}/params/expanders.cc
    ${BOARD_SUPPORT_DIR}/gui/display.cc
    PARENT_SCOPE
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
