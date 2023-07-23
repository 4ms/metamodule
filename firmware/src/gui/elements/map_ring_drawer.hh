#pragma once
#include "CoreModules/elements/elements.hh"
#include "gui/helpers/units_conversion.hh"
#include "gui/styles.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <cstdint>
#include <optional>

namespace MetaModule::ElementDrawerImpl
{} // namespace MetaModule::ElementDrawerImpl

namespace MetaModule
{
namespace MapRingDrawer
{
inline void
draw_mapped_ring(auto element, lv_obj_t *element_obj, std::optional<uint32_t> panel_el_id, uint32_t module_height) {
	if (!panel_el_id || !element_obj)
		return;

	//TODO: color and thickness set by variant type
	auto color = Gui::knob_palette[panel_el_id.value() % 6];
	const float ring_thickness = (panel_el_id.value() >= 6) ? 2.f : 4.f;

	float zoom = module_height / 240.f;

	lv_obj_set_style_outline_color(element_obj, color, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(element_obj, ring_thickness * zoom, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(element_obj, LV_OPA_50, LV_STATE_DEFAULT);
	lv_obj_set_style_radius(element_obj, 20, LV_STATE_DEFAULT);
}
}; // namespace MapRingDrawer
} // namespace MetaModule
