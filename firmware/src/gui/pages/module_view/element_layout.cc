#include "gui/pages/module_view/element_layout.hh"
#include "CoreModules/moduleFactory.hh"
#include "util/countzip.hh"
#include "util/string_compare.hh"

namespace MetaModule
{

// getInputName()/getOutputName() append " In"/" Out" to a jack's name when it doesn't
// already contain that word. Accept the name as it reads in the plugin's source, so
// the author doesn't have to know that rule.
static bool matches_with_jack_suffix(std::string_view element_name, std::string_view ref_name) {
	if (element_name.size() <= ref_name.size())
		return false;

	if (!equal_ci(element_name.substr(0, ref_name.size()), ref_name))
		return false;

	auto suffix = element_name.substr(ref_name.size());
	return equal_ci(suffix, " In") || equal_ci(suffix, " Out");
}

std::optional<unsigned> resolve_element_ref(std::vector<DrawnElement> const &drawn_elements, ElementRef const &ref) {
	constexpr auto NoIdx = ElementCount::Indices::NoElementMarker;

	if (ref.kind == ElementRef::Kind::Name) {
		// An exact name wins over one that only matches once " In"/" Out" is
		// allowed, so "Pitch" finds the knob even if there's also a "Pitch In" jack
		for (auto [i, drawn_element] : enumerate(drawn_elements)) {
			if (equal_ci(base_element(drawn_element.element).short_name, ref.name))
				return i;
		}

		for (auto [i, drawn_element] : enumerate(drawn_elements)) {
			if (matches_with_jack_suffix(base_element(drawn_element.element).short_name, ref.name))
				return i;
		}

		return std::nullopt;
	}

	if (ref.kind == ElementRef::Kind::ElementIdx) {
		if (ref.idx < drawn_elements.size())
			return ref.idx;
		return std::nullopt;
	}

	for (auto [i, drawn_element] : enumerate(drawn_elements)) {
		auto const &idx = drawn_element.gui_element.idx;

		switch (ref.kind) {
			case ElementRef::Kind::Param:
				if (idx.param_idx != NoIdx && idx.param_idx == ref.idx)
					return i;
				break;
			case ElementRef::Kind::Input:
				if (idx.input_idx != NoIdx && idx.input_idx == ref.idx)
					return i;
				break;
			case ElementRef::Kind::Output:
				if (idx.output_idx != NoIdx && idx.output_idx == ref.idx)
					return i;
				break;
			case ElementRef::Kind::Light:
				if (idx.light_idx != NoIdx && idx.light_idx == ref.idx)
					return i;
				break;
			default:
				break;
		}
	}

	return std::nullopt;
}

std::optional<unsigned> ElementLayout::find_group(ElementRef const &ref) const {
	if (ref.kind != ElementRef::Kind::Name)
		return std::nullopt;

	for (auto [i, group_name] : enumerate(group_names)) {
		if (equal_ci(group_name, ref.name))
			return i;
	}
	return std::nullopt;
}

// Resolve this module's registered groups, order, and custom names against its drawn elements.
void ElementLayout::build(std::string_view slug, std::vector<DrawnElement> const &drawn_elements) {
	group_names.clear();
	group_members.clear();
	top_level_entries.clear();
	errors.clear();
	element_group.assign(drawn_elements.size(), NoGroup);
	element_display_name.assign(drawn_elements.size(), {});

	auto resolve = [&drawn_elements](ElementRef const &ref) {
		return resolve_element_ref(drawn_elements, ref);
	};

	for (auto const &group : ModuleFactory::getElementGroups(slug)) {
		auto group_idx = (int16_t)group_names.size();
		std::vector<unsigned> members;

		for (auto const &ref : group.members) {
			auto drawn_idx = resolve(ref);

			if (!drawn_idx) {
				errors.push_back("group '" + group.name + "' has no element '" + ref.describe() + "'");
				continue;
			}

			// First group to claim an element keeps it
			if (element_group[*drawn_idx] != NoGroup)
				continue;

			element_group[*drawn_idx] = group_idx;
			members.push_back(*drawn_idx);
		}

		if (members.size()) {
			group_names.push_back(group.name);
			group_members.push_back(std::move(members));
		}
	}

	for (auto const &name : ModuleFactory::getElementNames(slug)) {
		auto drawn_idx = resolve(name.element);

		if (!drawn_idx) {
			errors.push_back("names: '" + name.element.describe() + "' is unknown");
			continue;
		}

		// First name given for an element is the one used
		if (element_display_name[*drawn_idx].size()) {
			errors.push_back("names: '" + name.element.describe() + "' appears more than once");
			continue;
		}

		element_display_name[*drawn_idx] = name.name;
	}

	std::vector<bool> element_placed(drawn_elements.size(), false);
	std::vector<bool> group_placed(group_names.size(), false);

	auto place_group = [&](unsigned group) {
		if (!group_placed[group]) {
			group_placed[group] = true;
			top_level_entries.push_back({.is_group = true, .idx = group});
		}
	};

	auto place_element = [&](unsigned drawn_idx) {
		if (!element_placed[drawn_idx]) {
			element_placed[drawn_idx] = true;
			top_level_entries.push_back({.is_group = false, .idx = drawn_idx});
		}
	};

	// A name is a group's name before it's an element's
	for (auto const &ref : ModuleFactory::getElementOrder(slug)) {
		if (auto group = find_group(ref)) {
			place_group(*group);
			continue;
		}

		auto drawn_idx = resolve(ref);
		if (!drawn_idx) {
			errors.push_back("order: '" + ref.describe() + "' is unknown");
			continue;
		}

		if (auto group = element_group[*drawn_idx]; group != NoGroup) {
			errors.push_back("order: " + ref.describe() + " is already in group '" + std::string(group_names[group]) +
							 "'");
			continue;
		}

		place_element(*drawn_idx);
	}

	for (unsigned i = 0; i < drawn_elements.size(); i++) {
		if (auto group = element_group[i]; group != NoGroup)
			place_group(group);
		else
			place_element(i);
	}
}

} // namespace MetaModule
