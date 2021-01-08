#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct FreqshiftModule : CommModule {

	enum ParamIds {
		COARSE_PARAM,
		FINE_PARAM,
		MIX_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		SIGNAL_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	FreqshiftModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("FREQSHIFT");
		selfID.typeID = "FREQSHIFT";
	}
};

struct FreqshiftWidget : CommModuleWidget {

	FreqshiftModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	FreqshiftWidget(FreqshiftModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addLabeledKnob("COARSE", FreqshiftModule::COARSE_PARAM, {0, 0});
		addLabeledKnob("FINE", FreqshiftModule::FINE_PARAM, {0, 1});
		addLabeledKnob("MIX", FreqshiftModule::MIX_PARAM, {0, 2});

		addLabeledInput("IN", FreqshiftModule::SIGNAL_INPUT, {0, 1});
		addLabeledOutput("OUT", FreqshiftModule::SIGNAL_OUTPUT, {0, 0});
	}
};

Model *modelFreqshift = createModel<FreqshiftModule, FreqshiftWidget>("FREQSHIFT");
