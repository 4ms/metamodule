#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct ReverbModule : CommModule {

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

	ReverbModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        core = ModuleFactory::create("REVERB");
		selfID.typeID = "REVERB";
	}
};

struct ReverbWidget : CommModuleWidget {

	ReverbModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	ReverbWidget(ReverbModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
	}
};

Model *modelReverb = createModel<ReverbModule, ReverbWidget>("REVERB");
