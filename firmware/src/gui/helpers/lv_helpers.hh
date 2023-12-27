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

} // namespace MetaModule
