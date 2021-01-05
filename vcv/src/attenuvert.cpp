#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/attCore.h"
#include "math.hh"

struct AttModule : CommModule {

	enum ParamIds {
		LEVEL1_PARAM,
		LEVEL2_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		INPUT1_INPUT,
		INPUT2_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	AttModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("ATTENVERT2");
		selfID.typeID = "ATTENVERT2";
	}
};

struct AttWidget : CommModuleWidget {

	AttModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	AttWidget(AttModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hpTemplate.svg")));

		addLabeledKnob("LEVEL", AttModule::LEVEL1_PARAM, {0, 0});
		addLabeledKnob("LEVEL", AttModule::LEVEL2_PARAM, {0, 1});

		addLabeledInput("IN 1", AttModule::INPUT1_INPUT, {0, 3});
		addLabeledInput("IN 2", AttModule::INPUT2_INPUT, {0, 2});

		addLabeledOutput("OUT 1", AttModule::OUT1_OUTPUT, {0, 1});
		addLabeledOutput("OUT 2", AttModule::OUT2_OUTPUT, {0, 0});
	}
};

Model *modelAtt = createModel<AttModule, AttWidget>("attenuvert");
