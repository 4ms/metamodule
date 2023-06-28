#pragma once
#include "CoreModules/elements/elements.hh"
#include "lvgl/lvgl.h"
#include "pages/animated_knob.hh"
#include "params.hh"
#include "patch/patch_data.hh"
#include <optional>

namespace MetaModule::ElementUpdateImpl
{

inline void update_element(Knob &element, const Params &params, const PatchData &patch, const GuiElement &gui) {
	float val = 0;
	if (gui.mapped_panel_element_id) {
		if (gui.mapped_panel_element_id < params.knobs.size())
			val = params.knobs[*gui.mapped_panel_element_id];
		//else MIDI mapped...

		float min = element.min_val;
		float max = element.max_val;
		val = (max - min) * val + min;
	} else {
		//static knob
		val = patch.get_static_knob_value(0, 0).value_or(0);
	}

	int32_t angle = val * 3000.f - 1500.f;
	int32_t cur_angle = lv_img_get_angle(gui.obj);

	if (std::abs(angle - cur_angle) > 10)
		lv_img_set_angle(gui.obj, angle);
}

inline void update_element(Slider &element,
						   const Params &params,
						   const PatchData &patch,
						   lv_obj_t *obj,
						   std::optional<uint16_t> panel_element_id) {
	float val = 0;
	if (panel_element_id) {
		if (panel_element_id < params.knobs.size())
			val = params.knobs[*panel_element_id];
		//else MIDI mapped...

		float min = element.min_val;
		float max = element.max_val;
		val = (max - min) * val + min;
	}
	//TODO: set position of handle
}

inline void update_element(BaseElement &, const Params &, const PatchData &, lv_obj_t *, std::optional<uint16_t>) {
}

} // namespace MetaModule::ElementUpdateImpl

namespace MetaModule
{

void update_element(auto &element, const Params &params, const PatchData &patch, const GuiElement &drawn) {
	ElementUpdateImpl::update_element(
		element, params, patch, drawn.obj, drawn.mapped_panel_element_id, drawn.module_id);
}

} // namespace MetaModule
