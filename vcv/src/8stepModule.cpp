#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct 8stepModule : CommModule {

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

	8stepModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        core = ModuleFactory::create("8STEP");
		selfID.typeID = "8STEP";
	}
};

struct 8stepWidget : CommModuleWidget {

	8stepModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	8stepWidget(8stepModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
	}
};

Model *model8step = createModel<8stepModule, 8stepWidget>("8STEP");
