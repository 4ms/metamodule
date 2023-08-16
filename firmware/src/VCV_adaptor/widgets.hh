#pragma once
#include "VCV_adaptor/app/Widget.hh"

namespace rack::componentlibrary
{

// These are defined in Rack, though some appear to be brand-specific

// clang-format off

// Screws

struct SvgScrew : widget::SvgWidget {};
struct ScrewSilver : SvgScrew {};

// Knobs

struct RoundBlackKnob : app::ParamWidget {};
struct RoundSmallBlackKnob : app::ParamWidget {};
struct RoundLargeBlackKnob : app::ParamWidget {};
struct RoundBigBlackKnob : app::ParamWidget {};
struct RoundHugeBlackKnob : app::ParamWidget {};
struct RoundBlackSnapKnob : app::ParamWidget {};

struct Davies1900hKnob : app::ParamWidget {};
struct Davies1900hWhiteKnob : app::ParamWidget {};
struct Davies1900hBlackKnob : app::ParamWidget {};
struct Davies1900hRedKnob : app::ParamWidget {};
struct Davies1900hLargeWhiteKnob : app::ParamWidget{};
struct Davies1900hLargeRedKnob : app::ParamWidget{};
struct Davies1900hLargeBlackKnob : app::ParamWidget{};

struct Rogan1PRed : app::ParamWidget {};
struct Rogan1PGreen : app::ParamWidget {};
struct Rogan1PWhite : app::ParamWidget {};
struct Rogan1PBlue : app::ParamWidget {};

struct Rogan1PSRed : app::ParamWidget {};
struct Rogan1PSGreen : app::ParamWidget {};
struct Rogan1PSWhite : app::ParamWidget {};
struct Rogan1PSBlue : app::ParamWidget {};

struct Rogan2PRed : app::ParamWidget {};
struct Rogan2PGreen : app::ParamWidget {};
struct Rogan2PWhite : app::ParamWidget {};
struct Rogan2PBlue : app::ParamWidget {};

struct Rogan2PSRed : app::ParamWidget {};
struct Rogan2PSGreen : app::ParamWidget {};
struct Rogan2PSWhite : app::ParamWidget {};
struct Rogan2PSBlue : app::ParamWidget {};

struct Rogan3PRed : app::ParamWidget {};
struct Rogan3PGreen : app::ParamWidget {};
struct Rogan3PWhite : app::ParamWidget {};
struct Rogan3PBlue : app::ParamWidget {};

struct Rogan3PSRed : app::ParamWidget {};
struct Rogan3PSGreen : app::ParamWidget {};
struct Rogan3PSWhite : app::ParamWidget {};
struct Rogan3PSBlue : app::ParamWidget {};

struct Rogan2SGray : app::ParamWidget {};
struct Rogan5PSGray : app::ParamWidget {};
struct Rogan6PSWhite: app::ParamWidget {};

struct SynthTechAlco : app::ParamWidget {};
struct Trimpot : app::ParamWidget {};

struct BefacoBigKnob : app::ParamWidget {};
struct BefacoTinyKnob : app::ParamWidget {};
struct BefacoSlidePot : app::ParamWidget {};

struct VCVSlider : app::ParamWidget {};
struct VCVSliderHorizontal : app::ParamWidget {};

// Jacks

struct CKD6 : app::ParamWidget {};
struct TL1105 : app::ParamWidget {};

struct PJ301MPort : app::PortWidget{};

// Switches

struct BefacoSwitch : app::ParamWidget {};
struct BefacoPush : app::ParamWidget {};
struct CKSS : app::ParamWidget {};
template <typename TBase> struct VCVLightBezel : app::SvgSwitch {};
struct VCVBezel : app::SvgSwitch {};
using LEDBezel = VCVBezel;

// Lights

template<typename T> struct MediumLight : app::ModuleLightWidget {};
template<typename T> struct SmallLight : app::ModuleLightWidget {};
template <typename TBase> struct VCVBezelLight : TBase {};
template <typename TBase> using LEDBezelLight = VCVBezelLight<TBase>;


struct GreenRedLight : app::ModuleLightWidget {};
struct RedLight : app::ModuleLightWidget {};
struct BlueLight : app::ModuleLightWidget {};
struct YellowLight : app::ModuleLightWidget {};
struct GreenLight : app::ModuleLightWidget {};
struct RedGreenBlueLight : app::ModuleLightWidget {};
// clang-format off

} // namespace rack

