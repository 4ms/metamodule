#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV-adaptor/widgets.hh"

namespace rack
{

// Default:
template<typename WidgetT>
inline MetaModule::Element create_element() {
	return MetaModule::Davies1900hBlackKnob{};
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
inline MetaModule::Element create_element<BefacoSlidePot>() {
	return MetaModule::BefacoSlidePot{};
}
template<>
inline MetaModule::Element create_element<BefacoSwitch>() {
	return MetaModule::BefacoSwitch{};
}
template<>
inline MetaModule::Element create_element<BefacoPush>() {
	return MetaModule::BefacoPush{};
}
template<>
inline MetaModule::Element create_element<CKSS>() {
	return MetaModule::Slider25mmHoriz{}; // TODO: What is CKSS? Is this the right element?
}
template<>
inline MetaModule::Element create_element<Davies1900hBlackKnob>() {
	return MetaModule::Davies1900hBlackKnob{};
}
template<>
inline MetaModule::Element create_element<Davies1900hKnob>() {
	return MetaModule::Davies1900hBlackKnob{};
}
template<>
inline MetaModule::Element create_element<Davies1900hWhiteKnob>() {
	return MetaModule::Davies1900hWhiteKnob{};
}
template<>
inline MetaModule::Element create_element<Davies1900hRedKnob>() {
	return MetaModule::Davies1900hRedKnob{};
}
template<>
inline MetaModule::Element create_element<Davies1900hLargeWhiteKnob>() {
	return MetaModule::Davies1900hLargeWhiteKnob{};
}
template<>
inline MetaModule::Element create_element<Rogan2SGray>() {
	return MetaModule::Rogan2SGray{};
}
template<>
inline MetaModule::Element create_element<Rogan2PSWhite>() {
	return MetaModule::Rogan2PSWhite{};
}
template<>
inline MetaModule::Element create_element<Rogan2PSRed>() {
	return MetaModule::Rogan2PSRed{};
}
template<>
inline MetaModule::Element create_element<Rogan2PSGreen>() {
	return MetaModule::Rogan2PSGreen{};
}
} // namespace rack
