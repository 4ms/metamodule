#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct DrumModule : CommModule {

	enum ParamIds {
		PITCH_PARAM,
		PITCH_ENV_PARAM,
		PITCH_AMT_PARAM,
		TONE_ENV_PARAM,
		NOISE_ENV_PARAM,
		NOISE_BLEND_PARAM,
		NUM_PARAMS
	};
	enum InputIds { TRIGGER_INPUT, NUM_INPUTS };
	enum OutputIds { DRUM_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	DrumModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("DRUM");
		selfID.typeID = "DRUM";
	}
};

struct DrumWidget : CommModuleWidget {

	DrumModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	DrumWidget(DrumModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/12hpTemplate.svg")));

		addModuleTitle("DRUM");

		addLabeledKnob("PITCH", DrumModule::PITCH_PARAM, {0, 0});
		addLabeledKnob("PITCH ENV", DrumModule::PITCH_ENV_PARAM, {1, 0});
		addLabeledKnob("PITCH AMT", DrumModule::PITCH_AMT_PARAM, {2, 0});

		addLabeledKnob("TONE ENV", DrumModule::TONE_ENV_PARAM, {0, 1});
		addLabeledKnob("NOISE ENV", DrumModule::NOISE_ENV_PARAM, {1, 1});
		addLabeledKnob("NOISE BLEND", DrumModule::NOISE_BLEND_PARAM, {2, 1});
	}
};

Model *modelDrum = createModel<DrumModule, DrumWidget>("DRUM");
