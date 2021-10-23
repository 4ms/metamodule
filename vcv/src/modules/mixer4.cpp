#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "math.hh"

struct Mixer4Module : public CommModule {

	enum ParamIds { LEVEL1_PARAM, LEVEL2_PARAM, LEVEL3_PARAM, LEVEL4_PARAM, NUM_PARAMS };
	enum InputIds { INPUT1_INPUT, INPUT2_INPUT, INPUT3_INPUT, INPUT4_INPUT, NUM_INPUTS };
	enum OutputIds { INV_OUTPUT, MIX_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	Mixer4Module()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		selfID.typeID = "MIXER4";
		core = ModuleFactory::create(selfID.typeID);
	}
};

struct Mixer4Widget : CommModuleWidget {

	Mixer4Module *mainModule;

	Label *valueLabel;
	Label *recLabel;

	Mixer4Widget(Mixer4Module *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hptemplate.svg")));

		addLabeledKnob("LVL1", Mixer4Module::LEVEL1_PARAM, {0, 0});
		addLabeledKnob("LVL2", Mixer4Module::LEVEL2_PARAM, {1, 0});
		addLabeledKnob("LVL3", Mixer4Module::LEVEL3_PARAM, {0, 1});
		addLabeledKnob("LVL4", Mixer4Module::LEVEL4_PARAM, {1, 1});

		addLabeledInput("IN1", Mixer4Module::INPUT1_INPUT, {0, 2});
		addLabeledInput("IN2", Mixer4Module::INPUT2_INPUT, {1, 2});
		addLabeledInput("IN3", Mixer4Module::INPUT3_INPUT, {0, 1});
		addLabeledInput("IN4", Mixer4Module::INPUT4_INPUT, {1, 1});

		addLabeledOutput("INV", Mixer4Module::INV_OUTPUT, {0, 0});
		addLabeledOutput("MIX", Mixer4Module::MIX_OUTPUT, {1, 0});

		addModuleTitle("MIXER");
	}
};

Model *modelMixer4 = createModel<Mixer4Module, Mixer4Widget>("mixer4");
