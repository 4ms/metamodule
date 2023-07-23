#pragma once
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

inline std::optional<float> get_param_value(const Params &params, const PatchData &patch, const GuiElement &drawn) {
	if (!drawn.obj)
		return {};

	float val = 0;
	if (drawn.mapped_panel_id) {
		// mapped knob
		if (drawn.mapped_panel_id < params.knobs.size())
			val = params.knobs[*drawn.mapped_panel_id];
		else
			return {}; // mapped to an invalid param id (error?)
	} else {
		//static knob
		return patch.get_static_knob_value(drawn.module_idx, drawn.idx);
	}
	return val;
}

} // namespace ElementUpdateImpl

inline void
update_element(const Knob &element, const Params &params, const PatchData &patch, const GuiElement &drawn) {
	if (auto val = ElementUpdateImpl::get_param_value(params, patch, drawn)) {
		int32_t angle = val.value() * 3000.f - 1500.f;
		if (angle < 0)
			angle += 3600;
		int32_t cur_angle = lv_img_get_angle(drawn.obj);

		if (std::abs(angle - cur_angle) > 10)
			lv_img_set_angle(drawn.obj, angle);
	}
}

inline void
update_element(const Slider &element, const Params &params, const PatchData &patch, const GuiElement &drawn) {
	if (auto val = ElementUpdateImpl::get_param_value(params, patch, drawn)) {
		auto handle = lv_obj_get_child(drawn.obj, 0);
		if (!handle) {
			pr_err("No handle sub-object for slider %16s\n", element.short_name.data());
			return;
		}
		auto height = lv_obj_get_height(drawn.obj);
		auto width = lv_obj_get_width(drawn.obj);

		if (height > width) {
			// Vertical Slider
			auto handle_height = lv_obj_get_height(handle);
			int32_t pos = (1.f - val.value()) * (height - handle_height);
			int32_t cur_pos = lv_obj_get_y(handle);
			if (pos != cur_pos)
				lv_obj_set_y(handle, pos);

		} else {
			// Horizontal Slider
			auto handle_width = lv_obj_get_width(handle);
			int32_t pos = (1.f - val.value()) * (width - handle_width);
			int32_t cur_pos = lv_obj_get_x(handle);
			if (pos != cur_pos)
				lv_obj_set_x(handle, pos);
		}
	}
}

inline void
update_element(const Toggle3pos &element, const Params &params, const PatchData &patch, const GuiElement &drawn) {
	if (auto val = ElementUpdateImpl::get_param_value(params, patch, drawn)) {
		auto handle = lv_obj_get_child(drawn.obj, 0);
		if (!handle) {
			printf_("No handle sub-object for toggle3pos %16s\n", element.short_name.data());
			return;
		}
		auto height = lv_obj_get_height(drawn.obj);
		//auto width = lv_obj_get_width(drawn.obj);

		// if (height > width) {
		// Vertical Toggle
		int32_t y = lv_obj_get_y(handle);
		int32_t cur_state = y > 0 ? 2 : y == 0 ? 1 : 0;
		int32_t state = *val > .75f ? 2 : *val > 0.25f ? 1 : 0;

		if (state != cur_state) {
			// printf_("sw:%d h=%d %d(y=%d)=>%d (y=", element.idx, height, cur_state, y, state);
			if (state == 2) {
				lv_obj_set_y(handle, height / 4);
				lv_obj_set_height(handle, height / 2);
				// printf_("%d)\n", height / 4);
			}
			if (state == 1) {
				lv_obj_set_y(handle, 0);
				lv_obj_set_height(handle, height / 4);
				// printf_("%d)\n", 0);
			}
			if (state == 0) {
				lv_obj_set_y(handle, -height / 4);
				lv_obj_set_height(handle, height / 2);
				// printf_("%d)\n", -height / 4);
			}
		}

		// } else {
		// Horizontal Toggle
		// auto handle_width = lv_obj_get_width(handle);
		// int32_t pos = (1.f - val.value()) * (width - handle_width);
		// int32_t cur_pos = lv_obj_get_x(handle);
		// if (pos != cur_pos)
		// 	lv_obj_set_x(handle, pos);
		// }
	}
}

inline void
update_element(const Toggle2pos &element, const Params &params, const PatchData &patch, const GuiElement &drawn) {
	if (auto val = ElementUpdateImpl::get_param_value(params, patch, drawn)) {
		//angle 0 => up
		//angle 1800 => down
	}
}

inline void update_element(const BaseElement &, const Params &, const PatchData &, const GuiElement &) {
}

} // namespace MetaModule
