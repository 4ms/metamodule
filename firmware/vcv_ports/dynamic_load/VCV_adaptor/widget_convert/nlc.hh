#pragma once
#include "CoreModules/elements/base_element.hh"
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"
#include "VCV_adaptor/widgets.hh"

// Forward declare widgets
struct SlothRedGreenLightWidget;

namespace MetaModule
{

template<>
inline Element make_element<rack::componentlibrary::LargeLight<SlothRedGreenLightWidget>>(BaseElement b) {
	return DualLight{{b, "LargeLight.png"}, {Colors565::Red, Colors565::Green}};
};

} // namespace MetaModule
