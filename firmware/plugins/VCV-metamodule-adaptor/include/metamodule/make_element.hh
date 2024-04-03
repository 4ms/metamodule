#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "componentlibrary.hpp"

namespace MetaModule
{

Element make_element_output(rack::app::SvgPort const *widget, BaseElement b);
Element make_element_input(rack::app::SvgPort const *widget, BaseElement b);
Element make_element(rack::app::SvgKnob *widget, BaseElement b);
Element make_element_slideswitch(rack::app::SvgSlider const *widget, BaseElement b);
Element make_element(rack::app::SvgSlider const *widget, BaseElement b);
Element make_element(rack::componentlibrary::Rogan const *widget, BaseElement b);
Element make_element(rack::app::SvgSwitch const *widget, BaseElement b);
Element make_element(rack::app::SvgScrew const *widget, BaseElement);
Element make_element(rack::widget::SvgWidget const *widget, BaseElement el);

//
// Lights (and buttons with lights)
//

template<typename LightBaseT>
Element make_element(rack::componentlibrary::VCVLightBezel<LightBaseT> const *widget, BaseElement el) {
	if (widget->light->getNumColors() == 3) {
		if (!widget->momentary)
			printf("make_element(): Latching RGB button not yet supported\n");

		return MomentaryButtonRGB{el, widget->frames[0]};

	} else if (widget->light->getNumColors() == 1) {
		auto c = widget->light->baseColors[0];
		if (widget->momentary)
			return MomentaryButtonLight{{el, widget->frames[0]}, RGB565{c.r, c.g, c.b}};
		else
			return LatchingButton{{el, widget->frames[0]}, RGB565{c.r, c.g, c.b}};

	} else {
		printf("make_element(): Unknown VCVLightBezel\n");
		return NullElement{};
	}
}

template<typename LightBaseT>
Element make_element(rack::componentlibrary::TSvgLight<LightBaseT> const *widget, BaseElement el) {
	if (widget->getNumColors() == 1) {
		auto c = widget->baseColors[0];
		return MonoLight{{el, widget->sw->svg_filename}, RGB565{c.r, c.g, c.b}};
	}
	if (widget->getNumColors() == 2) {
		auto c1 = widget->baseColors[0];
		auto c2 = widget->baseColors[1];
		return DualLight{{el, widget->sw->svg_filename}, {RGB565{c1.r, c1.g, c1.b}, RGB565{c2.r, c2.g, c2.b}}};
	}
	if (widget->getNumColors() == 3) {
		return RgbLight{el, widget->sw->svg_filename};
	}

	printf("Light widget not handled (%d colors)\n", widget->getNumColors());
	return NullElement{};
}

template<typename LightBaseT>
Element make_element(rack::componentlibrary::TGrayModuleLightWidget<LightBaseT> const *widget, BaseElement el) {

	auto size = to_mm(widget->box.size.x);

	std::string_view image = size <= 2.6f ? "rack-lib/SmallLight.png" : //4px => 2.14mm
							 size <= 3.7f ? "rack-lib/MediumLight.png" : //6px => 3.21mm
							 size <= 4.5f ? "4ms/comp/led_x.png" : //8px => 4.28mm
							 size <= 5.3f ? "rack-lib/LargeLight.png" : //9px => 4.82mm
							 size <= 6.5f ? "rack-lib/VCVBezelLight.png" : //11px => 5.89mm
											"rack-lib/VCVBezel.png"; //14px => 7.5mm

	if (widget->getNumColors() == 1) {
		auto c = widget->baseColors[0];
		return MonoLight{{el, image}, RGB565{c.r, c.g, c.b}};
	}
	if (widget->getNumColors() == 2) {
		auto c1 = widget->baseColors[0];
		auto c2 = widget->baseColors[1];
		return DualLight{{el, image}, {RGB565{c1.r, c1.g, c1.b}, RGB565{c2.r, c2.g, c2.b}}};
	}
	if (widget->getNumColors() == 3) {
		return RgbLight{el, image};
	}

	printf("Light widget not handled (%d colors)\n", widget->getNumColors());
	return NullElement{};
}

} // namespace MetaModule
