#pragma once
#include "VCV_adaptor/plugin/Plugin.hpp"
#include <string_view>

namespace rack::asset
{

inline std::string system(std::string_view filename = "") {
	return std::string("sys/") + std::string(filename);
}

inline std::string user(std::string_view filename = "") {
	return std::string("usr/") + std::string(filename);
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
