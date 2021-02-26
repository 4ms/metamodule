#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct ReverbModule : CommModule {

	enum ParamIds {
		SIZE_PARAM,
		DAMP_PARAM,
		MIX_PARAM,
		TIME_PARAM,
		APRATIO,
		CRATIO,
		NUM_PARAMS
	};
	enum InputIds { SIGNAL_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	ReverbModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("REVERB");
		selfID.typeID = "REVERB";

		inputJacks[ReverbModule::SIGNAL_INPUT]->scale = [](float f) { return f / 5.0f; };
		outputJacks[ReverbModule::SIGNAL_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct ReverbWidget : CommModuleWidget {

	ReverbModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	ReverbWidget(ReverbModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hpTemplate.svg")));

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hpTemplate.svg")));
		addModuleTitle("VERB");
		addLabeledKnob("SIZE", ReverbModule::SIZE_PARAM, {0, 0});
		addLabeledKnob("TIME", ReverbModule::TIME_PARAM, {1, 0});
		addLabeledKnob("DAMP", ReverbModule::DAMP_PARAM, {2, 0});
		addLabeledKnob("MIX", ReverbModule::MIX_PARAM, {3, 0});

		addLabeledKnob("AP Ratio", ReverbModule::APRATIO, {0, 1});
		addLabeledKnob("Comb Ratio", ReverbModule::CRATIO, {1, 1});
		addLabeledInput("IN", ReverbModule::SIGNAL_INPUT, {0, 0});
		addLabeledOutput("OUT", ReverbModule::SIGNAL_OUTPUT, {1, 0});
	}
};

Model *modelReverb = createModel<ReverbModule, ReverbWidget>("REVERB");
