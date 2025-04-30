#include "widget/SvgWidget.hpp"
#include "console/pr_dbg.hh"
#include "metamodule/svg.hh"

namespace rack::widget
{

SvgWidget::SvgWidget() {
	box.size = math::Vec();
}

void SvgWidget::wrap() {
	if (svg) {
		box.size = svg->getSize();
	} else {
		box.size = math::Vec();
	}
}

void SvgWidget::draw(const DrawArgs &args) {
	// nothing
}

// FIXME: set box size from svg
void SvgWidget::setSvg(std::shared_ptr<window::Svg> svg) {
	if (this->svg) {
		if (this->svg->filename() != svg->filename()) {
			// We can't re-assign our svg shared_ptr after ModuleWidget::addParam() has been called,
			// because the old shared_ptr would be deleted, leaving our Elements string_view dangling.
			// We can, however, change it before addParam is called (i.e. in the Widget constructor)
			pr_trace("Changing svg filename from %s to %s\n", this->svg->filename().data(), svg->filename().data());

			// Just change the filename
			this->svg->filename() = svg->filename();
			this->box.size = svg->getSize();
		}
	}

	else if (svg->filename().size())
	{
		this->svg = svg;
		this->box.size = svg->getSize();
		// pr_dbg(
		// 	"SvgWidget(%p)::setSvg(%s) set box.size to %f x %f\n", this, svg->filename.c_str(), box.size.x, box.size.y);
	}
}

} // namespace rack::widget
