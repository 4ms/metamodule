#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct PhaserModule : CommModule {

	enum ParamIds {
		LFO_SPEED_PARAM,
		LFO_DEPTH_PARAM,
		FREQ_MIN_PARAM,
		FREQ_MAX_PARAM,
		WIDTH_PARAM,
		FEEDBACK_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		SIGNAL_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	PhaserModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("PHASER");
		selfID.typeID = "PHASER";
	}
};

struct PhaserWidget : CommModuleWidget {

	PhaserModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	PhaserWidget(PhaserModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hptemplate.svg")));

		addLabeledKnob("SPEED", PhaserModule::LFO_SPEED_PARAM, {0, 0});
		addLabeledKnob("DEPTH", PhaserModule::LFO_DEPTH_PARAM, {1, 0});
		addLabeledKnob("MIN", PhaserModule::FREQ_MIN_PARAM, {0, 1});
		addLabeledKnob("MAX", PhaserModule::FREQ_MAX_PARAM, {1, 1});
		addLabeledKnob("WIDTH", PhaserModule::WIDTH_PARAM, {0, 2});
		addLabeledKnob("FEED", PhaserModule::FEEDBACK_PARAM, {1, 2});

		addLabeledInput("IN", PhaserModule::SIGNAL_INPUT, {0, 0});
		addLabeledOutput("OUT", PhaserModule::SIGNAL_OUTPUT, {1, 0});
	}
};

Model *modelPhaser = createModel<PhaserModule, PhaserWidget>("PHASER");
