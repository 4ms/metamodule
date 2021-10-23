#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct VoltagesourceModule : CommModule {

	enum ParamIds { VOLT1_PARAM, VOLT2_PARAM, NUM_PARAMS };
	enum InputIds { NUM_INPUTS };
	enum OutputIds { OUTPUT1_OUTPUT, OUTPUT2_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	VoltagesourceModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("VOLTAGESOURCE");
		selfID.typeID = "VOLTAGESOURCE";

		outputJacks[VoltagesourceModule::OUTPUT1_OUTPUT]->scale = [](float f) { return f * 5.0f; };
		outputJacks[VoltagesourceModule::OUTPUT2_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct VoltagesourceWidget : CommModuleWidget {

	VoltagesourceModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	VoltagesourceWidget(VoltagesourceModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addModuleTitle("SOURCE");
		addLabeledKnob("1", VoltagesourceModule::VOLT1_PARAM, {0, 0});
		addLabeledKnob("2", VoltagesourceModule::VOLT2_PARAM, {0, 1});
		addLabeledOutput("1", VoltagesourceModule::OUTPUT1_OUTPUT, {0, 1});
		addLabeledOutput("2", VoltagesourceModule::OUTPUT2_OUTPUT, {0, 0});
	}
};

Model *modelVoltagesource = createModel<VoltagesourceModule, VoltagesourceWidget>("VOLTAGESOURCE");
