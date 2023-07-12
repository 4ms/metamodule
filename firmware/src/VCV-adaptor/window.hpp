#pragma once
#include "VCV-adaptor/math.hpp"
#include <string_view>

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
	void loadString(std::string_view str) {
	}
	// math::Vec getSize() { return {0, 0}; }
	// int getNumShapes() { return 0; }
	// int getNumPaths() { return 0; }
	// int getNumPoints() { return 0; }
	static Svg *load(std::string_view filename) {
		return nullptr;
	}
};

struct Font {};
struct Image {};

struct Window {
	Font *loadFont(std::string_view) {
		return nullptr;
	}

	Image *loadImage(std::string_view) {
		return nullptr;
	}

	Svg *loadSvg(std::string_view) {
		return nullptr;
	}
};

} // namespace rack::window
