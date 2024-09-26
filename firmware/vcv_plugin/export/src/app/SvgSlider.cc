#include "console/pr_dbg.hh"
#include "metamodule/svg.hh"
#include <app/SvgSlider.hpp>

namespace rack::app
{

SvgSlider::SvgSlider()
	: fb(new widget::FramebufferWidget)
	, background(new widget::SvgWidget)
	, handle(new widget::SvgWidget) {
	addChild(fb);
	fb->addChild(background);
	fb->addChild(handle);
	// speed = 2.0;
}

SvgSlider::~SvgSlider() = default;

void SvgSlider::setBackgroundSvg(std::shared_ptr<window::Svg> svg) {
	if (svg && svg->filename.size()) {
		background->svg = svg;
		background->box.size = get_svg_size(background->svg->filename);
		this->box = background->box;
	} else
		pr_warn("Svgslider: Svg bg with empty name\n");
}

void SvgSlider::setHandleSvg(std::shared_ptr<window::Svg> svg) {
	if (svg && svg->filename.size()) {
		handle->svg = svg;
		handle->box.size = get_svg_size(svg->filename);
	} else
		pr_warn("Svgslider: Svg with empty name\n");
}

void SvgSlider::setHandlePos(math::Vec minHandlePos, math::Vec maxHandlePos) {
}

void SvgSlider::setHandlePosCentered(math::Vec minHandlePosCentered, math::Vec maxHandlePosCentered) {
}

} // namespace rack::app
