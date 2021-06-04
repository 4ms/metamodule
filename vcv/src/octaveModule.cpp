#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct OctaveModule : CommModule {

	enum ParamIds { OCTAVE_PARAM, NUM_PARAMS };
	enum InputIds { PITCH_INPUT, CV_INPUT, NUM_INPUTS };
	enum OutputIds { PITCH_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	OctaveModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("OCTAVE");
		selfID.typeID = "OCTAVE";

		inputJacks[OctaveModule::PITCH_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[OctaveModule::CV_INPUT]->scale = [](float f) { return f / 5.0f; };
		outputJacks[OctaveModule::PITCH_OUTPUT]->scale = [](float f) {return f*5.0f;};
	}
};

struct OctaveWidget : CommModuleWidget {

	OctaveModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	OctaveWidget(OctaveModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
		addLabeledKnob("OCTAVE", OctaveModule::OCTAVE_PARAM, {0, 0});
		addLabeledInput("CV", OctaveModule::CV_INPUT, {0, 2});
		addLabeledInput("IN", OctaveModule::PITCH_INPUT, {0, 1});
		addLabeledOutput("OUT", OctaveModule::PITCH_OUTPUT, {0, 0});

		addModuleTitle("OCT");
	}
};

Model *modelOctave = createModel<OctaveModule, OctaveWidget>("OCTAVE");
