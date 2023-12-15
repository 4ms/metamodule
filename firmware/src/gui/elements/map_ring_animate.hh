#pragma once
#include "gui/elements/context.hh"
#include "lvgl.h"
#include "src/misc/lv_color.h"

namespace MetaModule
{

struct MapRingDisplay {

	enum class StyleMode {
		HideAlways,
		CurModule,
		CurModuleIfPlaying,
		ShowAllIfPlaying,
		ShowAll,
	};
	struct Style {
		StyleMode mode;
		uint8_t opa = LV_OPA_50;
	};
	enum class Flash { On, Brighter };

	Style style{};

	void set_style(Style new_style) {
		style = new_style;
	}

	static void show(lv_obj_t *map_ring, unsigned opa) {
		if (!map_ring)
			return;
		lv_obj_set_style_outline_opa(map_ring, opa, LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(map_ring, opa, LV_STATE_DEFAULT);

		// Text is only legible if circle opa is > 40%
		if (opa > LV_OPA_40)
			lv_obj_set_style_text_opa(map_ring, LV_OPA_100, LV_STATE_DEFAULT);
		else
			lv_obj_set_style_text_opa(map_ring, LV_OPA_0, LV_STATE_DEFAULT);
	}

	static void hide(lv_obj_t *map_ring) {
		if (!map_ring)
			return;
		lv_obj_set_style_outline_opa(map_ring, LV_OPA_0, LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(map_ring, LV_OPA_0, LV_STATE_DEFAULT);
		lv_obj_set_style_text_opa(map_ring, LV_OPA_0, LV_STATE_DEFAULT);
	}

	// enum class IsOnHighlightedModule { Yes, No };
	// enum class IsPatchPlaying { Yes, No };
	void update(DrawnElement const &drawn_el, bool on_highlighted_module, bool is_patch_playing) {
		// TODO: different behavior depening on Element type
		update(drawn_el.gui_element.map_ring, style, on_highlighted_module, is_patch_playing);
	}

	static void update(lv_obj_t *map_ring, Style style, bool on_highlighted_module, bool is_patch_playing) {
		using enum StyleMode;

		switch (style.mode) {
			case ShowAllIfPlaying:
				if (is_patch_playing)
					MapRingDisplay::show(map_ring, style.opa);
				else
					MapRingDisplay::hide(map_ring);
				break;

			case CurModule:
				if (on_highlighted_module)
					MapRingDisplay::show(map_ring, style.opa);
				else
					MapRingDisplay::hide(map_ring);
				break;

			case CurModuleIfPlaying:
				if (on_highlighted_module && is_patch_playing)
					MapRingDisplay::show(map_ring, style.opa);
				else
					MapRingDisplay::hide(map_ring);
				break;

			case ShowAll:
				MapRingDisplay::show(map_ring, style.opa);
				break;

			case HideAlways:
				MapRingDisplay::hide(map_ring);
				break;
		}
	}

	void flash_once(lv_obj_t *map_ring, bool on_highlighted_module) {
		using enum StyleMode;
		if (style.mode == CurModuleIfPlaying && on_highlighted_module)
			flash_once(map_ring, Flash::Brighter);

		else if (style.mode == CurModule && on_highlighted_module)
			flash_once(map_ring, Flash::Brighter);

		else if (style.mode == ShowAllIfPlaying)
			flash_once(map_ring, Flash::Brighter);

		else if (style.mode == ShowAll)
			flash_once(map_ring, Flash::Brighter);

		else
			flash_once(map_ring, Flash::On);
	}

	static void flash_once(lv_obj_t *map_ring, Flash flash) {
		if (!map_ring)
			return;

		// auto cur_opa = lv_obj_get_style_outline_opa(map_ring, LV_STATE_DEFAULT);

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
				lv_obj_set_style_text_opa((lv_obj_t *)var, val, LV_STATE_DEFAULT);
				lv_obj_set_style_outline_opa((lv_obj_t *)var, val, LV_STATE_DEFAULT);
				lv_obj_set_style_border_opa((lv_obj_t *)var, val, LV_STATE_DEFAULT);
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
