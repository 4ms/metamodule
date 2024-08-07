#pragma once
#include "lvgl.h"

namespace MetaModule
{

inline void lv_hide(lv_obj_t *obj) {
	lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

inline void lv_show(lv_obj_t *obj) {
	lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

inline void lv_show(lv_obj_t *obj, bool visible) {
	if (visible)
		lv_show(obj);
	else
		lv_hide(obj);
}

inline void lv_disable(lv_obj_t *obj) {
	lv_obj_add_state(obj, LV_STATE_DISABLED);
}

inline void lv_enable(lv_obj_t *obj, bool enabled = true) {
	if (enabled)
		lv_obj_clear_state(obj, LV_STATE_DISABLED);
	else
		lv_disable(obj);
}

inline void lv_enable_all_children(lv_obj_t *obj) {
	auto num_children = lv_obj_get_child_cnt(obj);
	for (unsigned i = 0; i < num_children; i++)
		lv_enable(lv_obj_get_child(obj, i));
}

inline void lv_disable_all_children(lv_obj_t *obj) {
	auto num_children = lv_obj_get_child_cnt(obj);
	for (unsigned i = 0; i < num_children; i++)
		lv_disable(lv_obj_get_child(obj, i));
}

inline void lv_foreach_child(lv_obj_t *obj, auto action) {
	auto num_children = lv_obj_get_child_cnt(obj);
	for (unsigned i = 0; i < num_children; i++) {
		auto child = lv_obj_get_child(obj, i);
		bool should_continue = action(child, i);
		if (!should_continue)
			break;
	}
}

inline void label_scrolls(lv_obj_t *obj) {
	if (lv_obj_get_child_cnt(obj) > 0) {
		lv_label_set_long_mode(lv_obj_get_child(obj, 0), LV_LABEL_LONG_SCROLL);
	}
}

inline void label_clips(lv_obj_t *obj) {
	if (lv_obj_get_child_cnt(obj) > 0) {
		lv_label_set_long_mode(lv_obj_get_child(obj, 0), LV_LABEL_LONG_CLIP);
	}
}

inline void label_overflow_dot(lv_obj_t *obj) {
	if (lv_obj_get_child_cnt(obj) > 0) {
		lv_label_set_long_mode(lv_obj_get_child(obj, 0), LV_LABEL_LONG_DOT);
	}
}

inline void remove_all_event_cb(lv_obj_t *obj) {
	while (lv_obj_remove_event_cb(obj, nullptr))
		;
}

inline void set_content_max_height(lv_obj_t *obj, lv_coord_t max) {
	lv_obj_set_height(obj, LV_SIZE_CONTENT);
	lv_obj_refr_size(obj);
	if (lv_obj_get_height(obj) > max) {
		lv_obj_set_height(obj, max);
	}
}

[[maybe_unused]] inline bool lv_group_activate(lv_group_t *group) {
	auto indev = lv_indev_get_next(nullptr);
	if (indev && group) {
		lv_indev_set_group(indev, group);
		return true;
	}
	return false;
}

inline void lv_uncheck(lv_obj_t *obj) {
	lv_obj_clear_state(obj, LV_STATE_CHECKED);
}

inline void lv_check(lv_obj_t *obj, bool checked = true) {
	if (checked)
		lv_obj_add_state(obj, LV_STATE_CHECKED);
	else
		lv_uncheck(obj);
}

inline lv_obj_t *create_labeled_check_obj(lv_obj_t *parent, const char *name) {
	auto check_panel = lv_obj_create(parent);
	lv_obj_set_height(check_panel, 20);
	lv_obj_set_width(check_panel, LV_SIZE_CONTENT); /// 1
	lv_obj_set_align(check_panel, LV_ALIGN_CENTER);
	lv_obj_set_flex_flow(check_panel, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(check_panel, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_add_flag(check_panel, LV_OBJ_FLAG_OVERFLOW_VISIBLE); /// Flags
	lv_obj_clear_flag(check_panel,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SCROLLABLE |
						  LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
	lv_obj_set_scrollbar_mode(check_panel, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_radius(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(check_panel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(check_panel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(check_panel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(check_panel, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
	auto label = lv_label_create(check_panel);
	lv_obj_set_width(label, LV_SIZE_CONTENT);  /// 1
	lv_obj_set_height(label, LV_SIZE_CONTENT); /// 1
	lv_label_set_text(label, name);
	lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	auto check = lv_switch_create(check_panel);
	lv_obj_set_width(check, 35);
	lv_obj_set_height(check, 20);
	lv_obj_set_align(check, LV_ALIGN_TOP_RIGHT);
	lv_obj_add_flag(check, LV_OBJ_FLAG_SCROLL_ON_FOCUS);  /// Flags
	lv_obj_clear_flag(check, LV_OBJ_FLAG_GESTURE_BUBBLE); /// Flags
	lv_obj_set_style_radius(check, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(check, lv_color_hex(0x202328), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(check, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(check, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(check, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(check, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(check, 1, LV_PART_MAIN | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(check, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_opa(check, 255, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_width(check, 2, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_pad(check, 1, LV_PART_MAIN | LV_STATE_FOCUS_KEY);
	lv_obj_set_style_outline_color(check, lv_color_hex(0xFD8B18), LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(check, 200, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(check, 2, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(check, 1, LV_PART_MAIN | LV_STATE_CHECKED | LV_STATE_FOCUSED);

	lv_obj_set_style_radius(check, 20, LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(check, lv_color_hex(0x4067D3), LV_PART_INDICATOR | LV_STATE_CHECKED);
	lv_obj_set_style_bg_opa(check, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

	lv_obj_set_style_radius(check, 20, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(check, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(check, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(check, -4, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(check, -6, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(check, -5, LV_PART_KNOB | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(check, -5, LV_PART_KNOB | LV_STATE_DEFAULT);
	return check_panel;
}
} // namespace MetaModule
