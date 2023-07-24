#pragma once
#include "CoreModules/elements/elements.hh"
#include "gui/helpers/units_conversion.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include <cstdint>
#include <optional>

namespace MetaModule::MapRingDrawer
{

inline lv_obj_t *draw_mapped_ring(const BaseElement &,
								  lv_obj_t *element_obj,
								  lv_obj_t *canvas,
								  std::optional<uint32_t> panel_el_id,
								  uint32_t module_height) {
	if (!panel_el_id.has_value() || !element_obj)
		return nullptr;

	//TODO: color and thickness set by variant type
	auto color = Gui::knob_palette[panel_el_id.value() % 6];
	uint16_t gap;
	float ring_thickness;
	if (module_height == 240) {
		ring_thickness = (panel_el_id.value() >= 6) ? 2 : 4;
		gap = 2;

	} else {
		ring_thickness = (panel_el_id.value() >= 6) ? 2 : 3;
		gap = 0;
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
	lv_obj_set_style_border_opa(ring_obj, LV_OPA_TRANSP, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(ring_obj, gap, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ring_obj, color, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ring_obj, ring_thickness, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ring_obj, LV_OPA_TRANSP, LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ring_obj, 40, LV_STATE_DEFAULT);

	return ring_obj;
}

} // namespace MetaModule::MapRingDrawer
