#pragma once
#include "gui/fonts/fonts.hh"
#include "gui/helpers/lv_helpers.hh"
#include "lvgl.h"
#include "params/metaparams.hh"

namespace MetaModule
{

struct StatusBar {

	StatusBar() {
		label = lv_label_create(lv_layer_top());
		lv_obj_set_width(label, 100);
		lv_obj_set_height(label, 20);
		lv_obj_set_x(label, 0);
		lv_obj_set_y(label, 0);
		lv_obj_set_align(label, LV_ALIGN_TOP_RIGHT);
		lv_obj_set_flex_flow(label, LV_FLEX_FLOW_ROW);
		lv_obj_set_flex_align(label, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_SPACE_EVENLY);
		lv_label_set_text(label, "");
		lv_obj_clear_flag(label,
						  LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE |
							  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
							  LV_OBJ_FLAG_SCROLL_CHAIN); /// Flags
		lv_obj_set_scrollbar_mode(label, LV_SCROLLBAR_MODE_OFF);
		lv_obj_set_style_text_color(label, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_letter_space(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_line_space(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded50014, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_radius(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(label, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_right(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
		lv_obj_set_style_pad_bottom(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	}

	void show() {
		lv_show(label);
	}

	void hide() {
		lv_hide(label);
	}

	void show_battery(BatteryStatus stat) {
		if (stat.is_charging)
			lv_label_set_text_fmt(label, "Charging: %u%%", stat.level);
		else
			lv_label_set_text_fmt(label, "Battery: %u%%", stat.level);
	}

	lv_obj_t *label;
};

} // namespace MetaModule
