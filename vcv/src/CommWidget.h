#pragma once
#include "CommModule.h"
#include <rack.hpp>
using namespace rack;

// TODO: CommModuleWidget will go away, in favor of ModuleInfo technique (used by EnOsc)
class CommModuleWidget : public app::ModuleWidget {
protected:
	const float kKnobSpacingY = 17;
	const float kKnobSpacingX = 18;
	const float kTextOffset = 5;
	const float kTopMargin = 13;
	const float kBottomMargin = 15;
	const float kGridSpacingX = 30;
	const float kModuleHeight = 128.5f;

	void addLabeledKnob(const std::string labelText, int knobID, Vec posGrid, float defaultValue = 0.f);
	void addSmallLabeledKnob(const std::string labelText, int knobID, Vec posGrid, float defaultValue = 0.f);
	void addLabeledInput(const std::string labelText, int inputID, Vec posGrid);
	void addLabeledOutput(const std::string labelText, int outputID, Vec posGrid);

	void addLabeledKnobMM(const std::string labelText, int knobID, Vec posMM, float defaultValue = 0.f);
	void addSmallLabeledKnobMM(const std::string labelText, int knobID, Vec posMM, float defaultValue = 0.f);
	void addLabeledInputMM(const std::string labelText, int inputID, Vec posMM);
	void addLabeledOutputMM(const std::string labelText, int outputID, Vec posMM);

	void addLabeledKnobPx(const std::string labelText, int knobID, Vec posPx, float defaultValue = 0.f);
	void addSmallLabeledKnobPx(const std::string labelText, int knobID, Vec posPx, float defaultValue = 0.f);
	void addLabeledInputPx(const std::string labelText, int inputID, Vec posPx);
	void addLabeledOutputPx(const std::string labelText, int outputID, Vec posPx);

	void addLabeledToggle(const std::string labelText, int lightID, int paramID, Vec posGrid);
	void addLabeledToggleMM(const std::string labelText, const int lightID, const int paramID, const Vec position);
	void addLabeledMomentary(const std::string labelText, const int lightID, const int paramID, const Vec position);
	void addLabeledMomentaryMM(const std::string labelText, int lightID, int paramID, Vec posMM);

	void addModuleTitle(const std::string moduleTitle);

private:
	constexpr float gridToYFromTop(const float y);
	constexpr float gridToYFromBottom(const float y);
	constexpr float gridToXCentered(const float x);
	Vec gridFromTop2mm(Vec posGrid);
	Vec gridFromBottom2mm(Vec posGrid);
	Vec gridFromTop2px(Vec posGrid);
	Vec gridFromBottom2px(Vec posGrid);

	void addLabel(const std::string labelText, const Vec pos, const LabelButtonID id);
};

class MetaModuleTextBox : public LedDisplayTextField {
	virtual void draw(const DrawArgs &args) override;
};

struct Davies1900hBlackKnob4ms : Davies1900hKnob {
	Davies1900hBlackKnob4ms()
	{
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Davies1900hBlack_4ms.svg")));
	}
};

struct Davies1900hBlackKnobUnlined4ms : Davies1900hKnob {
	Davies1900hBlackKnobUnlined4ms()
	{
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Davies1900hBlackUnlined_4ms.svg")));
	}
};

struct DaviesLarge4ms : Davies1900hKnob {
	DaviesLarge4ms()
	{
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/DaviesLarge_4ms.svg")));
	}
};

struct Small9mmKnob : RoundKnob {
	Small9mmKnob()
	{
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/9mmKnob.svg")));
	}
};

struct Small9mmUnlinedKnob : RoundKnob {
	Small9mmUnlinedKnob()
	{
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/9mmUnlinedKnob.svg")));
	}
};

struct SubMiniToggle3pos : rack::app::SvgSwitch {
	SubMiniToggle3pos()
	{
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SubMiniToggle_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SubMiniToggle_1.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SubMiniToggle_2.svg")));
	}
};

struct SubMiniToggleHoriz3pos : rack::app::SvgSwitch {
	SubMiniToggleHoriz3pos()
	{
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SubMiniToggleH_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SubMiniToggleH_1.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SubMiniToggleH_2.svg")));
	}
};

struct SubMiniToggle2pos : rack::app::SvgSwitch {
	SubMiniToggle2pos()
	{
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SubMiniToggle_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SubMiniToggle_2.svg")));
	}
};

struct SubMiniToggleHoriz2pos : rack::app::SvgSwitch {
	SubMiniToggleHoriz2pos()
	{
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SubMiniToggleH_0.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SubMiniToggleH_2.svg")));
	}
};
