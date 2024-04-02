#pragma once
#include <app/CircularShadow.hpp>
#include <app/Knob.hpp>
#include <widget/FramebufferWidget.hpp>
#include <widget/SvgWidget.hpp>
#include <widget/TransformWidget.hpp>

namespace rack::app
{

/** A knob which rotates an SVG and caches it in a framebuffer */
struct SvgKnob : Knob {
	widget::FramebufferWidget *fb = &_fb;
	CircularShadow *shadow = &_shadow;
	widget::SvgWidget *sw = &_sw;
	widget::TransformWidget *tw = &_tw;

private:
	widget::FramebufferWidget _fb;
	CircularShadow _shadow;
	widget::SvgWidget _sw;
	widget::TransformWidget _tw;

	void setSvg(std::shared_ptr<window::Svg> svg);
};

} // namespace rack::app
