#include <app/SvgScrew.hpp>

namespace rack::app
{

SvgScrew::SvgScrew()
	: fb{new widget::FramebufferWidget}
	, sw{new widget::SvgWidget} {
}

SvgScrew::~SvgScrew() = default;

void SvgScrew::setSvg(std::shared_ptr<window::Svg> svg) {
}

} // namespace rack::app
