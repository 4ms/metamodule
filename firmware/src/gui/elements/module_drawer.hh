#pragma once
#include "CoreModules/elements/elements_index.hh"
#include "CoreModules/moduleFactory.hh"
#include "gui/elements/context.hh"
#include "gui/elements/draw.hh"
#include "gui/elements/map_ring_drawer.hh"
#include "gui/elements/mapping.hh"
#include "gui/images/faceplate_images.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch/patch_data.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

struct ModuleDrawer {
	lv_obj_t *container;
	uint32_t height;

	// Draws the module from patch, into container, using the provided buffer.
	lv_obj_t *draw_faceplate(ModuleTypeSlug slug, std::span<lv_color_t> canvas_buffer) {
		const lv_img_dsc_t *img = ModuleImages::get_image_by_slug(slug);
		if (!img) {
			if (!slug.is_equal("HubMedium"))
				pr_warn("Image not found for %s\n", slug.c_str());
			return nullptr;
		}

		float zoom = height / 240.f;

		uint32_t widthpx = img->header.w * zoom;
		if ((widthpx * height) > canvas_buffer.size()) {
			pr_warn("Buffer not big enough for %dpx x %dpx (%zu avail), not drawing\n",
					widthpx,
					height,
					canvas_buffer.size());
			return nullptr;
		}

		lv_obj_t *canvas = lv_canvas_create(container);
		if (!canvas) {
			pr_warn("Failed to create module canvas object\n");
			return nullptr;
		}

		lv_obj_set_size(canvas, widthpx, height);
		lv_canvas_set_buffer(canvas, canvas_buffer.data(), widthpx, height, LV_IMG_CF_TRUE_COLOR);

		// Draw module artwork
		lv_draw_img_dsc_t draw_img_dsc;
		lv_draw_img_dsc_init(&draw_img_dsc);
		draw_img_dsc.zoom = zoom * 256;

		pr_trace("Drawing faceplate %s (%d x %d)\n", slug.data(), widthpx, height);

		lv_canvas_draw_img(canvas, 0, 0, img, &draw_img_dsc);
		// Overflow visible: requires too much processing when zoomed-out to view lots of modules
		if (height == 240)
			lv_obj_add_flag(canvas, LV_OBJ_FLAG_OVERFLOW_VISIBLE);
		else
			lv_obj_clear_flag(canvas, LV_OBJ_FLAG_OVERFLOW_VISIBLE);

		return canvas;
	}

	// Draws the mapping rings for module_idx with in patch, onto the canvas object
	// Also appends the DrawnElement info to the given vector
	void draw_mapped_elements(const PatchData &patch,
							  uint32_t module_idx,
							  uint32_t active_knob_set,
							  lv_obj_t *canvas,
							  std::vector<DrawnElement> &drawn_elements,
							  bool draw_rings = true) {

		auto slug = patch.module_slugs[module_idx];

		// Draw module controls
		const auto moduleinfo = ModuleFactory::getModuleInfo(slug);

		//Reserve enough for what we will append
		drawn_elements.reserve(drawn_elements.size() + moduleinfo.elements.size());

		ElementCount::Indices indices{};
		for (const auto &element : moduleinfo.elements) {
			auto element_ctx = std::visit(
				[height = height, &patch, &indices, module_idx, canvas, active_knob_set](auto &el) -> GuiElement {
					auto obj = ElementDrawer::draw_element(el, canvas, height);
					auto mapping_id = ElementMapping::find_mapping(el, patch, module_idx, active_knob_set, indices);
					auto mapped_ring = MapRingDrawer::draw_mapped_ring(el, obj, canvas, mapping_id, height);

					auto count = ElementCount::count(el);

					// For each member of count that's 0, mark the corresponding member of indices as not being an element of that type
					// See tests/element_tests.cc SUBCASE("Some indices are invalid if the type does not match")
					auto el_idx = indices;
					if (count.num_params == 0)
						el_idx.param_idx = ElementCount::Indices::NoElementMarker;
					if (count.num_inputs == 0)
						el_idx.input_idx = ElementCount::Indices::NoElementMarker;
					if (count.num_outputs == 0)
						el_idx.output_idx = ElementCount::Indices::NoElementMarker;
					if (count.num_lights == 0)
						el_idx.light_idx = ElementCount::Indices::NoElementMarker;

					auto element_ctx = GuiElement{obj, mapped_ring, (uint16_t)module_idx, count, el_idx, mapping_id};

					indices = indices + count;
					return element_ctx;
				},
				element);
			drawn_elements.push_back({element_ctx, element});
		}
	}
};

} // namespace MetaModule
