#include "CommData.h"
#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "CoreModules/panel_medium_defs.hh"
#include "hub_base.hh"
#include "localPath.h"
#include "patch_writer.hh"
#include "plugin.hpp"

struct HubMedium : MetaModuleHubBase {

	enum ParamIds { ENUMS(KNOBS, PanelDef::NumPot + PanelDef::NumMetaRgbButton), WRITE_PATCH, NUM_PARAMS };
	enum InputIds { NUM_INPUTS = PanelDef::NumAudioIn + PanelDef::NumGateIn };
	enum OutputIds { NUM_OUTPUTS = PanelDef::NumAudioOut + PanelDef::NumGateOut };
	enum LightIds { NUM_LIGHTS = 0 };

	HubMedium()
	{
		for (int i = 0; i < PanelDef::NumKnobs; i++)
			knobMaps.emplace_back(i);

		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		selfID.typeID = "PANEL_MED";
	}

	~HubMedium() = default;

	void process(const ProcessArgs &args) override
	{
		processPatchButton(params[WRITE_PATCH].getValue());
		processKnobMaps();
		processCreatePatchFile();
	}
};

struct HubMediumWidget : MetaModuleHubBaseWidget {
	LedDisplayTextField *patchName;

	Vec fixDPI(Vec v)
	{
		return v.mult(75.f / 72.f);
	}

	HubMediumWidget(HubMedium *module)
	{
		setModule(module);
		hubModule = module;

		if (hubModule != nullptr) {
			hubModule->updateDisplay = [&]() { this->valueLabel->text = this->hubModule->labelText; };
			hubModule->updatePatchName = [&]() { this->hubModule->patchNameText = this->patchName->text; };
			hubModule->redrawPatchName = [&]() { this->patchName->text = this->hubModule->patchNameText; };
		}

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/meta-module-medium.svg")));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		valueLabel = createWidget<Label>(mm2px(Vec(0, 1)));
		valueLabel->color = rack::color::BLACK;
		valueLabel->text = "";
		valueLabel->fontSize = 10;
		addChild(valueLabel);

		patchName = createWidget<MetaModuleTextBox>(mm2px(Vec(24.6, 9.6)));
		if (hubModule != nullptr && hubModule->patchNameText.length() > 0)
			patchName->text = this->hubModule->patchNameText;
		else
			patchName->text = "Enter Patch Name";
		patchName->color = rack::color::WHITE;
		patchName->box.size = {mm2px(Vec(33.6, 31.3))};
		addChild(patchName);
		patchName->selectAll(); // Doesn't work :(

		addParam(createParamCentered<BefacoPush>((Vec(22.31, 43.16)), module, 0));

		addLabeledKnobPx<RoundSmallBlackKnob>("", 1, fixDPI({64.57, 53.24}));
		addLabeledKnobPx<RoundSmallBlackKnob>("", 2, fixDPI({27.94, 88.42}));
		addLabeledKnobPx<RoundSmallBlackKnob>("", 3, fixDPI({343.34, 92.99}));
		addLabeledKnobPx<RoundSmallBlackKnob>("", 4, fixDPI({295.26, 117.58}));
		addLabeledKnobPx<RoundSmallBlackKnob>("", 5, fixDPI({64.57, 120.56}));
		addLabeledKnobPx<RoundBlackKnob>("", 6, fixDPI({34.23, 166.3}));
		addLabeledKnobPx<RoundBlackKnob>("", 7, fixDPI({341.35, 166.41}));
		addLabeledKnobPx<RoundBlackKnob>("", 8, fixDPI({94.21, 193.61}));
		addLabeledKnobPx<RoundBlackKnob>("", 9, fixDPI({280.72, 193.68}));
		addLabeledKnobPx<RoundBlackKnob>("", 10, fixDPI({155.15, 213.81}));
		addLabeledKnobPx<RoundBlackKnob>("", 11, fixDPI({220.04, 214.26}));
		addLabeledKnobPx<RoundSmallBlackKnob>("", 12, fixDPI({44.14, 226.16}));

		addInput(createInputCentered<PJ301MPort>(fixDPI({22.9, 274.7}), module, 0));
		addInput(createInputCentered<PJ301MPort>(fixDPI({66.42, 274.7}), module, 1));
		addInput(createInputCentered<PJ301MPort>(fixDPI({109.61, 282.75}), module, 2));
		addInput(createInputCentered<PJ301MPort>(fixDPI({153.13, 282.75}), module, 3));
		addInput(createInputCentered<PJ301MPort>(fixDPI({36.34, 324.15}), module, 4));
		addInput(createInputCentered<PJ301MPort>(fixDPI({79.86, 324.15}), module, 5));
		addInput(createInputCentered<PJ301MPort>(fixDPI({122.6, 324.18}), module, 6));
		addInput(createInputCentered<PJ301MPort>(fixDPI({166.12, 324.18}), module, 7));

		addOutput(createOutputCentered<PJ301MPort>(fixDPI({352.74, 219.83}), module, 0));
		addOutput(createOutputCentered<PJ301MPort>(fixDPI({316.22, 238.83}), module, 1));
		addOutput(createOutputCentered<PJ301MPort>(fixDPI({308.9, 282.15}), module, 2));
		addOutput(createOutputCentered<PJ301MPort>(fixDPI({352.42, 282.15}), module, 3));
		addOutput(createOutputCentered<PJ301MPort>(fixDPI({222.16, 282.79}), module, 4));
		addOutput(createOutputCentered<PJ301MPort>(fixDPI({265.68, 282.79}), module, 5));
		addOutput(createOutputCentered<PJ301MPort>(fixDPI({209.28, 324.18}), module, 6));
		addOutput(createOutputCentered<PJ301MPort>(fixDPI({252.8, 324.18}), module, 7));
		addOutput(createOutputCentered<PJ301MPort>(fixDPI({295.21, 324.2}), module, 8));
		addOutput(createOutputCentered<PJ301MPort>(fixDPI({338.73, 324.2}), module, 9));
	}
};

Model *modelHubMedium = createModel<HubMedium, HubMediumWidget>("PANEL_MED");
