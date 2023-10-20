#pragma once
#include "CoreModules/elements/element_state_conversion.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/elements/context.hh"
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
	if (!gui_el.obj)
		return false;

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

// Toggle update
inline bool redraw_element(const Toggle3pos &element, const GuiElement &gui_el, float val) {
	using enum Toggle3pos::State_t;

	bool did_update_position = false;

	auto handle = lv_obj_get_child(gui_el.obj, 0);
	if (!handle) {
		pr_err("No handle sub-object for toggle3pos\n");
		return false;
	}
	auto height = lv_obj_get_height(gui_el.obj);
	//auto width = lv_obj_get_width(drawn.obj);

	// if (height > width) {
	// Vertical Toggle
	lv_obj_refr_size(handle);
	lv_obj_refr_pos(handle);
	int32_t y = lv_obj_get_y(handle);
	Toggle3pos::State_t cur_state = (y >= height / 2) ? DOWN : (y == 0) ? UP : CENTER;
	auto state = StateConversion::convertState(element, val);

	if (state != cur_state) {
		if (state == UP) {
			lv_obj_set_y(handle, 0);
			lv_obj_set_height(handle, height / 2);
		}
		if (state == CENTER) {
			lv_obj_set_y(handle, height / 2 - height / 8);
			lv_obj_set_height(handle, height / 4);
		}
		if (state == DOWN) {
			lv_obj_set_y(handle, height / 2);
			lv_obj_set_height(handle, height / 2);
		}
		did_update_position = true;
	}

	return did_update_position;
	// TODO: Horizontal Toggle
}

// Toggle 2pos update
inline bool redraw_element(const Toggle2pos &element, const GuiElement &gui_el, float val) {
	bool did_update_position = false;
	using enum Toggle2pos::State_t;

	auto handle = lv_obj_get_child(gui_el.obj, 0);
	if (!handle) {
		pr_err("No handle sub-object for toggle2pos\n");
		return false;
	}
	auto height = lv_obj_get_height(gui_el.obj);
	//auto width = lv_obj_get_width(drawn.obj);

	// if (height > width) {
	// Vertical Toggle
	lv_obj_refr_size(handle);
	lv_obj_refr_pos(handle);
	int32_t y = lv_obj_get_y(handle);
	auto cur_state = (y >= height / 2) ? DOWN : UP;
	auto state = StateConversion::convertState(element, val);

	if (state != cur_state) {
		if (state == UP) {
			lv_obj_set_y(handle, 0);
			lv_obj_set_height(handle, height / 2);
		}
		if (state == DOWN) {
			lv_obj_set_y(handle, height / 2);
			lv_obj_set_height(handle, height / 2);
		}
		did_update_position = true;
	}

	return did_update_position;
}

inline bool redraw_element(const BaseElement &, const GuiElement &, float) {
	return false;
}

} // namespace MetaModule::ElementRedrawDetails
