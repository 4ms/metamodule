#include "CommModule.h"
#include "CommWidget.h"
#include "util/math.hh"

struct DjembeModule : CommModule {

	enum ParamIds { FREQ, GAIN, SHARPNESS, STRIKE, NUM_PARAMS };
	enum InputIds { FREQCV, GAINCV, SHARPNESSCV, STRIKECV, TRIGIN, NUM_INPUTS };
	enum OutputIds { OUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	DjembeModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("DJEMBE");
		selfID.typeID = "DJEMBE";
		outputJacks[DjembeModule::OUT]->scale = [](float f) { return f * 8.0f; };
		inputJacks[DjembeModule::FREQCV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[DjembeModule::GAINCV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[DjembeModule::SHARPNESSCV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[DjembeModule::STRIKECV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[DjembeModule::TRIGIN]->scale = [](float f) { return f / 5.0f; };
	}
};

struct DjembeWidget : CommModuleWidget {

	DjembeModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	DjembeWidget(DjembeModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hptemplate.svg")));

		addModuleTitle("Djembe");

		addLabeledKnob("Pitch", DjembeModule::FREQ, {0, 0});
		addLabeledKnob("Sharpness", DjembeModule::SHARPNESS, {1, 0});
		addLabeledKnob("Hit", DjembeModule::GAIN, {0, 1});
		addLabeledKnob("StrikeAmt", DjembeModule::STRIKE, {1, 1});

		addLabeledInput("Trigger", DjembeModule::TRIGIN, {0, 2});
		addLabeledOutput("Out", DjembeModule::OUT, {1, 2});

		addLabeledInput("Pitch", DjembeModule::FREQCV, {0, 1});
		addLabeledInput("Sharpness", DjembeModule::SHARPNESSCV, {1, 1});
		addLabeledInput("Hit", DjembeModule::GAINCV, {0, 0});
		addLabeledInput("StrikeAmt", DjembeModule::STRIKECV, {1, 0});
	}
};

Model *modelDjembe = createModel<DjembeModule, DjembeWidget>("DJEMBE");
