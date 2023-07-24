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
	// enum class IsOnHighlightedModule { Yes, No };
	enum class Flash { On, Brighter };

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

	static void flash_once(lv_obj_t *map_ring, Style style, bool on_highlighted_module) {
		using enum Style;
		if (style == CurModuleIfPlaying && on_highlighted_module)
			flash_once(map_ring, Flash::Brighter);

		else if (style == CurModule && on_highlighted_module)
			flash_once(map_ring, Flash::Brighter);

		else if (style == ShowAllIfPlaying)
			flash_once(map_ring, Flash::Brighter);

		else if (style == ShowAll)
			flash_once(map_ring, Flash::Brighter);

		else
			flash_once(map_ring, Flash::On);
	}

	static void flash_once(lv_obj_t *map_ring, Flash flash) {
		if (!map_ring)
			return;

		auto cur_opa = lv_obj_get_style_outline_opa(map_ring, LV_STATE_DEFAULT);

		auto start = LV_OPA_50;
		auto end = LV_OPA_0;
		auto delay = 200;
		auto time = 500;
		if (flash == Flash::Brighter) {
			start = LV_OPA_100;
			end = LV_OPA_50;
			delay = 100;
			time = 100;
		}

		lv_anim_t a;
		lv_anim_init(&a);
		lv_anim_set_exec_cb(
			&a, (lv_anim_exec_xcb_t)[](void *var, int32_t val) {
				lv_obj_set_style_outline_opa((lv_obj_t *)var, val, LV_STATE_DEFAULT);
			});
		lv_anim_set_var(&a, map_ring);
		lv_anim_set_time(&a, time);
		lv_anim_set_values(&a, start, end);
		lv_anim_set_delay(&a, delay);
		lv_anim_set_path_cb(&a, lv_anim_path_ease_in);
		lv_anim_set_early_apply(&a, true);
		lv_anim_start(&a);
	}
};

} // namespace MetaModule
