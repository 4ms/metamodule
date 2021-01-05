#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/fadeDelayCore.h"
#include "math.hh"

struct FadeDelayModule : CommModule {

	enum ParamIds {
		DELAY_PARAM,
		FEED_PARAM,
		FADE_PARAM,
		MIX_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		DELAY_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		DELAY_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	FadeDelayModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("FADEDELAY");
		selfID.typeID = "FADEDELAY";
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

		addLabeledInput("IN", FadeDelayModule::DELAY_INPUT, {0, 0});
		addLabeledOutput("OUT", FadeDelayModule::DELAY_OUTPUT, {1, 0});
	}
};

Model *modelFadeDelay = createModel<FadeDelayModule, FadeDelayWidget>("fadedelay");
