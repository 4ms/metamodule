#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "patch/patch.hh"
#include <memory>

inline bool is_toggle(MappedKnob const &map) {
	return map.curve_type == MappedKnob::CurveType::Toggle;
}

inline void toggle_button(std::unique_ptr<CoreProcessor> &module, MappedKnob const &map, float val) {
	// Latching: toggle
	if (val > 0.5f) { //rising edge
		auto cur_val = module->get_param(map.param_id);

		// if param is currently closer to min, then set it to max (and vice-versa)
		if (std::abs(cur_val - map.min) < std::abs(cur_val - map.max)) {
			module->set_param(map.param_id, map.max);
		} else {
			module->set_param(map.param_id, map.min);
		}
	}
}
