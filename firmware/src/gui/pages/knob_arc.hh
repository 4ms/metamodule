#pragma once
#include "lvgl.h"
#include "patch/patch.hh"
#include <algorithm>
#include <cstdint>

template<unsigned min_arc, unsigned max_arc>
uint16_t lvgl_knob_angle(float knob_pos) {
	knob_pos = std::clamp<float>(knob_pos, 0.f, 1.f);
	uint16_t angle = knob_pos * (360 + max_arc - min_arc) + min_arc;
	if (angle > 360)
		angle -= 360;
	return angle;
}

template<unsigned min_arc, unsigned max_arc>
void set_knob_arc(MappedKnob const &map, lv_obj_t *arc, float val) {
	if (!arc)
		return;

	// Set min/max of arc
	lv_arc_set_mode(arc, (map.min < map.max) ? LV_ARC_MODE_NORMAL : LV_ARC_MODE_REVERSE);
	float left = std::min<float>(map.min, map.max);
	float right = std::max<float>(map.min, map.max);
	lv_arc_set_bg_angles(arc, lvgl_knob_angle<min_arc, max_arc>(left), lvgl_knob_angle<min_arc, max_arc>(right));

	// Set initial value
	lv_arc_set_value(arc, (uint16_t)(val * 120)); //for some reason we have a standard arc range of 120.
}
