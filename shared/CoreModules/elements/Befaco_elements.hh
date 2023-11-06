#pragma once
#include "base_element.hh"

namespace MetaModule
{

struct BefacoTinyKnob : Knob {};
struct BefacoTinyKnobWhite : BefacoTinyKnob {};
struct BefacoTinyKnobRed : BefacoTinyKnob {};
struct BefacoTinyKnobDarkGrey : BefacoTinyKnob {};
struct BefacoTinyKnobLightGrey : BefacoTinyKnob {};
struct BefacoTinyKnobBlack : BefacoTinyKnob {};

struct Davies1900hLargeGreyKnob : Knob {};
struct Davies1900hLightGreyKnob : Knob {};
struct Davies1900hDarkGreyKnob : Knob {};
struct Davies1900hLargeLightGreyKnob : Knob {};

struct BefacoSlidePotSmall : Slider {};
struct Crossfader : Slider {};

struct BefacoSwitchHorizontal : Toggle2posHoriz {};
struct CKSSHoriz2 : Toggle2posHoriz {};

struct CKSSVert7 : SlideSwitchNPos {
	constexpr CKSSVert7(float x, float y, Coords c, std::string_view s, std::string_view l)
		: SlideSwitchNPos{{x, y, c, s, l}, 7} {
	}
};

struct CKSSHoriz4 : Toggle2posHoriz {};
struct CKSSNarrow : Toggle2pos {};
struct CKSSNarrow3 : Toggle2pos {};

struct BefacoInputPort : JackInput {};
using BananutBlack = BefacoInputPort;

struct BefacoOutputPort : JackOutput {};
using BananutRed = BefacoOutputPort;

} // namespace MetaModule
