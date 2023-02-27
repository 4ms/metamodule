// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: MM

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_Screen1;
void ui_event_media(lv_event_t *e);
lv_obj_t *ui_media;
lv_obj_t *ui_Label2;
lv_obj_t *ui_patchlist;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 1
#error "LV_COLOR_16_SWAP should be 1 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_media(lv_event_t *e) {
	lv_event_code_t event_code = lv_event_get_code(e);
	lv_obj_t *target = lv_event_get_target(e);
	if (event_code == LV_EVENT_VALUE_CHANGED) {
		_ui_roller_set_property(ui_patchlist, _UI_ROLLER_PROPERTY_SELECTED_WITH_ANIM, 3);
	}
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void) {
	ui_Screen1 = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE); /// Flags

	ui_media = lv_roller_create(ui_Screen1);
	lv_roller_set_options(ui_media, "USB Drive\nSD Card\nInternal", LV_ROLLER_MODE_NORMAL);
	lv_obj_set_height(ui_media, 69);
	lv_obj_set_width(ui_media, LV_SIZE_CONTENT); /// 1
	lv_obj_set_x(ui_media, 4);
	lv_obj_set_y(ui_media, -4);
	lv_obj_set_align(ui_media, LV_ALIGN_BOTTOM_LEFT);
	lv_obj_set_flex_flow(ui_media, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(ui_media, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_obj_set_style_text_letter_space(ui_media, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui_media, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_media, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_media, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_Label2 = lv_label_create(ui_Screen1);
	lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT); /// 1
	lv_obj_set_x(ui_Label2, 92);
	lv_obj_set_y(ui_Label2, 8);
	lv_obj_set_flex_flow(ui_Label2, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(ui_Label2, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_label_set_text(ui_Label2, "Select a Patch:");
	lv_obj_set_style_text_font(ui_Label2, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_patchlist = lv_roller_create(ui_Screen1);
	lv_roller_set_options(ui_patchlist,
						  "patch 1\npatch 2\nreally long patch name 3\nanother patch\n4 Sea of Echoes\nAll Real "
						  "4ms\nEnosc Hex\nDjembe 2\n\n5\n",
						  LV_ROLLER_MODE_NORMAL);
	lv_obj_set_width(ui_patchlist, 224);
	lv_obj_set_height(ui_patchlist, 200);
	lv_obj_set_x(ui_patchlist, -4);
	lv_obj_set_y(ui_patchlist, -4);
	lv_obj_set_align(ui_patchlist, LV_ALIGN_BOTTOM_RIGHT);
	lv_obj_set_flex_flow(ui_patchlist, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(ui_patchlist, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);

	lv_obj_add_event_cb(ui_media, ui_event_media, LV_EVENT_ALL, NULL);
}

void ui_init(void) {
	lv_disp_t *dispp = lv_disp_get_default();
	lv_theme_t *theme = lv_theme_default_init(
		dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
	lv_disp_set_theme(dispp, theme);
	ui_Screen1_screen_init();
	lv_disp_load_scr(ui_Screen1);
}
