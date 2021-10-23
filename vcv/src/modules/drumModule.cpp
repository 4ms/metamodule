#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct DrumModule : CommModule {

	enum ParamIds {
		PITCH_PARAM,
		PITCH_ENV_PARAM,
		PITCH_AMT_PARAM,
		FM_RATIO_PARAM,
		FM_ENV_PARAM,
		FM_AMT_PARAM,
		TONE_ENV_PARAM,
		NOISE_ENV_PARAM,
		NOISE_BLEND_PARAM,
		NUM_PARAMS
	};
	enum InputIds { TRIGGER_INPUT, PITCH_INPUT, N_ENV_CV, FM_ENV_CV, PITCH_ENV_CV, TONE_ENV_CV, NUM_INPUTS };
	enum OutputIds { DRUM_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	DrumModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("DRUM");
		selfID.typeID = "DRUM";

		outputJacks[DrumModule::DRUM_OUTPUT]->scale = [](float f) { return f * 5.0f; };
		inputJacks[DrumModule::PITCH_INPUT]->scale = [](float f) { return f / 5.0f; };

		inputJacks[DrumModule::N_ENV_CV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[DrumModule::TONE_ENV_CV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[DrumModule::PITCH_ENV_CV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[DrumModule::FM_ENV_CV]->scale = [](float f) { return f / 5.0f; };
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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/12hptemplate.svg")));

		addModuleTitle("DRUM");

		addLabeledKnob("PITCH", DrumModule::PITCH_PARAM, {0, 0});
		addLabeledKnob("PITCH ENV", DrumModule::PITCH_ENV_PARAM, {1, 0});
		addLabeledKnob("PITCH AMT", DrumModule::PITCH_AMT_PARAM, {2, 0});

		addLabeledKnob("RATIO", DrumModule::FM_RATIO_PARAM, {0, 1});
		addLabeledKnob("FM ENV", DrumModule::FM_ENV_PARAM, {1, 1});
		addLabeledKnob("FM AMT", DrumModule::FM_AMT_PARAM, {2, 1});

		addLabeledKnob("TONE ENV", DrumModule::TONE_ENV_PARAM, {0, 2});
		addLabeledKnob("NOISE ENV", DrumModule::NOISE_ENV_PARAM, {1, 2});
		addLabeledKnob("NOISE BLEND", DrumModule::NOISE_BLEND_PARAM, {2, 2});

		addLabeledInput("N ENV", DrumModule::N_ENV_CV, {1, 0});
		addLabeledInput("FM ENV", DrumModule::FM_ENV_CV, {1, 1});
		addLabeledInput("P ENV", DrumModule::PITCH_ENV_CV, {1, 2});
		addLabeledInput("T ENV", DrumModule::TONE_ENV_CV, {1, 3});

		addLabeledInput("V/OCT", DrumModule::PITCH_INPUT, {0, 1});
		addLabeledInput("TRIGGER", DrumModule::TRIGGER_INPUT, {0, 0});
		addLabeledOutput("OUTPUT", DrumModule::DRUM_OUTPUT, {2, 0});
	}
};

Model *modelDrum = createModel<DrumModule, DrumWidget>("DRUM");
