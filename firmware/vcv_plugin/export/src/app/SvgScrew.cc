#include <app/SvgScrew.hpp>

namespace rack::app
{

SvgScrew::SvgScrew()
	: fb{new widget::FramebufferWidget}
	, sw{new widget::SvgWidget} {
	// fb and sw must be added to the widget tree so ~Widget/clearChildren frees them.
	// Without this they leak on every construction (3 blocks/screw: fb, fb->internal, sw)
	// — and since nearly every VCV panel has screws, this leaked on every module instance.
	addChild(fb);
	fb->addChild(sw);
}

SvgScrew::~SvgScrew() = default;

void SvgScrew::setSvg(std::shared_ptr<window::Svg> svg) {
}

} // namespace rack::app
