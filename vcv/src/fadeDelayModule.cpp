#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/fadeDelayCore.h"
#include "math.hh"

struct FadeDelayModule : CommModule {

	enum ParamIds { DELAY_PARAM, FEED_PARAM, FADE_PARAM, MIX_PARAM, DELAY_CV_PARAM, NUM_PARAMS };
	enum InputIds { DELAY_INPUT, CLOCK_INPUT, DELAY_CV_INPUT, FADE_CV_INPUT, FEED_CV_INPUT, NUM_INPUTS };
	enum OutputIds { DELAY_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	FadeDelayModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("FADEDELAY");
		selfID.typeID = "FADEDELAY";

		inputJacks[FadeDelayModule::DELAY_CV_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[FadeDelayModule::FADE_CV_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[FadeDelayModule::FEED_CV_INPUT]->scale = [](float f) { return f / 5.0f; };
	}
};

struct FadeDelayWidget : CommModuleWidget {

	FadeDelayModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	FadeDelayWidget(FadeDelayModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hpTemplate.svg")));

		addLabeledKnob("DELAY", FadeDelayModule::DELAY_PARAM, {0, 0});
		addLabeledKnob("FEED", FadeDelayModule::FEED_PARAM, {1, 0});
		addLabeledKnob("FADE", FadeDelayModule::FADE_PARAM, {0, 1});
		addLabeledKnob("MIX", FadeDelayModule::MIX_PARAM, {1, 1});
		addLabeledKnob("DELAY CV", FadeDelayModule::DELAY_CV_PARAM, {0, 2});

		addLabeledInput("DELAY", FadeDelayModule::DELAY_CV_INPUT, {0, 2});
		addLabeledInput("FEED", FadeDelayModule::FEED_CV_INPUT, {1, 2});
		addLabeledInput("FADE", FadeDelayModule::FADE_CV_INPUT, {1, 1});
		addLabeledInput("IN", FadeDelayModule::DELAY_INPUT, {0, 0});
		addLabeledInput("CLOCK", FadeDelayModule::CLOCK_INPUT, {0, 1});
		addLabeledOutput("OUT", FadeDelayModule::DELAY_OUTPUT, {1, 0});

		addModuleTitle("FADE DELAY");
	}
};

Model *modelFadeDelay = createModel<FadeDelayModule, FadeDelayWidget>("fadedelay");
