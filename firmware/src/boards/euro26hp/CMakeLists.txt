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

add_subdirectory(${BOARD_SUPPORT_DIR}/gui/ui_lvgl)

#
# ThorVG (required for CoreModules-4ms)
#
add_subdirectory(${FWDIR}/lib/thorvg ${CMAKE_BINARY_DIR}/thorvg)

#
# Board
#

add_library(board_a7 STATIC)

target_include_directories(
  board_a7
  PRIVATE ${FWDIR}
          ${FWDIR}/src
          ${FWDIR}/src/console
          ${FWDIR}/src/params
          ${FWDIR}/src/fs
          ${FWDIR}/src/core_a7
          ${BOARD_SUPPORT_DIR}
          ${FWDIR}/lib/mdrivlib
          ${FWDIR}/lib/mdrivlib/target/stm32mp1
          ${FWDIR}/lib/mdrivlib/target/stm32mp1_ca7
          ${LIBDIR}
          ${FWDIR}/lib/fatfs/source
          ${FWDIR}/src/fs/fatfs
          ${FWDIR}/lib/cmsis-device/stm32mp157c/include
)

target_sources(
  board_a7
  PRIVATE ${FWDIR}/lib/mdrivlib/drivers/codec_PCM3168.cc
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
          ${FWDIR}/src/patch_play/patch_player_catchup.cc
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

target_compile_definitions(board_a7 PRIVATE CPPUTIL_STATIC_STRING_USE_STD_STRING)

target_include_directories(board_a7 PRIVATE ${FWDIR}/lib/CoreModules/4ms)

target_link_libraries(
  board_a7
  PRIVATE mdrivlib_interface
          core-interface
          rack-interface
          CoreModules
          metamodule::patch-serial
          cpputil
          lvgl::lvgl
          ui_lvgl
          ThorVG
)

set(BOARD_a7_libraries
    lvgl::lvgl
    ui_lvgl
    ThorVG
    board_a7
    PARENT_SCOPE
)
