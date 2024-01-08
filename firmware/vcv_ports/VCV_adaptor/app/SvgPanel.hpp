#pragma once
#include "VCV_adaptor/widgets.hh"
#include "VCV_adaptor/window.hpp"
#include <string_view>

namespace rack::app
{

struct PanelBorder : widget::TransparentWidget {};

struct SvgPanel : widget::Widget {
	widget::FramebufferWidget *fb;
	widget::SvgWidget *sw;
	PanelBorder *panelBorder;
	window::Svg *svg;

	void setBackground(std::shared_ptr<window::Svg> svg) {
	}
};

DEPRECATED typedef SvgPanel SVGPanel;

} // namespace rack::app
