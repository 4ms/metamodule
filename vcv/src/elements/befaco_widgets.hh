#pragma once
#include "rack.hpp"

namespace Befaco
{
extern rack::Plugin *pluginInstance;
using namespace rack;

struct Knurlie : SvgScrew {
	Knurlie() { setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/Knurlie.svg"))); }
};

struct BefacoTinyKnobWhite : BefacoTinyKnob {
	BefacoTinyKnobWhite() {}
};

struct BefacoTinyKnobRed : BefacoTinyKnob {
	BefacoTinyKnobRed()
	{
		setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoTinyPointWhite.svg")));
		bg->setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoTinyKnobRed_bg.svg")));
	}
};

struct BefacoTinyKnobDarkGrey : BefacoTinyKnob {
	BefacoTinyKnobDarkGrey()
	{
		setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoTinyPointWhite.svg")));
		bg->setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoTinyKnobDarkGrey_bg.svg")));
	}
};

struct BefacoTinyKnobLightGrey : BefacoTinyKnob {
	BefacoTinyKnobLightGrey()
	{
		bg->setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoTinyKnobLightGrey_bg.svg")));
	}
};

struct BefacoTinyKnobBlack : BefacoTinyKnob {
	BefacoTinyKnobBlack()
	{
		setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoTinyPointWhite.svg")));
		bg->setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoTinyKnobBlack_bg.svg")));
	}
};

struct Davies1900hLargeGreyKnob : Davies1900hKnob {
	Davies1900hLargeGreyKnob()
	{
		setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/Davies1900hLargeGrey.svg")));
		bg->setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/Davies1900hLargeGrey_bg.svg")));
	}
};

struct Davies1900hLightGreyKnob : Davies1900hKnob {
	Davies1900hLightGreyKnob()
	{
		setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/Davies1900hLightGrey.svg")));
		bg->setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/Davies1900hLightGrey_bg.svg")));
	}
};

struct Davies1900hDarkGreyKnob : Davies1900hKnob {
	Davies1900hDarkGreyKnob()
	{
		setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/Davies1900hDarkGrey.svg")));
		bg->setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/Davies1900hDarkGrey_bg.svg")));
	}
};

/** Deprecated alias */
using Davies1900hDarkBlackAlt = Davies1900hBlackKnob;

struct BananutRed : app::SvgPort {
	BananutRed() { setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BananutRed.svg"))); }
};
/** Deprecated alias */
using BefacoOutputPort = BananutRed;

struct BananutBlack : app::SvgPort {
	BananutBlack() { setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BananutBlack.svg"))); }
};
/** Deprecated alias */
using BefacoInputPort = BananutBlack;

struct CKSSNarrow : app::SvgSwitch {
	CKSSNarrow()
	{
		addFrame(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/SwitchNarrow_0.svg")));
		addFrame(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/SwitchNarrow_2.svg")));
	}
};

struct Crossfader : app::SvgSlider {
	Crossfader()
	{
		setBackgroundSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/CrossfaderBackground.svg")));
		setHandleSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/CrossfaderHandle.svg")));
		minHandlePos = mm2px(Vec(4.5f, -0.8f));
		maxHandlePos = mm2px(Vec(34.5, -0.8f));
		horizontal = true;
		math::Vec margin = math::Vec(15, 5);
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
	}
};

struct BefacoSwitchHorizontal : app::SvgSwitch {
	BefacoSwitchHorizontal()
	{
		addFrame(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoSwitchHoriz_0.svg")));
		addFrame(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoSwitchHoriz_1.svg")));
		addFrame(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoSwitchHoriz_2.svg")));
	}
};

struct CKSSHoriz2 : app::SvgSwitch {
	CKSSHoriz2()
	{
		addFrame(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/SwitchNarrowHoriz_0.svg")));
		addFrame(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/SwitchNarrowHoriz_1.svg")));
	}
};

struct CKSSVert7 : app::SvgSlider {
	CKSSVert7()
	{
		math::Vec margin = math::Vec(3.5, 3.5);
		maxHandlePos = math::Vec(1, 1).plus(margin);
		minHandlePos = math::Vec(1, 45).plus(margin);
		setBackgroundSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/SwitchTallVert_bg.svg")));
		setHandleSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/SwitchTallVert_fg.svg")));
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
	}

	// disable double click as this messes with click to advance
	void onDoubleClick(const event::DoubleClick &e) override {}

	// cycle through the values (with reset) on click only (not drag)
	void onAction(const ActionEvent &e) override
	{
		ParamQuantity *paramQuantity = getParamQuantity();
		float range = paramQuantity->maxValue - paramQuantity->minValue;
		float newValue = paramQuantity->getValue() + 1.f;
		if (newValue > paramQuantity->maxValue) {
			newValue -= range + 1.f;
		}
		paramQuantity->setValue(newValue);
	}
};

struct CKSSHoriz4 : app::SvgSlider {
	CKSSHoriz4()
	{
		setBackgroundSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/SwitchWideHoriz_bg.svg")));
		setHandleSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/SwitchWideHoriz_fg.svg")));
		minHandlePos = mm2px(Vec(0.3f, 0.3f));
		maxHandlePos = mm2px(Vec(6.3f, 0.3f));
		horizontal = true;
		math::Vec margin = math::Vec(0, 0);
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
	}

	// disable double click as this messes with click to advance
	void onDoubleClick(const event::DoubleClick &e) override {}

	// cycle through the values (with reset) on click only (not drag)
	void onAction(const ActionEvent &e) override
	{
		ParamQuantity *paramQuantity = getParamQuantity();
		float range = paramQuantity->maxValue - paramQuantity->minValue;
		float newValue = paramQuantity->getValue() + 1.f;
		if (newValue > paramQuantity->maxValue) {
			newValue -= range + 1.f;
		}
		paramQuantity->setValue(newValue);
	}
};

struct CKSSNarrow3 : app::SvgSwitch {
	CKSSNarrow3()
	{
		addFrame(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/SwitchNarrow_0.svg")));
		addFrame(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/SwitchNarrow_1.svg")));
		addFrame(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/SwitchNarrow_2.svg")));
	}
};

struct Davies1900hLargeLightGreyKnob : Davies1900hKnob {
	Davies1900hLargeLightGreyKnob()
	{
		setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/Davies1900hLargeLightGrey.svg")));
		bg->setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/Davies1900hLargeLightGrey_bg.svg")));
	}
};

struct BefacoSlidePotSmall : app::SvgSlider {
	BefacoSlidePotSmall()
	{
		math::Vec margin = math::Vec(3.5, 3.5);
		maxHandlePos = math::Vec(-2, -2).plus(margin);
		minHandlePos = math::Vec(-2, 60).plus(margin);
		setBackgroundSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoSlidePotSmall.svg")));
		setHandleSvg(Svg::load(asset::plugin(pluginInstance, "res/components/befaco/BefacoSlidePotHandleSmall.svg")));
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
	}
};

} // namespace Befaco
