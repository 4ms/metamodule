#pragma once

#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
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

	std::optional<MappingDest> map(uint16_t module_id, ElementCount::Indices idx, PatchData &patch) {
		if (idx.param_idx != ElementCount::Indices::NoElementMarker) {

			// Abort if param is already mapped
			for (auto set_i : std::views::iota(0u, patch.knob_sets.size())) {
				if (patch.find_mapped_knob_idx(set_i, module_id, idx.param_idx).has_value()) {
					return std::nullopt;
				}
			}

			// Find first knobset with an unmapped panel knob
			for (uint16_t set_i : std::views::iota(0u, std::min<size_t>(MaxKnobSets, patch.knob_sets.size() + 1))) {

				for (uint16_t panel_knob_id : std::views::iota(0u, PanelDef::NumKnobs)) {
					if (patch.find_mapped_knob(set_i, panel_knob_id) == nullptr) {

						auto map = MappedKnob{.panel_knob_id = panel_knob_id,
											  .module_id = module_id,
											  .param_id = idx.param_idx,
											  .min = 0,
											  .max = 1,
											  .alias_name = ""};

						if (patch.add_update_mapped_knob(set_i, map)) {
							patch_mod_queue.put(AddMapping{.map = map, .set_id = set_i});
							return MappingDest{panel_knob_id, set_i};
						}
					}
				}
			}
			return std::nullopt;

		} else if (idx.input_idx != ElementCount::Indices::NoElementMarker) {
		} else if (idx.output_idx != ElementCount::Indices::NoElementMarker) {
		} else if (idx.light_idx != ElementCount::Indices::NoElementMarker) {
			// no mappings for lights
		}

		return std::nullopt;
	}
};

} // namespace MetaModule
