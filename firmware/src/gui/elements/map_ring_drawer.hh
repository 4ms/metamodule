#pragma once
#include "CoreModules/elements/elements.hh"
#include "gui/helpers/units_conversion.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include "patch/midi_def.hh"
#include <cstdint>
#include <optional>

namespace MetaModule::MapRingDrawer
{
inline lv_obj_t *draw_mapped_ring(const BaseElement &,
								  lv_obj_t *element_obj,
								  lv_obj_t *canvas,
								  std::optional<uint32_t> panel_el_id,
								  uint32_t module_height) {
	return nullptr;
}

inline lv_obj_t *draw_mapped_ring(const ParamElement &,
								  lv_obj_t *element_obj,
								  lv_obj_t *canvas,
								  std::optional<uint32_t> panel_el_id,
								  uint32_t module_height) {
	if (!panel_el_id.has_value() || !element_obj)
		return nullptr;

	auto panel_id = panel_el_id.value();

	//TODO: color and thickness set by variant type
	lv_color_t color;
	uint16_t gap;
	float ring_thickness;
	if (panel_id >= MidiCC0) {
		ring_thickness = 1;
		gap = 3;
		color = Gui::palette_main[4];
	} else {
		color = Gui::knob_palette[panel_id % 6];
		if (module_height == 240) {
			ring_thickness = (panel_id >= 6) ? 2 : 4;
			gap = 2;

		} else {
			ring_thickness = (panel_id >= 6) ? 2 : 3;
			gap = 0;
		}
	}

	lv_obj_refr_size(element_obj);
	lv_obj_refr_pos(element_obj);
	auto x = lv_obj_get_x(element_obj);
	auto y = lv_obj_get_y(element_obj);
	auto w = lv_obj_get_width(element_obj);
	auto h = lv_obj_get_height(element_obj);

	//TODO: shrink box around center by width * (1-zoom)
	// So that it's consistant at all zoom levels
	// float zoom = module_height / 240.f;

	auto ring_obj = lv_obj_create(canvas);
	lv_obj_set_pos(ring_obj, x, y);
	lv_obj_set_size(ring_obj, w, h);

	lv_obj_set_style_bg_opa(ring_obj, LV_OPA_TRANSP, LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ring_obj, 0, LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ring_obj, LV_OPA_TRANSP, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ring_obj, gap, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ring_obj, color, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ring_obj, ring_thickness, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ring_obj, LV_OPA_TRANSP, LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ring_obj, 40, LV_STATE_DEFAULT);

	lv_obj_clear_flag(ring_obj, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_scrollbar_mode(ring_obj, LV_SCROLLBAR_MODE_OFF);

	return ring_obj;
}

inline lv_obj_t *
draw_mapped_jack(const JackElement &, lv_obj_t *element_obj, lv_obj_t *canvas, std::optional<uint32_t> panel_el_id) {

	if (!panel_el_id.has_value() || !element_obj)
		return nullptr;

	auto circle = Gui::create_map_circle(canvas);

	lv_obj_refr_size(element_obj);
	lv_obj_refr_pos(element_obj);
	lv_obj_set_pos(circle, lv_obj_get_x(element_obj), lv_obj_get_y(element_obj));
	lv_obj_set_size(circle, lv_obj_get_width(element_obj), lv_obj_get_height(element_obj));

	lv_obj_refr_size(element_obj);
	lv_obj_refr_pos(element_obj);
	lv_obj_set_pos(circle, lv_obj_get_x(element_obj), lv_obj_get_y(element_obj));
	lv_obj_set_size(circle, lv_obj_get_width(element_obj), lv_obj_get_height(element_obj));

	auto panel_id = panel_el_id.value();
	lv_obj_set_style_outline_color(circle, Gui::knob_palette[panel_id], LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(circle, Gui::knob_palette[panel_id], LV_STATE_DEFAULT);

	return circle;
}

inline lv_obj_t *draw_mapped_ring(const JackInput &el,
								  lv_obj_t *element_obj,
								  lv_obj_t *canvas,
								  std::optional<uint32_t> panel_el_id,
								  uint32_t module_height) {

	auto circle = draw_mapped_jack(el, element_obj, canvas, panel_el_id);

	if (!circle)
		return nullptr;

	if (auto label = lv_obj_get_child(circle, 0)) {

		auto panel_id = panel_el_id.value();

		if (panel_id < 6)
			lv_label_set_text_fmt(label, "%d", int(panel_id + 1));
		else
			lv_label_set_text_fmt(label, "G%d", int(panel_id - 5));
	}

	return circle;
}

inline lv_obj_t *draw_mapped_ring(const JackOutput &el,
								  lv_obj_t *element_obj,
								  lv_obj_t *canvas,
								  std::optional<uint32_t> panel_el_id,
								  uint32_t module_height) {

	auto circle = draw_mapped_jack(el, element_obj, canvas, panel_el_id);

	if (!circle)
		return nullptr;

	if (auto label = lv_obj_get_child(circle, 0)) {

		auto panel_id = panel_el_id.value();
		lv_label_set_text_fmt(label, "%d", int(panel_id + 1));
	}

	return circle;
}

} // namespace MetaModule::MapRingDrawer
