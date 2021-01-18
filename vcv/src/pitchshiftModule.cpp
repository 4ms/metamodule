#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct PitchshiftModule : CommModule {

	enum ParamIds { COARSE_PARAM, FINE_PARAM, WINDOW_PARAM, MIX_PARAM, NUM_PARAMS };
	enum InputIds { SIGNAL_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	PitchshiftModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("PITCHSHIFT");
		selfID.typeID = "PITCHSHIFT";
	}
};

struct PitchshiftWidget : CommModuleWidget {

	PitchshiftModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	PitchshiftWidget(PitchshiftModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
		addLabeledKnob("COARSE", PitchshiftModule::COARSE_PARAM, {0, 0});
		addLabeledKnob("FINE", PitchshiftModule::FINE_PARAM, {0, 1});
		addLabeledKnob("WINDOW", PitchshiftModule::WINDOW_PARAM, {0, 2});
		addLabeledKnob("MIX", PitchshiftModule::MIX_PARAM, {0, 3});

		addLabeledInput("IN", PitchshiftModule::SIGNAL_INPUT, {0, 1});
		addLabeledOutput("OUT", PitchshiftModule::SIGNAL_OUTPUT, {0, 0});
	}
};

Model *modelPitchshift = createModel<PitchshiftModule, PitchshiftWidget>("PITCHSHIFT");
