#pragma once
#include "ryml.hpp"
#include "ryml_init.hh"
#include "ryml_std.hpp"
#include <span>
#include <string>

namespace MetaModule::Plugin
{

inline bool parse_mm_json(std::span<char> file_data) {
	RymlInit::init_once();

	ryml::Tree tree = ryml::parse_in_place(ryml::substr(file_data.data(), file_data.size()));

	if (tree.num_children(0) == 0)
		return false;

	ryml::ConstNodeRef root = tree.rootref();

	if (!root.has_child("Settings"))
		return false;

	ryml::ConstNodeRef node = root["Settings"];

	return true;
}

} // namespace MetaModule::Plugin
