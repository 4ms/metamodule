#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct MinmaxModule : CommModule {

	enum ParamIds { NUM_PARAMS };
	enum InputIds { A_INPUT, B_INPUT, NUM_INPUTS };
	enum OutputIds { MIN_OUTPUT, MAX_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	MinmaxModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("MINMAX");
		selfID.typeID = "MINMAX";
	}
};

struct MinmaxWidget : CommModuleWidget {

	MinmaxModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	MinmaxWidget(MinmaxModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addLabeledInput("IN A", MinmaxModule::A_INPUT, {0, 3});
		addLabeledInput("IN B", MinmaxModule::B_INPUT, {0, 2});
		addLabeledOutput("MIN", MinmaxModule::MIN_OUTPUT, {0, 1});
		addLabeledOutput("MAX", MinmaxModule::MAX_OUTPUT, {0, 0});
	}
};

Model *modelMinmax = createModel<MinmaxModule, MinmaxWidget>("MINMAX");
