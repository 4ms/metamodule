#pragma once
#include "CoreModules/elements/elements.hh"
#include "componentlibrary.hpp"

namespace MetaModule
{
// Jack:
Element make_element(rack::app::SvgPort *widget);
Element make_element(rack::app::PortWidget *widget);

// Params:
Element make_element(rack::app::Knob *widget);
Element make_element(rack::app::SvgKnob *widget);
Element make_element(rack::componentlibrary::Rogan *widget);
Element make_element(rack::app::SliderKnob *widget);
Element make_element(rack::app::SvgSlider *widget);

// Switches
Element make_element(rack::app::SvgSwitch *widget);

// Lights:
Element make_element(rack::app::MultiLightWidget *widget);

// Images (non-interactive)
Element make_element(rack::widget::SvgWidget *widget);
Element make_element(rack::app::SvgButton *widget);

// Text
Element make_element(rack::widget::MetaModuleDisplay *widget);


// Not supported/not found:
Element make_element(rack::app::SvgScrew *widget);
Element make_element(rack::app::ParamWidget *widget);
Element make_element(rack::widget::Widget *widget);

//
// Param with light
//

Element make_element(rack::app::SvgSwitch *widget, rack::app::MultiLightWidget *light);
Element make_element(rack::app::SvgSlider *widget, rack::app::MultiLightWidget *light);

//
// SVG Light
//
Element make_element(rack::app::MultiLightWidget *, std::string_view image);

} // namespace MetaModule
