#include "settings_serialize.hh"
#include "ryml.hpp"
#include "ryml_init.hh"
#include "ryml_std.hpp"
#include <span>

namespace MetaModule
{

namespace Settings
{

uint32_t serialize(UserSettings const &settings, std::span<char> buffer) {
	RymlInit::init_once();

	ryml::Tree tree;
	auto root = tree.rootref();
	root |= ryml::MAP;

	auto data = root["Settings"];
	data |= ryml::MAP;

	data["low_sel"] << settings.low_sel;
	data["mid_sel"] << settings.mid_sel;
	data["high_sel"] << settings.high_sel;

	auto res = ryml::emit_yaml(tree, c4::substr(buffer.data(), buffer.size()));
	return res.size();
}

//
} // namespace Settings
} // namespace MetaModule
