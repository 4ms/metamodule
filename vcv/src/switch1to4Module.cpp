#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct Switch1to4Module : CommModule {

	enum ParamIds { NUM_PARAMS };
	enum InputIds { CLOCK_INPUT, RESET_INPUT, SIGNAL_INPUT, NUM_INPUTS };
	enum OutputIds { ENUMS(SIGNAL_OUTPUTS, 4), NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	Switch1to4Module()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("SWITCH1TO4");
		selfID.typeID = "SWITCH1TO4";
	}
};

struct Switch1to4Widget : CommModuleWidget {

	Switch1to4Module *mainModule;

	Label *valueLabel;
	Label *recLabel;

	Switch1to4Widget(Switch1to4Module *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hpTemplate.svg")));

		addLabeledInput("CLOCK", Switch1to4Module::CLOCK_INPUT, {0, 1});
		addLabeledInput("RESET", Switch1to4Module::RESET_INPUT, {0, 0});

		for (int i = 0; i < 4; i++) {
			addLabeledOutput(
				"OUT " + std::to_string(i + 1), Switch1to4Module::SIGNAL_OUTPUTS + i, {1, static_cast<float>(3 - i)});
		}

		addLabeledInput("IN", Switch1to4Module::SIGNAL_INPUT, {1, 4});
	}
};

Model *modelSwitch1to4 = createModel<Switch1to4Module, Switch1to4Widget>("SWITCH1TO4");
