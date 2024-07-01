#pragma once

#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "console/pr_dbg.hh"
#include "patch/patch_data.hh"
#include <ranges>
#include <span>

namespace MetaModule
{

class AutoMapper {
public:
	static bool make(uint16_t module_id, ElementCount::Indices idx, PatchData &patch) {

		if (idx.param_idx != ElementCount::Indices::NoElementMarker) {

			// Abort if param is already mapped
			for (auto set_i : std::views::iota(0u, patch.knob_sets.size())) {
				if (patch.find_mapped_knob_idx(set_i, module_id, idx.param_idx).has_value()) {
					return false;
				}
			}

			// Find first knobset with an unmapped panel knob

			for (auto set_i : std::views::iota(0u, std::min<size_t>(MaxKnobSets, patch.knob_sets.size() + 1))) {

				for (uint16_t panel_knob_id : std::views::iota(0u, PanelDef::NumKnobs)) {
					if (patch.find_mapped_knob(set_i, panel_knob_id) == nullptr) {
						pr_dbg("Auto mapping module %d, param %d to panel knob %d in set %d\n",
							   module_id,
							   idx.param_idx,
							   panel_knob_id,
							   set_i);
						return patch.add_update_mapped_knob(set_i,
															MappedKnob{.panel_knob_id = panel_knob_id,
																	   .module_id = module_id,
																	   .param_id = uint16_t(idx.param_idx),
																	   .min = 0,
																	   .max = 1,
																	   .alias_name = ""});
					}
				}
			}
		} else if (idx.input_idx != ElementCount::Indices::NoElementMarker) {
		} else if (idx.output_idx != ElementCount::Indices::NoElementMarker) {
		} else if (idx.light_idx != ElementCount::Indices::NoElementMarker) {
			// no mappings for lights
		}

		return false;
	}
};

} // namespace MetaModule
