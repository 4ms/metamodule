#pragma once
#include "VCV-adaptor/app/Widget.hh"

namespace rack
{

// These are defined in Rack, though some appear to be brand-specific

// clang-format off
struct SvgScrew : widget::SvgWidget {};
struct ScrewSilver : SvgScrew {};

struct BefacoBigKnob : app::ParamWidget {};
struct BefacoTinyKnob : app::ParamWidget {};
struct BefacoSlidePot : app::ParamWidget {};
struct BefacoSwitch : app::ParamWidget {};
struct BefacoPush : app::ParamWidget {};
struct CKSS : app::ParamWidget {};
struct Davies1900hBlackKnob : app::ParamWidget {};
struct Davies1900hKnob : app::ParamWidget {};
struct Davies1900hWhiteKnob : app::ParamWidget {};
struct Davies1900hRedKnob : app::ParamWidget {};
struct Davies1900hLargeWhiteKnob : app::ParamWidget{};

struct Rogan2SGray : app::ParamWidget {};
struct Rogan1PSRed : app::ParamWidget {};
struct Rogan1PSGreen : app::ParamWidget {};
struct Rogan1PSWhite : app::ParamWidget {};
struct Rogan1PSBlue : app::ParamWidget {};
struct Rogan2PSRed : app::ParamWidget {};
struct Rogan2PSGreen : app::ParamWidget {};
struct Rogan2PSWhite : app::ParamWidget {};
struct Rogan2PSBlue : app::ParamWidget {};
struct Rogan3PSRed : app::ParamWidget {};
struct Rogan3PSGreen : app::ParamWidget {};
struct Rogan3PSWhite : app::ParamWidget {};
struct Rogan3PSBlue : app::ParamWidget {};

struct CKD6 : app::ParamWidget {};
struct TL1105 : app::ParamWidget {};

struct PJ301MPort : app::PortWidget{};

template<typename T> struct MediumLight : widget::SvgWidget {};
template<typename T> struct SmallLight : widget::SvgWidget {};
struct GreenRedLight : widget::SvgWidget {};
struct RedLight : widget::SvgWidget {};
struct YellowLight : widget::SvgWidget {};
struct GreenLight : widget::SvgWidget {};
struct RedGreenBlueLight : widget::SvgWidget {};
// clang-format off

} // namespace rack

