#pragma once

#include <memory>
#include <common.hpp>
#include <math.hpp>
#include <window/svg.hpp>

struct NVGLUframebuffer {
};

namespace rack::window {

// struct Svg {
// 	void loadString(std::string_view str);
// 	static std::shared_ptr<Svg> load(std::string_view filename);
// };

struct Font {
	int handle;
};

struct Image {};

struct Window {
	std::shared_ptr<Font> loadFont(std::string_view); 
	std::shared_ptr<Image> loadImage(std::string_view);
	std::shared_ptr<Svg> loadSvg(std::string_view); 
};
}

