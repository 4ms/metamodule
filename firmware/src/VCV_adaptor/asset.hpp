#pragma once
#include "VCV_adaptor/plugin/Plugin.hpp"
#include <string_view>

namespace rack::asset
{

inline void svg_to_png(std::string &path) {
	if (auto svg_pos = path.find(".svg"); svg_pos != std::string::npos) {
		path.replace(svg_pos, 4, ".png");
	}
}

inline std::string system(std::string_view filename = "") {
	auto path = std::string("sys/") + std::string(filename);
	svg_to_png(path);
	return path;
}

inline std::string user(std::string_view filename = "") {
	auto path = std::string("usr/") + std::string(filename);
	svg_to_png(path);
	return path;
}

inline std::string plugin(plugin::Plugin *plugin, std::string_view filename = "") {
	std::string path = "";
	if (plugin)
		path = plugin->slug + std::string("/");

	path += filename;
	svg_to_png(path);
	return path;
}

} // namespace rack::asset
