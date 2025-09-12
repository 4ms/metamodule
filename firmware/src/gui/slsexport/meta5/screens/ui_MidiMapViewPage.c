#include "../ui.h"

void ui_MidiMapViewPage_screen_init(void) {
	ui_MidiMapViewPage = lv_obj_create(NULL);
	lv_obj_clear_flag(ui_MidiMapViewPage, LV_OBJ_FLAG_SCROLLABLE); /// Flags
	lv_obj_set_flex_flow(ui_MidiMapViewPage, LV_FLEX_FLOW_ROW_WRAP);
	lv_obj_set_flex_align(ui_MidiMapViewPage, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_obj_set_style_pad_left(ui_MidiMapViewPage, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_MidiMapViewPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_MidiMapViewPage, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_MidiMapViewPage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MidiMapViewCont = lv_obj_create(ui_MidiMapViewPage);
	lv_obj_set_width(ui_MidiMapViewCont, 312);
	lv_obj_set_height(ui_MidiMapViewCont, 232);
	lv_obj_set_x(ui_MidiMapViewCont, 0);
	lv_obj_set_y(ui_MidiMapViewCont, 6);
	lv_obj_set_align(ui_MidiMapViewCont, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_MidiMapViewCont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(ui_MidiMapViewCont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
	lv_obj_clear_flag(ui_MidiMapViewCont,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
						  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
	lv_obj_set_style_radius(ui_MidiMapViewCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui_MidiMapViewCont, lv_color_hex(0x333333), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui_MidiMapViewCont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui_MidiMapViewCont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_recolor(ui_MidiMapViewCont, lv_color_hex(0x666666), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_recolor_opa(ui_MidiMapViewCont, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui_MidiMapViewCont, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui_MidiMapViewCont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui_MidiMapViewCont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui_MidiMapViewCont, lv_color_hex(0x777777), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui_MidiMapViewCont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui_MidiMapViewCont, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ui_MidiMapViewCont, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui_MidiMapViewCont, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui_MidiMapViewCont, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui_MidiMapViewCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_MidiMapViewCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_MidiMapViewCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_MidiMapViewCont, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui_MidiMapViewCont, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui_MidiMapViewCont, 8, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MidiMapLeftColumn = lv_obj_create(ui_MidiMapViewCont);
	lv_obj_remove_style_all(ui_MidiMapLeftColumn);
	lv_obj_set_width(ui_MidiMapLeftColumn, lv_pct(49));
	lv_obj_set_height(ui_MidiMapLeftColumn, lv_pct(100));
	lv_obj_set_align(ui_MidiMapLeftColumn, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_MidiMapLeftColumn, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(ui_MidiMapLeftColumn, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_obj_add_flag(ui_MidiMapLeftColumn, LV_OBJ_FLAG_OVERFLOW_VISIBLE); /// Flags
	lv_obj_add_flag(ui_MidiMapLeftColumn, LV_OBJ_FLAG_SCROLLABLE);		 /// Flags
	lv_obj_clear_flag(ui_MidiMapLeftColumn,
					  LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE |
						  LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE); /// Flags
	lv_obj_set_style_pad_left(ui_MidiMapLeftColumn, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_MidiMapLeftColumn, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_MidiMapLeftColumn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_MidiMapLeftColumn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui_MidiMapLeftColumn, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui_MidiMapLeftColumn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MidiMapInputsTitle = lv_label_create(ui_MidiMapLeftColumn);
	lv_obj_set_width(ui_MidiMapInputsTitle, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(ui_MidiMapInputsTitle, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_MidiMapInputsTitle, LV_ALIGN_CENTER);
	lv_label_set_text(ui_MidiMapInputsTitle, "MIDI Jacks");
	lv_obj_set_style_text_color(ui_MidiMapInputsTitle, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_MidiMapInputsTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_MidiMapInputsTitle, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui_MidiMapInputsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_MidiMapInputsTitle, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui_MidiMapInputsTitle, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_MidiMapInputsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_MidiMapInputsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_MidiMapInputsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MidiMapRightColumn = lv_obj_create(ui_MidiMapViewCont);
	lv_obj_remove_style_all(ui_MidiMapRightColumn);
	lv_obj_set_width(ui_MidiMapRightColumn, lv_pct(49));
	lv_obj_set_height(ui_MidiMapRightColumn, lv_pct(100));
	lv_obj_set_align(ui_MidiMapRightColumn, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(ui_MidiMapRightColumn, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(ui_MidiMapRightColumn, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_obj_clear_flag(ui_MidiMapRightColumn, LV_OBJ_FLAG_CLICKABLE); /// Flags
	lv_obj_add_flag(ui_MidiMapRightColumn, LV_OBJ_FLAG_SCROLLABLE);	 /// Flags
	lv_obj_set_style_pad_row(ui_MidiMapRightColumn, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui_MidiMapRightColumn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

	ui_MidiMapOutputsTitle = lv_label_create(ui_MidiMapRightColumn);
	lv_obj_set_width(ui_MidiMapOutputsTitle, LV_SIZE_CONTENT);	/// 1
	lv_obj_set_height(ui_MidiMapOutputsTitle, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(ui_MidiMapOutputsTitle, LV_ALIGN_CENTER);
	lv_label_set_text(ui_MidiMapOutputsTitle, "MIDI Params");
	lv_obj_set_style_text_color(ui_MidiMapOutputsTitle, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui_MidiMapOutputsTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui_MidiMapOutputsTitle, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui_MidiMapOutputsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui_MidiMapOutputsTitle, &ui_font_MuseoSansRounded70016, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui_MidiMapOutputsTitle, 16, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui_MidiMapOutputsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui_MidiMapOutputsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui_MidiMapOutputsTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}
