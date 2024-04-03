#include <asset.hpp>
#include <plugin/Plugin.hpp>
#include <string_view>

namespace rack::asset
{

static void svg_to_png(std::string &path) {
	if (auto svg_pos = path.find(".svg"); svg_pos != std::string::npos) {
		path.replace(svg_pos, 4, ".png");
	}
}

static void set_drive(std::string &path) {
	// #ifdef METAMODULE_INTERNAL_PLUGIN
	// 	path = "M:/" + path;
	// #else
	// path = "P:/" + path;
	// #endif
}

std::string system(std::string_view filename) {
	auto path = std::string(filename);
	svg_to_png(path);

	const std::string_view prefix{"res/ComponentLibrary/"};
	if (path.starts_with(prefix)) {
		path = path.substr(prefix.length());
		path = std::string("rack-lib/") + path;
	}

	set_drive(path);
	return path;
}

std::string user(std::string_view filename) {
	auto path = std::string("usr/") + std::string(filename);
	svg_to_png(path);
	set_drive(path);
	return path;
}

std::string plugin(plugin::Plugin *plugin, std::string_view filename) {
	std::string path{filename};

	// Strip the res/
	if (path.substr(0, 4) == "res/") {
		path = path.substr(4);
	}

	// Add plugin/ if it exists
	if (plugin)
		path = plugin->slug + std::string("/") + path;
	else
		printf("No plugin slug\n");

	// .svg => .png
	svg_to_png(path);

	set_drive(path);

	return path;
}

std::string systemDir = "";
std::string userDir = "";
std::string bundlePath = "";

} // namespace rack::asset
