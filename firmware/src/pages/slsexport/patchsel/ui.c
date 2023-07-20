// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: MM

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_PatchSelector;
lv_obj_t *ui_Title;
lv_obj_t *ui_mediapanel;
lv_obj_t *ui_USBbut;
lv_obj_t *ui_USBlabel;
lv_obj_t *ui_SDbut;
lv_obj_t *ui_SDlabel;
lv_obj_t *ui_Flashbut;
lv_obj_t *ui_Flashlabel;
lv_obj_t *ui_patchlist;
lv_obj_t *ui_waitspinner;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
#error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP != 0
#error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_PatchSelector_screen_init(void) {
	ui_PatchSelector = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_PatchSelector, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_flex_flow(ui_PatchSelector, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(ui_PatchSelector, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END);
	lv_obj_set_style_pad_left(ui_PatchSelector, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_PatchSelector, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_PatchSelector, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_PatchSelector, 4, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_Title = lv_label_create(ui_PatchSelector);
	lv_obj_set_width(ui_Title, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(ui_Title, LV_SIZE_CONTENT); /// 1
	lv_obj_set_x(ui_Title, 92);
	lv_obj_set_y(ui_Title, 8);
	lv_obj_set_flex_flow(ui_Title, LV_FLEX_FLOW_COLUMN_WRAP_REVERSE);
	lv_obj_set_flex_align(ui_Title, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_BETWEEN);
	lv_label_set_text(ui_Title, "Select a Patch:");
	lv_obj_set_style_text_font(ui_Title, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_mediapanel = lv_obj_create(ui_PatchSelector);
	lv_obj_set_height(ui_mediapanel, 71);
	lv_obj_set_flex_grow(ui_mediapanel, 1);
	lv_obj_set_align(ui_mediapanel, LV_ALIGN_LEFT_MID);
	lv_obj_set_flex_flow(ui_mediapanel, LV_FLEX_FLOW_ROW_WRAP);
	lv_obj_set_flex_align(ui_mediapanel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_SPACE_AROUND);
	lv_obj_add_flag(ui_mediapanel, LV_OBJ_FLAG_FLEX_IN_NEW_TRACK); /// Flags
	lv_obj_clear_flag(ui_mediapanel,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_scrollbar_mode(ui_mediapanel, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_pad_left(ui_mediapanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_mediapanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_mediapanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_mediapanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui_mediapanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui_mediapanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_USBbut = lv_btn_create(ui_mediapanel);
	lv_obj_set_height(ui_USBbut, 20);
	lv_obj_set_width(ui_USBbut, lv_pct(100));
	lv_obj_set_x(ui_USBbut, -153);
	lv_obj_set_y(ui_USBbut, 43);
	lv_obj_set_align(ui_USBbut, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_USBbut,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
						  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_radius(ui_USBbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_USBbut, lv_color_hex(0x292831), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_USBbut, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui_USBbut, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_USBbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_USBbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_USBbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_USBbut, lv_color_hex(0xFF9800), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui_USBbut, 255, LV_PART_MAIN | LV_STATE_CHECKED);

	ui_USBlabel = lv_label_create(ui_USBbut);
	lv_obj_set_width(ui_USBlabel, LV_SIZE_CONTENT);	 /// 1
	lv_obj_set_height(ui_USBlabel, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_USBlabel, LV_ALIGN_LEFT_MID);
	lv_label_set_long_mode(ui_USBlabel, LV_LABEL_LONG_CLIP);
	lv_label_set_text(ui_USBlabel, "USB");
	lv_obj_set_style_text_font(ui_USBlabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_SDbut = lv_btn_create(ui_mediapanel);
	lv_obj_set_height(ui_SDbut, 20);
	lv_obj_set_width(ui_SDbut, lv_pct(100));
	lv_obj_set_x(ui_SDbut, -153);
	lv_obj_set_y(ui_SDbut, 43);
	lv_obj_set_align(ui_SDbut, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_SDbut,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
						  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_radius(ui_SDbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_SDbut, lv_color_hex(0x292831), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_SDbut, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui_SDbut, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_SDbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_SDbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_SDbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_SDbut, lv_color_hex(0xFF9800), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui_SDbut, 255, LV_PART_MAIN | LV_STATE_CHECKED);

	ui_SDlabel = lv_label_create(ui_SDbut);
	lv_obj_set_width(ui_SDlabel, LV_SIZE_CONTENT);	/// 1
	lv_obj_set_height(ui_SDlabel, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_SDlabel, LV_ALIGN_LEFT_MID);
	lv_label_set_long_mode(ui_SDlabel, LV_LABEL_LONG_CLIP);
	lv_label_set_text(ui_SDlabel, " Card");
	lv_obj_set_style_text_font(ui_SDlabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_Flashbut = lv_btn_create(ui_mediapanel);
	lv_obj_set_height(ui_Flashbut, 20);
	lv_obj_set_width(ui_Flashbut, lv_pct(100));
	lv_obj_set_x(ui_Flashbut, -153);
	lv_obj_set_y(ui_Flashbut, 43);
	lv_obj_set_align(ui_Flashbut, LV_ALIGN_CENTER);
	lv_obj_clear_flag(ui_Flashbut,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
						  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_radius(ui_Flashbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_Flashbut, lv_color_hex(0x292831), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_Flashbut, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui_Flashbut, 8, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_Flashbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_Flashbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_Flashbut, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_Flashbut, lv_color_hex(0xFF9800), LV_PART_MAIN | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(ui_Flashbut, 255, LV_PART_MAIN | LV_STATE_CHECKED);

	ui_Flashlabel = lv_label_create(ui_Flashbut);
	lv_obj_set_width(ui_Flashlabel, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(ui_Flashlabel, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_Flashlabel, LV_ALIGN_LEFT_MID);
	lv_label_set_long_mode(ui_Flashlabel, LV_LABEL_LONG_CLIP);
	lv_label_set_text(ui_Flashlabel, " Internal");
	lv_obj_set_style_text_font(ui_Flashlabel, &lv_font_montserrat_10, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_patchlist = lv_roller_create(ui_PatchSelector);
	lv_roller_set_options(ui_patchlist,
						  "patch 1\npatch 2\nreally long patch name 3\nanother patch\n4 Sea of Echoes\nAll Real "
						  "4ms\nEnosc Hex\nDjembe 2\n\n5\n",
						  LV_ROLLER_MODE_NORMAL);
	lv_obj_set_height(ui_patchlist, 200);
	lv_obj_set_flex_grow(ui_patchlist, 3);
	lv_obj_set_x(ui_patchlist, -4);
	lv_obj_set_y(ui_patchlist, -4);
	lv_obj_set_align(ui_patchlist, LV_ALIGN_BOTTOM_RIGHT);
	lv_obj_set_style_text_letter_space(ui_patchlist, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui_patchlist, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui_patchlist, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(ui_patchlist, lv_color_hex(0xFF9800), LV_PART_SELECTED | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_patchlist, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

	ui_waitspinner = lv_spinner_create(ui_PatchSelector, 1000, 90);
	lv_obj_set_width(ui_waitspinner, 65);
	lv_obj_set_height(ui_waitspinner, 67);
	lv_obj_set_align(ui_waitspinner, LV_ALIGN_CENTER);
	lv_obj_add_flag(ui_waitspinner, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_IGNORE_LAYOUT | LV_OBJ_FLAG_FLOATING); /// Flags
	lv_obj_clear_flag(ui_waitspinner,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
						  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_arc_color(ui_waitspinner, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui_waitspinner, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_arc_color(ui_waitspinner, lv_color_hex(0xA9A9A9), LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_opa(ui_waitspinner, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
	lv_obj_set_style_arc_width(ui_waitspinner, 10, LV_PART_INDICATOR | LV_STATE_DEFAULT);
}

// void ui_init( void )
// {
// lv_disp_t *dispp = lv_disp_get_default();
// lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
// lv_disp_set_theme(dispp, theme);
// ui_PatchSelector_screen_init();
// lv_disp_load_scr( ui_PatchSelector);
// }
