#pragma once
#include "base_element.hh"

namespace MetaModule
{
// Yes, these are from Rack, even though they are for Befaco
struct BefacoSlidePot : Slider {};
struct BefacoBigKnob : Knob {};
struct BefacoSwitch : Toggle2pos {};
struct BefacoPush : MomentaryButton {};

struct Davies1900hWhiteKnob : Knob {};
struct Davies1900hRedKnob : Knob {};
struct Davies1900hLargeWhiteKnob : Knob {};
struct Rogan2SGray : Knob {};
struct Rogan2PSWhite : Knob {};
struct Rogan2PSRed : Knob {};
struct Rogan2PSGreen : Knob {};

struct PJ301MPortIn : JackInput {};
struct PJ301MPortOut : JackOutput {};

struct CKSS : Toggle2pos {}; // TODO: What is CKSS? Is this the right element?

template<typename LedT>
struct MediumLight : LedT {};

} // namespace MetaModule
