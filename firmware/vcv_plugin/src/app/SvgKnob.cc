#include "console/pr_dbg.hh"
#include "metamodule/svg.hh"
#include <app/SvgKnob.hpp>

namespace rack::app
{

void SvgKnob::setSvg(std::shared_ptr<window::Svg> svg) {
	sw->setSvg(svg);
	box.size = sw->box.size;
}

} // namespace rack::app
