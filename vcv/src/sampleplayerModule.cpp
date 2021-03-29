#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct SampleplayerModule : CommModule {

	enum ParamIds { NUM_PARAMS };
	enum InputIds { TRIGGER_INPUT, NUM_INPUTS };
	enum OutputIds { SAMPLE_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	SampleplayerModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("SAMPLEPLAYER");
		selfID.typeID = "SAMPLEPLAYER";
	}
};

struct SampleplayerWidget : CommModuleWidget {

	SampleplayerModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	SampleplayerWidget(SampleplayerModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addModuleTitle("SAMPLER");
		addLabeledInput("TRIGGER", SampleplayerModule::TRIGGER_INPUT, {0, 1});
		addLabeledOutput("OUTPUT", SampleplayerModule::SAMPLE_OUTPUT, {0, 0});
	}
};

Model *modelSampleplayer = createModel<SampleplayerModule, SampleplayerWidget>("SAMPLEPLAYER");
