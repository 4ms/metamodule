#pragma once
#include <widget/Widget.hpp>

namespace rack::widget
{

/** Owns and draws a window::Svg */
struct SvgWidget : Widget {
	std::shared_ptr<window::Svg> svg;

	//MM:
	std::string svg_filename; //TODO: use svg->filename

	SvgWidget();

	/** Sets the box size to the SVG image size */
	void wrap();

	/** Sets and wraps the SVG */
	void setSvg(std::shared_ptr<window::Svg> svg);
	DEPRECATED void setSVG(std::shared_ptr<window::Svg> svg) {
		setSvg(svg);
	}

	void draw(const DrawArgs &args) override;
};

DEPRECATED typedef SvgWidget SVGWidget;

} // namespace rack::widget
