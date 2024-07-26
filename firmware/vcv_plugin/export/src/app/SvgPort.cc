#include "console/pr_dbg.hh"
#include "metamodule/svg.hh"
#include <app/SvgPort.hpp>

namespace rack::app
{

SvgPort::SvgPort()
	: fb(new widget::FramebufferWidget)
	, shadow(new CircularShadow)
	, sw(new widget::SvgWidget) {
	addChild(fb);
	fb->addChild(shadow);

	shadow->box.size = math::Vec();

	fb->addChild(sw);
}

void SvgPort::setSvg(std::shared_ptr<window::Svg> svg) {
	sw->setSvg(svg);
	if (sw->svg) {
		box.size = sw->box.size;
		fb->box.size = sw->box.size;
	} else
		pr_err("SvgPort: svg with empty name\n");
}

void ThemedSvgPort::setSvg(std::shared_ptr<window::Svg> lightSvg, std::shared_ptr<window::Svg> darkSvg) {
	// Get the box size from either SVG that will load
	SvgPort::setSvg(lightSvg);
	if (!box.size.isFinite())
		SvgPort::setSvg(darkSvg);

	this->lightSvg = lightSvg;
	this->darkSvg = darkSvg;
}

} // namespace rack::app
