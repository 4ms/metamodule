#include "widget/SvgWidget.hpp"
#include "metamodule/svg.hh"

namespace rack::widget
{

void SvgWidget::setSvg(std::shared_ptr<window::Svg> svg) {
	svg_filename = svg->filename;
	box.size = get_svg_size(svg_filename);
}

} // namespace rack::widget
