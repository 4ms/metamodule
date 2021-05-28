#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct Switch4to1Module : CommModule {

	enum ParamIds { NUM_PARAMS };
	enum InputIds { CLOCK_INPUT, RESET_INPUT, ENUMS(SIGNAL_INPUTS, 4), CV_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	Switch4to1Module()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("SWITCH4TO1");
		selfID.typeID = "SWITCH4TO1";

		inputJacks[Switch4to1Module::CV_INPUT]->scale = [](float f) { return f / 5.0f; };
	}
};

struct Switch4to1Widget : CommModuleWidget {

	Switch4to1Module *mainModule;

	Label *valueLabel;
	Label *recLabel;

	Switch4to1Widget(Switch4to1Module *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hptemplate.svg")));

		addLabeledInput("CLOCK", Switch4to1Module::CLOCK_INPUT, {0, 1});
		addLabeledInput("RESET", Switch4to1Module::RESET_INPUT, {0, 0});
		addLabeledInput("CV", Switch4to1Module::CV_INPUT, {0, 2});

		for (int i = 0; i < 4; i++) {
			addLabeledInput(
				"IN " + std::to_string(i + 1), Switch4to1Module::SIGNAL_INPUTS + i, {1, static_cast<float>(4 - i)});
		}

		addLabeledOutput("OUT", Switch4to1Module::SIGNAL_OUTPUT, {1, 0});

		addModuleTitle("SWITCH 4:1");
	}
};

Model *modelSwitch4to1 = createModel<Switch4to1Module, Switch4to1Widget>("SWITCH4TO1");
