#include "window/Svg.hpp"
#include "metamodule/svg.hh"
#include "util/static_string.hh"

namespace rack::window
{

struct Svg::Internal {
	StaticString<255> filename;
	math::Vec size{};
};

std::string_view Svg::filename() {
	if (handle)
		return handle->filename;
	else
		return "";
}

// Svg::Svg(std::string_view fname) {
// 	loadFile(std::string(fname));
// }

Svg::~Svg() {
	if (handle)
		delete handle;
}

std::shared_ptr<Svg> Svg::load(const std::string &filename) {
	auto svg = std::make_shared<Svg>();
	svg->loadFile(filename);
	return svg;
}

void Svg::loadFile(const std::string &filename) {
	if (!handle) {
		handle = new Internal;
	}
	handle->filename.copy(filename);
	handle->size = get_svg_size(filename);
}

void Svg::loadString(const std::string &str) {
	// not supported
}

math::Vec Svg::getSize() {
	if (handle)
		return handle->size;
	else
		return {};
}

int getNumShapes() {
	return 0;
}

int getNumPaths() {
	return 0;
}

int getNumPoints() {
	return 0;
}

void draw(NVGcontext *vg) {
}

} // namespace rack::window
