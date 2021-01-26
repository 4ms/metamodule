#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct DetuneModule : CommModule {

	enum ParamIds { WOW_SPEED_PARAM, WOW_DEPTH_PARAM, FLUTTER_SPEED_PARAM, FLUTTER_DEPTH_PARAM, NUM_PARAMS };
	enum InputIds { SIGNAL_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	DetuneModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("DETUNE");
		selfID.typeID = "DETUNE";
	}
};

struct DetuneWidget : CommModuleWidget {

	DetuneModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	DetuneWidget(DetuneModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hpTemplate.svg")));

		addLabeledKnob("WOW S", DetuneModule::WOW_SPEED_PARAM, {0, 0});
		addLabeledKnob("WOW D", DetuneModule::WOW_DEPTH_PARAM, {0, 1});
		addLabeledKnob("F S", DetuneModule::FLUTTER_SPEED_PARAM, {0, 2});
		addLabeledKnob("F D", DetuneModule::FLUTTER_DEPTH_PARAM, {0, 3});

		addLabeledInput("IN", DetuneModule::SIGNAL_INPUT, {0, 1});
		addLabeledOutput("OUT", DetuneModule::SIGNAL_OUTPUT, {0, 0});

		addModuleTitle("DTUNE");
	}
};

Model *modelDetune = createModel<DetuneModule, DetuneWidget>("DETUNE");
