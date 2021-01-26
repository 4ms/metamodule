#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct FmoscModule : CommModule {

	enum ParamIds { COARSE_TUNE_PARAM, INDEX_PARAM, RATIO_PARAM, NUM_PARAMS };
	enum InputIds { NUM_INPUTS };
	enum OutputIds { MAIN_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	FmoscModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("FMOSC");
		selfID.typeID = "FMOSC";
	}
};

struct FmoscWidget : CommModuleWidget {

	FmoscModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	FmoscWidget(FmoscModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/12hpTemplate.svg")));

		addLabeledKnob("PITCH", FmoscModule::COARSE_TUNE_PARAM, {0, 0});
		addLabeledKnob("INDEX", FmoscModule::INDEX_PARAM, {1, 0});
		addLabeledKnob("RATIO", FmoscModule::RATIO_PARAM, {0, 1});

		addLabeledOutput("OUT", FmoscModule::MAIN_OUTPUT, {2, 0});

		addModuleTitle("FM OSCILLATOR");
	}
};

Model *modelFmosc = createModel<FmoscModule, FmoscWidget>("FMOSC");
