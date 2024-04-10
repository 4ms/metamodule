#include "metamodule/svg.hh"
#include <app/SvgPort.hpp>

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

} // namespace rack::app
