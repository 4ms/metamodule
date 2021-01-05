#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct ClkdividerModule : CommModule {

	enum ParamIds {
		DIVISION_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		CLOCK_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	ClkdividerModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        core = ModuleFactory::create("CLKDIVIDER");
		selfID.typeID = "CLKDIVIDER";
	}
};

struct ClkdividerWidget : CommModuleWidget {

	ClkdividerModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	ClkdividerWidget(ClkdividerModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

addLabeledKnob("DIV",ClkdividerModule::DIVISION_PARAM,{0,0});
		addLabeledInput("CLK IN",ClkdividerModule::CLOCK_INPUT,{0,1});
		addLabeledOutput("CLK OUT",ClkdividerModule::CLOCK_OUTPUT,{0,0});
	}
};

Model *modelClkdivider = createModel<ClkdividerModule, ClkdividerWidget>("CLKDIVIDER");
