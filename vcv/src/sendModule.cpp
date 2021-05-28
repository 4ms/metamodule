#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "math.hh"

struct SendModule : CommModule {

	enum ParamIds {
		LEVEL1_PARAM,
		LEVEL2_PARAM,
		LEVEL3_PARAM,
		LEVEL4_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT1_OUTPUT,
		OUTPUT2_OUTPUT,
		OUTPUT3_OUTPUT,
		OUTPUT4_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	SendModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("SEND_1TO4");
		selfID.typeID = "SEND_1TO4";
	}
};

struct SendWidget : CommModuleWidget {

	SendModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	SendWidget(SendModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hptemplate.svg")));

		addLabeledKnob("LVL1", SendModule::LEVEL1_PARAM, {0, 0});
		addLabeledKnob("LVL2", SendModule::LEVEL2_PARAM, {1, 0});
		addLabeledKnob("LVL3", SendModule::LEVEL3_PARAM, {0, 1});
		addLabeledKnob("LVL4", SendModule::LEVEL4_PARAM, {1, 1});

		addLabeledInput("IN", SendModule::SIGNAL_INPUT, {0, 2});

		addLabeledOutput("OUT1", SendModule::OUTPUT1_OUTPUT, {0, 1});
		addLabeledOutput("OUT2", SendModule::OUTPUT2_OUTPUT, {1, 1});
		addLabeledOutput("OUT3", SendModule::OUTPUT3_OUTPUT, {0, 0});
		addLabeledOutput("OUT4", SendModule::OUTPUT4_OUTPUT, {1, 0});

		addModuleTitle("SEND");
	}
};

Model *modelSend = createModel<SendModule, SendWidget>("send");
