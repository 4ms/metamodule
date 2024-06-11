#include "metamodule/svg.hh"
#include <app/SvgSwitch.hpp>

namespace rack::app
{

SvgSwitch::SvgSwitch()
	: fb(new widget::FramebufferWidget)
	, shadow(new CircularShadow)
	, sw(new widget::SvgWidget) {
	addChild(fb);
	fb->addChild(shadow);
	shadow->box.size = math::Vec();
	fb->addChild(sw);
}

SvgSwitch::~SvgSwitch() = default;

void SvgSwitch::addFrame(std::shared_ptr<window::Svg> svg) {
	if (svg->filename.length()) {
		frames.push_back(svg);
		if (frames.size() == 1) {
			box.size = get_svg_size(svg->filename);
			sw->box.size = box.size;
		}
	}
}

} // namespace rack::app
