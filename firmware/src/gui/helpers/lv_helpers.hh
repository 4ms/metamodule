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

} // namespace MetaModule
