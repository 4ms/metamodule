#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct ReverbModule : CommModule {

	enum ParamIds { SIZE_PARAM, DAMP_PARAM, MIX_PARAM, NUM_PARAMS };
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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addModuleTitle("VERB");
		addLabeledKnob("SIZE", ReverbModule::SIZE_PARAM, {0, 0});
		addLabeledKnob("DAMP", ReverbModule::DAMP_PARAM, {0, 1});
		addLabeledKnob("MIX", ReverbModule::MIX_PARAM, {0, 2});
		addLabeledInput("IN", ReverbModule::SIGNAL_INPUT, {0, 1});
		addLabeledOutput("OUT", ReverbModule::SIGNAL_OUTPUT, {0, 0});
	}
};

Model *modelReverb = createModel<ReverbModule, ReverbWidget>("REVERB");
