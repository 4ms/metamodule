#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"

// use the Rack widgets?
// #include "VCV_adaptor/widget_convert/Rack.hh"

struct TestWidgetSlider;

namespace MetaModule
{

template<>
inline Element make_element<TestWidgetSlider>(BaseElement b) {
	return MetaModule::Slider{{b, "testslider.png"}};
}

} // namespace MetaModule
