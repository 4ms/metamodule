#include "widget/SvgWidget.hpp"
#include "console/pr_dbg.hh"
#include "metamodule/svg.hh"

namespace rack::widget
{

void SvgWidget::setSvg(std::shared_ptr<window::Svg> svg) {
	if (this->svg) {
		if (this->svg->filename != svg->filename) {
			// We can't re-assign our svg shared_ptr after ModuleWidget::addParam() has been called,
			// because the old shared_ptr would be deleted, leaving our Elements string_view dangling.
			// We can, however, change it before addParam is called (i.e. in the Widget constructor)
			pr_warn("Changing svg filename from %s to %s\n", this->svg->filename.c_str(), svg->filename.c_str());

			this->svg->filename = svg->filename;
			this->box.size = get_svg_size(svg->filename);
		}
	}

	else if (svg->filename.size())
	{
		this->svg = svg;
		this->box.size = get_svg_size(svg->filename);
		// pr_dbg(
		// 	"SvgWidget(%p)::setSvg(%s) set box.size to %f x %f\n", this, svg->filename.c_str(), box.size.x, box.size.y);
	}
}

} // namespace rack::widget
