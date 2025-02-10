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

void ThemedSvgScrew::setSvg(std::shared_ptr<window::Svg> lightSvg, std::shared_ptr<window::Svg> darkSvg) {
	this->lightSvg = lightSvg;
	this->darkSvg = darkSvg;
	SvgScrew::setSvg(settings::preferDarkPanels ? darkSvg : lightSvg);
}
} // namespace rack::app
