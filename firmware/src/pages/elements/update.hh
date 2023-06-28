#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pages/elements/context.hh"
#include "params.hh"
#include "patch/patch_data.hh"
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
		int32_t angle = *val * 3000.f - 1500.f;
		int32_t cur_angle = lv_img_get_angle(drawn.obj);

		if (std::abs(angle - cur_angle) > 10)
			lv_img_set_angle(drawn.obj, angle);
	}
}

inline void
update_element(const Slider &element, const Params &params, const PatchData &patch, const ElementContext &drawn) {
	if (auto val = ElementUpdateImpl::get_param_value(params, patch, drawn)) {
		//TODO: set position of handle
	}
}

inline void update_element(const BaseElement &, const Params &, const PatchData &, const ElementContext &) {
}

} // namespace MetaModule
