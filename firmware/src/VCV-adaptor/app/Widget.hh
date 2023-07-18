#pragma once
#include "VCV-adaptor/widget/Widget.hh"

namespace rack::app
{

// Ports
struct PortWidget : widget::SvgWidget {};
struct SvgPort : app::PortWidget {};

// Params
struct ParamWidget : widget::SvgWidget {
	int paramId = -1;
};

struct SvgSlider : app::ParamWidget {
	math::Vec minHandlePos;
	math::Vec maxHandlePos;
	bool horizontal;
	widget::SvgWidget *background = &_background;

	void setBackgroundSvg(auto) {
	}
	void setHandleSvg(auto) {
	}

private:
	widget::SvgWidget _background;
};

struct SvgSwitch : ParamWidget {
	bool momentary;
	void addFrame(std::shared_ptr<window::Svg>) {
	}
};

} // namespace rack::app
