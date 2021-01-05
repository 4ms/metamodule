#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "example_patch.hh"
#include "patch_player.hh"
#include "plugin.hpp"

struct PatchPlayerModule : Module {

	enum ParamIds {
		ENUMS(KNOBS, 8),
		NUM_PARAMS
	};
	enum InputIds {
		AUDIO_IN_L,
		AUDIO_IN_R,
		CV_1,
		CV_2,
		CV_3,
		CV_4,
		NUM_INPUTS
	};
	enum OutputIds {
		AUDIO_OUT_L,
		AUDIO_OUT_R,
		NUM_OUTPUTS
	};
	enum LightIds {
		REC_LIGHT,
		NUM_LIGHTS
	};

	PatchPlayer player;

	PatchPlayerModule()
	{
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		player.load_patch(example_patch);
	}

	void process(const ProcessArgs &args) override
	{
		for (int i = 0; i < NUM_INPUTS; i++) {
			player.set_panel_input(i, inputs[i].getVoltage() / 10.0f);
		}
		for (int i = 0; i < NUM_PARAMS; i++) {
			player.set_panel_param(i, params[i].getValue());
		}

		player.update_patch(example_patch);

		for (int i = 0; i < NUM_OUTPUTS; i++) {
			outputs[i].setVoltage(player.get_panel_output(i) * 10.0f);
		}
	}
};

struct PatchPlayerWidget : CommModuleWidget {

	PatchPlayerWidget(Module *module)
	{
		setModule(module);

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hpTemplate.svg")));

		addLabeledKnob("A", 0, {0, 0});
		addLabeledKnob("B", 1, {1, 0});
		addLabeledKnob("C", 2, {2, 0});
		addLabeledKnob("D", 3, {3, 0});
		addLabeledKnob("a", 4, {0, 1});
		addLabeledKnob("b", 5, {1, 1});
		addLabeledKnob("c", 6, {2, 1});
		addLabeledKnob("d", 7, {3, 1});

		for (int i = 0; i < PatchPlayerModule::NUM_OUTPUTS; i++) {
			addLabeledOutput("OUT", i, {(float)i, 1});
		}
		for (int i = 0; i < PatchPlayerModule::NUM_INPUTS; i++) {
			addLabeledInput("IN", i, {(float)i, 0});
		}
	}
};

Model *modelPatchPlayer = createModel<PatchPlayerModule, PatchPlayerWidget>("PatchPlayer");
