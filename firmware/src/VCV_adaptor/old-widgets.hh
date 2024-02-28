#pragma once
#include "VCV_adaptor/app/SvgScrew.hpp"
#include "VCV_adaptor/app/Widget.hh"
#include "VCV_adaptor/asset.hpp"
//TODO Replace this with Rack/include/componentlibrary.hpp

namespace rack
{
namespace componentlibrary
{

////////////////////
// Color scheme
////////////////////

static const NVGcolor SCHEME_BLACK_TRANSPARENT = nvgRGBA(0x00, 0x00, 0x00, 0x00);
static const NVGcolor SCHEME_BLACK = nvgRGB(0x00, 0x00, 0x00);
static const NVGcolor SCHEME_WHITE = nvgRGB(0xff, 0xff, 0xff);
static const NVGcolor SCHEME_RED = nvgRGB(0xed, 0x2c, 0x24);
static const NVGcolor SCHEME_ORANGE = nvgRGB(0xf2, 0xb1, 0x20);
static const NVGcolor SCHEME_YELLOW = nvgRGB(0xff, 0xd7, 0x14);
static const NVGcolor SCHEME_GREEN = nvgRGB(0x90, 0xc7, 0x3e);
static const NVGcolor SCHEME_CYAN = nvgRGB(0x22, 0xe6, 0xef);
static const NVGcolor SCHEME_BLUE = nvgRGB(0x29, 0xb2, 0xef);
static const NVGcolor SCHEME_PURPLE = nvgRGB(0xd5, 0x2b, 0xed);
static const NVGcolor SCHEME_LIGHT_GRAY = nvgRGB(0xe6, 0xe6, 0xe6);
static const NVGcolor SCHEME_DARK_GRAY = nvgRGB(0x17, 0x17, 0x17);

// clang-format off

// Screws
struct ScrewSilver : app::SvgScrew {};
struct ThemedScrew : app::ThemedSvgScrew {};

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

struct Rogan : app::ParamWidget {
	std::unique_ptr<widget::SvgWidget> bg {new widget::SvgWidget};
	std::unique_ptr<widget::SvgWidget> fg {new widget::SvgWidget};
};

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

struct BefacoBigKnob : app::SvgKnob {
	widget::SvgWidget* bg;

	BefacoBigKnob() : bg(new widget::SvgWidget) {
		printf("BefacoBigKnob()\n");
		minAngle = -0.75f * M_PI;
		maxAngle = 0.75f * M_PI;
		setSvg(window::Svg::load(asset::system("res/ComponentLibrary/BefacoBigKnob.svg")));

		
		// fb->addChildBelow(bg, tw);
		bg->setSvg(window::Svg::load(asset::system("res/ComponentLibrary/BefacoBigKnob_bg.svg")));
	}
};

struct BefacoTinyKnob : app::SvgKnob {
	widget::SvgWidget* bg;

	BefacoTinyKnob() : bg(new widget::SvgWidget) {
		minAngle = -0.8f * M_PI;
		maxAngle = 0.8f * M_PI;

		
		// fb->addChildBelow(bg, tw);

		setSvg(window::Svg::load(asset::system("res/ComponentLibrary/BefacoTinyPointBlack.svg")));
		bg->setSvg(window::Svg::load(asset::system("res/ComponentLibrary/BefacoTinyKnobWhite_bg.svg")));
	}
};

struct BefacoSlidePot : app::SvgSlider {
	BefacoSlidePot() {
		setBackgroundSvg(window::Svg::load(asset::system("res/ComponentLibrary/BefacoSlidePot.svg")));
		setHandleSvg(window::Svg::load(asset::system("res/ComponentLibrary/BefacoSlidePotHandle.svg")));
		math::Vec margin = math::Vec(3.5, 3.5);
		setHandlePos(math::Vec(-1, 87).plus(margin), math::Vec(-1, -2).plus(margin));
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
	}
};

struct VCVSlider : app::SvgSlider {
	VCVSlider() {
		setBackgroundSvg(window::Svg::load(asset::system("res/ComponentLibrary/VCVSlider.svg")));
		setHandleSvg(window::Svg::load(asset::system("res/ComponentLibrary/VCVSliderHandle.svg")));
		setHandlePosCentered(
			math::Vec(19.84260/2, 76.53517 - 11.74218/2),
			math::Vec(19.84260/2, 0.0 + 11.74218/2)
		);
	}
};
using LEDSlider = VCVSlider;

struct VCVSliderHorizontal : app::SvgSlider {
	VCVSliderHorizontal() {
		horizontal = true;
		setBackgroundSvg(window::Svg::load(asset::system("res/ComponentLibrary/VCVSliderHorizontal.svg")));
		setHandlePos(window::mm2px(math::Vec(0.738, 0.738).plus(math::Vec(0, 2))), window::mm2px(math::Vec(22.078, 0.738).plus(math::Vec(0, 2))));
	}
};
using LEDSliderHorizontal = VCVSliderHorizontal;



// Jacks

struct CKD6 : app::ParamWidget {};
struct TL1105 : app::ParamWidget {};

struct PJ301MPort : app::PortWidget{};
struct ThemedPJ301MPort : app::ThemedSvgPort {};

// Switches

struct BefacoSwitch : app::ParamWidget {};
struct BefacoPush : app::ParamWidget {};
struct CKSS : app::ParamWidget {};
template <typename TBase> struct VCVLightBezel : app::SvgSwitch {};
struct VCVBezel : app::SvgSwitch {};
using LEDBezel = VCVBezel;

// Lights

template<typename T> struct LargeLight : T {};
template<typename T> struct MediumLight : T {};
template<typename T> struct SmallLight : T {};
template <typename TBase> struct VCVBezelLight : TBase {};
template <typename TBase> using LEDBezelLight = VCVBezelLight<TBase>;


struct GreenRedLight : app::ModuleLightWidget {};
struct RedLight : app::ModuleLightWidget {};
struct BlueLight : app::ModuleLightWidget {};
struct YellowLight : app::ModuleLightWidget {};
struct GreenLight : app::ModuleLightWidget {};
struct RedGreenBlueLight : app::ModuleLightWidget {};
struct GrayModuleLightWidget : app::ModuleLightWidget {};
// clang-format off

} // namespace componentlibrary

struct GrayModuleLightWidget : app::ModuleLightWidget {};

} // namespace rack

