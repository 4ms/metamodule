#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/Rack_fwd.hh"
#include "VCV_adaptor/widget_convert/base.hh"

namespace rack
{

//TODO put rest of widgets from Rack_fwd.hh here

template<>
struct ElementConvert<componentlibrary::BefacoBigKnob> {
	using ElementType = MetaModule::BefacoBigKnob;
};

template<>
struct ElementConvert<componentlibrary::BefacoTinyKnob> {
	using ElementType = MetaModule::BefacoTinyKnobBlack;
};

template<>
struct ElementConvert<componentlibrary::BefacoSlidePot> {
	using ElementType = MetaModule::BefacoSlidePot;
};

template<>
struct ElementConvert<componentlibrary::BefacoSwitch> {
	using ElementType = MetaModule::BefacoSwitch;
};

template<>
struct ElementConvert<componentlibrary::BefacoPush> {
	using ElementType = MetaModule::BefacoPush;
};

template<>
struct ElementConvert<componentlibrary::CKSS> { // TODO: What is CKSS? Is this the right element?
	using ElementType = MetaModule::Toggle2pos;
};

template<>
struct ElementConvert<componentlibrary::Davies1900hBlackKnob> {
	using ElementType = MetaModule::Davies1900hBlackKnob;
};

template<>
struct ElementConvert<componentlibrary::Davies1900hWhiteKnob> {
	using ElementType = MetaModule::Davies1900hWhiteKnob;
};

template<>
struct ElementConvert<componentlibrary::Davies1900hRedKnob> {
	using ElementType = MetaModule::Davies1900hRedKnob;
};

template<>
struct ElementConvert<componentlibrary::Davies1900hLargeWhiteKnob> {
	using ElementType = MetaModule::Davies1900hLargeWhiteKnob;
};

template<>
struct ElementConvert<componentlibrary::Rogan2SGray> {
	using ElementType = MetaModule::Rogan2SGray;
};

template<>
struct ElementConvert<componentlibrary::Rogan2PSWhite> {
	using ElementType = MetaModule::Rogan2PSWhite;
};

template<>
struct ElementConvert<componentlibrary::Rogan2PSRed> {
	using ElementType = MetaModule::Rogan2PSRed;
};

template<>
struct ElementConvert<componentlibrary::Rogan2PSGreen> {
	using ElementType = MetaModule::Rogan2PSGreen;
};

template<>
struct ElementConvert<componentlibrary::PJ301MPort> {
	using ElementTypeInput = MetaModule::PJ301MPortIn;
	using ElementTypeOutput = MetaModule::PJ301MPortOut;
};

} // namespace rack
