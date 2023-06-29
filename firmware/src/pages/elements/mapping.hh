#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "pages/elements/context.hh"
#include "patch/patch_data.hh"
#include <cstdint>

namespace MetaModule
{

namespace ElementMapping
{

inline std::optional<uint16_t> find_mapping(const BaseElement &, const PatchData &, uint16_t, ElementCount::Indices) {
	return {};
}

inline std::optional<uint16_t>
find_mapping(const ParamElement &, const PatchData &patch, uint16_t module_idx, ElementCount::Indices indices) {
	if (auto panel_map = patch.find_mapped_knob(module_idx, indices.param_idx))
		return panel_map->panel_knob_id;
	else
		return {};
}

inline std::optional<uint16_t>
find_mapping(const JackInput &, const PatchData &patch, uint16_t module_idx, ElementCount::Indices indices) {
	if (auto panel_map = patch.find_mapped_injack(Jack(module_idx, indices.input_idx)))
		return panel_map->panel_jack_id;
	else
		return {};
}

inline std::optional<uint16_t>
find_mapping(const JackOutput &, const PatchData &patch, uint16_t module_idx, ElementCount::Indices indices) {
	if (auto panel_map = patch.find_mapped_outjack(Jack{(uint16_t)module_idx, indices.output_idx}))
		return panel_map->panel_jack_id;
	else
		return {};
}
}; // namespace ElementMapping

} // namespace MetaModule
