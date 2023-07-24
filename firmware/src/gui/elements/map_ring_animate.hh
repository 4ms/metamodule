#pragma once
#include "lvgl.h"

namespace MetaModule
{

struct MapRingDisplay {

	enum class Style {
		HideAlways,
		CurModule,
		CurModuleIfPlaying,
		ShowAllIfPlaying,
		ShowAll,
	};

	static void show(lv_obj_t *map_ring) {
		if (!map_ring)
			return;
		lv_obj_set_style_outline_opa(map_ring, LV_OPA_50, LV_STATE_DEFAULT);
	}

	static void hide(lv_obj_t *map_ring) {
		if (!map_ring)
			return;
		lv_obj_set_style_outline_opa(map_ring, LV_OPA_0, LV_STATE_DEFAULT);
	}

	static void flash_once(lv_obj_t *map_ring) {
		if (!map_ring)
			return;

		lv_anim_t a;
		lv_anim_init(&a);
		lv_anim_set_exec_cb(
			&a, (lv_anim_exec_xcb_t)[](void *var, int32_t val) {
				lv_obj_set_style_outline_opa((lv_obj_t *)var, val, LV_STATE_DEFAULT);
			});
		lv_anim_set_var(&a, map_ring);
		lv_anim_set_time(&a, 500);
		lv_anim_set_values(&a, LV_OPA_50, LV_OPA_0);
		lv_anim_set_delay(&a, 200);
		lv_anim_set_path_cb(&a, lv_anim_path_ease_in);
		lv_anim_set_early_apply(&a, true);
		lv_anim_start(&a);
	}
};

} // namespace MetaModule
