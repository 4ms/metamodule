#pragma once
#include "CoreModules/CoreProcessor.hh"
#include "patch/patch.hh"
#include <algorithm>
#include <cmath>
#include <memory>

inline bool is_toggle(MappedKnob const &map) {
	return map.curve_type == MappedKnob::CurveType::Toggle;
}

inline bool is_cycle(MappedKnob const &map) {
	return map.curve_type == MappedKnob::CurveType::Cycle;
}

// Toggle and Cycle maps change the param only on a rising edge
inline bool is_latching(MappedKnob const &map) {
	return is_toggle(map) || is_cycle(map);
}

inline void toggle_param(std::unique_ptr<CoreProcessor> &module, MappedKnob const &map) {
	auto cur_val = module->get_param(map.param_id);

	// if param is currently closer to min, then set it to max (and vice-versa)
	if (std::abs(cur_val - map.min) < std::abs(cur_val - map.max)) {
		module->set_param(map.param_id, map.max);
	} else {
		module->set_param(map.param_id, map.min);
	}
}

// Advances a param with num_pos discrete positions (value == pos / (num_pos - 1)) to the next position
// within the map's min/max range, wrapping around. Steps from min towards max (so max < min steps backwards).
// Falls back to toggling if the param is not multi-position or the range spans fewer than 2 positions.
inline void cycle_param(std::unique_ptr<CoreProcessor> &module, MappedKnob const &map, unsigned num_pos) {
	if (num_pos < 2) {
		toggle_param(module, map);
		return;
	}

	const float steps = num_pos - 1;

	// Min/Max are set in 1% increments, so allow for rounding
	const float tolerance = 0.006f * steps;
	const int lo = std::ceil(std::min(map.min, map.max) * steps - tolerance);
	const int hi = std::floor(std::max(map.min, map.max) * steps + tolerance);

	if (hi <= lo) {
		toggle_param(module, map);
		return;
	}

	const bool reversed = map.max < map.min;
	const int cur = std::lround(module->get_param(map.param_id) * steps);

	int next;
	if (cur < lo || cur > hi)
		next = reversed ? hi : lo;
	else if (reversed)
		next = (cur == lo) ? hi : cur - 1;
	else
		next = (cur == hi) ? lo : cur + 1;

	module->set_param(map.param_id, next / steps);
}

inline void latch_param(std::unique_ptr<CoreProcessor> &module, MappedKnob const &map, unsigned num_pos) {
	if (is_cycle(map))
		cycle_param(module, map, num_pos);
	else
		toggle_param(module, map);
}

inline void latch_button(std::unique_ptr<CoreProcessor> &module, MappedKnob const &map, unsigned num_pos, float val) {
	// Latching: toggle or cycle
	if (val > 0.5f) //rising edge
		latch_param(module, map, num_pos);
}
