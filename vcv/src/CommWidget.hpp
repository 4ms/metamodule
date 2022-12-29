#pragma once
#include "CommModule.hpp"
#include "MappableKnob.hpp"
#include <rack.hpp>
using namespace rack;

class CommModuleWidget : public app::ModuleWidget {
protected:
	static constexpr float kKnobSpacingY = 17;
	static constexpr float kKnobSpacingX = 18;
	static constexpr float kTextOffset = 5;
};

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
