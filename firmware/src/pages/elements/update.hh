#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pages/elements/context.hh"
#include "params.hh"
#include "patch/patch_data.hh"
#include "printf.h"
#include <optional>

namespace MetaModule
{

namespace ElementUpdateImpl
{

inline std::optional<float> get_param_value(const Params &params, const PatchData &patch, const ElementContext &drawn) {
	float val = 0;
	if (drawn.mapped_panel_id) {
		if (drawn.mapped_panel_id < params.knobs.size())
			val = params.knobs[*drawn.mapped_panel_id];
		else
			return {}; // mapped, but not found in patch
	} else {
		//static knob
		if (auto maybe_val = patch.get_static_knob_value(drawn.module_idx, drawn.idx))
			val = maybe_val.value();
		else
			return {}; // not found in module
	}
	return val;
}

} // namespace ElementUpdateImpl

inline void
update_element(const Knob &element, const Params &params, const PatchData &patch, const ElementContext &drawn) {
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
update_element(const Slider &element, const Params &params, const PatchData &patch, const ElementContext &drawn) {
	if (auto val = ElementUpdateImpl::get_param_value(params, patch, drawn)) {
		auto handle = lv_obj_get_child(drawn.obj, 0);
		if (!handle) {
			printf_("No handle sub-object for slider %16s\n", element.short_name.data());
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
update_element(const Toggle3pos &element, const Params &params, const PatchData &patch, const ElementContext &drawn) {
	if (auto val = ElementUpdateImpl::get_param_value(params, patch, drawn)) {
		//angle 0 => up
		//angle 1800 => down
	}
}

inline void
update_element(const Toggle2pos &element, const Params &params, const PatchData &patch, const ElementContext &drawn) {
	if (auto val = ElementUpdateImpl::get_param_value(params, patch, drawn)) {
		//angle 0 => up
		//angle 1800 => down
	}
}

inline void update_element(const BaseElement &, const Params &, const PatchData &, const ElementContext &) {
}

} // namespace MetaModule
