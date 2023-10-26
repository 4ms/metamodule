#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"
#include "VCV_adaptor/widgets.hh"

namespace rack
{

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
struct ElementConvert<componentlibrary::CKSS> {
	using ElementType = MetaModule::CKSS;
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
struct ElementConvert<componentlibrary::Rogan1PSWhite> {
	using ElementType = MetaModule::Rogan1PSWhite;
};

template<>
struct ElementConvert<componentlibrary::Rogan1PSRed> {
	using ElementType = MetaModule::Rogan1PSRed;
};

template<>
struct ElementConvert<componentlibrary::Rogan1PSGreen> {
	using ElementType = MetaModule::Rogan1PSGreen;
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
struct ElementConvert<componentlibrary::Rogan1PRed> {
	using ElementType = MetaModule::Rogan1PRed;
};

template<>
struct ElementConvert<componentlibrary::Rogan> {
	using ElementType = MetaModule::Rogan1PRed;
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
struct ElementConvert<componentlibrary::Rogan3PSWhite> {
	using ElementType = MetaModule::Rogan3PSWhite;
};

template<>
struct ElementConvert<componentlibrary::Rogan3PSRed> {
	using ElementType = MetaModule::Rogan3PSRed;
};

template<>
struct ElementConvert<componentlibrary::Rogan3PSGreen> {
	using ElementType = MetaModule::Rogan3PSGreen;
};

template<>
struct ElementConvert<componentlibrary::Trimpot> {
	using ElementType = MetaModule::Trimpot;
};

template<>
struct ElementConvert<componentlibrary::CKD6> {
	using ElementType = MetaModule::CKD6;
};

template<>
struct ElementConvert<componentlibrary::TL1105> {
	using ElementType = MetaModule::TL1105;
};

template<>
struct ElementConvert<componentlibrary::LEDBezel> {
	using ElementType = MetaModule::LEDBezel;
};

template<>
struct ElementConvert<componentlibrary::VCVLightBezel<componentlibrary::RedGreenBlueLight>> {
	using ElementType = MetaModule::VCVLightBezel<MetaModule::RedGreenBlueLight>;
};

template<>
struct ElementConvert<componentlibrary::SmallLight<componentlibrary::RedLight>> {
	using ElementType = MetaModule::SmallLight<MetaModule::RedLight>;
};

template<>
struct ElementConvert<componentlibrary::SmallLight<componentlibrary::GreenLight>> {
	using ElementType = MetaModule::SmallLight<MetaModule::GreenLight>;
};

template<>
struct ElementConvert<componentlibrary::SmallLight<componentlibrary::GreenRedLight>> {
	using ElementType = MetaModule::SmallLight<MetaModule::GreenRedLight>;
};

template<>
struct ElementConvert<componentlibrary::PJ301MPort> {
	using ElementTypeInput = MetaModule::PJ301MPortIn;
	using ElementTypeOutput = MetaModule::PJ301MPortOut;
};

template<>
struct ElementConvert<componentlibrary::ThemedPJ301MPort> {
	using ElementTypeInput = MetaModule::PJ301MPortIn;
	using ElementTypeOutput = MetaModule::PJ301MPortOut;
};

} // namespace rack
