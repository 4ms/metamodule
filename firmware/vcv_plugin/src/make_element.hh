#pragma once
#include "CoreModules/elements/elements.hh"
#include "componentlibrary.hpp"

namespace MetaModule
{

// Params:
Element make_element(rack::app::Knob *widget, BaseElement b);
Element make_element(rack::app::SvgKnob *widget, BaseElement b);
Element make_element(rack::app::SvgSlider *widget, BaseElement b);
Element make_element(rack::componentlibrary::Rogan *widget, BaseElement b);
Element make_element(rack::app::SvgSwitch *widget, BaseElement b);
Element make_element(rack::app::SvgScrew *widget, BaseElement);
Element make_element(rack::app::ParamWidget *widget, BaseElement el);
Element make_element(rack::widget::SvgWidget *widget, BaseElement el);
Element make_element(rack::app::SliderKnob *widget, BaseElement b);
Element make_element(rack::app::MultiLightWidget *widget, BaseElement el);
Element make_element(rack::widget::Widget *widget, BaseElement);
Element make_element(rack::app::SvgButton *widget, BaseElement b);

// Jack:
Element make_element(rack::app::SvgPort *widget, BaseElement b);
Element make_element(rack::app::PortWidget *widget, BaseElement b);

// Lights:
Element make_element_lightslider(rack::app::SvgSlider *widget, BaseElement el);
Element make_multi_led_element(std::string_view image, rack::app::MultiLightWidget *, BaseElement const &);
Element make_button_light(rack::app::MultiLightWidget *, rack::app::SvgSwitch *, BaseElement const &);

//
// Button with lights
//

template<typename LightBaseT>
Element make_element(rack::componentlibrary::VCVLightBezel<LightBaseT> *widget, BaseElement el) {
	return make_button_light(widget->light, widget, el);
}

//
// SVG Light
//

template<typename LightBaseT>
Element make_element(rack::componentlibrary::TSvgLight<LightBaseT> *widget, BaseElement el) {
	return make_multi_led_element(widget->sw->svg->filename, widget, el);
}

} // namespace MetaModule
