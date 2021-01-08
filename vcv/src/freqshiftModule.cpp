#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct FreqshiftModule : CommModule {

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

	FreqshiftModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        core = ModuleFactory::create("FREQSHIFT");
		selfID.typeID = "FREQSHIFT";
	}
};

struct FreqshiftWidget : CommModuleWidget {

	FreqshiftModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	FreqshiftWidget(FreqshiftModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
	}
};

Model *modelFreqshift = createModel<FreqshiftModule, FreqshiftWidget>("FREQSHIFT");
