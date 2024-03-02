#pragma once
#include "CoreModules/elements/elements.hh"
#include "componentlibrary.hpp"

namespace MetaModule
{

inline Element make_element_output(rack::app::SvgPort *widget, BaseElement b) {
	return JackOutput{b, widget->svg_filename};
}

inline Element make_element_input(rack::app::SvgPort *widget, BaseElement b) {
	return JackInput{b, widget->svg_filename};
}

inline Element make_element(rack::app::SvgScrew *widget, BaseElement) {
	return NullElement{};
}

inline Element make_element(rack::widget::SvgWidget *widget, BaseElement el) {
	printf("Unknown SvgWidget\n");
	return NullElement{};
}

inline Element make_element(rack::app::SvgKnob *widget, BaseElement b) {
	return Knob{b, widget->svg_filename};
}

inline Element make_element_slideswitch(rack::app::SvgSlider *widget, BaseElement b) {
	//num_pos and labels are filled in later
	return SlideSwitch{{b, widget->svg_filename}, 2, widget->handle->svg_filename};
}

inline Element make_element(rack::app::SvgSlider *widget, BaseElement b) {
	return Slider{{b, widget->svg_filename}, widget->handle->svg_filename};
}

inline Element make_element(rack::app::SvgSwitch *widget, BaseElement b) {
	if (widget->frames.size() == 3) {
		return FlipSwitch{{b}, 3, {widget->frames[0], widget->frames[1], widget->frames[2]}};

	} else if (widget->frames.size() == 2) {
		return FlipSwitch{{b}, 2, {widget->frames[0], widget->frames[1]}};

	} else {
		printf("make_element(): Unknown SvgSwitch, frames size is not 2 or 3\n");
		return NullElement{};
	}
}

inline Element make_element(rack::app::ModuleLightWidget *widget, BaseElement el) {
	return NullElement{};
}

} // namespace MetaModule
