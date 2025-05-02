#pragma once
#include "CoreModules/hub/button_expander_defs.hh"
#include "catchup_param.hh"
#include "conf/panel_conf.hh"
#include "patch-serial/patch/patch.hh"
#include <vector>

namespace MetaModule
{

struct MappedParam {
	MappedKnob map;
	CatchupParam catchup;
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

			// Note: if needed, for performance we could check the catchup mode here, and
			// if it's ResumeOnMotion, then just call module[]->set_param (skip calls to get_param)

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
		if (panel_knob_id < catchup_inaccessible.size())
			catchup_inaccessible[panel_knob_id] = false;
		set_panel_param(modules, active_knob_maps, panel_knob_id, panel_knobs[panel_knob_id]);
	}

	void reset(auto &modules, ParamSet &active_knob_maps) {

		// Reset all catchups in the new active knobset.
		// This allows them to change to catchup mode if necessary
		for (unsigned i = 0u; auto &knob : active_knob_maps) {

			for (auto &knob_map : knob) {
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
