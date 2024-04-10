#include "metamodule/svg.hh"
#include <app/SvgSlider.hpp>

namespace rack::app
{

void SvgSlider::setBackgroundSvg(std::shared_ptr<window::Svg> svg) {
	//TODO: should we just set this->SvgWidget::svg_filename here? then we don't have to special-case it in make_element
	if (svg && svg->filename.size()) {
		background->svg_filename = svg->filename;
		background->box.size = get_svg_size(background->svg_filename);
	} else
		printf("Svgslider: Svg bg with empty name\n");
}

void SvgSlider::setHandleSvg(std::shared_ptr<window::Svg> svg) {
	if (svg && svg->filename.size()) {
		handle->svg_filename = svg->filename;
		handle->box.size = get_svg_size(handle->svg_filename);
	} else
		printf("Svgslider: Svg with empty name\n");
}

void SvgSlider::setHandlePos(math::Vec minHandlePos, math::Vec maxHandlePos) {
}

void SvgSlider::setHandlePosCentered(math::Vec minHandlePosCentered, math::Vec maxHandlePosCentered) {
}

} // namespace rack::app
