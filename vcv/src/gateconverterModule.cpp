#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct GateconverterModule : CommModule {

	enum ParamIds { LENGTH_PARAM, DELAY_PARAM, NUM_PARAMS };
	enum InputIds { GATE_INPUT, NUM_INPUTS };
	enum OutputIds { GATE_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	GateconverterModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("GATECONVERTER");
		selfID.typeID = "GATECONVERTER";

		inputJacks[GateconverterModule::GATE_INPUT]->scale = [](float f) { return f / 5.0f; };
		outputJacks[GateconverterModule::GATE_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct GateconverterWidget : CommModuleWidget {

	GateconverterModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	GateconverterWidget(GateconverterModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
		addLabeledKnob("LENGTH", GateconverterModule::LENGTH_PARAM, {0, 0});
		addLabeledKnob("DELAY", GateconverterModule::DELAY_PARAM, {0, 1});
		addLabeledInput("IN", GateconverterModule::GATE_INPUT, {0, 1});
		addLabeledOutput("OUT", GateconverterModule::GATE_OUTPUT, {0, 0});

		addModuleTitle("GATE");
	}
};

Model *modelGateconverter = createModel<GateconverterModule, GateconverterWidget>("GATECONVERTER");
