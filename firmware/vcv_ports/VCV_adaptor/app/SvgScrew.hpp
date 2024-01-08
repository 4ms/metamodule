#pragma once
#include "VCV_adaptor/settings.hpp"
#include "VCV_adaptor/widget/Widget.hh"
#include "common.hpp"

namespace rack::app
{

/** If you don't add these to your ModuleWidget, they will fall out of the rack... */
struct SvgScrew : widget::Widget {
	widget::FramebufferWidget *fb;
	widget::SvgWidget *sw;

	void setSvg(std::shared_ptr<window::Svg> svg) {
	}
};

struct ThemedSvgScrew : SvgScrew {
	void setSvg(std::shared_ptr<window::Svg> lightSvg, std::shared_ptr<window::Svg> darkSvg) {
	}
	void step() override {
	}
};

} // namespace rack::app
