#include "console/pr_dbg.hh"
#include "metamodule/svg.hh"
#include <app/SvgKnob.hpp>

namespace rack::app
{

void SvgKnob::setSvg(std::shared_ptr<window::Svg> svg) {
	sw->setSvg(svg);
	tw->box.size = sw->box.size;
	fb->box.size = sw->box.size;
	box.size = sw->box.size;
}

SvgKnob::SvgKnob()
	: fb(new widget::FramebufferWidget)
	, shadow(new CircularShadow)
	, sw(new widget::SvgWidget)
	, tw(new widget::TransformWidget) {
	addChild(fb);
	fb->addChild(shadow);
	shadow->box.size = math::Vec();
	fb->addChild(tw);
	tw->addChild(sw);
}

} // namespace rack::app
