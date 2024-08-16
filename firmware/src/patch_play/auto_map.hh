#pragma once

#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "conf/panel_conf.hh"
#include "console/pr_dbg.hh"
#include "patch/patch_data.hh"
#include "patch_play/patch_mod_queue.hh"
#include <ranges>
#include <span>

namespace MetaModule
{

class AutoMapper {
	PatchModQueue &patch_mod_queue;

public:
	AutoMapper(PatchModQueue &patch_mod_queue)
		: patch_mod_queue{patch_mod_queue} {
	}

	struct MappingDest {
		uint16_t panel_el_id{};
		uint16_t set_id{};
	};

	[[maybe_unused]] std::optional<MappingDest> map(uint16_t module_id, ElementCount::Indices idx, PatchData &patch) {
		if (idx.param_idx != ElementCount::Indices::NoElementMarker) {
			return map_param(module_id, idx.param_idx, patch);

		} else if (idx.input_idx != ElementCount::Indices::NoElementMarker) {
			return map_input(module_id, idx.input_idx, patch);

		} else if (idx.output_idx != ElementCount::Indices::NoElementMarker) {
			return map_output(module_id, idx.output_idx, patch);

		} else if (idx.light_idx != ElementCount::Indices::NoElementMarker) {
			// no mappings for lights
		}

		return std::nullopt;
	}

	std::optional<MappingDest> map_param(uint16_t module_id, uint16_t param_idx, PatchData &patch) {
		// Abort if param is already mapped
		for (auto set_i = 0u; set_i < patch.knob_sets.size(); set_i++) {
			if (patch.find_mapped_knob_idx(set_i, module_id, param_idx).has_value()) {
				return std::nullopt;
			}
		}

		// Map to first knobset with an unmapped panel knob
		for (uint16_t set_i = 0; set_i < std::min<size_t>(MaxKnobSets, patch.knob_sets.size() + 1); set_i++) {

			for (uint16_t panel_knob_id = 0; panel_knob_id < PanelDef::NumKnobs; panel_knob_id++) {
				if (patch.find_mapped_knob(set_i, panel_knob_id) == nullptr) {

					auto map = MappedKnob{.panel_knob_id = panel_knob_id,
										  .module_id = module_id,
										  .param_id = param_idx,
										  .min = 0,
										  .max = 1,
										  .alias_name = ""};

					if (patch.add_update_mapped_knob(set_i, map)) {
						patch_mod_queue.put(AddMapping{.map = map, .set_id = set_i});
						pr_trace("Auto mapping module %d param %d ", module_id, param_idx);
						pr_trace("to panel knob %d in set %d\n", panel_knob_id, set_i);
						return MappingDest{panel_knob_id, set_i};
					}
				}
			}
		}
		return std::nullopt;
	}

	std::optional<MappingDest> map_input(uint16_t module_id, uint16_t input_idx, PatchData &patch) {
		Jack jack{.module_id = module_id, .jack_id = input_idx};

		// Abort if already mapped to a panel
		if (patch.find_mapped_injack(jack)) {
			return std::nullopt;
		}

		// Abort if already patched to another module's output jack
		if (patch.find_internal_cable_with_injack(jack)) {
			return std::nullopt;
		}

		// Find first unmapped panel input jack
		// Note: we ignore Gate In jacks here, since we have no way to know if a jack is audio/CV or gate
		for (uint16_t panel_jack_id = 0; panel_jack_id < PanelDef::NumAudioIn; panel_jack_id++) {
			if (patch.find_mapped_injack(panel_jack_id) == nullptr) {
				patch.add_mapped_injack(panel_jack_id, jack);
				patch_mod_queue.put(
					AddJackMapping{.panel_jack_id = panel_jack_id, .jack = jack, .type = ElementType::Input});
				pr_trace("Auto mapping module %d injack %d to In %d\n", module_id, input_idx, panel_jack_id);
				return MappingDest{panel_jack_id};
			}
		}

		return std::nullopt;
	}

	std::optional<MappingDest> map_output(uint16_t module_id, uint16_t output_idx, PatchData &patch) {
		Jack jack{.module_id = module_id, .jack_id = output_idx};

		// Abort if already mapped to a panel
		if (patch.find_mapped_outjack(jack)) {
			return std::nullopt;
		}

		// Abort if already patched to another module
		if (patch.find_internal_cable_with_outjack(jack)) {
			return std::nullopt;
		}

		// Map to first unmapped panel output jack
		for (uint16_t panel_jack_id = 0; panel_jack_id < PanelDef::NumAudioOut; panel_jack_id++) {
			if (patch.find_mapped_outjack(panel_jack_id) == nullptr) {
				patch.add_mapped_outjack(panel_jack_id, jack);
				patch_mod_queue.put(
					AddJackMapping{.panel_jack_id = panel_jack_id, .jack = jack, .type = ElementType::Output});
				pr_trace("Auto mapping module %d outjack %d to In %d\n", module_id, output_idx, panel_jack_id);
				return MappingDest{panel_jack_id};
			}
		}

		return std::nullopt;
	}
};

} // namespace MetaModule
