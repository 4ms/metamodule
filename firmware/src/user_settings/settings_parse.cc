#include "settings_parse.hh"
#include "ryml.hpp"
#include "ryml_init.hh"
#include "ryml_std.hpp"
#include <span>

namespace MetaModule
{

template<typename T>
void read_or_default(ryml::ConstNodeRef const &n, c4::csubstr name, T *s, auto member_ptr) {
	if (n.is_map() && n.has_child(name)) {
		n[name] >> s->*member_ptr;
	} else {
		s->*member_ptr = T{}.*member_ptr;
	}
}

namespace Settings
{

bool parse(std::span<char> yaml, UserSettings *settings) {
	RymlInit::init_once();

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(yaml.data(), yaml.size()));

	if (tree.num_children(0) == 0)
		return false;

	ryml::ConstNodeRef root = tree.rootref();

	if (!root.has_child("Settings"))
		return false;

	ryml::ConstNodeRef node = root["Settings"];

	read_or_default(node, "low_sel", settings, &UserSettings::low_sel);
	read_or_default(node, "mid_sel", settings, &UserSettings::mid_sel);
	read_or_default(node, "high_sel", settings, &UserSettings::high_sel);

	return true;
}

} // namespace Settings
} // namespace MetaModule
