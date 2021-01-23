#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct LowpassgateModule : CommModule {

	enum ParamIds {
		LEVEL_PARAM,
		CV_PARAM,
		DECAY_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CV_INPUT,
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

	LowpassgateModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        core = ModuleFactory::create("LOWPASSGATE");
		selfID.typeID = "LOWPASSGATE";
		inputJacks[LowpassgateModule::SIGNAL_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[LowpassgateModule::CV_INPUT]->scale = [](float f) { return f / 5.0f; };
		outputJacks[LowpassgateModule::SIGNAL_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct LowpassgateWidget : CommModuleWidget {

	LowpassgateModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	LowpassgateWidget(LowpassgateModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addLabeledKnob("LVL",LowpassgateModule::LEVEL_PARAM,{0,0});
		addLabeledKnob("CV",LowpassgateModule::CV_PARAM,{0,1});
		addLabeledKnob("DECAY",LowpassgateModule::DECAY_PARAM,{0,2});

		addLabeledOutput("OUT",LowpassgateModule::SIGNAL_OUTPUT,{0,0});
		addLabeledInput("CV",LowpassgateModule::CV_INPUT,{0,2});
		addLabeledInput("IN",LowpassgateModule::SIGNAL_INPUT,{0,1});

		addModuleTitle("LPG");
	}
};

Model *modelLowpassgate = createModel<LowpassgateModule, LowpassgateWidget>("LOWPASSGATE");
