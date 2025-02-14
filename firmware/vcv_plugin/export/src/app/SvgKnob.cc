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
	, tw(new widget::TransformWidget)
	, sw(new widget::SvgWidget) {

	addChild(fb);
	fb->addChild(shadow);
	shadow->box.size = math::Vec();
	fb->addChild(tw);
	tw->addChild(sw);
}

void SvgKnob::onChange(const ChangeEvent &e) {
}

} // namespace rack::app
