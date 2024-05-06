#include "window/Svg.hpp"

namespace rack::window
{

Svg::Svg(std::string_view fname)
	: filename{fname} {
}

Svg::~Svg() = default;

} // namespace rack::window
