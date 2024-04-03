#pragma once
#include <widget/Widget.hpp>

namespace rack::widget
{

/** Owns and draws a window::Svg */
struct SvgWidget : Widget {
	std::shared_ptr<window::Svg> svg;

	//MM:
	std::string svg_filename; //TODO: use svg->filename
	NVGcolor bgColor{};

	SvgWidget();

	void wrap() {
	}

	void setSvg(std::shared_ptr<window::Svg> svg);
	void setSVG(std::shared_ptr<window::Svg> svg) {
		setSvg(svg);
	}
};

DEPRECATED typedef SvgWidget SVGWidget;

} // namespace rack::widget
