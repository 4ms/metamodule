#include "metamodule/svg.hh"
#include <app/SvgButton.hpp>

namespace rack::app
{

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
