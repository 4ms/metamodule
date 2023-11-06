#pragma once
#include "CoreModules/elements/elements.hh"
#include <cstdio>

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

} // namespace MetaModule
