#pragma once

#include "mapping/mappable_knob.hh"
#include "plugin.hh"

class MetaModuleTextBox : public LedDisplayTextField {
	void draw(const DrawArgs &args) override { LedDisplayTextField::draw(args); }
};

struct Davies1900hBlackKnob4ms : MappableKnob<Davies1900hKnob> {
	Davies1900hBlackKnob4ms()
	{
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/Davies1900hBlack.svg")));
	}
};

struct Davies1900hBlackKnobUnlined4ms : MappableKnob<Davies1900hKnob> {
	Davies1900hBlackKnobUnlined4ms()
	{
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/Davies1900hBlack_no_pip.svg")));
	}
};

struct DaviesLarge4ms : MappableKnob<Davies1900hKnob> {
	DaviesLarge4ms() { setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/Davies_large.svg"))); }
};

struct Small9mmKnob : MappableKnob<RoundKnob> {
	Small9mmKnob() { setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/9mm_knob.svg"))); }
};

struct Small9mmUnlinedKnob : MappableKnob<RoundKnob> {
	Small9mmUnlinedKnob()
	{
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/9mm_knob_no_pip.svg")));
	}
};

struct SubMiniToggle3pos : rack::app::SvgSwitch {
	SubMiniToggle3pos()
	{
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggle_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggle_1.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggle_2.svg")));
	}
};

struct SubMiniToggleHoriz3pos : rack::app::SvgSwitch {
	SubMiniToggleHoriz3pos()
	{
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggleH_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggleH_1.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggleH_2.svg")));
	}
};

struct SubMiniToggle2pos : rack::app::SvgSwitch {
	SubMiniToggle2pos()
	{
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggle_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggle_2.svg")));
	}
};

struct SubMiniToggleHoriz2pos : rack::app::SvgSwitch {
	SubMiniToggleHoriz2pos()
	{
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggleH_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/components/SubMiniToggleH_2.svg")));
	}
};

template<typename TSwitch>
struct LatchingSwitch : TSwitch {
	LatchingSwitch() { this->momentary = false; }
};

template<typename TBase>
struct FourmsSliderLight : RectangleLight<TSvgLight<TBase>> {
	FourmsSliderLight()
	{
		this->setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/FourmsSliderLight.svg")));
	}
};

struct FourmsSlider : app::SvgSlider {
	FourmsSlider()
	{
		setBackgroundSvg(Svg::load(asset::plugin(pluginInstance, "res/components/FourmsSlider.svg")));
		setHandleSvg(Svg::load(asset::plugin(pluginInstance, "res/components/FourmsSliderHandle.svg")));
		setHandlePosCentered(math::Vec(19.84260 / 2, 76.53517 - 11.74218 / 2),
							 math::Vec(19.84260 / 2, 0.0 + 11.74218 / 2));
		// maxHandlePos = mm2px(math::Vec(22.078, 0.738));
		// minHandlePos = mm2px(math::Vec(0.738, 0.738));
	}
};

template<typename TLightBase = RedLight>
struct FourmsLightSlider : LightSlider<FourmsSlider, FourmsSliderLight<TLightBase>> {
	FourmsLightSlider() = default;
};

template<typename TBase>
struct FourmsSliderHorizontalLight : RectangleLight<TSvgLight<TBase>> {
	FourmsSliderHorizontalLight()
	{
		this->setSvg(Svg::load(asset::plugin(pluginInstance, "res/components/FourmsSliderLightHorizontal.svg")));
	}
};

struct FourmsSliderHorizontal : app::SvgSlider {
	FourmsSliderHorizontal()
	{
		horizontal = true;
		maxHandlePos = mm2px(math::Vec(22.078, 0.738));
		minHandlePos = mm2px(math::Vec(0.738, 0.738));
		setBackgroundSvg(Svg::load(asset::plugin(pluginInstance, "res/components/FourmsSliderHorizontal.svg")));
	}
};
template<typename TLightBase = RedLight>
struct FourmsLightSliderHorizontal : LightSlider<FourmsSliderHorizontal, FourmsSliderHorizontalLight<TLightBase>> {
	FourmsLightSliderHorizontal()
	{
		// TODO Fix positions
		this->light->box.size = mm2px(math::Vec(3.276, 1.524));
		// TODO Fix SVG
		this->setHandleSvg(Svg::load(asset::plugin(pluginInstance, "res/components/FourmsSliderHorizontalHandle.svg")));
	}
};
