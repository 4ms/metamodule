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

struct BefacoInputPort : JackInput {};
using BananutBlack = BefacoInputPort;

struct BefacoOutputPort : JackOutput {};
using BananutRed = BefacoOutputPort;

} // namespace MetaModule
