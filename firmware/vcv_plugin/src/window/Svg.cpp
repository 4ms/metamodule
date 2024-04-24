#include "window/Svg.hpp"

namespace rack::window
{

Svg::Svg(std::string_view fname)
	: filename{fname} {
	// printf("Svg(%s @%p)\n", filename.c_str(), filename.data());
}

Svg::~Svg() = default;
//{ printf("~Svg(%s @%p)\n", filename.c_str(), filename.data());}

} // namespace rack::window
