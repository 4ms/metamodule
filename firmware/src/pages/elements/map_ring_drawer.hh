#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl.h"
#include "pages/elements/element_draw_helpers.hh"
#include "pages/styles.hh"
#include "pr_dbg.hh"
#include <cstdint>

namespace MetaModule::ElementDrawerImpl
{

struct Rect {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;

	//clang-14 needs this
	Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
		: x{x}
		, y{y}
		, w{w}
		, h{h} {
	}
};

// Default: do nothing
inline void draw_mapped_ring(const BaseElement &, uint32_t, lv_obj_t *, Rect &, uint32_t) {
}

inline void
draw_mapped_ring(const ParamElement &, uint32_t module_height, lv_obj_t *canvas, Rect &r, uint32_t panel_knob_id) {
	// Parameters for ring size
	// Thinner circle for uvwxyz small panel knobs
	const float ring_thickness = (panel_knob_id >= 6) ? 4.f : 8.f;

	lv_draw_arc_dsc_t ring;
	lv_draw_arc_dsc_init(&ring);
	ring.opa = LV_OPA_50;

	float scale = module_height / 240.f;
	float ring_offset = (panel_knob_id >= 6) ? 4.f : 8.f;
	float radius = (r.h + r.w) / 2.f * 0.5f + ring_offset * scale;

	ring.color = Gui::knob_palette[panel_knob_id % 6];
	ring.width = ring_thickness * scale;

	uint16_t c_x = r.x + r.w / 2.f;
	uint16_t c_y = r.y + r.h / 2.f;

	lv_canvas_draw_arc(canvas, c_x, c_y, radius, 0, 3600, &ring);
}

inline void
draw_mapped_ring(const Slider &, uint32_t module_height, lv_obj_t *canvas, Rect &r, uint32_t panel_knob_id) {
	// Parameters for ring size
	const float ring_thickness = (panel_knob_id >= 6) ? 4.f : 10.f;

	float scale = module_height / 240.f;

	lv_draw_rect_dsc_t ring;
	lv_draw_rect_dsc_init(&ring);
	ring.border_opa = LV_OPA_70;
	ring.border_width = ring_thickness * scale;
	ring.border_color = Gui::knob_palette[panel_knob_id % 6];
	ring.bg_opa = LV_OPA_0;
	ring.outline_opa = LV_OPA_0;
	ring.shadow_opa = LV_OPA_0;

	lv_canvas_draw_rect(canvas, r.x, r.y, r.w, r.h, &ring);
}

inline void
draw_mapped_ring(const JackElement &, uint32_t module_height, lv_obj_t *canvas, Rect &r, uint32_t panel_jack_id) {
	uint16_t c_x = r.x + r.w / 2.f;
	uint16_t c_y = r.y + r.h / 2.f;

	lv_draw_arc_dsc_t ring;
	lv_draw_arc_dsc_init(&ring);
	ring.width = 4;
	ring.opa = LV_OPA_70;
	ring.color = Gui::palette_main[panel_jack_id % 8];

	uint16_t radius = (((r.h + r.w) / 2.f) + 6.f) / 2.f;
	lv_canvas_draw_arc(canvas, c_x, c_y, radius, 0, 3600, &ring);
}

} // namespace MetaModule::ElementDrawerImpl

namespace MetaModule
{
struct MapRingDrawer {
	uint32_t module_height;
	lv_obj_t *canvas;

	void draw_mapped_ring(auto element, lv_obj_t *element_obj, uint32_t panel_el_id) {
		if (!element_obj)
			return;

		lv_obj_refr_size(element_obj);
		uint16_t w = lv_obj_get_width(element_obj);
		uint16_t h = lv_obj_get_height(element_obj);

		auto [x, y] = element.coords == Coords::Center ?
						  ElementDrawerImpl::mm_to_center_px(element.x_mm, element.y_mm, w, h, module_height) :
						  ElementDrawerImpl::mm_to_px(element.x_mm, element.y_mm, module_height);

		ElementDrawerImpl::Rect r(x, y, w, h);
		ElementDrawerImpl::draw_mapped_ring(element, module_height, canvas, r, panel_el_id);
	}
};
} // namespace MetaModule
