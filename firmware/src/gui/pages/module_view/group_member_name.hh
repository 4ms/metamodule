#pragma once
#include <string>
#include <string_view>

namespace MetaModule::ModView
{

// Call fn(word) for each space-separated word in str
template<typename F>
void for_each_word(std::string_view str, F &&fn) {
	while (str.size()) {
		auto end = str.find(' ');
		auto word = str.substr(0, end);
		if (word.size())
			fn(word);
		if (end == std::string_view::npos)
			break;
		str.remove_prefix(end + 1);
	}
}

// How a group member's name is shown inside its group: any word that's also a word in the
// group's name is removed, since the group name is shown as a header above it.
// Words are separated by spaces only, and matching is case-sensitive.
// e.g. In group "Channel A", "Feedback A" is shown as "Feedback", but "A1_Gain" is unchanged.
// A name that would be left empty is shown unchanged.
inline std::string group_member_name(std::string_view name, std::string_view group_name) {
	auto in_group_name = [group_name](std::string_view word) {
		bool found = false;
		for_each_word(group_name, [&](std::string_view group_word) { found = found || group_word == word; });
		return found;
	};

	std::string display;
	for_each_word(name, [&](std::string_view word) {
		if (in_group_name(word))
			return;
		if (display.size())
			display += ' ';
		display += word;
	});

	return display.size() ? display : std::string(name);
}

} // namespace MetaModule::ModView
