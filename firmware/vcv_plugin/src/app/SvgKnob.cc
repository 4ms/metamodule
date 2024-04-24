#include "console/pr_dbg.hh"
#include "metamodule/svg.hh"
#include <app/SvgKnob.hpp>

namespace rack::app
{

void SvgKnob::setSvg(std::shared_ptr<window::Svg> svg) {
	if (svg->filename.size()) {
		sw->svg = svg;
		box.size = get_svg_size(svg->filename);
		// printf("SvgKnob:svg_filename %s\n", sw->svg_filename.c_str());
	} else
		pr_dbg("SvgKnob: svg with empty name\n");
}

} // namespace rack::app
