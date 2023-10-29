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
struct Rogan1PRed : Knob {};
struct Rogan1PSGreen : Knob {};
struct Rogan1PSRed : Knob {};
struct Rogan1PSWhite : Knob {};
struct Rogan2SGray : Knob {};
struct Rogan2PSWhite : Knob {};
struct Rogan2PSRed : Knob {};
struct Rogan2PSGreen : Knob {};
struct Rogan3PSWhite : Knob {};
struct Trimpot : Knob {};

struct PJ301MPortIn : JackInput {};
struct PJ301MPortOut : JackOutput {};

struct CKSS : Toggle2pos {};
struct CKSSRot : Toggle2pos {};

struct LEDBezel : MomentaryButton {};
struct TL1105 : MomentaryButton {}; //is this right?
struct CKD6 : MomentaryButton {};	//is this right?

template<typename LedT>
struct VCVLightBezel : LedT {};

template<typename LedT>
struct MediumLight : LedT {};

template<typename LedT>
struct SmallLight : LedT {};

} // namespace MetaModule
