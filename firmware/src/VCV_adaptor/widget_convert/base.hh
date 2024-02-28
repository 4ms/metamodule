#pragma once
#include "CoreModules/elements/elements.hh"
#include "componentlibrary.hpp"
#include "widget/Widget.hh"

namespace MetaModule
{

template<typename RackWidgetT>
Element make_element(BaseElement) {
	return NullElement{};
}

template<typename RackWidgetT>
Element make_element_output(BaseElement) {
	return NullElement{};
}

template<typename RackWidgetT>
Element make_element_input(BaseElement) {
	return NullElement{};
}

inline Element make_element(rack::app::SvgScrew *widget, BaseElement) {
	return NullElement{};
}

inline Element make_element(rack::widget::SvgWidget *widget, BaseElement el) {
	return NullElement{};
}

inline Element make_element(rack::app::SvgSwitch *widget, BaseElement b) {
	if (widget->frames.size() == 3) {
		printf("Frames: 3 %s\n", widget->frames[0].c_str());
		return FlipSwitch{{b}, 3, {widget->frames[0], widget->frames[1], widget->frames[2]}};
	} else if (widget->frames.size() == 2) {
		printf("Frames: 2 %s\n", widget->frames[0].c_str());
		return FlipSwitch{{b}, 2, {widget->frames[0], widget->frames[1]}};
	}
	return NullElement{};
}

inline Element make_element(rack::app::ModuleLightWidget *widget, BaseElement el) {
	return NullElement{};
}

} // namespace MetaModule
