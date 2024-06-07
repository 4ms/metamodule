#include "console/pr_dbg.hh"
#include "metamodule/svg.hh"
#include <app/SvgKnob.hpp>

namespace rack::app
{

void SvgKnob::setSvg(std::shared_ptr<window::Svg> svg) {
	sw->setSvg(svg);
	tw->box.size = sw->box.size;
	fb->box.size = sw->box.size;
	box.size = sw->box.size;
	pr_dbg("SvgKnob::setSvg(%s) set box.size to %f x %f\n", svg->filename.c_str(), box.size.x, box.size.y);
}

} // namespace rack::app
