#pragma once
#include "CoreModules/elements/elements.hh"
#include "componentlibrary.hpp"
#include "widget/Widget.hh"

namespace MetaModule
{

template<typename RackWidgetT>
Element make_element(BaseElement) {
	printf("Unknown WidgetT\n");
	return NullElement{};
}

inline Element make_element_output(rack::app::SvgPort *widget, BaseElement b) {
	printf("make_element_output %s\n", widget->svg_filename.c_str());
	return JackOutput{b, widget->svg_filename};
}

inline Element make_element_input(rack::app::SvgPort *widget, BaseElement b) {
	printf("make_element_output %s\n", widget->svg_filename.c_str());
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
	printf("make_element(SvgKnob): filename=%s\n", widget->svg_filename.c_str());
	return Knob{b, widget->svg_filename};
}

inline Element make_element_switch(rack::app::SvgSlider *widget, BaseElement b) {
	printf("make_element_switch(SvgSlider)\n");
	return SlideSwitch{{b, widget->svg_filename}, 2, widget->handle->svg_filename}; //labels filled in later
}

inline Element make_element(rack::app::SvgSlider *widget, BaseElement b) {
	printf("make_element(SvgSlider)\n");
	return Slider{{b, widget->svg_filename}, widget->handle->svg_filename};
}

inline Element make_element(rack::app::SvgSwitch *widget, BaseElement b) {
	if (widget->frames.size() == 3) {
		printf("Frames: 3 %s\n", widget->frames[0].c_str());
		return FlipSwitch{{b}, 3, {widget->frames[0], widget->frames[1], widget->frames[2]}};

	} else if (widget->frames.size() == 2) {
		printf("Frames: 2 %s\n", widget->frames[0].c_str());
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
