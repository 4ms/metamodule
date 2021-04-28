#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "math.hh"

struct CrossfadeModule : public CommModule {

	enum ParamIds { CROSSFADE_PARAM, NUM_PARAMS };
	enum InputIds { INPUT1_INPUT, INPUT2_INPUT, CV_INPUT, NUM_INPUTS };
	enum OutputIds { CROSSFADE_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	CrossfadeModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("XFADE");
		selfID.typeID = "XFADE";

		inputJacks[CrossfadeModule::CV_INPUT]->scale = [](float f) { return f / 5.0f; };
	}
};

struct CrossfadeWidget : CommModuleWidget {

	CrossfadeModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	CrossfadeWidget(CrossfadeModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hpTemplate.svg")));

		addLabeledKnob("FADE", CrossfadeModule::CROSSFADE_PARAM, {0, 0});

		addLabeledInput("CV", CrossfadeModule::CV_INPUT, {0, 3});

		addLabeledInput("IN1", CrossfadeModule::INPUT1_INPUT, {0, 2});
		addLabeledInput("IN2", CrossfadeModule::INPUT2_INPUT, {0, 1});

		addLabeledOutput("OUT", CrossfadeModule::CROSSFADE_OUTPUT, {0, 0});
		addModuleTitle("FADE");
	}
};

Model *modelCrossfade = createModel<CrossfadeModule, CrossfadeWidget>("crossfade");
