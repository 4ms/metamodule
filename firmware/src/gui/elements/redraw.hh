#pragma once
#include "CoreModules/elements/element_state_conversion.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/elements/context.hh"
#include "gui/images/image_fs.hh"
#include "lvgl.h"
#include "pr_dbg.hh"
#include <cmath>

namespace MetaModule::ElementRedrawDetails
{

inline bool redraw_element(const Knob &, const GuiElement &gui_el, float val) {
	bool did_update_position = false;

	constexpr int32_t threshold_centidegrees = 30; // = 3.0 degrees

	int32_t angle = val * 3000.f - 1500.f;
	while (angle < 0)
		angle += 3600;
	int32_t cur_angle = lv_img_get_angle(gui_el.obj);

	if (std::abs(angle - cur_angle) > threshold_centidegrees) {
		lv_img_set_angle(gui_el.obj, angle);
		did_update_position = true;
	}

	return did_update_position;
}

// Slider update
inline bool redraw_element(const Slider &element, const GuiElement &gui_el, float val) {
	bool did_update_position = false;

	auto handle = lv_obj_get_child(gui_el.obj, 0);
	if (!handle) {
		pr_err("No handle sub-object for slider %16s\n", element.short_name.data());
		return false;
	}
	auto height = lv_obj_get_height(gui_el.obj);
	auto width = lv_obj_get_width(gui_el.obj);

	if (height > width) {
		// Vertical Slider
		auto handle_height = lv_obj_get_height(handle);
		int32_t pos = (1.f - val) * (height - handle_height);
		int32_t cur_pos = lv_obj_get_y(handle);
		if (pos != cur_pos) {
			lv_obj_set_y(handle, pos);
			did_update_position = true;
		}

	} else {
		// Horizontal Slider
		auto handle_width = lv_obj_get_width(handle);
		int32_t pos = val * (width - handle_width);
		int32_t cur_pos = lv_obj_get_x(handle);
		if (pos != cur_pos) {
			lv_obj_set_x(handle, pos);
			did_update_position = true;
		}
	}

	return did_update_position;
}

inline bool redraw_element(const FlipSwitch &element, const GuiElement &gui_el, float val) {
	bool did_change_frame = false;

	unsigned frame_num = StateConversion::convertState(element, val);

	if (frame_num < element.frames.size()) {
		auto img = PNGFileSystem::read(element.frames[frame_num]);
		auto cur_img = lv_img_get_src(gui_el.obj);
		if (img && img != cur_img) {
			lv_img_set_src(gui_el.obj, img);
			did_change_frame = true;
		}
	}

	return did_change_frame;
}

inline bool redraw_element(const SlideSwitch &element, const GuiElement &gui_el, float val) {
	auto handle = lv_obj_get_child(gui_el.obj, 0);
	if (!handle) {
		pr_err("No handle object for SlideSwitch\n");
		return false;
	}
	// major axis = height if vertical, width if horizontal.

	auto height = lv_obj_get_height(gui_el.obj);
	auto width = lv_obj_get_width(gui_el.obj);
	bool vert = height > width;
	auto major_dim = vert ? height : width;
	auto handle_major_dim = major_dim / element.num_pos;
	lv_coord_t major_range = major_dim - handle_major_dim;

	lv_obj_refr_size(handle);
	lv_obj_refr_pos(handle);
	int32_t cur_pos = vert ? lv_obj_get_y(handle) : lv_obj_get_x(handle);

	if (element.direction == SlideSwitch::Ascend::UpLeft)
		cur_pos = major_range - cur_pos;

	// cur_pos ranges from 0 to major_range
	auto cur_state = StateConversion::convertState(element, (float)cur_pos / (float)major_range) - 1;
	auto new_state = StateConversion::convertState(element, val) - 1; //0..N-1 0..6

	bool did_update_position = false;

	if (new_state != cur_state) {
		lv_coord_t new_pos = ((float)new_state / (float)(element.num_pos - 1)) * major_range;

		if (element.direction == SlideSwitch::Ascend::UpLeft)
			new_pos = major_range - new_pos;

		if (vert)
			lv_obj_set_y(handle, new_pos);
		else
			lv_obj_set_x(handle, new_pos);
		did_update_position = true;
	}

	return did_update_position;
}

inline bool redraw_element(const BaseElement &, const GuiElement &, float) {
	return false;
}

} // namespace MetaModule::ElementRedrawDetails
