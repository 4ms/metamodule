#pragma once
#include "CoreModules/elements/element_counter.hh"
#include "patch_file/patch_location.hh"
#include <cstdint>
#include <optional>

namespace MetaModule
{

// Tabs of the System Menu, in the order they appear
enum class SystemMenuTabId : unsigned { Info, Plugins, Prefs, System, FirmwareUpdate, NumTabs };

struct PageArguments {
	std::optional<PatchLocation> patch_loc{};
	std::optional<PatchLocHash> patch_loc_hash{};
	std::optional<uint16_t> module_id{};
	std::optional<uint16_t> mappedknob_id{};
	std::optional<uint32_t> view_knobset_id{};
	std::optional<ElementCount::Counts> element_counts{};
	std::optional<ElementCount::Indices> element_indices{};
	std::optional<bool> detail_mode{};
	std::optional<std::pair<float, float>> element_mm{};
	std::optional<bool> replace_module{};
	std::optional<SystemMenuTabId> system_menu_tab{};

	bool operator==(PageArguments const &that) const = default;
};

} // namespace MetaModule
