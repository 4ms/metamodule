file(GLOB font_sources ${BOARD_SUPPORT_DIR}/gui/fonts/fonts/*.c)

add_library(ui_lvgl STATIC ${font_sources})

target_include_directories(ui_lvgl PRIVATE ${FWDIR}/lib/lvgl)
