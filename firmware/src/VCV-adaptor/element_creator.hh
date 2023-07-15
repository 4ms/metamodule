#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV-adaptor/widgets.hh"

namespace rack
{

template<typename TParamWidget>
struct ElementConvert {
	using ElementType = MetaModule::Davies1900hBlackKnob;
};

template<>
struct ElementConvert<BefacoBigKnob> {
	using ElementType = MetaModule::BefacoBigKnob;
};

template<>
struct ElementConvert<BefacoTinyKnob> {
	using ElementType = MetaModule::BefacoTinyKnob;
};

template<>
struct ElementConvert<BefacoSlidePot> {
	using ElementType = MetaModule::BefacoSlidePot;
};

template<>
struct ElementConvert<BefacoSwitch> {
	using ElementType = MetaModule::BefacoSwitch;
};

template<>
struct ElementConvert<BefacoPush> {
	using ElementType = MetaModule::BefacoPush;
};

template<>
struct ElementConvert<CKSS> { // TODO: What is CKSS? Is this the right element?
	using ElementType = MetaModule::Slider25mmHoriz;
};

template<>
struct ElementConvert<Davies1900hBlackKnob> {
	using ElementType = MetaModule::Davies1900hBlackKnob;
};

template<>
struct ElementConvert<Davies1900hKnob> {
	using ElementType = MetaModule::Davies1900hBlackKnob;
};

template<>
struct ElementConvert<Davies1900hWhiteKnob> {
	using ElementType = MetaModule::Davies1900hWhiteKnob;
};

template<>
struct ElementConvert<Davies1900hRedKnob> {
	using ElementType = MetaModule::Davies1900hRedKnob;
};

template<>
struct ElementConvert<Davies1900hLargeWhiteKnob> {
	using ElementType = MetaModule::Davies1900hLargeWhiteKnob;
};

template<>
struct ElementConvert<Rogan2SGray> {
	using ElementType = MetaModule::Rogan2SGray;
};

template<>
struct ElementConvert<Rogan2PSWhite> {
	using ElementType = MetaModule::Rogan2PSWhite;
};

template<>
struct ElementConvert<Rogan2PSRed> {
	using ElementType = MetaModule::Rogan2PSRed;
};

template<>
struct ElementConvert<Rogan2PSGreen> {
	using ElementType = MetaModule::Rogan2PSGreen;
};

} // namespace rack
