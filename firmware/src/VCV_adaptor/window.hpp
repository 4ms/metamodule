#pragma once
#include "VCV_adaptor/math.hpp"
#include <memory>
#include <string>
#include <string_view>
#include <utility>

namespace rack::window
{
static const float SVG_DPI = 75.f;
static const float MM_PER_IN = 25.4f;

inline float in2px(float in) {
	return in * SVG_DPI;
}

inline math::Vec in2px(math::Vec in) {
	return in.mult(SVG_DPI);
}

inline float mm2px(float mm) {
	return mm * (SVG_DPI / MM_PER_IN);
}

inline math::Vec mm2px(math::Vec mm) {
	return mm.mult(SVG_DPI / MM_PER_IN);
}

struct Svg {
	std::string filename;

	Svg(std::string_view fname)
		: filename{fname} {
	}

	// void loadString(std::string_view str) {
	// }
	// math::Vec getSize() { return {0, 0}; }
	// int getNumShapes() { return 0; }
	// int getNumPaths() { return 0; }
	// int getNumPoints() { return 0; }
	static std::shared_ptr<Svg> load(std::string_view filename) {
		printf("Svg::load %.*s\n", filename.size(), filename.data());
		return std::make_shared<Svg>(filename);
	}
};

struct Font {
	int handle;
};

struct Image {};

struct Window {
	std::shared_ptr<Font> loadFont(std::string_view) {
		return nullptr;
	}

	std::shared_ptr<Image> loadImage(std::string_view) {
		return nullptr;
	}

	std::shared_ptr<Svg> loadSvg(std::string const &filename) {
		printf("Window::loadSvg %.*s\n", (int)filename.size(), filename.data());
		auto svg = std::make_shared<Svg>(filename);
		return svg;
	}
};

} // namespace rack::window
