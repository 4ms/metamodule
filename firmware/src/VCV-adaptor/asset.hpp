#pragma once
#include "VCV-adaptor/plugin/Plugin.hpp"
#include <string_view>

namespace rack::asset
{

inline std::string_view system(std::string_view filename = "") {
	return "";
}

inline std::string_view user(std::string_view filename = "") {
	return "";
}

inline std::string_view plugin(plugin::Plugin *plugin, std::string_view filename = "") {
	return "";
}

} // namespace rack::asset
