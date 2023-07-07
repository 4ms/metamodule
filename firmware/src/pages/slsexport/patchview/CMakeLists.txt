SET(SOURCES components/ui_comp_buttons_2.c
    components/ui_comp_buttons_3.c
    components/ui_comp.c
    screens/ui_PatchView.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    images/ui_img_symbols_raw_light_play_light1_png.c
    images/ui_img_symbols_raw_play_dark1_png.c
    images/ui_img_symbols_raw_light_knob_light1_png.c
    images/ui_img_symbols_raw_knob_dark1_png.c
    images/ui_img_symbols_raw_light_plus_light1_png.c
    images/ui_img_symbols_raw_plus_dark1_png.c
    images/ui_img_symbols_raw_light_info_light3_png.c
    images/ui_img_symbols_raw_info_dark3_png.c
    images/ui_img_symbols_raw_light_settings_light27_png.c
    images/ui_img_symbols_raw_settings_dark27_png.c
    images/ui_img_symbols_raw_light_info_light1_png.c
    images/ui_img_symbols_raw_light_info_light2_png.c
    images/ui_img_symbols_raw_light_info_light4_png.c
    images/ui_img_symbols_raw_light_knob_light2_png.c
    images/ui_img_symbols_raw_light_knob_light3_png.c
    images/ui_img_symbols_raw_light_play_light2_png.c
    images/ui_img_symbols_raw_light_plus_light2_png.c
    images/ui_img_symbols_raw_light_settings_light2_png.c
    images/ui_img_symbols_raw_info_dark1_png.c
    images/ui_img_symbols_raw_info_dark2_png.c
    images/ui_img_symbols_raw_info_dark4_png.c
    images/ui_img_symbols_raw_knob_dark2_png.c
    images/ui_img_symbols_raw_knob_dark3_png.c
    images/ui_img_symbols_raw_play_dark2_png.c
    images/ui_img_symbols_raw_plus_dark2_png.c
    images/ui_img_symbols_raw_settings_dark2_png.c
    fonts/ui_font_Arial_16_bpp4.c
    fonts/ui_font_Arial_bpp2.c)

add_library(ui ${SOURCES})
