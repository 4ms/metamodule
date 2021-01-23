#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct FourstepModule : CommModule {

	enum ParamIds {
		STEP1_PARAM,
		STEP2_PARAM,
		STEP3_PARAM,
		STEP4_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		VOLTAGE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	FourstepModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("FOURSTEP");
		selfID.typeID = "FOURSTEP";

		outputJacks[FourstepModule::VOLTAGE_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct FourstepWidget : CommModuleWidget {

	FourstepModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	FourstepWidget(FourstepModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addLabeledKnob("1", FourstepModule::STEP1_PARAM, {0, 0});
		addLabeledKnob("2", FourstepModule::STEP2_PARAM, {0, 1});
		addLabeledKnob("3", FourstepModule::STEP3_PARAM, {0, 2});
		addLabeledKnob("4", FourstepModule::STEP4_PARAM, {0, 3});

		addLabeledInput("CLK", FourstepModule::CLOCK_INPUT, {0, 1});
		addLabeledOutput("OUT", FourstepModule::VOLTAGE_OUTPUT, {0, 0});

		addModuleTitle("SEQ 4");
	}
};

Model *modelFourstep = createModel<FourstepModule, FourstepWidget>("FOURSTEP");
