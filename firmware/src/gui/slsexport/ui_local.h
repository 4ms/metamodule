#pragma once

#include "meta5/ui.h"

namespace MetaModule
{
inline lv_obj_t *create_plugin_list_item(lv_obj_t *parent, const char *name) {
	lv_obj_t *obj = lv_btn_create(parent);
	lv_obj_set_width(obj, lv_pct(100));
	lv_obj_set_height(obj, 23);
	lv_obj_set_align(obj, LV_ALIGN_LEFT_MID);
	lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_obj_clear_flag(obj,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
						  LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
						  LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
	lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_radius(obj, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(obj, lv_color_hex(0x888888), LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(obj, 64, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(obj, 6, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(obj, 4, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(obj, 2, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(obj, 2, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(obj, lv_color_hex(0xFD8B18), LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(obj, 255, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(obj, 2, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(obj, 1, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(obj, lv_color_hex(0xFD8B18), LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(obj, 255, LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(obj, 2, LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(obj, 1, LV_STATE_FOCUS_KEY);

	lv_obj_t *label = lv_label_create(obj);
	lv_obj_set_width(label, lv_pct(100));
	lv_obj_set_height(label, lv_pct(100));
	lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
	lv_label_set_long_mode(label, LV_LABEL_LONG_DOT);
	lv_label_set_text(label, name);
	lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded70016, LV_STATE_DEFAULT);

	return obj;
}
} // namespace MetaModule
