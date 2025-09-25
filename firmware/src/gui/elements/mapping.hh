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

// Finds mappings in the given knob_set OR in the MIDI knob set
// If there are mappings in both, then it prioritizes returning the non-MIDI mapping
inline std::optional<uint16_t> find_mapping(const ParamElement &,
											const PatchData &patch,
											uint16_t module_idx,
											unsigned knob_set,
											ElementCount::Indices const indices) {
	if (knob_set == PatchData::MIDIKnobSet) {
		if (auto panel_map = patch.find_midi_map(module_idx, indices.param_idx))
			return panel_map->panel_knob_id;
		else
			return {};
	} else {
		if (auto panel_map = patch.find_mapped_knob(knob_set, module_idx, indices.param_idx))
			return panel_map->panel_knob_id;
		else if (auto panel_map = patch.find_midi_map(module_idx, indices.param_idx))
			return panel_map->panel_knob_id;
		else
			return {};
	}
}

// Finds panel mappings to the given input jack.
// If knob_set is MIDIKnobSet, then it will look for MIDI maps, otherwise it returns the first mapping it finds
// TODO: make this prioritize non-MIDI mappings?
inline std::optional<uint16_t> find_mapping(const JackInput &,
											const PatchData &patch,
											uint16_t module_idx,
											unsigned knob_set,
											ElementCount::Indices const indices) {
	if (knob_set == PatchData::MIDIKnobSet) {
		if (auto panel_map = patch.find_mapped_midi_injack(Jack{(uint16_t)module_idx, indices.input_idx}))
			return panel_map->panel_jack_id;

	} else if (auto panel_map = patch.find_mapped_injack(Jack{(uint16_t)module_idx, indices.input_idx}))
		return panel_map->panel_jack_id;

	return {};
}

// Finds panel mappings to the given output jack
// We don't support MIDI output maps, so the knob_set parameter is ignored
inline std::optional<uint16_t> find_mapping(const JackOutput &,
											const PatchData &patch,
											uint16_t module_idx,
											unsigned knob_set,
											ElementCount::Indices const indices) {
	if (auto panel_map = patch.find_mapped_outjack(Jack{(uint16_t)module_idx, indices.output_idx}))
		return panel_map->panel_jack_id;
	else
		return {};
}
}; // namespace ElementMapping

} // namespace MetaModule
