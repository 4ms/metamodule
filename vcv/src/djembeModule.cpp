#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct DjembeModule : CommModule {

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

	DjembeModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        core = ModuleFactory::create("DJEMBE");
		selfID.typeID = "DJEMBE";
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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
	}
};

Model *modelDjembe = createModel<DjembeModule, DjembeWidget>("DJEMBE");
