#pragma once
#include "VCV_adaptor/componentlibrary.hpp"
#include "VCV_adaptor/window.hpp"
#include <string_view>

namespace rack::app
{

struct PanelBorder : widget::TransparentWidget {};

struct SvgPanel : widget::Widget {
	widget::FramebufferWidget *fb;
	widget::SvgWidget *sw;
	PanelBorder *panelBorder;
	std::shared_ptr<window::Svg> svg;

	void setBackground(std::shared_ptr<window::Svg> svg) {
		this->svg = svg;
	}
};

DEPRECATED typedef SvgPanel SVGPanel;

} // namespace rack::app
