#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "gui/elements/context.hh"
#include "patch/patch_data.hh"
#include <cstdint>

namespace MetaModule
{

namespace ElementMapping
{

inline std::optional<uint16_t>
find_mapping(const BaseElement &, const PatchData &, uint16_t, unsigned, ElementCount::Indices const) {
	return {};
}

inline std::optional<uint16_t> find_mapping(const ParamElement &,
											const PatchData &patch,
											uint16_t module_idx,
											unsigned active_set,
											ElementCount::Indices const indices) {
	if (auto panel_map = patch.find_mapped_knob(active_set, module_idx, indices.param_idx))
		return panel_map->panel_knob_id;
	else if (auto panel_map = patch.find_midi_map(module_idx, indices.param_idx))
		return panel_map->panel_knob_id;
	else
		return {};
}

inline std::optional<uint16_t> find_mapping(
	const JackInput &, const PatchData &patch, uint16_t module_idx, unsigned, ElementCount::Indices const indices) {
	if (auto panel_map = patch.find_mapped_injack(Jack{(uint16_t)module_idx, indices.input_idx}))
		return panel_map->panel_jack_id;
	else
		return {};
}

inline std::optional<uint16_t> find_mapping(
	const JackOutput &, const PatchData &patch, uint16_t module_idx, unsigned, ElementCount::Indices const indices) {
	if (auto panel_map = patch.find_mapped_outjack(Jack{(uint16_t)module_idx, indices.output_idx}))
		return panel_map->panel_jack_id;
	else
		return {};
}
}; // namespace ElementMapping

} // namespace MetaModule
