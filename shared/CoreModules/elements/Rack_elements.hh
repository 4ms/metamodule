#pragma once
#include "base_element.hh"

namespace MetaModule
{
// Yes, these are from Rack, even though they are for Befaco
struct BefacoSlidePot : Slider {};
struct BefacoBigKnob : Knob {};
// struct BefacoSwitch : Toggle2pos {};

struct Davies1900hWhiteKnob : Knob {};
struct Davies1900hRedKnob : Knob {};
struct Davies1900hLargeWhiteKnob : Knob {};
struct Rogan1PRed : Knob {};
struct Rogan1PSGreen : Knob {};
struct Rogan1PSRed : Knob {};
struct Rogan1PSWhite : Knob {};
struct Rogan2SGray : Knob {};
struct Rogan2PSWhite : Knob {};
struct Rogan2PSRed : Knob {};
struct Rogan2PSGreen : Knob {};
struct Rogan3PSWhite : Knob {};
struct Rogan3PSRed : Knob {};
struct Rogan3PSGreen : Knob {};
struct Trimpot : Knob {};

struct PJ301MPortIn : JackInput {};
struct PJ301MPortOut : JackOutput {};

struct LEDBezel : MomentaryButton {};

template<typename LedT>
struct VCVLightBezel : LedT {};

template<typename LedT>
struct MediumLight : LedT {};

template<typename LedT>
struct SmallLight : LedT {};

} // namespace MetaModule
