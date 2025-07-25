#pragma once
#include "CoreModules/moduleFactory.hh"
#include "gui/elements/context.hh"
#include "gui/elements/draw.hh"
#include "gui/elements/map_ring_drawer.hh"
#include "gui/elements/mapping.hh"
#include "gui/images/paths.hh"
#include "patch/patch_data.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

struct ModuleDrawer {
	enum Error { FaceplateNotFound, CantDecodeFaceplateFile, BufferTooSmall, CanvasCreateFailed };

	lv_obj_t *container;
	uint32_t height;

	// Returns faceplate filename, and width of the png (or 0 if cannot read/decode file).
	std::pair<std::string, lv_coord_t> read_faceplate(std::string_view slug) {
		const auto img_filename = ModuleImages::get_faceplate_path(slug);

		if (img_filename.length() <= 2) {
			if (!slug.ends_with("HubMedium"))
				pr_warn("Image not found for %.*s\n", (int)slug.size(), slug.data());
			return {"", 0};
		}

		float zoom = height / 240.f;

		lv_img_header_t img_header;
		auto res = lv_img_decoder_get_info(img_filename.c_str(), &img_header);
		if (res != LV_RES_OK) {
			pr_warn("Could not read image %s for module %.*s\n", img_filename.data(), slug.size(), slug.data());
			return {img_filename, 0};
		}

		uint32_t widthpx = img_header.w * zoom;

		pr_trace("Read faceplate for %s (%d x %d)\n", slug.data(), widthpx, height);

		return {img_filename, widthpx};
	}

	// Draws the module from patch, into container, using the provided buffer.
	lv_obj_t *draw_faceplate(std::string_view img_filename, lv_coord_t widthpx, std::span<lv_color_t> canvas_buffer) {
		if (img_filename.size() == 0 || widthpx == 0)
			return nullptr;

		lv_obj_scroll_to_x(container, 0, LV_ANIM_OFF);
		lv_obj_scroll_to_y(container, 0, LV_ANIM_OFF);

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
		draw_img_dsc.zoom = float(height / 240.f) * 256;

		lv_canvas_draw_img(canvas, 0, 0, img_filename.data(), &draw_img_dsc);
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

		unsigned i = 0;
		for (const auto &element : moduleinfo.elements) {
			auto &indices = moduleinfo.indices[i];
			auto gui_element = std::visit(
				[height = height, &patch, &indices, module_idx, canvas, active_knob_set](auto &el) -> GuiElement {
					auto obj = ElementDrawer::draw_element(el, canvas, height);
					auto mapping_id = ElementMapping::find_mapping(el, patch, module_idx, active_knob_set, indices);
					auto mapped_ring = MapRingDrawer::draw_mapped_ring(el, obj, canvas, mapping_id, height);

					auto count = ElementCount::count(el);
					auto el_idx = ElementCount::mark_unused_indices(indices, count);

					return GuiElement{obj, mapped_ring, (uint16_t)module_idx, count, el_idx, mapping_id};
				},
				element);
			i++;
			drawn_elements.push_back({gui_element, element});
		}
	}

	void draw_elements(BrandModuleSlug slug, lv_obj_t *canvas) {
		const auto moduleinfo = ModuleFactory::getModuleInfo(slug);
		for (const auto &element : moduleinfo.elements) {
			std::visit([this, canvas](auto &el) { ElementDrawer::draw_element(el, canvas, height); }, element);
		}
	}

	void draw_mapped_ring(
		PatchData const &patch, uint32_t module_idx, uint32_t active_knob_set, lv_obj_t *canvas, DrawnElement &drawn) {

		auto &gui_el = drawn.gui_element;
		gui_el.map_ring = std::visit(
			[&](auto &el) {
				auto mapping_id = ElementMapping::find_mapping(el, patch, module_idx, active_knob_set, gui_el.idx);
				gui_el.mapped_panel_id = mapping_id;
				return MapRingDrawer::draw_mapped_ring(el, gui_el.obj, canvas, mapping_id, height);
			},
			drawn.element);
	}
};

} // namespace MetaModule
