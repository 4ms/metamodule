#include "patch_player.hh"

namespace MetaModule
{

// Set mode for all maps
void PatchPlayer::set_catchup_mode(CatchupParam::Mode mode, bool allow_jump_outofrange) {
	catchup_manager.set_default_mode(mode, allow_jump_outofrange);

	for (auto &knobset : knob_maps) {
		for (auto &knob : knobset) {
			for (auto &map : knob) {
				map.catchup.set_mode(mode);
			}
		}
	}
}

// Set mode for one mapping only
// If knob_set_idx is out of range, then active knob set will be changed.
void PatchPlayer::set_catchup_mode(int knob_set_idx, unsigned module_id, unsigned param_id, CatchupParam::Mode mode) {
	if (knob_set_idx < 0 || knob_set_idx >= (int)knob_maps.size())
		knob_set_idx = active_knob_set;

	for (auto &knob : knob_maps[knob_set_idx]) {
		for (auto &map : knob) {
			if (map.map.module_id == module_id && map.map.param_id == param_id) {
				map.catchup.set_mode(mode);
				return;
			}
		}
	}
}

// Set mode for a particular param on a particular module, in any/all knobsets
void PatchPlayer::set_catchup_mode(unsigned module_id, unsigned param_id, CatchupParam::Mode mode) {
	for (auto &knobset : knob_maps) {
		for (auto &knob : knobset) {
			for (auto &map : knob) {
				if (map.map.module_id == module_id && map.map.param_id == param_id) {
					map.catchup.set_mode(mode);
					return;
				}
			}
		}
	}
}

bool PatchPlayer::is_param_tracking(unsigned module_id, unsigned param_id) {
	for (auto const &knob : knob_maps[active_knob_set]) {
		for (auto const &map : knob) {
			if (map.map.module_id == module_id && map.map.param_id == param_id) {
				return map.catchup.is_tracking();
			}
		}
	}
	return false;
}

std::optional<unsigned> PatchPlayer::panel_knob_catchup_inaccessible() {
	for (auto panel_knob_id = 0u; panel_knob_id < PanelDef::NumKnobs; panel_knob_id++) {
		if (catchup_manager.is_out_of_range(panel_knob_id))
			return panel_knob_id;
	}
	return {};
}

} // namespace MetaModule
