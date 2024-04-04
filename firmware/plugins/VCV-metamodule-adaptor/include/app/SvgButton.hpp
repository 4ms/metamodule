#pragma once
#include <app/CircularShadow.hpp>
#include <app/common.hpp>
#include <widget/FramebufferWidget.hpp>
#include <widget/OpaqueWidget.hpp>
#include <widget/SvgWidget.hpp>

namespace rack::app
{

struct SvgButton : widget::OpaqueWidget {
	widget::FramebufferWidget *fb = &_fb;
	CircularShadow *shadow = &_shadow;
	widget::SvgWidget *sw = &_sw;

	// std::vector<std::shared_ptr<window::Svg>> frames;
	// MM simplifies:
	std::vector<std::string> frames;

	void addFrame(std::shared_ptr<window::Svg> svg);

private:
	widget::FramebufferWidget _fb;
	CircularShadow _shadow;
	widget::SvgWidget _sw;
};

} // namespace rack::app
