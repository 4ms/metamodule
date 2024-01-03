#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "patch_file/patch_location.hh"
#include <cstdint>
#include <optional>

namespace MetaModule
{

struct PageArguments {
	std::optional<PatchLocation> patch_loc{};
	std::optional<PatchLocHash> patch_loc_hash{};
	std::optional<uint16_t> module_id{};
	std::optional<uint16_t> mappedknob_id{};
	std::optional<uint16_t> view_knobset_id{};
	std::optional<ElementCount::Counts> element_counts{};
	std::optional<ElementCount::Indices> element_indices{};

	bool operator==(PageArguments const &that) const = default;
};

} // namespace MetaModule
