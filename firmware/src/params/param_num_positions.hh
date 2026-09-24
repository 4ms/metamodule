#pragma once
#include "CoreModules/elements/elements.hh"
#include "CoreModules/moduleFactory.hh"
#include "patch/patch_data.hh"
#include "util/overloaded.hh"
#include <string_view>

namespace MetaModule
{

// Returns the number of discrete positions of a param element (switches, snapped knobs, choices),
// or 0 if it's continuous
inline unsigned get_num_positions(Element const &element) {
	return std::visit(overloaded{
		[](BaseElement const &) { return 0u; },
		[]<typename T>(T const &el) requires(std::derived_from<T, Switch> || std::derived_from<T, KnobSnapped> ||
											 std::derived_from<T, AltParamChoice>)
		{ return el.num_pos; },
		},
		element);
}

// Returns the number of discrete positions of a module's param, or 0 if it's continuous or not found
inline unsigned get_param_num_positions(std::string_view module_slug, unsigned param_id) {
	auto const &info = ModuleFactory::getModuleInfo(module_slug);

	// Search in reverse (the matching element is the last one with the matching index)
	for (int el_id = std::min(info.indices.size(), info.elements.size()) - 1; el_id >= 0; el_id--) {
		if (info.indices[el_id].param_idx == param_id)
			return get_num_positions(info.elements[el_id]);
	}
	return 0;
}

// Buttons mapped to params with num_pos > 2 default to Cycle mode. Everything else defaults to Normal.
inline MappedKnob::CurveType default_curve_type(MappedKnob const &map, PatchData const &patch) {
	if (!map.is_button() && !map.is_midi_notegate())
		return MappedKnob::Normal;

	if (map.module_id >= patch.module_slugs.size())
		return MappedKnob::Normal;

	auto num_pos = get_param_num_positions(patch.module_slugs[map.module_id], map.param_id);
	return num_pos > 2 ? MappedKnob::Cycle : MappedKnob::Normal;
}

} // namespace MetaModule
