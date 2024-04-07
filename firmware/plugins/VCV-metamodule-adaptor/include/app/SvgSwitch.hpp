#pragma once
#include <app/CircularShadow.hpp>
#include <app/Switch.hpp>
#include <app/common.hpp>
#include <widget/FramebufferWidget.hpp>
#include <widget/SvgWidget.hpp>

namespace rack::app
{

struct SvgSwitch : Switch {
	widget::FramebufferWidget *fb = &_fb;
	CircularShadow *shadow = &_shadow;
	widget::SvgWidget *sw = &_sw;

	// std::vector<std::shared_ptr<window::Svg>> frames;
	// MM simplifies:
	std::vector<std::string> frames;

	// Use frames 0 and 1 when the mouse is pressed and released, instead of using the param value as the frame index.
	bool latch = false;

	void addFrame(std::shared_ptr<window::Svg> svg);

private:
	widget::FramebufferWidget _fb;
	CircularShadow _shadow;
	widget::SvgWidget _sw;
};

using SVGSwitch = SvgSwitch;

} // namespace rack::app
