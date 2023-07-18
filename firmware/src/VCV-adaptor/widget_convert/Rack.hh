#pragma once
#include "CoreModules/elements/elements.hh"
#include "VCV-adaptor/widget_convert/base.hh"
#include "VCV-adaptor/widgets.hh"

namespace rack
{

template<>
struct ElementConvert<BefacoBigKnob> {
	using ElementType = MetaModule::BefacoBigKnob;
};

template<>
struct ElementConvert<BefacoTinyKnob> {
	using ElementType = MetaModule::BefacoTinyKnob;
};

template<>
struct ElementConvert<BefacoSlidePot> {
	using ElementType = MetaModule::BefacoSlidePot;
};

template<>
struct ElementConvert<BefacoSwitch> {
	using ElementType = MetaModule::BefacoSwitch;
};

template<>
struct ElementConvert<BefacoPush> {
	using ElementType = MetaModule::BefacoPush;
};

template<>
struct ElementConvert<CKSS> { // TODO: What is CKSS? Is this the right element?
	using ElementType = MetaModule::Slider25mmHoriz;
};

template<>
struct ElementConvert<Davies1900hBlackKnob> {
	using ElementType = MetaModule::Davies1900hBlackKnob;
};

template<>
struct ElementConvert<Davies1900hKnob> {
	using ElementType = MetaModule::Davies1900hBlackKnob;
};

template<>
struct ElementConvert<Davies1900hWhiteKnob> {
	using ElementType = MetaModule::Davies1900hWhiteKnob;
};

template<>
struct ElementConvert<Davies1900hRedKnob> {
	using ElementType = MetaModule::Davies1900hRedKnob;
};

template<>
struct ElementConvert<Davies1900hLargeWhiteKnob> {
	using ElementType = MetaModule::Davies1900hLargeWhiteKnob;
};

template<>
struct ElementConvert<Rogan2SGray> {
	using ElementType = MetaModule::Rogan2SGray;
};

template<>
struct ElementConvert<Rogan2PSWhite> {
	using ElementType = MetaModule::Rogan2PSWhite;
};

template<>
struct ElementConvert<Rogan2PSRed> {
	using ElementType = MetaModule::Rogan2PSRed;
};

template<>
struct ElementConvert<Rogan2PSGreen> {
	using ElementType = MetaModule::Rogan2PSGreen;
};
}

namespace rack
{
namespace app
{
struct ModuleLightWidget;
}
template<typename TBase = app::ModuleLightWidget>
struct TGrayModuleLightWidget;

template<typename TBase = app::ModuleLightWidget>
struct TWhiteLight;

template<typename TBase = app::ModuleLightWidget>
struct TRedLight;

template<typename TBase = app::ModuleLightWidget>
struct TGreenLight;

}

// using SvgLight = TSvgLight<>;
//  using WhiteLight = TWhiteLight<>;
//  using RedLight = TRedLight<>;
//  using GreenLight = TGreenLight<>;
//  using BlueLight = TBlueLight<>;
//  using YellowLight = TYellowLight<>;
//  using GreenRedLight = TGreenRedLight<>;
//  using RedGreenBlueLight = TRedGreenBlueLight<>;

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
struct LargeSimpleLight<rack::TGrayModuleLightWidget<>>;

template<typename TBase>
struct MediumSimpleLight;

template<>
struct MediumSimpleLight<rack::TGrayModuleLightWidget<>>;

template<typename TBase>
struct SmallSimpleLight;

template<>
struct SmallSimpleLight<rack::TGrayModuleLightWidget<>>;

template<typename TBase>
struct TinySimpleLight;

template<>
struct TinySimpleLight<rack::TGrayModuleLightWidget<>>;

template<typename TBase>
struct RectangleLight;

template<typename TBase>
struct VCVBezelLight;

template<typename TBase>
using LEDBezelLight = VCVBezelLight<TBase>;

template<typename TBase>
struct PB61303Light;

//////////////////
Knobs
	//////////////////

	struct RoundBlackKnob : RoundKnob {

	struct RoundSmallBlackKnob : RoundKnob {

		struct RoundLargeBlackKnob : RoundKnob {

			struct RoundBigBlackKnob : RoundKnob {

				struct RoundHugeBlackKnob : RoundKnob {

					struct RoundBlackSnapKnob : RoundBlackKnob {

						struct Davies1900hWhiteKnob : Davies1900hKnob {
							struct Davies1900hBlackKnob : Davies1900hKnob {
								struct Davies1900hRedKnob : Davies1900hKnob {
									struct Davies1900hLargeWhiteKnob : Davies1900hKnob {
										struct Davies1900hLargeBlackKnob : Davies1900hKnob {
											struct Davies1900hLargeRedKnob : Davies1900hKnob {

												struct Rogan6PSWhite : Rogan {
													struct Rogan5PSGray : Rogan {
														struct Rogan3PSBlue : Rogan {
															struct Rogan3PSRed : Rogan {
																struct Rogan3PSGreen : Rogan {
																	struct Rogan3PSWhite : Rogan {
																		struct Rogan3PBlue : Rogan {
																			struct Rogan3PRed : Rogan {
																				struct Rogan3PGreen : Rogan {
																					struct Rogan3PWhite : Rogan {

																						struct Rogan2SGray : Rogan {

																							struct Rogan2PSBlue :
																								Rogan {

																								struct Rogan2PSRed :
																									Rogan {

																									struct
																										Rogan2PSGreen :
																										Rogan {

																										struct
																											Rogan2PSWhite :
																											Rogan {
																											Rogan2PSWhite() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"SW"
																													"hi"
																													"te"
																													".s"
																													"v"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"S_"
																													"bg"
																													".s"
																													"v"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"SW"
																													"hi"
																													"te"
																													"_f"
																													"g."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											Rogan2PBlue :
																											Rogan {
																											Rogan2PBlue() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"Bl"
																													"ue"
																													".s"
																													"v"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"Bl"
																													"ue"
																													"_f"
																													"g."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											Rogan2PRed :
																											Rogan {
																											Rogan2PRed() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"Re"
																													"d."
																													"sv"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"Re"
																													"d_"
																													"fg"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										struct
																											Rogan2PGreen :
																											Rogan {
																											Rogan2PGreen() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"Gr"
																													"ee"
																													"n."
																													"sv"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"Gr"
																													"ee"
																													"n_"
																													"fg"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										struct
																											Rogan2PWhite :
																											Rogan {
																											Rogan2PWhite() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"Wh"
																													"it"
																													"e."
																													"sv"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"2P"
																													"Wh"
																													"it"
																													"e_"
																													"fg"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										struct
																											Rogan1PSBlue :
																											Rogan {
																											Rogan1PSBlue() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"SB"
																													"lu"
																													"e."
																													"sv"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"S_"
																													"bg"
																													".s"
																													"v"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"SB"
																													"lu"
																													"e_"
																													"fg"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										struct
																											Rogan1PSRed :
																											Rogan {
																											Rogan1PSRed() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"SR"
																													"ed"
																													".s"
																													"v"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"S_"
																													"bg"
																													".s"
																													"v"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"SR"
																													"ed"
																													"_f"
																													"g."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											Rogan1PSGreen :
																											Rogan {
																											Rogan1PSGreen() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"SG"
																													"re"
																													"en"
																													".s"
																													"v"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"S_"
																													"bg"
																													".s"
																													"v"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"SG"
																													"re"
																													"en"
																													"_f"
																													"g."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											Rogan1PSWhite :
																											Rogan {
																											Rogan1PSWhite() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"SW"
																													"hi"
																													"te"
																													".s"
																													"v"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"S_"
																													"bg"
																													".s"
																													"v"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"SW"
																													"hi"
																													"te"
																													"_f"
																													"g."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											Rogan1PBlue :
																											Rogan {
																											Rogan1PBlue() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"Bl"
																													"ue"
																													".s"
																													"v"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"Bl"
																													"ue"
																													"_f"
																													"g."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											Rogan1PRed :
																											Rogan {
																											Rogan1PRed() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"Re"
																													"d."
																													"sv"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"Re"
																													"d_"
																													"fg"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										struct
																											Rogan1PGreen :
																											Rogan {
																											Rogan1PGreen() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"Gr"
																													"ee"
																													"n."
																													"sv"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"Gr"
																													"ee"
																													"n_"
																													"fg"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										struct
																											Rogan1PWhite :
																											Rogan {
																											Rogan1PWhite() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"Wh"
																													"it"
																													"e."
																													"sv"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																												fg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/R"
																													"og"
																													"an"
																													"1P"
																													"Wh"
																													"it"
																													"e_"
																													"fg"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										struct
																											SynthTechAlco :
																											app::
																												SvgKnob {
																											widget::
																												SvgWidget
																													*bg;

																											SynthTechAlco() {
																												minAngle =
																													-0.82 *
																													M_PI;
																												maxAngle =
																													0.82 *
																													M_PI;

																												bg = new widget::
																													SvgWidget;
																												fb->addChildBelow(
																													bg,
																													tw);

																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/S"
																													"yn"
																													"th"
																													"Te"
																													"ch"
																													"Al"
																													"co"
																													".s"
																													"v"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/S"
																													"yn"
																													"th"
																													"Te"
																													"ch"
																													"Al"
																													"co"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																											}
																										};

																										struct Trimpot :
																											app::
																												SvgKnob {
																											widget::
																												SvgWidget
																													*bg;

																											Trimpot() {
																												minAngle =
																													-0.75 *
																													M_PI;
																												maxAngle =
																													0.75 *
																													M_PI;

																												bg = new widget::
																													SvgWidget;
																												fb->addChildBelow(
																													bg,
																													tw);

																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/T"
																													"ri"
																													"mp"
																													"ot"
																													".s"
																													"v"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/T"
																													"ri"
																													"mp"
																													"ot"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											BefacoBigKnob :
																											app::
																												SvgKnob {
																											widget::
																												SvgWidget
																													*bg;

																											BefacoBigKnob() {
																												minAngle =
																													-0.75 *
																													M_PI;
																												maxAngle =
																													0.75 *
																													M_PI;
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/B"
																													"ef"
																													"ac"
																													"oB"
																													"ig"
																													"Kn"
																													"ob"
																													".s"
																													"v"
																													"g")));

																												bg = new widget::
																													SvgWidget;
																												fb->addChildBelow(
																													bg,
																													tw);
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/B"
																													"ef"
																													"ac"
																													"oB"
																													"ig"
																													"Kn"
																													"ob"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											BefacoTinyKnob :
																											app::
																												SvgKnob {
																											widget::
																												SvgWidget
																													*bg;

																											BefacoTinyKnob() {
																												minAngle =
																													-0.8 *
																													M_PI;
																												maxAngle =
																													0.8 *
																													M_PI;

																												bg = new widget::
																													SvgWidget;
																												fb->addChildBelow(
																													bg,
																													tw);

																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/B"
																													"ef"
																													"ac"
																													"oT"
																													"in"
																													"yP"
																													"oi"
																													"nt"
																													"Bl"
																													"ac"
																													"k."
																													"sv"
																													"g")));
																												bg->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/B"
																													"ef"
																													"ac"
																													"oT"
																													"in"
																													"yK"
																													"no"
																													"bW"
																													"hi"
																													"te"
																													"_b"
																													"g."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											BefacoSlidePot :
																											app::
																												SvgSlider {
																											BefacoSlidePot() {
																												math::Vec margin =
																													math::Vec(
																														3.5,
																														3.5);
																												maxHandlePos =
																													math::Vec(
																														-1,
																														-2)
																														.plus(
																															margin);
																												minHandlePos =
																													math::Vec(
																														-1,
																														87)
																														.plus(
																															margin);
																												setBackgroundSvg(
																													Svg::load(asset::system(
																														"re"
																														"s/"
																														"Co"
																														"mp"
																														"on"
																														"en"
																														"tL"
																														"ib"
																														"ra"
																														"ry"
																														"/B"
																														"ef"
																														"ac"
																														"oS"
																														"li"
																														"de"
																														"Po"
																														"t."
																														"sv"
																														"g")));
																												setHandleSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/B"
																													"ef"
																													"ac"
																													"oS"
																													"li"
																													"de"
																													"Po"
																													"tH"
																													"an"
																													"dl"
																													"e."
																													"sv"
																													"g")));
																												background
																													->box
																													.pos =
																													margin;
																												box.size =
																													background
																														->box
																														.size
																														.plus(
																															margin
																																.mult(
																																	2));
																											}
																										};

																										struct
																											VCVSlider :
																											app::
																												SvgSlider {
																											VCVSlider() {
																												setBackgroundSvg(
																													Svg::load(asset::system(
																														"re"
																														"s/"
																														"Co"
																														"mp"
																														"on"
																														"en"
																														"tL"
																														"ib"
																														"ra"
																														"ry"
																														"/V"
																														"CV"
																														"Sl"
																														"id"
																														"er"
																														".s"
																														"v"
																														"g")));
																												setHandleSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/V"
																													"CV"
																													"Sl"
																													"id"
																													"er"
																													"Ha"
																													"nd"
																													"le"
																													".s"
																													"v"
																													"g")));
																												setHandlePosCentered(
																													math::Vec(
																														19.84260 /
																															2,
																														76.53517 -
																															11.74218 /
																																2),
																													math::Vec(
																														19.84260 /
																															2,
																														0.0 +
																															11.74218 /
																																2));
																											}
																										};
																										using LEDSlider =
																											VCVSlider;

																										struct
																											VCVSliderHorizontal :
																											app::
																												SvgSlider {
																											VCVSliderHorizontal() {
																												horizontal =
																													true;
																												// TODO Fix positions
																												maxHandlePos = mm2px(
																													math::Vec(
																														22.078,
																														0.738)
																														.plus(math::Vec(
																															0,
																															2)));
																												minHandlePos = mm2px(
																													math::Vec(
																														0.738,
																														0.738)
																														.plus(math::Vec(
																															0,
																															2)));
																												// TODO Fix SVG
																												setBackgroundSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/V"
																													"CV"
																													"Sl"
																													"id"
																													"er"
																													"Ho"
																													"ri"
																													"zo"
																													"nt"
																													"al"
																													".s"
																													"v"
																													"g")));
																											}
																										};
																										using LEDSliderHorizontal =
																											VCVSliderHorizontal;

																										/** An SvgSlider with an attached light.
Construct with createLightParamCentered() helper function.
*/
																										template<
																											typename TBase,
																											typename TLightBase =
																												RedLight>
																										struct
																											LightSlider;

																										template<
																											typename TBase>
																										struct
																											VCVSliderLight :
																											RectangleLight<
																												TSvgLight<
																													TBase>> {
																											VCVSliderLight() {
																												this->setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/V"
																													"CV"
																													"Sl"
																													"id"
																													"er"
																													"Li"
																													"gh"
																													"t."
																													"sv"
																													"g")));
																											}
																										};
																										template<
																											typename TBase>
																										using LEDSliderLight =
																											VCVSliderLight<
																												TBase>;

																										template<
																											typename TLightBase =
																												RedLight>
																										struct
																											VCVLightSlider :
																											LightSlider<
																												VCVSlider,
																												VCVSliderLight<
																													TLightBase>> {
																											VCVLightSlider() {
																											}
																										};
																										template<
																											typename TLightBase =
																												RedLight>
																										using LEDLightSlider =
																											VCVLightSlider<
																												TLightBase>;

																										/** Deprecated. Use VCVSliderLight with your preferred LightWidget. */
																										struct
																											LEDSliderGreen :
																											VCVLightSlider<
																												GreenLight> {
																										};
																										struct
																											LEDSliderRed :
																											VCVLightSlider<
																												RedLight> {
																										};
																										struct
																											LEDSliderYellow :
																											VCVLightSlider<
																												YellowLight> {
																										};
																										struct
																											LEDSliderBlue :
																											VCVLightSlider<
																												BlueLight> {
																										};
																										struct
																											LEDSliderWhite :
																											VCVLightSlider<
																												WhiteLight> {
																										};

																										template<
																											typename TLightBase =
																												RedLight>
																										struct
																											VCVLightSliderHorizontal :
																											LightSlider<
																												VCVSliderHorizontal,
																												TLightBase> {
																											VCVLightSliderHorizontal() {
																												// TODO Fix positions
																												this->light
																													->box
																													.size = mm2px(
																													math::Vec(
																														3.276,
																														1.524));
																												// TODO Fix SVG
																												this->setHandleSvg(
																													Svg::load(asset::system(
																														"re"
																														"s/"
																														"Co"
																														"mp"
																														"on"
																														"en"
																														"tL"
																														"ib"
																														"ra"
																														"ry"
																														"/V"
																														"CV"
																														"Sl"
																														"id"
																														"er"
																														"Ho"
																														"ri"
																														"zo"
																														"nt"
																														"al"
																														"Ha"
																														"nd"
																														"le"
																														".s"
																														"v"
																														"g")));
																											}
																										};
																										template<
																											typename TLightBase =
																												RedLight>
																										using LEDLightSliderHorizontal =
																											VCVLightSliderHorizontal<
																												TLightBase>;

																										////////////////////
																										// Ports
																										////////////////////

																										struct
																											PJ301MPort :
																											app::
																												SvgPort {
																											PJ301MPort() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/P"
																													"J3"
																													"01"
																													"M."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											PJ3410Port :
																											app::
																												SvgPort {
																											PJ3410Port() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/P"
																													"J3"
																													"41"
																													"0."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											CL1362Port :
																											app::
																												SvgPort {
																											CL1362Port() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/C"
																													"L1"
																													"36"
																													"2."
																													"sv"
																													"g")));
																											}
																										};

																										////////////////////
																										// Switches
																										////////////////////

																										template<
																											typename TSwitch>
																										struct
																											MomentarySwitch :
																											TSwitch {
																											MomentarySwitch() {
																												this->momentary =
																													true;
																											}
																										};

																										struct NKK :
																											app::
																												SvgSwitch {
																											NKK() {
																												shadow
																													->opacity =
																													0.0;
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/N"
																													"KK"
																													"_0"
																													".s"
																													"v"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/N"
																													"KK"
																													"_1"
																													".s"
																													"v"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/N"
																													"KK"
																													"_2"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										struct CKSS :
																											app::
																												SvgSwitch {
																											CKSS() {
																												shadow
																													->opacity =
																													0.0;
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/C"
																													"KS"
																													"S_"
																													"0."
																													"sv"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/C"
																													"KS"
																													"S_"
																													"1."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											CKSSThree :
																											app::
																												SvgSwitch {
																											CKSSThree() {
																												shadow
																													->opacity =
																													0.0;
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/C"
																													"KS"
																													"ST"
																													"hr"
																													"ee"
																													"_0"
																													".s"
																													"v"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/C"
																													"KS"
																													"ST"
																													"hr"
																													"ee"
																													"_1"
																													".s"
																													"v"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/C"
																													"KS"
																													"ST"
																													"hr"
																													"ee"
																													"_2"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										struct
																											CKSSThreeHorizontal :
																											app::
																												SvgSwitch {
																											CKSSThreeHorizontal() {
																												shadow
																													->opacity =
																													0.0;
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/C"
																													"KS"
																													"ST"
																													"hr"
																													"ee"
																													"Ho"
																													"ri"
																													"zo"
																													"nt"
																													"al"
																													"_0"
																													".s"
																													"v"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/C"
																													"KS"
																													"ST"
																													"hr"
																													"ee"
																													"Ho"
																													"ri"
																													"zo"
																													"nt"
																													"al"
																													"_1"
																													".s"
																													"v"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/C"
																													"KS"
																													"ST"
																													"hr"
																													"ee"
																													"Ho"
																													"ri"
																													"zo"
																													"nt"
																													"al"
																													"_2"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										struct CKD6 :
																											app::
																												SvgSwitch {
																											CKD6() {
																												momentary =
																													true;
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/C"
																													"KD"
																													"6_"
																													"0."
																													"sv"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/C"
																													"KD"
																													"6_"
																													"1."
																													"sv"
																													"g")));
																											}
																										};

																										struct TL1105 :
																											app::
																												SvgSwitch {
																											TL1105() {
																												momentary =
																													true;
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/T"
																													"L1"
																													"10"
																													"5_"
																													"0."
																													"sv"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/T"
																													"L1"
																													"10"
																													"5_"
																													"1."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											VCVButton :
																											app::
																												SvgSwitch {
																											VCVButton() {
																												momentary =
																													true;
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/V"
																													"CV"
																													"Bu"
																													"tt"
																													"on"
																													"_0"
																													".s"
																													"v"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/V"
																													"CV"
																													"Bu"
																													"tt"
																													"on"
																													"_1"
																													".s"
																													"v"
																													"g")));
																											}
																										};
																										using LEDButton =
																											VCVButton;

																										struct
																											VCVLatch :
																											VCVButton {
																											VCVLatch() {
																												momentary =
																													false;
																												latch =
																													true;
																											}
																										};

																										/** Looks best with MediumSimpleLight<WhiteLight> or a color of your choice.
*/
																										template<
																											typename TLight>
																										struct
																											VCVLightButton :
																											VCVButton {
																											app::ModuleLightWidget
																												*light;

																											VCVLightButton() {
																												light =
																													new TLight;
																												// Move center of light to center of box
																												light
																													->box
																													.pos =
																													box.size
																														.div(
																															2)
																														.minus(
																															light
																																->box
																																.size
																																.div(
																																	2));
																												addChild(
																													light);
																											}

																											app::ModuleLightWidget *
																											getLight() {
																												return light;
																											}
																										};
																										template<
																											typename TLight>
																										using LEDLightButton =
																											VCVLightButton<
																												TLight>;

																										template<
																											typename TLight>
																										struct
																											VCVLightLatch :
																											VCVLightButton<
																												TLight> {
																											VCVLightLatch() {
																												this->momentary =
																													false;
																												this->latch =
																													true;
																											}
																										};

																										struct
																											BefacoSwitch :
																											app::
																												SvgSwitch {
																											BefacoSwitch() {
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/B"
																													"ef"
																													"ac"
																													"oS"
																													"wi"
																													"tc"
																													"h_"
																													"0."
																													"sv"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/B"
																													"ef"
																													"ac"
																													"oS"
																													"wi"
																													"tc"
																													"h_"
																													"1."
																													"sv"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/B"
																													"ef"
																													"ac"
																													"oS"
																													"wi"
																													"tc"
																													"h_"
																													"2."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											BefacoPush :
																											app::
																												SvgSwitch {
																											BefacoPush() {
																												momentary =
																													true;
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/B"
																													"ef"
																													"ac"
																													"oP"
																													"us"
																													"h_"
																													"0."
																													"sv"
																													"g")));
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/B"
																													"ef"
																													"ac"
																													"oP"
																													"us"
																													"h_"
																													"1."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											VCVBezel :
																											app::
																												SvgSwitch {
																											VCVBezel() {
																												momentary =
																													true;
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/V"
																													"CV"
																													"Be"
																													"ze"
																													"l."
																													"sv"
																													"g")));
																											}
																										};
																										using LEDBezel =
																											VCVBezel;

																										struct
																											VCVBezelLatch :
																											VCVBezel {
																											VCVBezelLatch() {
																												momentary =
																													false;
																												latch =
																													true;
																											}
																										};

																										template<
																											typename TLightBase =
																												WhiteLight>
																										struct
																											VCVLightBezel :
																											VCVBezel {
																											app::ModuleLightWidget
																												*light;

																											VCVLightBezel() {
																												light = new VCVBezelLight<
																													TLightBase>;
																												// Move center of light to center of box
																												light
																													->box
																													.pos =
																													box.size
																														.div(
																															2)
																														.minus(
																															light
																																->box
																																.size
																																.div(
																																	2));
																												addChild(
																													light);
																											}

																											app::ModuleLightWidget *
																											getLight() {
																												return light;
																											}
																										};
																										template<
																											typename TLightBase =
																												WhiteLight>
																										using LEDLightBezel =
																											VCVLightBezel<
																												TLightBase>;

																										template<
																											typename TLightBase =
																												WhiteLight>
																										struct
																											VCVLightBezelLatch :
																											VCVLightBezel<
																												TLightBase> {
																											VCVLightBezelLatch() {
																												this->momentary =
																													false;
																												this->latch =
																													true;
																											}
																										};

																										struct PB61303 :
																											app::
																												SvgSwitch {
																											PB61303() {
																												momentary =
																													true;
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/P"
																													"B6"
																													"13"
																													"03"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										////////////////////
																										// Misc
																										////////////////////

																										struct
																											ScrewSilver :
																											app::
																												SvgScrew {
																											ScrewSilver() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/S"
																													"cr"
																													"ew"
																													"Si"
																													"lv"
																													"er"
																													".s"
																													"v"
																													"g")));
																											}
																										};

																										struct
																											ScrewBlack :
																											app::
																												SvgScrew {
																											ScrewBlack() {
																												setSvg(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/S"
																													"cr"
																													"ew"
																													"Bl"
																													"ac"
																													"k."
																													"sv"
																													"g")));
																											}
																										};

																										struct
																											SegmentDisplay :
																											widget::
																												Widget {
																											int lightsLen =
																												0;
																											bool vertical =
																												false;
																											float margin =
																												mm2px(
																													0.5);

																											void draw(
																												const DrawArgs
																													&args)
																												override {
																												// Background
																												nvgBeginPath(
																													args.vg);
																												nvgRect(
																													args.vg,
																													0,
																													0,
																													box.size
																														.x,
																													box.size
																														.y);
																												nvgFillColor(
																													args.vg,
																													color::
																														BLACK);
																												nvgFill(
																													args.vg);
																												Widget::draw(
																													args);
																											}

																											template<
																												typename TLightBase =
																													WhiteLight>
																											void
																											setLights(
																												engine::Module
																													*module,
																												int firstLightId,
																												int lightsLen) {
																												clearChildren();
																												this->lightsLen =
																													lightsLen;
																												float r =
																													(vertical ?
																														 box.size
																															 .y :
																														 box.size
																															 .x) -
																													margin;
																												for (
																													int i =
																														0;
																													i <
																													lightsLen;
																													i++)
																												{
																													float p =
																														float(
																															i) /
																														lightsLen;
																													app::ModuleLightWidget
																														*light =
																															new RectangleLight<
																																TLightBase>;
																													if (vertical)
																													{
																														light
																															->box
																															.pos
																															.y =
																															p * r +
																															margin;
																														light
																															->box
																															.size
																															.y =
																															r / lightsLen -
																															margin;
																														light
																															->box
																															.size
																															.x =
																															box.size
																																.x;
																													} else
																													{
																														light
																															->box
																															.pos
																															.x =
																															p * r +
																															margin;
																														light
																															->box
																															.size
																															.x =
																															r / lightsLen -
																															margin;
																														light
																															->box
																															.size
																															.y =
																															box.size
																																.y;
																													}
																													light
																														->module =
																														module;
																													light
																														->firstLightId =
																														firstLightId;
																													firstLightId +=
																														light
																															->baseColors
																															.size();
																													addChild(
																														light);
																												}
																											}
																										};

																										struct
																											AudioButton_ADAT :
																											app::
																												AudioButton {
																											AudioButton_ADAT() {
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/A"
																													"DA"
																													"T."
																													"sv"
																													"g")));
																												shadow
																													->opacity =
																													0.0;
																											}
																										};

																										struct
																											AudioButton_USB_B :
																											app::
																												AudioButton {
																											AudioButton_USB_B() {
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/U"
																													"SB"
																													"_B"
																													".s"
																													"v"
																													"g")));
																												shadow
																													->opacity =
																													0.0;
																											}
																										};

																										struct
																											MidiButton_MIDI_DIN :
																											app::
																												MidiButton {
																											MidiButton_MIDI_DIN() {
																												addFrame(Svg::load(asset::system(
																													"re"
																													"s/"
																													"Co"
																													"mp"
																													"on"
																													"en"
																													"tL"
																													"ib"
																													"ra"
																													"ry"
																													"/M"
																													"ID"
																													"I_"
																													"DI"
																													"N."
																													"sv"
																													"g")));
																												shadow
																													->opacity =
																													0.0;
																											}
																										};
