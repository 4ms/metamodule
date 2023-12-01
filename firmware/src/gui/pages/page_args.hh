#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "patch_file/patch_location.hh"
#include <cstdint>
#include <optional>

namespace MetaModule
{

struct PageArguments {
	std::optional<PatchLocation> selected_patch_loc{};
	std::optional<uint16_t> selected_module_id{};
	std::optional<uint16_t> selected_mappedknob_id{};
	std::optional<uint16_t> selected_knob_id{};
	// std::optional<uint16_t> active_knobset_id{};
	std::optional<uint16_t> view_knobset_id{};
	std::optional<ElementCount::Counts> selected_element_counts{};
	std::optional<ElementCount::Indices> selected_element_indices{};

	bool operator==(PageArguments const &that) const = default;
};

} // namespace MetaModule
