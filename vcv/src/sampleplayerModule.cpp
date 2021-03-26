#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct SampleplayerModule : CommModule {

	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

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
	}
};

Model *modelSampleplayer = createModel<SampleplayerModule, SampleplayerWidget>("SAMPLEPLAYER");
