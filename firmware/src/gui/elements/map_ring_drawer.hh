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

inline lv_obj_t *draw_mapped_ring(const JackInput &el,
								  lv_obj_t *element_obj,
								  lv_obj_t *canvas,
								  std::optional<uint32_t> panel_el_id,
								  uint32_t module_height) {
	if (!panel_el_id.has_value() || !element_obj)
		return nullptr;

	auto panel_id = panel_el_id.value();

	lv_obj_refr_size(element_obj);
	lv_obj_refr_pos(element_obj);
	auto x = lv_obj_get_x(element_obj);
	auto y = lv_obj_get_y(element_obj);
	auto w = lv_obj_get_width(element_obj);
	auto h = lv_obj_get_height(element_obj);

	// TODO: Make this a style
	lv_obj_t *circle = lv_btn_create(canvas);
	lv_obj_set_align(circle, LV_ALIGN_TOP_LEFT);
	lv_obj_add_flag(circle, LV_OBJ_FLAG_OVERFLOW_VISIBLE | LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_obj_clear_flag(circle,
					  LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
						  LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC |
						  LV_OBJ_FLAG_SCROLL_MOMENTUM | LV_OBJ_FLAG_SCROLL_CHAIN);
	lv_obj_set_style_radius(circle, 40, LV_PART_MAIN);

	// lv_obj_set_style_border_width(circle, 3, LV_PART_MAIN);
	// lv_obj_set_style_border_opa(circle, LV_OPA_TRANSP, LV_STATE_DEFAULT);

	lv_obj_set_style_bg_color(circle, lv_color_white(), LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(circle, LV_OPA_50, LV_STATE_DEFAULT);

	lv_obj_set_style_outline_opa(circle, LV_OPA_100, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(circle, 3, LV_STATE_DEFAULT);
	lv_obj_set_style_outline_pad(circle, 0, LV_STATE_DEFAULT);

	lv_obj_set_style_radius(circle, 40, LV_STATE_DEFAULT);
	lv_obj_clear_flag(circle, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_scrollbar_mode(circle, LV_SCROLLBAR_MODE_OFF);

	lv_obj_t *label;
	label = lv_label_create(circle);
	lv_obj_set_width(label, LV_SIZE_CONTENT);
	lv_obj_set_height(label, LV_SIZE_CONTENT);
	lv_obj_set_align(label, LV_ALIGN_CENTER);
	lv_obj_set_style_text_color(label, lv_color_hex(0x000000), LV_PART_MAIN);
	lv_obj_set_style_text_opa(label, 255, LV_PART_MAIN);
	lv_obj_set_style_pad_all(label, 0, LV_PART_MAIN);
	//////////////

	lv_obj_set_pos(circle, x, y);
	lv_obj_set_size(circle, w, h);

	lv_obj_set_style_outline_color(circle, Gui::knob_palette[panel_id], LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(label, Gui::knob_palette[panel_id], LV_STATE_DEFAULT);
	if (panel_id < 6)
		lv_label_set_text_fmt(label, "%d", panel_id + 1);
	else
		lv_label_set_text_fmt(label, "G%d", panel_id - 5);
	lv_obj_set_style_text_font(label, &ui_font_MuseoSansRounded50012, LV_STATE_DEFAULT);

	return circle;
}

} // namespace MetaModule::MapRingDrawer
