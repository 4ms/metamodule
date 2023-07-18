#pragma once

// Forward declarations for widgets

// Dependent types:
namespace rack
{

namespace app
{
struct ModuleLightWidget;
}

namespace componentlibrary
{

template<typename TBase = app::ModuleLightWidget>
struct TGrayModuleLightWidget;

template<typename TBase = app::ModuleLightWidget>
struct TWhiteLight;

template<typename TBase = app::ModuleLightWidget>
struct TRedLight;

template<typename TBase = app::ModuleLightWidget>
struct TGreenLight;

// Main types:

// TODO: add tempalte specializations as used in VCV modules

template<typename TBase>
struct LargeLight;

template<typename TBase>
struct MediumLight;

template<typename TBase>
struct SmallLight;

template<typename TBase>
struct TinyLight;

template<typename TBase>
struct LargeSimpleLight;

template<>
struct LargeSimpleLight<TGrayModuleLightWidget<>>;

template<typename TBase>
struct MediumSimpleLight;

template<>
struct MediumSimpleLight<TGrayModuleLightWidget<>>;

template<typename TBase>
struct SmallSimpleLight;

template<>
struct SmallSimpleLight<TGrayModuleLightWidget<>>;

template<typename TBase>
struct TinySimpleLight;

template<>
struct TinySimpleLight<TGrayModuleLightWidget<>>;

template<typename TBase>
struct RectangleLight;

template<typename TBase>
struct VCVBezelLight;

template<typename TBase>
using LEDBezelLight = VCVBezelLight<TBase>;

template<typename TBase>
struct PB61303Light;

struct RoundBlackKnob;
struct RoundSmallBlackKnob;
struct RoundLargeBlackKnob;
struct RoundBigBlackKnob;
struct RoundHugeBlackKnob;
struct RoundBlackSnapKnob;

struct Davies1900hWhiteKnob;
struct Davies1900hBlackKnob;
struct Davies1900hRedKnob;
struct Davies1900hLargeWhiteKnob;
struct Davies1900hLargeBlackKnob;
struct Davies1900hLargeRedKnob;

struct Rogan6PSWhite;
struct Rogan5PSGray;
struct Rogan3PSBlue;
struct Rogan3PSRed;
struct Rogan3PSGreen;
struct Rogan3PSWhite;
struct Rogan3PBlue;
struct Rogan3PRed;
struct Rogan3PGreen;
struct Rogan3PWhite;
struct Rogan2SGray;
struct Rogan2PSBlue;
struct Rogan2PSRed;
struct Rogan2PSGreen;
struct Rogan2PSWhite;
struct Rogan2PBlue;
struct Rogan2PRed;
struct Rogan2PGreen;
struct Rogan2PWhite;
struct Rogan1PSBlue;
struct Rogan1PSRed;
struct Rogan1PSGreen;
struct Rogan1PSWhite;
struct Rogan1PBlue;
struct Rogan1PRed;
struct Rogan1PGreen;
struct Rogan1PWhite;
struct SynthTechAlco;
struct Trimpot;
struct BefacoBigKnob;
struct BefacoTinyKnob;
struct BefacoSlidePot;
struct VCVSlider;
struct VCVSliderHorizontal;

template<typename TBase, typename TLightBase = TRedLight<>>
struct LightSlider;

template<typename TBase>
struct VCVSliderLight;

template<typename TBase>
using LEDSliderLight = VCVSliderLight<TBase>;

template<typename TLightBase = TRedLight<>>
struct VCVLightSlider;

template<typename TLightBase = TRedLight<>>
using LEDLightSlider = VCVLightSlider<TLightBase>;

struct LEDSliderGreen;
struct LEDSliderRed;
struct LEDSliderYellow;
struct LEDSliderBlue;
struct LEDSliderWhite;

template<typename TLightBase = TRedLight<>>
struct VCVLightSliderHorizontal;

template<typename TLightBase = TRedLight<>>
using LEDLightSliderHorizontal = VCVLightSliderHorizontal<TLightBase>;

struct PJ301MPort;
struct PJ3410Port;
struct CL1362Port;

template<typename TSwitch>
struct MomentarySwitch;

struct NKK;
struct CKSS;
struct CKSSThree;
struct CKSSThreeHorizontal;
struct CKD6;
struct TL1105;
struct VCVButton;
struct VCVLatch;

template<typename TLight>
struct VCVLightButton;

template<typename TLight>
using LEDLightButton = VCVLightButton<TLight>;

template<typename TLight>
struct VCVLightLatch;

struct BefacoSwitch;
struct BefacoPush;
struct VCVBezel;

struct VCVBezelLatch;

template<typename TLightBase = TWhiteLight<>>
struct VCVLightBezel;

template<typename TLightBase = TWhiteLight<>>
using LEDLightBezel = VCVLightBezel<TLightBase>;

template<typename TLightBase = TWhiteLight<>>
struct VCVLightBezelLatch;

struct PB61303;
struct ScrewSilver;
struct ScrewBlack;
struct SegmentDisplay;
struct AudioButton_ADAT;
struct AudioButton_USB_B;
struct MidiButton_MIDI_DIN;

} // namespace componentlibrary
} // namespace rack
