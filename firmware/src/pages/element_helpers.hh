#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "CoreModules/module_info_base.hh"
#include "draw_helpers.hh" //for std::vector<DrawHelper::MKnob> mapped_knobs,
#include "lvgl/lvgl.h"
#include "pages/elements/element_image.hh"
#include "patch/patch_data.hh"
#include "pr_dbg.hh"

namespace MetaModule
{

struct MapRingDrawer {
	uint32_t module_height;
	lv_obj_t *canvas;

	// Control Ring

	void draw_control_ring(const Knob &el, const lv_img_dsc_t *img, uint32_t panel_knob_id) {
		// Parameters for ring size
		constexpr float ring_offset = 8.f;
		// Thinner circle for uvwxyz small panel knobs
		const float ring_thickness = (panel_knob_id >= 6) ? 4.f : 10.f;

		lv_draw_arc_dsc_t ring;
		lv_draw_arc_dsc_init(&ring);
		ring.opa = LV_OPA_50;

		float scale = module_height / 240.f;
		float radius = img->header.w * 0.5f + ring_offset * scale;

		uint16_t c_x = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height) + img->header.w / 2.f);
		uint16_t c_y = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height) + img->header.h / 2.f);

		ring.color = Gui::knob_palette[panel_knob_id % 6];
		// TODO: how to draw MIDI maps?

		ring.width = ring_thickness * scale;

		lv_canvas_draw_arc(canvas, c_x, c_y, radius, 0, 3600, &ring);
	}

	void draw_control_ring(const Slider &el, const lv_img_dsc_t *img, uint32_t panel_knob_id) {
		// Parameters for ring size
		// Thinner circle for uvwxyz small panel knobs
		const float ring_thickness = (panel_knob_id >= 6) ? 4.f : 10.f;

		float scale = module_height / 240.f;

		lv_draw_rect_dsc_t ring;
		lv_draw_rect_dsc_init(&ring);
		ring.border_opa = LV_OPA_50;
		ring.border_width = ring_thickness * scale;
		ring.border_color = Gui::knob_palette[panel_knob_id % 6];
		ring.bg_opa = LV_OPA_0;
		ring.outline_opa = LV_OPA_0;
		ring.shadow_opa = LV_OPA_0;

		auto w = img->header.w;
		auto h = img->header.h;
		uint16_t x = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height) - w / 2.f);
		uint16_t y = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height) - h / 2.f);
		lv_canvas_draw_rect(canvas, x, y, w, h, &ring);
	}

	void draw_jack_ring(const JackElement &el, const lv_img_dsc_t *img, uint32_t panel_jack_id) {
		uint16_t c_x = std::round(ElementInfoBase::mm_to_px(el.x_mm, module_height) + img->header.w / 2.f);
		uint16_t c_y = std::round(ElementInfoBase::mm_to_px(el.y_mm, module_height) + img->header.h / 2.f);

		Gui::mapped_jack_small_arcdsc.color = Gui::palette_main[panel_jack_id % 8];
		uint16_t radius = (img->header.w + 6) / 2;
		lv_canvas_draw_arc(canvas, c_x, c_y, radius, 0, 3600, &Gui::mapped_jack_small_arcdsc);
	}
};

struct Mappings {
	std::vector<DrawHelper::MKnob> knobs;
};

struct MappedElement {
	uint32_t module_height;
	uint32_t module_idx;
	lv_obj_t *element_obj;
	lv_obj_t *canvas;
	const lv_img_dsc_t *element_img;
	const PatchData &patch;
	Mappings &mappings;

	void operator()(const BaseElement &) {
	}

	void operator()(const Knob &el) {
		if (!element_obj || !element_img)
			return;
		if (auto mapped_knob = patch.find_mapped_knob(module_idx, el.idx)) {
			mappings.knobs.push_back({element_obj, *mapped_knob, DrawHelper::RotaryPot});

			MapRingDrawer{module_height, canvas}.draw_control_ring(el, element_img, mapped_knob->panel_knob_id);
		}
	}
	//TODO: this is the same as Knob& except for the DrawHelper::RotaryPot/LinearSlider, how to not repeat?
	void operator()(const Slider &el) {
		if (!element_obj || !element_img)
			return;
		if (auto mapped_knob = patch.find_mapped_knob(module_idx, el.idx)) {
			mappings.knobs.push_back({element_obj, *mapped_knob, DrawHelper::LinearSlider});

			MapRingDrawer{module_height, canvas}.draw_control_ring(el, element_img, mapped_knob->panel_knob_id);
		}
	}

	void operator()(const JackInput &el) {
		if (!element_img)
			return;
		if (auto mapped_jack = patch.find_mapped_injack(Jack{(uint16_t)module_idx, (uint16_t)el.idx})) {
			MapRingDrawer{module_height, canvas}.draw_jack_ring(el, element_img, mapped_jack->panel_jack_id);
		}
	}

	void operator()(const JackOutput &el) {
		if (!element_img)
			return;
		if (auto mapped_jack = patch.find_mapped_outjack(Jack{(uint16_t)module_idx, (uint16_t)el.idx})) {
			MapRingDrawer{module_height, canvas}.draw_jack_ring(el, element_img, mapped_jack->panel_jack_id);
		}
	}
};
} // namespace MetaModule
