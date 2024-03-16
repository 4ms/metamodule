#include "Widget.hh"
#include "svg.hh"

namespace rack::app
{

void SvgPort::setSvg(std::shared_ptr<window::Svg> svg) {
	if (svg->filename.size()) {
		svg_filename = svg->filename;
		box.size = get_svg_size(svg_filename);
		// printf("SvgPort:svg_filename %s\n", svg_filename.c_str());
	} else
		printf("SvgPort: svg with empty name\n");
}

void ThemedSvgPort::setSvg(std::shared_ptr<window::Svg> lightSvg, std::shared_ptr<window::Svg> darkSvg) {
	svg_filename = lightSvg->filename;
	this->lightSvg = lightSvg;
	this->darkSvg = darkSvg;
}

void SvgSlider::setBackgroundSvg(std::shared_ptr<window::Svg> svg) {
	if (svg->filename.size()) {
		background->svg_filename = svg->filename;
		background->box.size = get_svg_size(svg_filename);
	} else
		printf("Svgslider: Svg bg with empty name\n");
}

void SvgSlider::setHandleSvg(std::shared_ptr<window::Svg> svg) {
	if (svg->filename.size()) {
		handle->svg_filename = svg->filename;
		handle->box.size = get_svg_size(svg_filename);
	} else
		printf("Svgslider: Svg with empty name\n");
}

void SvgSlider::setHandlePos(math::Vec minHandlePos, math::Vec maxHandlePos) {
}

void SvgSlider::setHandlePosCentered(math::Vec minHandlePosCentered, math::Vec maxHandlePosCentered) {
}

void SvgSwitch::addFrame(std::shared_ptr<window::Svg> svg) {
	if (svg->filename.length()) {
		frames.push_back(svg->filename);
		if (frames.size() == 1) {
			box.size = get_svg_size(svg->filename);
			sw->box.size = box.size;
		}
	}
}

} // namespace rack::app
