#include "window/Svg.hpp"

namespace rack::window
{

Svg::Svg(std::string_view fname)
	: filename{fname} {
}

Svg::~Svg() = default;

std::shared_ptr<Svg> Svg::load(const std::string &filename) {
	return make_shared<Svg>(filename);
}

} // namespace rack::window
