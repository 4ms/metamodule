#pragma once
#include "gui/dyn_display_drawer.hh"
#include "gui/helpers/lv_helpers.hh"
#include "gui/pages/base.hh"
#include "gui/pages/page_list.hh"

#include "conf/screen_buffer_conf.hh"

namespace MetaModule
{

struct FullscreenGraphicPage : PageBase {

	FullscreenGraphicPage(PatchContext info)
		: PageBase{info, PageId::FullscreenGraphic} {

		screen = lv_obj_create(NULL);
		lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_opa(screen, LV_OPA_100, LV_PART_MAIN);
		lv_obj_set_style_bg_color(screen, lv_color_black(), LV_PART_MAIN);
		lv_obj_set_size(screen, ScreenBufferConf::viewWidth, ScreenBufferConf::viewHeight);
		lv_obj_set_style_pad_all(screen, 0, LV_PART_MAIN);
		lv_obj_set_style_border_width(screen, 0, LV_PART_MAIN);
		lv_obj_set_style_outline_width(screen, 0, LV_PART_MAIN);

		canvas = lv_canvas_create(screen);
		lv_obj_clear_flag(canvas, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_set_style_bg_color(canvas, lv_color_hex(0x110000), LV_PART_MAIN);
		lv_obj_set_style_bg_opa(canvas, LV_OPA_100, LV_PART_MAIN);

		init_bg(screen);

		base_canvas = lv_canvas_create(screen);
		lv_obj_set_size(base_canvas, 1, 1);
		lv_show(base_canvas, false);
	}

	void prepare_focus() final {
		if (!args.module_id.has_value())
			return;

		// Get first graphic display
		auto patch = patches.get_playing_patch();
		auto slug = patch->module_slugs[args.module_id.value()];
		auto info = ModuleFactory::getModuleInfo(slug);
		for (auto [idx, el] : zip(info.indices, info.elements)) {
			if (auto disp = std::get_if<DynamicGraphicDisplay>(&el)) {
				if (disp->width_mm > 0 && disp->height_mm > 0) {
					pr_dbg("Found DynamicGraphicDisplay idx %u x %f y %f\n",
						   idx.light_idx,
						   disp->width_mm,
						   disp->height_mm);
					args.element_mm = {disp->width_mm, disp->height_mm};
					args.element_indices = ElementCount::Indices{.light_idx = idx.light_idx};
				}
			}
		}

		if (!args.element_indices.has_value())
			return;

		if (args.element_indices->light_idx == ElementCount::Indices::NoElementMarker)
			return;

		if (!args.element_mm)
			return;

		auto width_mm = args.element_mm->first;
		auto height_mm = args.element_mm->second;

		const float ratio = width_mm / height_mm;
		const float screen_ratio = (float)ScreenBufferConf::viewWidth / ScreenBufferConf::viewHeight;
		uint16_t w =
			(ratio >= screen_ratio) ? ScreenBufferConf::viewWidth : std::round(ScreenBufferConf::viewHeight * ratio);
		uint16_t h =
			(ratio <= screen_ratio) ? ScreenBufferConf::viewHeight : std::round(ScreenBufferConf::viewWidth / ratio);

		pr_dbg("Actual size (light_idx %u): %u x %u\n", args.element_indices.value(), w, h);
		lv_obj_set_size(canvas, w, h);

		// Debug border:
		// lv_obj_set_style_border_width(canvas, 1, LV_PART_MAIN);
		// lv_obj_set_style_border_color(canvas, lv_color_hex(0xff0000), LV_PART_MAIN);
		// lv_obj_set_style_border_opa(canvas, LV_OPA_50, LV_PART_MAIN);

		lv_obj_align(canvas, LV_ALIGN_CENTER, 0, 0);
		lv_obj_refr_size(canvas);
		lv_obj_update_layout(canvas);

		dyn_drawer = std::make_unique<DynamicDisplayDrawer>(patch_playloader, *args.module_id);

		find_base_module(*args.module_id);

		dyn_drawer->add_display(args.element_indices->light_idx, width_mm, height_mm, canvas);

		dynamic_elements_prepared = false;
	}

	void update() final {
		// pos_x = (pos_x + 6) % 400;
		// pos_y = (pos_y + 6) % 960;
		// lv_obj_set_pos(test, pos_x, pos_y);

		if (dyn_drawer) {
			prepare_dynamic_elements();
			dyn_drawer->draw();
		}
	}

	void blur() final {
		if (dyn_drawer) {
			dyn_drawer->blur();

			if (canvas && lv_obj_is_valid(canvas)) {
				lv_foreach_child(canvas, [](lv_obj_t *child, unsigned id) {
					if (child && lv_obj_is_valid(child))
						lv_obj_del_async(child);
				});

				if (lv_canvas_get_img(canvas)) {
					lv_canvas_fill_bg(canvas, lv_color_black(), LV_OPA_100);
				}
			}
		}
	}

private:
	void prepare_dynamic_elements() {
		if (!dynamic_elements_prepared) {
			dyn_drawer->prepare(screen);
			dynamic_elements_prepared = true;
		}
	}

	void find_base_module(unsigned module_id) {
		if (patch_is_playing(args.patch_loc_hash)) {
			auto patch = patches.get_playing_patch();
			auto slug = module_id < patch->module_slugs.size() ? patch->module_slugs[module_id] : "";

			auto const &info = ModuleFactory::getModuleInfo(slug);

			for (auto i = 0u; auto const &el : info.elements) {
				if (auto *graphic = std::get_if<DynamicGraphicDisplay>(&el)) {
					if (graphic->full_module) {
						dyn_drawer->add_display(info.indices[i].light_idx, 0, 0, base_canvas);
					}
				}
				i++;
			}
		}
	}

	lv_obj_t *screen;
	lv_obj_t *canvas;

	lv_obj_t *base_canvas;

	// lv_obj_t *test;
	// int pos_x = 0;
	// int pos_y = 0;

	std::unique_ptr<DynamicDisplayDrawer> dyn_drawer{};

	bool dynamic_elements_prepared = false;
};

} // namespace MetaModule
