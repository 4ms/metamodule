#pragma once
#include <common.hpp>
#include <settings.hpp>
#include <widget/FramebufferWidget.hpp>
#include <widget/SvgWidget.hpp>
#include <widget/Widget.hpp>

namespace rack
{
namespace app
{

/** If you don't add these to your ModuleWidget, they will fall out of the rack... */
struct SvgScrew : widget::Widget {
	widget::FramebufferWidget *fb;
	widget::SvgWidget *sw;

	void setSvg(std::shared_ptr<window::Svg> svg) {
	}
};

DEPRECATED typedef SvgScrew SVGScrew;

struct ThemedSvgScrew : SvgScrew {
	std::shared_ptr<window::Svg> lightSvg;
	std::shared_ptr<window::Svg> darkSvg;

	void setSvg(std::shared_ptr<window::Svg> lightSvg, std::shared_ptr<window::Svg> darkSvg) {
		this->lightSvg = lightSvg;
		this->darkSvg = darkSvg;
		SvgScrew::setSvg(settings::preferDarkPanels ? darkSvg : lightSvg);
	}
};

} // namespace app
} // namespace rack
