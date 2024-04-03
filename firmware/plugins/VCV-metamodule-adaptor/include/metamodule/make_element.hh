#pragma once
#include "CoreModules/elements/element_info.hh"
#include "CoreModules/elements/elements.hh"
#include "componentlibrary.hpp"

namespace MetaModule
{

//TODO: All of these functions: put in a .cc. For template functions, put as much as possible in a .cc

//
// Jacks
//

inline Element make_element_output(rack::app::SvgPort const *widget, BaseElement b) {
	return JackOutput{b, widget->svg_filename};
}

inline Element make_element_input(rack::app::SvgPort const *widget, BaseElement b) {
	return JackInput{b, widget->svg_filename};
}

//
// Pots/Sliders
//

//TODO: don't set box size here
// either have dedicated function refresh_widget_size()
// or in SvgWidget::setSvg, set its parents size recursively (if not set)
inline Element make_element(rack::app::SvgKnob *widget, BaseElement b) {
	// SvgKnobs have a base SVG, and sometimes have a bg svg.
	// If there is a bg svg, then use its name.
	if (widget->fb->_bg && widget->fb->_bg->svg_filename.length()) {
		if (widget->box.size == rack::math::Vec{})
			widget->box.size = widget->fb->_bg->box.size;
		return Knob{b, widget->fb->_bg->svg_filename};
	} else
		return Knob{b, widget->svg_filename};
}

inline Element make_element_slideswitch(rack::app::SvgSlider const *widget, BaseElement b) {
	//Note: num_pos and labels are filled in later
	if (widget->background->svg_filename.length()) {
		return SlideSwitch{{b, widget->background->svg_filename}, 2, widget->handle->svg_filename};
	} else {
		return SlideSwitch{{b, widget->svg_filename}, 2, widget->handle->svg_filename};
	}
}

inline Element make_element(rack::app::SvgSlider const *widget, BaseElement b) {
	if (widget->background->svg_filename.length()) {
		return Slider{{b, widget->background->svg_filename}, widget->handle->svg_filename};
	} else {
		return Slider{{b, widget->svg_filename}, widget->handle->svg_filename};
	}
}

inline Element make_element(rack::componentlibrary::Rogan const *widget, BaseElement b) {
	// Rogan knobs have a bg svg, base svg, and fg svg. The main svg rotates, the others do not.
	// The fg and base svgs are always the same color and thus are combined into one PNG for the MetaModule.
	// The bg svg is lighting effect gradient and can be ignored for MetaModule's low-res screen.
	return Knob{b, widget->svg_filename};
}

//
// Switch/Button
//

inline Element make_element(rack::app::SvgSwitch const *widget, BaseElement b) {
	if (widget->momentary) {
		return MomentaryButton{b, widget->frames[0]};

	} else if (widget->frames.size() == 3) {
		return FlipSwitch{{b}, 3, {widget->frames[0], widget->frames[1], widget->frames[2]}};

	} else if (widget->frames.size() == 2) {
		return FlipSwitch{{b}, 2, {widget->frames[0], widget->frames[1]}};

	} else if (widget->frames.size() == 1) {
		return MomentaryButton{b, widget->frames[0]};

	} else {
		printf("make_element(): Unknown SvgSwitch, frames size is not 1, 2 or 3\n");
		return NullElement{};
	}
}

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

//
// Lights
//

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

//
// Not supported
//

inline Element make_element(rack::app::SvgScrew const *widget, BaseElement) {
	return NullElement{};
}

inline Element make_element(rack::widget::SvgWidget const *widget, BaseElement el) {
	printf("Unknown SvgWidget\n");
	return NullElement{};
}

} // namespace MetaModule
