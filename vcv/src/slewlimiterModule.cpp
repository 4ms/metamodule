#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct SlewlimiterModule : CommModule {

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

	SlewlimiterModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        core = ModuleFactory::create("SLEWLIMITER");
		selfID.typeID = "SLEWLIMITER";
	}
};

struct SlewlimiterWidget : CommModuleWidget {

	SlewlimiterModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	SlewlimiterWidget(SlewlimiterModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
	}
};

Model *modelSlewlimiter = createModel<SlewlimiterModule, SlewlimiterWidget>("SLEWLIMITER");
