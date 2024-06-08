#pragma once
#include "CoreModules/elements/elements.hh"
#include "componentlibrary.hpp"

namespace MetaModule
{
// Jack:
Element make_element(rack::app::SvgPort *widget, BaseElement b);
Element make_element(rack::app::PortWidget *widget, BaseElement b);

// Params:
Element make_element(rack::app::Knob *widget, BaseElement b);
Element make_element(rack::app::SvgKnob *widget, BaseElement b);
Element make_element(rack::app::SliderKnob *widget, BaseElement b);
Element make_element(rack::app::SvgSlider *widget, BaseElement b);

// Switches
Element make_element(rack::app::SvgSwitch *widget, BaseElement b);

// Lights:
Element make_element(rack::app::MultiLightWidget *widget, BaseElement el);
// Element make_element_lightslider(rack::app::SvgSlider *widget, BaseElement el);

// Images (non-interactive)
Element make_element(rack::widget::SvgWidget *widget, BaseElement el);
Element make_element(rack::app::SvgButton *widget, BaseElement b);

// Not supported/not found:
Element make_element(rack::app::SvgScrew *widget, BaseElement);
Element make_element(rack::app::ParamWidget *widget, BaseElement el);
Element make_element(rack::widget::Widget *widget, BaseElement);

//
// Button with lights
//

Element make_button_light(rack::app::SvgSwitch *widget, rack::app::MultiLightWidget *light);

// template<typename LightBaseT>
// Element make_element(rack::componentlibrary::VCVLightBezel<LightBaseT> *widget, BaseElement) {
// 	return make_button_light(widget->light, widget);
// }

//
// SVG Light
//

Element make_multi_led_element(std::string_view image, rack::app::MultiLightWidget *, BaseElement const &);

template<typename LightBaseT>
Element make_element(rack::componentlibrary::TSvgLight<LightBaseT> *widget, BaseElement el) {
	return make_multi_led_element(widget->sw->svg->filename, widget, el);
}

} // namespace MetaModule
