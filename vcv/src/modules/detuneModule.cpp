#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct DetuneModule : CommModule {

	enum ParamIds { WOW_SPEED_PARAM, WOW_DEPTH_PARAM, FLUTTER_SPEED_PARAM, FLUTTER_DEPTH_PARAM, NUM_PARAMS };
	enum InputIds { SIGNAL_INPUT, DETUNE_CV, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	DetuneModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("DETUNE");
		selfID.typeID = "DETUNE";

		inputJacks[DetuneModule::DETUNE_CV]->scale = [](float f) { return f / 5.0f; };
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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hptemplate.svg")));

		addLabeledKnob("Wow Speed", DetuneModule::WOW_SPEED_PARAM, {0, 0});
		addLabeledKnob("Wow Depth", DetuneModule::WOW_DEPTH_PARAM, {0, 1});
		addLabeledKnob("Flut Speed", DetuneModule::FLUTTER_SPEED_PARAM, {0, 2});
		addLabeledKnob("Flut Depth", DetuneModule::FLUTTER_DEPTH_PARAM, {0, 3});

		addLabeledInput("Detune", DetuneModule::DETUNE_CV, {0, 2});
		addLabeledInput("In", DetuneModule::SIGNAL_INPUT, {0, 1});
		addLabeledOutput("Out", DetuneModule::SIGNAL_OUTPUT, {0, 0});

		addModuleTitle("DETUNE");
	}
};

Model *modelDetune = createModel<DetuneModule, DetuneWidget>("DETUNE");
