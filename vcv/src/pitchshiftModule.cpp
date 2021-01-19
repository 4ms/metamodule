#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct PitchshiftModule : CommModule {

	enum ParamIds { COARSE_PARAM, FINE_PARAM, WINDOW_PARAM, MIX_PARAM, NUM_PARAMS };
	enum InputIds { SIGNAL_INPUT, SHIFT_CV, WINDOW_CV, MIX_CV, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	PitchshiftModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("PITCHSHIFT");
		selfID.typeID = "PITCHSHIFT";
		inputJacks[PitchshiftModule::SHIFT_CV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[PitchshiftModule::WINDOW_CV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[PitchshiftModule::MIX_CV]->scale = [](float f) { return f / 5.0f; };
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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hpTemplate.svg")));
		addLabeledKnob("COARSE", PitchshiftModule::COARSE_PARAM, {0, 0});
		addLabeledKnob("FINE", PitchshiftModule::FINE_PARAM, {1, 0});
		addLabeledKnob("WINDOW", PitchshiftModule::WINDOW_PARAM, {0, 1});
		addLabeledKnob("MIX", PitchshiftModule::MIX_PARAM, {1, 1});

		addLabeledInput("SHIFT", PitchshiftModule::SHIFT_CV, {0, 2});
		addLabeledInput("WINDOW", PitchshiftModule::WINDOW_CV, {0, 1});
		addLabeledInput("MIX", PitchshiftModule::MIX_CV, {1, 1});

		addLabeledInput("IN", PitchshiftModule::SIGNAL_INPUT, {0, 0});
		addLabeledOutput("OUT", PitchshiftModule::SIGNAL_OUTPUT, {1, 0});
	}
};

Model *modelPitchshift = createModel<PitchshiftModule, PitchshiftWidget>("PITCHSHIFT");
