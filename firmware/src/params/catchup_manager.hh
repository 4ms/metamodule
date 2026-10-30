#pragma once
#include "catchup_param.hh"
#include "panel_knob.hh"
#include "patch-serial/patch/patch.hh"
#include "toggle_param.hh"
#include <algorithm>
#include <cmath>
#include <vector>

namespace MetaModule
{

struct MappedParam {
	MappedKnob map;
	CatchupParam catchup;
	uint16_t num_pos = 0; // Number of discrete positions of the module param (0 = continuous), used by Cycle maps
};
//[0-11] knobs
//[12-43] buttons
using ParamSet = std::array<std::vector<MappedParam>, NumTotalParams>;

class CatchupManager {

	std::array<float, NumTotalParams> panel_knobs{0.f};
	std::array<bool, NumTotalParams> catchup_inaccessible{false};

	CatchupParam::Mode default_mode{CatchupParam::Mode::ResumeOnMotion};

	bool allow_jump_out_of_range = false;

public:
	void set_panel_param(auto &modules, ParamSet &active_knob_maps, unsigned panel_knob_id, float val) {
		if (panel_knob_id >= panel_knobs.size())
			return;

		panel_knobs[panel_knob_id] = val;

		for (auto &knob_map : active_knob_maps[panel_knob_id]) {
			auto &map = knob_map.map;

			if (is_button(map)) {
				if (is_latching(map)) {
					latch_button(modules[map.module_id], map, knob_map.num_pos, val);
				} else {
					modules[map.module_id]->set_param(map.param_id, map.get_mapped_val(val));
				}
				continue;
			}

			// For performance if it's ResumeOnMotion, then just call module[]->set_param (skip calls to get_param)
			if (knob_map.catchup.mode == CatchupParam::Mode::ResumeOnMotion) {
				knob_map.catchup.update(map.get_mapped_val(val), {});
				modules[map.module_id]->set_param(map.param_id, map.get_mapped_val(val));
				continue;
			}

			auto module_val = modules[map.module_id]->get_param(map.param_id);
			auto scaled_phys_val = map.get_mapped_val(val); //0.501 to 0

			if (auto v = knob_map.catchup.update(scaled_phys_val, module_val)) {
				modules[map.module_id]->set_param(map.param_id, *v);

				// Read the module's value back after setting it. This handles cases where the
				// module stores a different value than the one set.
				// E.g. "ParamQuantity::snapEnabled" or "Pot::integral"
				auto new_module_val = modules[map.module_id]->get_param(map.param_id);
				knob_map.catchup.report_actual_module_val(new_module_val);

			} else {

				if (auto new_panel_val = check_out_of_range(val, module_val, map)) {
					if (allow_jump_out_of_range) {
						jump_param(modules, knob_map, scaled_phys_val, *new_panel_val);
					} else {
						catchup_inaccessible[panel_knob_id] = true;
					}
				}
			}
		}
	}

	// Pro: a panel encoder turned `clicks` clicks (positive = clockwise). Each param it's mapped to
	// moves from its value by `step` per click (in the map's 0..1 range), or by one position per click
	// if it has discrete positions. There's no catchup: nothing jumps.
	void step_panel_encoder(auto &modules, ParamSet &active_knob_maps, unsigned panel_knob_id, int clicks, float step) {
		if (panel_knob_id >= PanelDef::NumKnobs)
			return;

		for (auto &knob_map : active_knob_maps[panel_knob_id]) {
			auto &map = knob_map.map;
			auto &module = modules[map.module_id];
			auto module_val = module->get_param(map.param_id);

			float pos;
			if (knob_map.num_pos > 1) {
				float const last_pos = knob_map.num_pos - 1;
				int const dir = map.max < map.min ? -1 : 1;
				pos = map.unmap_val((std::round(module_val * last_pos) + dir * clicks) / last_pos);
			} else {
				pos = knob_map.catchup.encoder_pos(module_val).value_or(map.unmap_val(module_val)) + clicks * step;
			}
			pos = std::clamp(pos, 0.f, 1.f);

			module->set_param(map.param_id, map.get_mapped_val(pos));
			knob_map.catchup.set_encoder_pos(pos, module->get_param(map.param_id));
		}
	}

	std::optional<float> check_out_of_range(float panel_val, float module_val, MappedKnob const &map) {
		// If user moves the knob to the extreme position (0 or 1), and the module's knob
		// is still not reachable, then mark this catchup as inaccessible.
		// The GUI thread will query for this state and send a notification.
		bool pot_low = panel_val < 2.f / 4095.f;
		bool pot_high = panel_val > 4093.f / 4095.f;

		if (pot_low || pot_high) {
			auto min_scaled = map.get_mapped_val(0);
			auto max_scaled = map.get_mapped_val(1);
			if (min_scaled > max_scaled) {
				std::swap(min_scaled, max_scaled);
				std::swap(pot_low, pot_high);
			}

			if ((pot_low && module_val < min_scaled) || (pot_high && module_val > max_scaled)) {
				return float(pot_low ? min_scaled : max_scaled);
			}
		}

		return std::nullopt;
	}

	void set_panel_param_no_play(unsigned panel_knob_id, float val) {
		panel_knobs[panel_knob_id] = val;
	}

	bool is_out_of_range(unsigned panel_knob_id) {
		if (panel_knob_id < catchup_inaccessible.size()) {
			auto res = catchup_inaccessible[panel_knob_id];
			catchup_inaccessible[panel_knob_id] = false;
			return res;
		} else
			return false;
	}

	void jump_param(auto &modules, MappedParam &map, float scaled_phys_val, float new_panel_val) {
		map.catchup.enter_tracking(scaled_phys_val);
		modules[map.map.module_id]->set_param(map.map.param_id, new_panel_val);
		auto new_module_val = modules[map.map.module_id]->get_param(map.map.param_id);
		map.catchup.report_actual_module_val(new_module_val);
	}

	void recalc_panel_param(auto &modules, ParamSet &active_knob_maps, unsigned panel_knob_id) {
		// An encoder has no position to set its params to
		if (PanelDef::is_encoder(panel_knob_id))
			return;

		if (panel_knob_id < catchup_inaccessible.size())
			catchup_inaccessible[panel_knob_id] = false;
		set_panel_param(modules, active_knob_maps, panel_knob_id, panel_knobs[panel_knob_id]);
	}

	void reset(auto &modules, ParamSet &active_knob_maps) {

		// Reset all catchups in the new active knobset.
		// This allows them to change to catchup mode if necessary
		for (unsigned i = 0u; auto &knob : active_knob_maps) {

			for (auto &knob_map : knob) {
				if (is_button(knob_map.map) || is_panel_encoder(knob_map.map))
					continue;

				auto module_val = modules[knob_map.map.module_id]->get_param(knob_map.map.param_id);
				float scaled_phys_val = knob_map.map.get_mapped_val(panel_knobs[i]);

				knob_map.catchup.reset_phys_val(scaled_phys_val, module_val);

				if (auto new_panel_val = check_out_of_range(panel_knobs[i], module_val, knob_map.map)) {
					if (allow_jump_out_of_range) {
						jump_param(modules, knob_map, scaled_phys_val, *new_panel_val);
					} else {
						catchup_inaccessible[i] = true;
					}
				}
			}
			i++;
		}

		for (auto &stuck : catchup_inaccessible) {
			stuck = false;
		}
	}

	void set_default_mode(CatchupParam::Mode mode, bool allow_jump_outofrange) {
		default_mode = mode;
		allow_jump_out_of_range = allow_jump_outofrange;
	}

	CatchupParam::Mode get_default_mode() {
		return default_mode;
	}
};

} // namespace MetaModule
