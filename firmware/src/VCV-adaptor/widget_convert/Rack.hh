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

//using SvgLight = TSvgLight<>;
// using GrayModuleLightWidget = TGrayModuleLightWidget<>;
// using WhiteLight = TWhiteLight<>;
// using RedLight = TRedLight<>;
// using GreenLight = TGreenLight<>;
// using BlueLight = TBlueLight<>;
// using YellowLight = TYellowLight<>;
// using GreenRedLight = TGreenRedLight<>;
// using RedGreenBlueLight = TRedGreenBlueLight<>;

// template <typename TBase>
// struct LargeLight : TSvgLight<TBase> {

// template <typename TBase>
// struct MediumLight : TSvgLight<TBase> {

// template <typename TBase>
// struct SmallLight : TSvgLight<TBase> {

// template <typename TBase>
// struct TinyLight : TSvgLight<TBase> {
// 	TinyLight() {

// template <typename TBase = GrayModuleLightWidget>
// struct LargeSimpleLight : TBase {

// template <typename TBase = GrayModuleLightWidget>
// struct MediumSimpleLight : TBase {

// template <typename TBase = GrayModuleLightWidget>
// struct SmallSimpleLight : TBase {

// template <typename TBase = GrayModuleLightWidget>
// struct TinySimpleLight : TBase {

// template <typename TBase>
// struct RectangleLight : TBase {

// template <typename TBase>
// struct VCVBezelLight : TBase {

// template <typename TBase>
// using LEDBezelLight = VCVBezelLight<TBase>;

// template <typename TBase>
// struct PB61303Light : TBase {

////////////////////
// Knobs
////////////////////

// struct RoundBlackKnob : RoundKnob {

// struct RoundSmallBlackKnob : RoundKnob {

// struct RoundLargeBlackKnob : RoundKnob {

// struct RoundBigBlackKnob : RoundKnob {

// struct RoundHugeBlackKnob : RoundKnob {

// struct RoundBlackSnapKnob : RoundBlackKnob {

// struct Davies1900hWhiteKnob : Davies1900hKnob {
// struct Davies1900hBlackKnob : Davies1900hKnob {
// struct Davies1900hRedKnob : Davies1900hKnob {
// struct Davies1900hLargeWhiteKnob : Davies1900hKnob {
// struct Davies1900hLargeBlackKnob : Davies1900hKnob {
// struct Davies1900hLargeRedKnob : Davies1900hKnob {

// struct Rogan6PSWhite : Rogan {
// struct Rogan5PSGray : Rogan {
// struct Rogan3PSBlue : Rogan {
// struct Rogan3PSRed : Rogan {
// struct Rogan3PSGreen : Rogan {
// struct Rogan3PSWhite : Rogan {
// struct Rogan3PBlue : Rogan {
// struct Rogan3PRed : Rogan {
// struct Rogan3PGreen : Rogan {
// struct Rogan3PWhite : Rogan {

// struct Rogan2SGray : Rogan {

// struct Rogan2PSBlue : Rogan {

// struct Rogan2PSRed : Rogan {

// struct Rogan2PSGreen : Rogan {

//struct Rogan2PSWhite : Rogan {
//	Rogan2PSWhite() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2PSWhite.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2PS_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2PSWhite_fg.svg")));
//	}
//};

//struct Rogan2PBlue : Rogan {
//	Rogan2PBlue() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2PBlue.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2P_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2PBlue_fg.svg")));
//	}
//};

//struct Rogan2PRed : Rogan {
//	Rogan2PRed() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2PRed.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2P_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2PRed_fg.svg")));
//	}
//};

//struct Rogan2PGreen : Rogan {
//	Rogan2PGreen() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2PGreen.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2P_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2PGreen_fg.svg")));
//	}
//};

//struct Rogan2PWhite : Rogan {
//	Rogan2PWhite() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2PWhite.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2P_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan2PWhite_fg.svg")));
//	}
//};

//struct Rogan1PSBlue : Rogan {
//	Rogan1PSBlue() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PSBlue.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PS_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PSBlue_fg.svg")));
//	}
//};

//struct Rogan1PSRed : Rogan {
//	Rogan1PSRed() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PSRed.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PS_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PSRed_fg.svg")));
//	}
//};

//struct Rogan1PSGreen : Rogan {
//	Rogan1PSGreen() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PSGreen.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PS_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PSGreen_fg.svg")));
//	}
//};

//struct Rogan1PSWhite : Rogan {
//	Rogan1PSWhite() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PSWhite.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PS_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PSWhite_fg.svg")));
//	}
//};

//struct Rogan1PBlue : Rogan {
//	Rogan1PBlue() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PBlue.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1P_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PBlue_fg.svg")));
//	}
//};

//struct Rogan1PRed : Rogan {
//	Rogan1PRed() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PRed.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1P_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PRed_fg.svg")));
//	}
//};

//struct Rogan1PGreen : Rogan {
//	Rogan1PGreen() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PGreen.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1P_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PGreen_fg.svg")));
//	}
//};

//struct Rogan1PWhite : Rogan {
//	Rogan1PWhite() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PWhite.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1P_bg.svg")));
//		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan1PWhite_fg.svg")));
//	}
//};

//struct SynthTechAlco : app::SvgKnob {
//	widget::SvgWidget *bg;

//	SynthTechAlco() {
//		minAngle = -0.82 * M_PI;
//		maxAngle = 0.82 * M_PI;

//		bg = new widget::SvgWidget;
//		fb->addChildBelow(bg, tw);

//		setSvg(Svg::load(asset::system("res/ComponentLibrary/SynthTechAlco.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/SynthTechAlco_bg.svg")));
//	}
//};

//struct Trimpot : app::SvgKnob {
//	widget::SvgWidget *bg;

//	Trimpot() {
//		minAngle = -0.75 * M_PI;
//		maxAngle = 0.75 * M_PI;

//		bg = new widget::SvgWidget;
//		fb->addChildBelow(bg, tw);

//		setSvg(Svg::load(asset::system("res/ComponentLibrary/Trimpot.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Trimpot_bg.svg")));
//	}
//};

//struct BefacoBigKnob : app::SvgKnob {
//	widget::SvgWidget *bg;

//	BefacoBigKnob() {
//		minAngle = -0.75 * M_PI;
//		maxAngle = 0.75 * M_PI;
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/BefacoBigKnob.svg")));

//		bg = new widget::SvgWidget;
//		fb->addChildBelow(bg, tw);
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/BefacoBigKnob_bg.svg")));
//	}
//};

//struct BefacoTinyKnob : app::SvgKnob {
//	widget::SvgWidget *bg;

//	BefacoTinyKnob() {
//		minAngle = -0.8 * M_PI;
//		maxAngle = 0.8 * M_PI;

//		bg = new widget::SvgWidget;
//		fb->addChildBelow(bg, tw);

//		setSvg(Svg::load(asset::system("res/ComponentLibrary/BefacoTinyPointBlack.svg")));
//		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/BefacoTinyKnobWhite_bg.svg")));
//	}
//};

//struct BefacoSlidePot : app::SvgSlider {
//	BefacoSlidePot() {
//		math::Vec margin = math::Vec(3.5, 3.5);
//		maxHandlePos = math::Vec(-1, -2).plus(margin);
//		minHandlePos = math::Vec(-1, 87).plus(margin);
//		setBackgroundSvg(Svg::load(asset::system("res/ComponentLibrary/BefacoSlidePot.svg")));
//		setHandleSvg(Svg::load(asset::system("res/ComponentLibrary/BefacoSlidePotHandle.svg")));
//		background->box.pos = margin;
//		box.size = background->box.size.plus(margin.mult(2));
//	}
//};

//struct VCVSlider : app::SvgSlider {
//	VCVSlider() {
//		setBackgroundSvg(Svg::load(asset::system("res/ComponentLibrary/VCVSlider.svg")));
//		setHandleSvg(Svg::load(asset::system("res/ComponentLibrary/VCVSliderHandle.svg")));
//		setHandlePosCentered(math::Vec(19.84260 / 2, 76.53517 - 11.74218 / 2),
//							 math::Vec(19.84260 / 2, 0.0 + 11.74218 / 2));
//	}
//};
//using LEDSlider = VCVSlider;

//struct VCVSliderHorizontal : app::SvgSlider {
//	VCVSliderHorizontal() {
//		horizontal = true;
//		// TODO Fix positions
//		maxHandlePos = mm2px(math::Vec(22.078, 0.738).plus(math::Vec(0, 2)));
//		minHandlePos = mm2px(math::Vec(0.738, 0.738).plus(math::Vec(0, 2)));
//		// TODO Fix SVG
//		setBackgroundSvg(Svg::load(asset::system("res/ComponentLibrary/VCVSliderHorizontal.svg")));
//	}
//};
//using LEDSliderHorizontal = VCVSliderHorizontal;

///** An SvgSlider with an attached light.
//Construct with createLightParamCentered() helper function.
//*/
//template<typename TBase, typename TLightBase = RedLight>
//struct LightSlider : TBase {
//	app::ModuleLightWidget *light;

//	LightSlider() {
//		light = new TLightBase;
//		this->addChild(light);
//	}

//	app::ModuleLightWidget *getLight() {
//		return light;
//	}

//	void step() override {
//		TBase::step();
//		// Move center of light to center of handle
//		light->box.pos = this->handle->box.pos.plus(this->handle->box.size.div(2)).minus(light->box.size.div(2));
//	}
//};

//template<typename TBase>
//struct VCVSliderLight : RectangleLight<TSvgLight<TBase>> {
//	VCVSliderLight() {
//		this->setSvg(Svg::load(asset::system("res/ComponentLibrary/VCVSliderLight.svg")));
//	}
//};
//template<typename TBase>
//using LEDSliderLight = VCVSliderLight<TBase>;

//template<typename TLightBase = RedLight>
//struct VCVLightSlider : LightSlider<VCVSlider, VCVSliderLight<TLightBase>> {
//	VCVLightSlider() {
//	}
//};
//template<typename TLightBase = RedLight>
//using LEDLightSlider = VCVLightSlider<TLightBase>;

///** Deprecated. Use VCVSliderLight with your preferred LightWidget. */
//struct LEDSliderGreen : VCVLightSlider<GreenLight> {};
//struct LEDSliderRed : VCVLightSlider<RedLight> {};
//struct LEDSliderYellow : VCVLightSlider<YellowLight> {};
//struct LEDSliderBlue : VCVLightSlider<BlueLight> {};
//struct LEDSliderWhite : VCVLightSlider<WhiteLight> {};

//template<typename TLightBase = RedLight>
//struct VCVLightSliderHorizontal : LightSlider<VCVSliderHorizontal, TLightBase> {
//	VCVLightSliderHorizontal() {
//		// TODO Fix positions
//		this->light->box.size = mm2px(math::Vec(3.276, 1.524));
//		// TODO Fix SVG
//		this->setHandleSvg(Svg::load(asset::system("res/ComponentLibrary/VCVSliderHorizontalHandle.svg")));
//	}
//};
//template<typename TLightBase = RedLight>
//using LEDLightSliderHorizontal = VCVLightSliderHorizontal<TLightBase>;

//////////////////////
//// Ports
//////////////////////

//struct PJ301MPort : app::SvgPort {
//	PJ301MPort() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/PJ301M.svg")));
//	}
//};

//struct PJ3410Port : app::SvgPort {
//	PJ3410Port() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/PJ3410.svg")));
//	}
//};

//struct CL1362Port : app::SvgPort {
//	CL1362Port() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/CL1362.svg")));
//	}
//};

//////////////////////
//// Switches
//////////////////////

//template<typename TSwitch>
//struct MomentarySwitch : TSwitch {
//	MomentarySwitch() {
//		this->momentary = true;
//	}
//};

//struct NKK : app::SvgSwitch {
//	NKK() {
//		shadow->opacity = 0.0;
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/NKK_0.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/NKK_1.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/NKK_2.svg")));
//	}
//};

//struct CKSS : app::SvgSwitch {
//	CKSS() {
//		shadow->opacity = 0.0;
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKSS_0.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKSS_1.svg")));
//	}
//};

//struct CKSSThree : app::SvgSwitch {
//	CKSSThree() {
//		shadow->opacity = 0.0;
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKSSThree_0.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKSSThree_1.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKSSThree_2.svg")));
//	}
//};

//struct CKSSThreeHorizontal : app::SvgSwitch {
//	CKSSThreeHorizontal() {
//		shadow->opacity = 0.0;
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKSSThreeHorizontal_0.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKSSThreeHorizontal_1.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKSSThreeHorizontal_2.svg")));
//	}
//};

//struct CKD6 : app::SvgSwitch {
//	CKD6() {
//		momentary = true;
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKD6_0.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/CKD6_1.svg")));
//	}
//};

//struct TL1105 : app::SvgSwitch {
//	TL1105() {
//		momentary = true;
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/TL1105_0.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/TL1105_1.svg")));
//	}
//};

//struct VCVButton : app::SvgSwitch {
//	VCVButton() {
//		momentary = true;
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/VCVButton_0.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/VCVButton_1.svg")));
//	}
//};
//using LEDButton = VCVButton;

//struct VCVLatch : VCVButton {
//	VCVLatch() {
//		momentary = false;
//		latch = true;
//	}
//};

///** Looks best with MediumSimpleLight<WhiteLight> or a color of your choice.
//*/
//template<typename TLight>
//struct VCVLightButton : VCVButton {
//	app::ModuleLightWidget *light;

//	VCVLightButton() {
//		light = new TLight;
//		// Move center of light to center of box
//		light->box.pos = box.size.div(2).minus(light->box.size.div(2));
//		addChild(light);
//	}

//	app::ModuleLightWidget *getLight() {
//		return light;
//	}
//};
//template<typename TLight>
//using LEDLightButton = VCVLightButton<TLight>;

//template<typename TLight>
//struct VCVLightLatch : VCVLightButton<TLight> {
//	VCVLightLatch() {
//		this->momentary = false;
//		this->latch = true;
//	}
//};

//struct BefacoSwitch : app::SvgSwitch {
//	BefacoSwitch() {
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/BefacoSwitch_0.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/BefacoSwitch_1.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/BefacoSwitch_2.svg")));
//	}
//};

//struct BefacoPush : app::SvgSwitch {
//	BefacoPush() {
//		momentary = true;
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/BefacoPush_0.svg")));
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/BefacoPush_1.svg")));
//	}
//};

//struct VCVBezel : app::SvgSwitch {
//	VCVBezel() {
//		momentary = true;
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/VCVBezel.svg")));
//	}
//};
//using LEDBezel = VCVBezel;

//struct VCVBezelLatch : VCVBezel {
//	VCVBezelLatch() {
//		momentary = false;
//		latch = true;
//	}
//};

//template<typename TLightBase = WhiteLight>
//struct VCVLightBezel : VCVBezel {
//	app::ModuleLightWidget *light;

//	VCVLightBezel() {
//		light = new VCVBezelLight<TLightBase>;
//		// Move center of light to center of box
//		light->box.pos = box.size.div(2).minus(light->box.size.div(2));
//		addChild(light);
//	}

//	app::ModuleLightWidget *getLight() {
//		return light;
//	}
//};
//template<typename TLightBase = WhiteLight>
//using LEDLightBezel = VCVLightBezel<TLightBase>;

//template<typename TLightBase = WhiteLight>
//struct VCVLightBezelLatch : VCVLightBezel<TLightBase> {
//	VCVLightBezelLatch() {
//		this->momentary = false;
//		this->latch = true;
//	}
//};

//struct PB61303 : app::SvgSwitch {
//	PB61303() {
//		momentary = true;
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/PB61303.svg")));
//	}
//};

//////////////////////
//// Misc
//////////////////////

//struct ScrewSilver : app::SvgScrew {
//	ScrewSilver() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/ScrewSilver.svg")));
//	}
//};

//struct ScrewBlack : app::SvgScrew {
//	ScrewBlack() {
//		setSvg(Svg::load(asset::system("res/ComponentLibrary/ScrewBlack.svg")));
//	}
//};

//struct SegmentDisplay : widget::Widget {
//	int lightsLen = 0;
//	bool vertical = false;
//	float margin = mm2px(0.5);

//	void draw(const DrawArgs &args) override {
//		// Background
//		nvgBeginPath(args.vg);
//		nvgRect(args.vg, 0, 0, box.size.x, box.size.y);
//		nvgFillColor(args.vg, color::BLACK);
//		nvgFill(args.vg);
//		Widget::draw(args);
//	}

//	template<typename TLightBase = WhiteLight>
//	void setLights(engine::Module *module, int firstLightId, int lightsLen) {
//		clearChildren();
//		this->lightsLen = lightsLen;
//		float r = (vertical ? box.size.y : box.size.x) - margin;
//		for (int i = 0; i < lightsLen; i++) {
//			float p = float(i) / lightsLen;
//			app::ModuleLightWidget *light = new RectangleLight<TLightBase>;
//			if (vertical) {
//				light->box.pos.y = p * r + margin;
//				light->box.size.y = r / lightsLen - margin;
//				light->box.size.x = box.size.x;
//			} else {
//				light->box.pos.x = p * r + margin;
//				light->box.size.x = r / lightsLen - margin;
//				light->box.size.y = box.size.y;
//			}
//			light->module = module;
//			light->firstLightId = firstLightId;
//			firstLightId += light->baseColors.size();
//			addChild(light);
//		}
//	}
//};

//struct AudioButton_ADAT : app::AudioButton {
//	AudioButton_ADAT() {
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/ADAT.svg")));
//		shadow->opacity = 0.0;
//	}
//};

//struct AudioButton_USB_B : app::AudioButton {
//	AudioButton_USB_B() {
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/USB_B.svg")));
//		shadow->opacity = 0.0;
//	}
//};

//struct MidiButton_MIDI_DIN : app::MidiButton {
//	MidiButton_MIDI_DIN() {
//		addFrame(Svg::load(asset::system("res/ComponentLibrary/MIDI_DIN.svg")));
//		shadow->opacity = 0.0;
//	}
//};

} // namespace rack
