#pragma once
#include "CoreModules/element_group.hh"
#include "gui/elements/context.hh"
#include <cstdint>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace MetaModule
{

// How a module's elements are listed in the module view's element list: its groups,
// top-level order, and custom names from plugin-mm.json, resolved against the module's
// drawn elements.
//
// This is the only place that resolves them, so the module view and the image
// generation test always agree on what's an error.
struct ElementLayout {
	static constexpr int16_t NoGroup = -1;

	struct Entry {
		bool is_group;
		unsigned idx; // group index, or drawn element index
	};

	std::vector<std::string_view> group_names;
	std::vector<std::vector<unsigned>> group_members; // drawn element indices, in the order they're shown
	std::vector<int16_t> element_group;				  // the group that each drawn element belongs to, or NoGroup
	std::vector<std::string_view> element_display_name; // custom name for each drawn element, or empty
	std::vector<Entry> top_level_entries;				// the top-level list, in the order it's shown

	// Problems with the module's groups, order, or names: each one is a mistake in plugin-mm.json
	std::vector<std::string> errors;

	void build(std::string_view slug, std::vector<DrawnElement> const &drawn_elements);

	// A name in a module's order that names one of its groups
	std::optional<unsigned> find_group(ElementRef const &ref) const;
};

// The drawn element that an ElementRef refers to: by name, by index into the module's
// Elements array, or by param/jack/light id
std::optional<unsigned> resolve_element_ref(std::vector<DrawnElement> const &drawn_elements, ElementRef const &ref);

} // namespace MetaModule
