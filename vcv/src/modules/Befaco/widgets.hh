#pragma once
#include <rack.hpp>

extern rack::Plugin *pluginInstance;

struct Knurlie : rack::SvgScrew {
	Knurlie() {
		setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/Knurlie.svg")));
	}
};

struct BefacoTinyKnobWhite : rack::BefacoTinyKnob {
	BefacoTinyKnobWhite() {
	}
};

struct BefacoTinyKnobRed : rack::BefacoTinyKnob {
	BefacoTinyKnobRed() {
		setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoTinyPointWhite.svg")));
		bg->setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoTinyKnobRed_bg.svg")));
	}
};

struct BefacoTinyKnobDarkGrey : rack::BefacoTinyKnob {
	BefacoTinyKnobDarkGrey() {
		setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoTinyPointWhite.svg")));
		bg->setSvg(
			rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoTinyKnobDarkGrey_bg.svg")));
	}
};

struct BefacoTinyKnobLightGrey : rack::BefacoTinyKnob {
	BefacoTinyKnobLightGrey() {
		bg->setSvg(
			rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoTinyKnobLightGrey_bg.svg")));
	}
};

struct BefacoTinyKnobBlack : rack::BefacoTinyKnob {
	BefacoTinyKnobBlack() {
		setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoTinyPointWhite.svg")));
		bg->setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoTinyKnobBlack_bg.svg")));
	}
};

struct Davies1900hLargeGreyKnob : rack::Davies1900hKnob {
	Davies1900hLargeGreyKnob() {
		setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/Davies1900hLargeGrey.svg")));
		bg->setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/Davies1900hLargeGrey_bg.svg")));
	}
};

struct Davies1900hLightGreyKnob : rack::Davies1900hKnob {
	Davies1900hLightGreyKnob() {
		setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/Davies1900hLightGrey.svg")));
		bg->setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/Davies1900hLightGrey_bg.svg")));
	}
};

struct Davies1900hDarkGreyKnob : rack::Davies1900hKnob {
	Davies1900hDarkGreyKnob() {
		setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/Davies1900hDarkGrey.svg")));
		bg->setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/Davies1900hDarkGrey_bg.svg")));
	}
};

/** Deprecated alias */
using Davies1900hDarkBlackAlt = rack::Davies1900hBlackKnob;

struct BananutRed : rack::app::SvgPort {
	BananutRed() {
		setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BananutRed.svg")));
	}
};
/** Deprecated alias */
using BefacoOutputPort = BananutRed;

struct BananutBlack : rack::app::SvgPort {
	BananutBlack() {
		setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BananutBlack.svg")));
	}
};
/** Deprecated alias */
using BefacoInputPort = BananutBlack;

struct CKSSNarrow : rack::app::SvgSwitch {
	CKSSNarrow() {
		addFrame(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/SwitchNarrow_0.svg")));
		addFrame(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/SwitchNarrow_2.svg")));
	}
};

struct Crossfader : rack::app::SvgSlider {
	Crossfader() {
		setBackgroundSvg(
			rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/CrossfaderBackground.svg")));
		setHandleSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/CrossfaderHandle.svg")));
		minHandlePos = rack::mm2px(rack::Vec(4.5f, -0.8f));
		maxHandlePos = rack::mm2px(rack::Vec(34.5, -0.8f));
		horizontal = true;
		rack::Vec margin = rack::Vec(15, 5);
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
	}
};

struct BefacoSwitchHorizontal : rack::app::SvgSwitch {
	BefacoSwitchHorizontal() {
		addFrame(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoSwitchHoriz_0.svg")));
		addFrame(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoSwitchHoriz_1.svg")));
		addFrame(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoSwitchHoriz_2.svg")));
	}
};

struct CKSSHoriz2 : rack::app::SvgSwitch {
	CKSSHoriz2() {
		addFrame(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/SwitchNarrowHoriz_0.svg")));
		addFrame(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/SwitchNarrowHoriz_1.svg")));
	}
};

struct CKSSVert7 : rack::app::SvgSlider {
	CKSSVert7() {
		rack::Vec margin = rack::Vec(3.5, 3.5);
		maxHandlePos = rack::Vec(1, 1).plus(margin);
		minHandlePos = rack::Vec(1, 45).plus(margin);
		setBackgroundSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/SwitchTallVert_bg.svg")));
		setHandleSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/SwitchTallVert_fg.svg")));
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
	}

	// disable double click as this messes with click to advance
	void onDoubleClick(const rack::event::DoubleClick &e) override {
	}

	// cycle through the values (with reset) on click only (not drag)
	void onAction(const ActionEvent &e) override {
		rack::ParamQuantity *paramQuantity = getParamQuantity();
		float range = paramQuantity->maxValue - paramQuantity->minValue;
		float newValue = paramQuantity->getValue() + 1.f;
		if (newValue > paramQuantity->maxValue) {
			newValue -= range + 1.f;
		}
		paramQuantity->setValue(newValue);
	}
};

struct CKSSHoriz4 : rack::app::SvgSlider {
	CKSSHoriz4() {
		setBackgroundSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/SwitchWideHoriz_bg.svg")));
		setHandleSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/SwitchWideHoriz_fg.svg")));
		minHandlePos = rack::mm2px(rack::Vec(0.3f, 0.3f));
		maxHandlePos = rack::mm2px(rack::Vec(6.3f, 0.3f));
		horizontal = true;
		rack::Vec margin = rack::Vec(0, 0);
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
	}

	// disable double click as this messes with click to advance
	void onDoubleClick(const rack::event::DoubleClick &e) override {
	}

	// cycle through the values (with reset) on click only (not drag)
	void onAction(const ActionEvent &e) override {
		rack::ParamQuantity *paramQuantity = getParamQuantity();
		float range = paramQuantity->maxValue - paramQuantity->minValue;
		float newValue = paramQuantity->getValue() + 1.f;
		if (newValue > paramQuantity->maxValue) {
			newValue -= range + 1.f;
		}
		paramQuantity->setValue(newValue);
	}
};

struct CKSSNarrow3 : rack::app::SvgSwitch {
	CKSSNarrow3() {
		addFrame(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/SwitchNarrow_0.svg")));
		addFrame(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/SwitchNarrow_1.svg")));
		addFrame(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/SwitchNarrow_2.svg")));
	}
};

struct Davies1900hLargeLightGreyKnob : rack::Davies1900hKnob {
	Davies1900hLargeLightGreyKnob() {
		setSvg(rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/Davies1900hLargeLightGrey.svg")));
		bg->setSvg(
			rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/Davies1900hLargeLightGrey_bg.svg")));
	}
};

struct BefacoSlidePotSmall : rack::app::SvgSlider {
	BefacoSlidePotSmall() {
		rack::Vec margin = rack::Vec(3.5, 3.5);
		maxHandlePos = rack::Vec(-2, -2).plus(margin);
		minHandlePos = rack::Vec(-2, 60).plus(margin);
		setBackgroundSvg(
			rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoSlidePotSmall.svg")));
		setHandleSvg(
			rack::Svg::load(rack::asset::plugin(pluginInstance, "res/components/BefacoSlidePotHandleSmall.svg")));
		background->box.pos = margin;
		box.size = background->box.size.plus(margin.mult(2));
	}
};
