#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct EnvelopefollowerModule : CommModule {

	enum ParamIds {
		THRESHOLD_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		ENVELOPE_OUTPUT,
		GATE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	EnvelopefollowerModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        core = ModuleFactory::create("ENVELOPEFOLLOWER");
		selfID.typeID = "ENVELOPEFOLLOWER";
	}
};

struct EnvelopefollowerWidget : CommModuleWidget {

	EnvelopefollowerModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	EnvelopefollowerWidget(EnvelopefollowerModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addLabeledKnob("THRESHOLD", EnvelopefollowerModule::THRESHOLD_PARAM, {0, 0});
		addLabeledInput("INPUT", EnvelopefollowerModule::SIGNAL_INPUT, {0, 2});
		addLabeledOutput("GATE", EnvelopefollowerModule::GATE_OUTPUT, {0, 1});
		addLabeledOutput("ENV", EnvelopefollowerModule::ENVELOPE_OUTPUT, {0, 0});

		addModuleTitle("FLW");

	}
};

Model *modelEnvelopefollower = createModel<EnvelopefollowerModule, EnvelopefollowerWidget>("ENVELOPEFOLLOWER");
