#pragma once
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

namespace MetaModule
{

struct ModuleDrawer {
	lv_obj_t *container;
	uint32_t height;

	// Draws the module from patch, into container, using the provided buffer.
	std::pair<uint32_t, lv_obj_t *> draw_faceplate(ModuleTypeSlug slug, std::span<lv_color_t> canvas_buffer) {
		const lv_img_dsc_t *img = ModuleImages::get_image_by_slug(slug, height);
		if (!img) {
			printf_("Image not found for %s\n", slug.c_str());
			return {0, nullptr};
		}
		auto widthpx = img->header.w;
		if ((widthpx * height) > canvas_buffer.size()) {
			printf_("Buffer not big enough for %dpx, not drawing\n", widthpx);
			return {0, nullptr};
		}

		lv_obj_t *canvas = lv_canvas_create(container);
		if (!canvas)
			return {0, nullptr};

		lv_obj_set_size(canvas, widthpx, height);
		lv_canvas_set_buffer(canvas, canvas_buffer.data(), widthpx, height, LV_IMG_CF_TRUE_COLOR);

		// Draw module artwork
		lv_draw_img_dsc_t draw_img_dsc;
		lv_draw_img_dsc_init(&draw_img_dsc);
		lv_canvas_draw_img(canvas, 0, 0, img, &draw_img_dsc);

		return {widthpx, canvas};
	}

	std::vector<lv_obj_t *> draw_elements(ModuleTypeSlug slug, lv_obj_t *canvas) {
		// Draw elements:
		const auto moduleinfo = ModuleFactory::getModuleInfo2(slug);
		auto center_coords = moduleinfo.uses_center_coords;
		ElementImage images{height};
		ElementDrawer el_drawer{height, canvas, center_coords};

		std::vector<lv_obj_t *> drawn_elements;

		for (const auto &element : moduleinfo.elements) {
			auto drawn = std::visit(
				[&images, &el_drawer](auto &el) -> auto {
					auto img = images.get_img(el);
					auto obj = el_drawer.draw_element(el, img);
					return obj;
				},
				element);
			drawn_elements.push_back(drawn);
		}

		return drawn_elements;
	}

	// Draws the mapping rings for module_idx with in patch, onto the canvas object
	// Appends the mapping info to the Mappings vector
	void draw_mappings(const PatchData &patch,
					   uint32_t module_idx,
					   lv_obj_t *canvas,
					   const std::vector<lv_obj_t *> &objs,
					   Mappings &mappings) {
		auto slug = patch.module_slugs[module_idx];

		// Draw module controls
		const auto moduleinfo = ModuleFactory::getModuleInfo2(slug);
		auto center_coords = moduleinfo.uses_center_coords;
		MapRegister mapper{module_idx, patch, mappings};
		MapRingDrawer ring_drawer{height, canvas, center_coords};

		unsigned i = 0;
		for (const auto &element : moduleinfo.elements) {
			std::visit(
				[&ring_drawer, &mapper, &objs, &i](auto &el) {
				auto obj = objs[i];
				if (!obj)
					return;
				if (auto panel_param_id = mapper.register_mapping(el, obj))
					ring_drawer.draw_mapped_ring(el, obj, *panel_param_id);
				},
				element);
			i++;
		}
	}

	// Draws the mapping rings for module_idx with in patch, onto the canvas object
	// Also appends the mapping info to the Mappings vector
	void draw_mapped_elements(const PatchData &patch, uint32_t module_idx, lv_obj_t *canvas, Mappings &mappings) {
		auto slug = patch.module_slugs[module_idx];

		// Draw module controls
		const auto moduleinfo = ModuleFactory::getModuleInfo2(slug);
		auto center_coords = moduleinfo.uses_center_coords;
		ElementImage images{height};
		ElementDrawer el_drawer{height, canvas, center_coords};
		MapRegister mapper{module_idx, patch, mappings};
		MapRingDrawer ring_drawer{height, canvas, center_coords};

		unsigned element_idx = 0;
		for (const auto &element : moduleinfo.elements) {
			std::visit(
				[&ring_drawer, &images, &el_drawer, &mapper, &element_idx](auto &el) {
				auto img = images.get_img(el);
				auto obj = el_drawer.draw_element(el, img);
				if (obj) {
					if (auto panel_param_id = mapper.register_mapping(el, obj))
						ring_drawer.draw_mapped_ring(el, obj, *panel_param_id);
				}
				// auto de = DrawnElement{obj, element_idx++, 0/*param_idx?*/, panel_param_id};
				},
				element);
		}
	}
};

} // namespace MetaModule
