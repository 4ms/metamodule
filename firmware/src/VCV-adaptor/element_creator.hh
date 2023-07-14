#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV-adaptor/widgets.hh"

namespace rack
{

template<typename WidgetT>
inline MetaModule::Element create_element() {
	return {};
}

template<>
inline MetaModule::Element create_element<BefacoBigKnob>() {
	return MetaModule::BefacoBigKnob{};
}

template<>
inline MetaModule::Element create_element<BefacoTinyKnob>() {
	return MetaModule::BefacoTinyKnob{};
}

template<>
inline MetaModule::Element create_element<Davies1900hRedKnob>() {
	return MetaModule::Davies1900hRedKnob{};
}

} // namespace rack
