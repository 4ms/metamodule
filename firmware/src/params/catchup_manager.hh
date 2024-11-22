#pragma once
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
using ParamSet = std::array<std::vector<MappedParam>, PanelDef::NumKnobs>;

class CatchupManager {

	std::array<float, PanelDef::NumKnobs> panel_knobs{};

public:
	void set_panel_param(auto &modules, ParamSet &active_knob_maps, unsigned panel_knob_id, float val) {
		panel_knobs[panel_knob_id] = val;

		for (auto &knob_map : active_knob_maps[panel_knob_id]) {
			auto &map = knob_map.map;

			auto module_val = modules[map.module_id]->get_param(map.param_id);
			auto scaled_phys_val = map.get_mapped_val(val);
			if (auto v = knob_map.catchup.update(scaled_phys_val, module_val)) {
				modules[map.module_id]->set_param(map.param_id, *v);
			}
		}
	}

	void reset(auto &modules, ParamSet &active_knob_maps) {
		// Reset all catchups in the new active knobset.
		// This allows them to change to catchup mode if necessary
		for (unsigned i = 0u; auto &knob : active_knob_maps) {
			for (auto &map : knob) {
				auto module_val = modules[map.map.module_id]->get_param(map.map.param_id);
				map.catchup.reset_phys_val(panel_knobs[i], module_val);
			}
			i++;
		}
	}
};

} // namespace MetaModule
