#include "CommData.h"
#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "CoreModules/panel_mini_defs.hh"
#include "hub_base.hh"
#include "hub_knob_menu.hh"
#include "knob_map.hh"
#include "localPath.h"
#include "paletteHub.hh"
#include "patch_writer.hh"
#include "plugin.hpp"
#include "string.h"
#include "util/string_util.hh"
#include <fstream>
#include <functional>

struct MetaModuleMiniHub : public MetaModuleHubBase {

	enum ParamIds { ENUMS(KNOBS, PanelDef::NumKnobs), GET_INFO, NUM_PARAMS };
	enum InputIds { AUDIO_IN_L, AUDIO_IN_R, CV_1, CV_2, CV_3, CV_4, GATE_IN_1, GATE_IN_2, CLOCK_IN, NUM_INPUTS };
	enum OutputIds { AUDIO_OUT_L, AUDIO_OUT_R, AUDIO_OUT_3, AUDIO_OUT_4, CLOCK_OUT, NUM_OUTPUTS };
	enum LightIds { WRITE_LIGHT, NUM_LIGHTS };

	MetaModuleMiniHub()
	{
		for (int i = 0; i < PanelDef::NumKnobs; i++)
			knobMaps.emplace_back(i);

		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		selfID.typeID = "PANEL_8";
	}

	~MetaModuleMiniHub() {}

	void process(const ProcessArgs &args) override
	{
		processPatchButton(params[GET_INFO].getValue());
		processKnobMaps();
		processCreatePatchFile();
	}
};

struct MetaModuleMiniHubWidget : MetaModuleHubBaseWidget {

	Label *valueLabel;
	Label *valueLabel2;
	LedDisplayTextField *patchName;
	MetaModuleMiniHub *expModule;

	MetaModuleMiniHubWidget(MetaModuleMiniHub *module)
	{
		setModule(module);
		expModule = module;

		if (expModule != nullptr) {
			expModule->updateDisplay = [&]() { this->valueLabel->text = this->expModule->labelText; };
			expModule->updatePatchName = [&]() { this->expModule->patchNameText = this->patchName->text; };
			expModule->redrawPatchName = [&]() { this->patchName->text = this->expModule->patchNameText; };
		}
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/meta-module-no-words.svg")));

		// addParam(createParamCentered<BefacoPush>(mm2px(Vec(69.7, 19.5)), module, MetaModuleHub::GET_INFO));
		addLabeledToggleMM("WRITE", MetaModuleMiniHub::WRITE_LIGHT, MetaModuleMiniHub::GET_INFO, {70, 19.5});

		valueLabel = createWidget<Label>(mm2px(Vec(0, 1)));
		valueLabel->color = rack::color::BLACK;
		valueLabel->text = "";
		valueLabel->fontSize = 10;
		addChild(valueLabel);

		patchName = createWidget<MetaModuleTextBox>(mm2px(Vec(24.6, 9.6)));
		if (expModule != nullptr && expModule->patchNameText.length() > 0)
			patchName->text = this->expModule->patchNameText;
		else
			patchName->text = "Enter Patch Name";
		patchName->color = rack::color::WHITE;
		patchName->box.size = {mm2px(Vec(33.6, 31.3))};
		addChild(patchName);
		patchName->selectAll(); // Doesn't work :(

		addLabeledKnobMM<RoundBlackKnob>("A", 0, {9, 38.9});
		addLabeledKnobMM<RoundBlackKnob>("B", 1, {29.4, 51.7});
		addLabeledKnobMM<RoundBlackKnob>("C", 2, {51.6, 51.7});
		addLabeledKnobMM<RoundBlackKnob>("D", 3, {72, 38.9});
		addLabeledKnobMM<RoundSmallBlackKnob>("a", 4, {8.6, 59.6});
		addLabeledKnobMM<RoundSmallBlackKnob>("b", 5, {32.1, 73.0});
		addLabeledKnobMM<RoundSmallBlackKnob>("c", 6, {49.0, 73.0});
		addLabeledKnobMM<RoundSmallBlackKnob>("d", 7, {72.6, 59.6});

		addLabeledInputMM("CV IN 1", MetaModuleMiniHub::CV_1, {7.6, 74.5});
		addLabeledInputMM("CV IN 2", MetaModuleMiniHub::CV_2, {20, 82.1});
		addLabeledInputMM("CV IN 3", MetaModuleMiniHub::CV_3, {60.7, 82.4});
		addLabeledInputMM("CV IN 4", MetaModuleMiniHub::CV_4, {73.1, 74.5});

		addLabeledInputMM("Gate In 1", MetaModuleMiniHub::GATE_IN_1, {9, 94.5});
		addLabeledInputMM("Gate In 2", MetaModuleMiniHub::GATE_IN_2, {71.7, 94.5});
		addLabeledInputMM("Clock In", MetaModuleMiniHub::CLOCK_IN, {40.4, 88.9});

		addLabeledInputMM("Audio IN L", MetaModuleMiniHub::AUDIO_IN_L, {8.2, 111.8});
		addLabeledInputMM("Audio IN R", MetaModuleMiniHub::AUDIO_IN_R, {23.4, 111.8});

		addLabeledOutputMM("Audio OUT L", MetaModuleMiniHub::AUDIO_OUT_L, {57.3, 111.8});
		addLabeledOutputMM("Audio OUT R", MetaModuleMiniHub::AUDIO_OUT_R, {72.8, 111.8});

		addLabeledOutputMM("CV Out 1", MetaModuleMiniHub::AUDIO_OUT_3, {25.7, 96.2});
		addLabeledOutputMM("CV Out 2", MetaModuleMiniHub::AUDIO_OUT_4, {55, 96.2});

		addLabeledOutputMM("Clock Out", MetaModuleMiniHub::CLOCK_OUT, {40.4, 106.4});
	}
};

// Model *modelMetaModuleMiniHub = createModel<MetaModuleMiniHub, MetaModuleMiniHubWidget>("metaModuleMiniHubModule");
