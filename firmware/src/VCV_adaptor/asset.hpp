#pragma once
#include "VCV_adaptor/plugin/Plugin.hpp"
#include <string_view>

namespace rack::asset
{

inline std::string_view system(std::string_view filename = "") {
	// printf("asset::system(%.*s)\n", (int)filename.size(), filename.data());
	return "";
}

inline std::string_view user(std::string_view filename = "") {
	// printf("asset::user(%.*s)\n", (int)filename.size(), filename.data());
	return "";
}

inline std::string plugin(plugin::Plugin *plugin, std::string_view filename = "") {
	std::string path = "";
	if (plugin)
		path = plugin->slug + std::string("/");
	path += filename;
	return path;
}

} // namespace rack::asset
