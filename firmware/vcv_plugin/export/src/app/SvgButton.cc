#include "metamodule/svg.hh"
#include <app/SvgButton.hpp>

namespace rack::app
{

SvgButton::SvgButton()
	: fb(new widget::FramebufferWidget)
	, shadow(new CircularShadow)
	, sw(new widget::SvgWidget) {
	addChild(fb);
	fb->addChild(shadow);
	shadow->box.size = math::Vec();
	fb->addChild(sw);
}

SvgButton::~SvgButton() = default;

void SvgButton::addFrame(std::shared_ptr<window::Svg> svg) {
	if (svg->filename.length()) {
		frames.push_back(svg);
		if (frames.size() == 1) {
			sw->setSvg(svg);
			box.size = get_svg_size(svg->filename);
		}
	}
}

} // namespace rack::app
