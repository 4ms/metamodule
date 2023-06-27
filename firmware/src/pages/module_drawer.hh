#pragma once
// #include "CoreModules/elements/element_info.hh"
// #include "CoreModules/elements/elements.hh"
#include "CoreModules/moduleFactory.hh"
#include "CoreModules/module_info_base.hh"
#include "images/image_list.hh"
#include "lvgl/lvgl.h"
#include "pages/animated_knob.hh"
#include "pages/elements/base_image.hh"
#include "pages/elements/element_draw_helpers.hh"
#include "pages/elements/element_drawer.hh"
#include "pages/elements/map_ring_drawer.hh"
#include "pages/map_register.hh"
#include "pages/styles.hh"
#include "patch/patch_data.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

struct ModuleDrawer {
	lv_obj_t *container;
	const PatchData &patch;
	uint32_t height;

	ModuleDrawer(lv_obj_t *container, const PatchData &patch, uint32_t height)
		: container{container}
		, patch{patch}
		, height{height} {
	}

	lv_obj_t *draw_with_mappings(uint32_t module_idx, uint8_t *canvas_buffer, Mappings &mappings) {
		auto slug = patch.module_slugs[module_idx];
		const lv_img_dsc_t *img = ModuleImages::get_image_by_slug(slug, height);
		if (!img) {
			printf_("Image not found for %s\n", slug.c_str());
			return nullptr;
		}
		auto widthpx = img->header.w;

		lv_obj_t *canvas = lv_canvas_create(container);
		if (!canvas)
			return nullptr;

		lv_obj_add_style(canvas, &Gui::plain_border_style, LV_STATE_DEFAULT);
		lv_obj_add_flag(canvas, LV_OBJ_FLAG_CLICKABLE);
		lv_obj_clear_flag(canvas, LV_OBJ_FLAG_SCROLLABLE); //inherited from parent?
		lv_obj_add_flag(canvas, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_style(canvas, &Gui::selected_module_style, LV_STATE_FOCUS_KEY);

		lv_obj_set_size(canvas, widthpx, height);
		lv_canvas_set_buffer(canvas, canvas_buffer, widthpx, height, LV_IMG_CF_TRUE_COLOR);

		// Draw module artwork
		lv_draw_img_dsc_t draw_img_dsc;
		lv_draw_img_dsc_init(&draw_img_dsc);
		lv_canvas_draw_img(canvas, 0, 0, img, &draw_img_dsc);

		// Draw module controls
		const auto moduleinfo = ModuleFactory::getModuleInfo2(slug);
		auto center_coords = moduleinfo.uses_center_coords;
		ElementImage images{height};
		ElementDrawer el_drawer{height, canvas, center_coords};
		MapRegister mapper{module_idx, patch, mappings};
		MapRingDrawer ring_drawer{height, canvas, center_coords};

		for (const auto &element : moduleinfo.elements) {
			std::visit(
				[&ring_drawer, &images, &el_drawer, &mapper](auto &el) {
				auto img = images.get_img(el);
				auto obj = el_drawer.draw_element(el, img);
				if (!obj)
					return;

				if (auto panel_param_id = mapper.register_mapping(el, obj)) {
					ring_drawer.draw_mapped_ring(el, obj, img, *panel_param_id);
				}

				mapper.count(el);
				},
				element);
		}

		return canvas;
	}
};

} // namespace MetaModule
