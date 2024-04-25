#include "metamodule/svg.hh"
#include <app/SvgPort.hpp>

namespace rack::app
{

SvgPort::SvgPort() {
	addChild(fb);
	fb->addChild(shadow);
	// Avoid breakage if plugins fail to call setSvg()
	// In that case, just disable the shadow.
	shadow->box.size = math::Vec();
	fb->addChild(sw);
}

void SvgPort::setSvg(std::shared_ptr<window::Svg> svg) {
	sw->setSvg(svg);
	if (sw->svg) {
		box.size = sw->box.size;
		fb->box.size = sw->box.size;
	} else
		printf("SvgPort: svg with empty name\n");
}

void ThemedSvgPort::setSvg(std::shared_ptr<window::Svg> lightSvg, std::shared_ptr<window::Svg> darkSvg) {
	sw->setSvg(lightSvg);
	this->lightSvg = lightSvg;
	this->darkSvg = darkSvg;
}

} // namespace rack::app
