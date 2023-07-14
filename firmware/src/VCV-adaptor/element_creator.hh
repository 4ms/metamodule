#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV-adaptor/widgets.hh"

namespace rack
{

template<typename WidgetT>
MetaModule::Element create_element() {
	return {};
}

template<>
MetaModule::Element create_element<BefacoBigKnob>() {
	return MetaModule::BefacoBigKnob{};
}

template<>
MetaModule::Element create_element<BefacoTinyKnob>() {
	return MetaModule::BefacoTinyKnob{};
}

template<>
MetaModule::Element create_element<Davies1900hRedKnob>() {
	return MetaModule::Davies1900hRedKnob{};
}

} // namespace rack
