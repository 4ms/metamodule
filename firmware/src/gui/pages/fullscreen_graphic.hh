#pragma once
#include "gui/dyn_display_drawer.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"

namespace MetaModule
{

struct FullscreenGraphicPage : PageBase {

	FullscreenGraphicPage(PatchContext info)
		: PageBase{info, PageId::FullscreenGraphic} {

		screen = lv_obj_create(NULL);
		lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_opa(screen, LV_OPA_100, LV_PART_MAIN);
		lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN);
		lv_obj_set_size(screen, 320, 240);
		lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);
		lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
		lv_obj_set_style_outline_width(screen, 0, LV_PART_MAIN);

		canvas = lv_canvas_create(screen);

		init_bg(screen);
	}

	void init(float width_mm, float height_mm) {
		if (args.module_id && args.element_indices) {
			if (args.element_indices->light_idx != ElementCount::Indices::NoElementMarker) {

				const float ratio = width_mm / height_mm;
				const float screen_ratio = 320.f / 240.f;
				uint16_t w = (ratio >= screen_ratio) ? 320 : std::round(240 * ratio);
				uint16_t h = (ratio <= screen_ratio) ? 240 : std::round(320 / ratio);

				lv_obj_set_size(canvas, w, h);

				dyn_drawer = std::make_unique<DynamicDisplayDrawer>(
					patch_playloader, *args.module_id, args.element_indices->light_idx, width_mm, height_mm, canvas);
			}
		}
		dynamic_elements_prepared = false;
	}

	void prepare_focus() final {
		if (!patch_is_playing(args.patch_loc_hash))
			return;

		// if (!args.module_id.has_value() || !args.element_indices.has_value())
		// 	return;

		// if (args.element_indices->light_idx == ElementCount::Indices::NoElementMarker)
		// 	return;

		// auto patch = patches.get_playing_patch();
		// if (!patch)
		// 	return;

		// if (*args.module_id >= patch->module_slugs.size())
		// 	return;

		// auto const &slug = patch->module_slugs[*args.module_id];
		// auto const &info = ModuleFactory::getModuleInfo(slug);
	}

	void update() final {
		if (gui_state.back_button.is_just_released()) {
			page_list.request_last_page();
		}

		if (dyn_drawer) {
			prepare_dynamic_elements();
			dyn_drawer->draw();
		}
	}

	void blur() final {
		if (dyn_drawer)
			dyn_drawer->blur();
	}

private:
	void prepare_dynamic_elements() {
		if (!dynamic_elements_prepared) {
			dyn_drawer->prepare(screen);
			dynamic_elements_prepared = true;
		}
	}

	lv_obj_t *screen;
	lv_obj_t *canvas;

	std::unique_ptr<DynamicDisplayDrawer> dyn_drawer{};

	bool dynamic_elements_prepared = false;
};

} // namespace MetaModule
