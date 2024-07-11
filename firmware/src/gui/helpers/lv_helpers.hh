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

inline void lv_enable(lv_obj_t *obj) {
	lv_obj_clear_state(obj, LV_STATE_DISABLED);
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

void lv_uncheck(lv_obj_t *obj) {
	lv_obj_clear_state(obj, LV_STATE_CHECKED);
}

void lv_check(lv_obj_t *obj, bool checked = true) {
	if (checked)
		lv_obj_add_state(obj, LV_STATE_CHECKED);
	else
		lv_uncheck(obj);
}
} // namespace MetaModule
