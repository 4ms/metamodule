#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct ClkmultiplierModule : CommModule {

	enum ParamIds {
		MULT_PARAM,
		NUM_PARAMS,
	};
	enum InputIds {
		CLOCK_INPUT,
		NUM_INPUTS,
	};
	enum OutputIds {
		CLOCK_OUTPUT,
		NUM_OUTPUTS,
	};
	enum LightIds {
		NUM_LIGHTS,
	};

	ClkmultiplierModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("CLKMULTIPLIER");
		selfID.typeID = "CLKMULTIPLIER";
	}
};

struct ClkmultiplierWidget : CommModuleWidget {

	Label *valueLabel;
	Label *recLabel;

	ClkmultiplierWidget(ClkmultiplierModule *module)
	{
		setModule(module);

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
		addLabeledKnob("MULT", ClkmultiplierModule::MULT_PARAM, {0, 0});
		addLabeledInput("CLK IN", ClkmultiplierModule::CLOCK_INPUT, {0, 1});
		addLabeledOutput("CLK OUT", ClkmultiplierModule::CLOCK_OUTPUT, {0, 0});
	}
};

Model *modelClkmultiplier = createModel<ClkmultiplierModule, ClkmultiplierWidget>("CLKMULTIPLIER");
