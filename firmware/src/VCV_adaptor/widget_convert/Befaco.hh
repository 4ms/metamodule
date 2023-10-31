#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV_adaptor/widget_convert/base.hh"

// Forward declare widgets from Befaco/src/plugin.hpp
struct Knurlie;
struct BefacoTinyKnobWhite;
struct BefacoTinyKnobRed;
struct BefacoTinyKnobDarkGrey;
struct BefacoTinyKnobLightGrey;
struct BefacoTinyKnobBlack;
struct Davies1900hLargeGreyKnob;
struct Davies1900hLightGreyKnob;
struct Davies1900hDarkGreyKnob;
struct BananutRed;
struct BananutBlack;
struct CKSSNarrow;
struct Crossfader;
struct BefacoSwitchHorizontal;
struct CKSSHoriz2;
struct CKSSVert7;
struct CKSSHoriz4;
struct CKSSNarrow3;
struct Davies1900hLargeLightGreyKnob;
struct BefacoSlidePotSmall;
// From StereoStrip.cpp
struct ThreeStateBefacoSwitchMomentary;

// Conversions from Befaco widgets to MetaModule Elements:

namespace rack
{

template<>
struct ElementConvert<Knurlie> {
	using ElementType = MetaModule::NullElement;
};

template<>
struct ElementConvert<BefacoTinyKnobWhite> {
	using ElementType = MetaModule::BefacoTinyKnobWhite;
};

template<>
struct ElementConvert<BefacoTinyKnobRed> {
	using ElementType = MetaModule::BefacoTinyKnobRed;
};

template<>
struct ElementConvert<BefacoTinyKnobDarkGrey> {
	using ElementType = MetaModule::BefacoTinyKnobDarkGrey;
};

template<>
struct ElementConvert<BefacoTinyKnobLightGrey> {
	using ElementType = MetaModule::BefacoTinyKnobLightGrey;
};

template<>
struct ElementConvert<BefacoTinyKnobBlack> {
	using ElementType = MetaModule::BefacoTinyKnobBlack;
};

template<>
struct ElementConvert<Davies1900hLargeGreyKnob> {
	using ElementType = MetaModule::Davies1900hLargeGreyKnob;
};

template<>
struct ElementConvert<Davies1900hLightGreyKnob> {
	using ElementType = MetaModule::Davies1900hLightGreyKnob;
};

template<>
struct ElementConvert<Davies1900hDarkGreyKnob> {
	using ElementType = MetaModule::Davies1900hDarkGreyKnob;
};

template<>
struct ElementConvert<BananutRed> {
	using ElementTypeOutput = MetaModule::BefacoOutputPort;
};

template<>
struct ElementConvert<BananutBlack> {
	using ElementTypeInput = MetaModule::BefacoInputPort;
};

template<>
struct ElementConvert<CKSSNarrow> {
	using ElementType = MetaModule::CKSSNarrow;
};

template<>
struct ElementConvert<Crossfader> {
	using ElementType = MetaModule::Crossfader;
};

template<>
struct ElementConvert<BefacoSwitchHorizontal> {
	using ElementType = MetaModule::BefacoSwitchHorizontal;
};

template<>
struct ElementConvert<CKSSHoriz2> {
	using ElementType = MetaModule::CKSSHoriz2;
};

template<>
struct ElementConvert<CKSSVert7> {
	using ElementType = MetaModule::CKSSVert7;
};

template<>
struct ElementConvert<CKSSHoriz4> {
	using ElementType = MetaModule::CKSSHoriz4;
};

template<>
struct ElementConvert<CKSSNarrow3> {
	using ElementType = MetaModule::CKSSNarrow3;
};

template<>
struct ElementConvert<Davies1900hLargeLightGreyKnob> {
	using ElementType = MetaModule::Davies1900hLargeLightGreyKnob;
};

template<>
struct ElementConvert<BefacoSlidePotSmall> {
	using ElementType = MetaModule::BefacoSlidePotSmall;
};

template<>
struct ElementConvert<ThreeStateBefacoSwitchMomentary> {
	using ElementType = MetaModule::Toggle3pos;
};

} // namespace rack
