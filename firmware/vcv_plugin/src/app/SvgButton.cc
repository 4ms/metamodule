#include "metamodule/svg.hh"
#include <app/SvgButton.hpp>

namespace rack::app
{

void SvgButton::addFrame(std::shared_ptr<window::Svg> svg) {
	if (svg->filename.length()) {
		frames.push_back(svg->filename);
		if (frames.size() == 1) {
			box.size = get_svg_size(svg->filename);
			sw->box.size = box.size;
		}
	}
}

} // namespace rack::app
