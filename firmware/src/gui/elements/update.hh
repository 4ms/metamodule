#pragma once
#include "CoreModules/elements/element_state_conversion.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/elements/context.hh"
#include "lvgl.h"
#include "params.hh"
#include "patch/patch_data.hh"
#include "pr_dbg.hh"
#include <optional>

namespace MetaModule
{

namespace ElementUpdateImpl
{

inline std::optional<float> get_param_value(const Params &params, const PatchData &patch, const GuiElement &gui_el) {
	if (!gui_el.obj)
		return {};

	float val = 0;
	if (gui_el.mapped_panel_id) {
		// mapped knob
		if (gui_el.mapped_panel_id < params.knobs.size())
			val = params.knobs[*gui_el.mapped_panel_id];
		else
			return {}; // mapped to an invalid param id (error?)
	} else {
		//static knob
		return patch.get_static_knob_value(gui_el.module_idx, gui_el.idx);
	}
	return val;
}

} // namespace ElementUpdateImpl

// Knob update
inline bool
update_element(const Knob &element, const Params &params, const PatchData &patch, const GuiElement &gui_el) {
	bool updated_position = false;
	constexpr int32_t threshold_degrees = 30;

	if (auto val = ElementUpdateImpl::get_param_value(params, patch, gui_el)) {
		int32_t angle = val.value() * 3000.f - 1500.f;
		if (angle < 0)
			angle += 3600;
		int32_t cur_angle = lv_img_get_angle(gui_el.obj);

		if (std::abs(angle - cur_angle) > threshold_degrees) {
			lv_img_set_angle(gui_el.obj, angle);
			updated_position = true;
		}
	}

	return updated_position;
}

// Slider update
inline bool
update_element(const Slider &element, const Params &params, const PatchData &patch, const GuiElement &gui_el) {
	bool updated_position = false;

	if (auto val = ElementUpdateImpl::get_param_value(params, patch, gui_el)) {
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
			int32_t pos = (1.f - val.value()) * (height - handle_height);
			int32_t cur_pos = lv_obj_get_y(handle);
			if (pos != cur_pos) {
				lv_obj_set_y(handle, pos);
				updated_position = true;
			}

		} else {
			// Horizontal Slider
			auto handle_width = lv_obj_get_width(handle);
			int32_t pos = (1.f - val.value()) * (width - handle_width);
			int32_t cur_pos = lv_obj_get_x(handle);
			if (pos != cur_pos) {
				lv_obj_set_x(handle, pos);
				updated_position = true;
			}
		}
	}
	return updated_position;
}

// Toggle update
inline bool
update_element(const Toggle3pos &element, const Params &params, const PatchData &patch, const GuiElement &gui_el) {
	using enum Toggle3pos::State_t;
	bool updated_position = false;

	if (auto val = ElementUpdateImpl::get_param_value(params, patch, gui_el)) {
		auto handle = lv_obj_get_child(gui_el.obj, 0);
		if (!handle) {
			printf_("No handle sub-object for toggle3pos\n");
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
		auto state = StateConversion::convertState(element, *val);

		if (state != cur_state) {
			updated_position = true;
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
		}

		// TODO: Horizontal Toggle
	}

	return updated_position;
}

// Toggle 2pos update
inline bool
update_element(const Toggle2pos &element, const Params &params, const PatchData &patch, const GuiElement &gui_el) {
	using enum Toggle2pos::State_t;
	bool updated_position = false;

	if (auto val = ElementUpdateImpl::get_param_value(params, patch, gui_el)) {
		auto handle = lv_obj_get_child(gui_el.obj, 0);
		if (!handle) {
			printf_("No handle sub-object for toggle2pos\n");
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
		auto state = StateConversion::convertState(element, *val);

		if (state != cur_state) {
			updated_position = true;
			if (state == UP) {
				lv_obj_set_y(handle, 0);
				lv_obj_set_height(handle, height / 2);
			}
			if (state == DOWN) {
				lv_obj_set_y(handle, height / 2);
				lv_obj_set_height(handle, height / 2);
			}
		}
	}

	return updated_position;
}

// default/catch-all
inline bool update_element(const BaseElement &, const Params &, const PatchData &, const GuiElement &) {
	return false;
}

} // namespace MetaModule
