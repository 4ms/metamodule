#include "widget/SvgWidget.hpp"
#include "metamodule/svg.hh"

namespace rack::widget
{

void SvgWidget::setSvg(std::shared_ptr<window::Svg> svg) {
	this->svg = svg;
	box.size = get_svg_size(svg->filename);
}

} // namespace rack::widget
