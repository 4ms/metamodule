#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct EightstepModule : CommModule {

	enum ParamIds {
		STEP1_PARAM,
		STEP2_PARAM,
		STEP3_PARAM,
		STEP4_PARAM,
		STEP5_PARAM,
		STEP6_PARAM,
		STEP7_PARAM,
		STEP8_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
		RESET_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		END_OUTPUT,
		VOLTAGE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	EightstepModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("EIGHTSTEP");
		selfID.typeID = "EIGHTSTEP";
		outputJacks[EightstepModule::VOLTAGE_OUTPUT]->scale = [](float f) { return f * 5.0f; };
		outputJacks[EightstepModule::END_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct EightstepWidget : CommModuleWidget {

	EightstepModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	EightstepWidget(EightstepModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hpTemplate.svg")));

		addLabeledKnob("1", EightstepModule::STEP1_PARAM, {0, 0});
		addLabeledKnob("2", EightstepModule::STEP2_PARAM, {1, 0});
		addLabeledKnob("3", EightstepModule::STEP3_PARAM, {0, 1});
		addLabeledKnob("4", EightstepModule::STEP4_PARAM, {1, 1});
		addLabeledKnob("5", EightstepModule::STEP5_PARAM, {0, 2});
		addLabeledKnob("6", EightstepModule::STEP6_PARAM, {1, 2});
		addLabeledKnob("7", EightstepModule::STEP7_PARAM, {0, 3});
		addLabeledKnob("8", EightstepModule::STEP8_PARAM, {1, 3});

		addLabeledInput("CLK", EightstepModule::CLOCK_INPUT, {0, 1});
		addLabeledInput("RST", EightstepModule::RESET_INPUT, {1, 1});

		addLabeledOutput("OUT", EightstepModule::VOLTAGE_OUTPUT, {0, 0});
		addLabeledOutput("END", EightstepModule::END_OUTPUT, {1, 0});
	}
};

Model *modelEightstep = createModel<EightstepModule, EightstepWidget>("EIGHTSTEP");
