#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/comparatorCore.h"
#include "math.hh"

struct ComparatorModule : CommModule {

	enum ParamIds {
		THRESHOLD_PARAM,
		CV_ATT_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL_INPUT,
		CV_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		SIGNAL_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	ComparatorModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("COMPARATOR");
		selfID.typeID = "COMPARATOR";

		inputJacks[ComparatorModule::SIGNAL_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[ComparatorModule::CV_INPUT]->scale = [](float f) { return f / 5.0f; };
		outputJacks[ComparatorModule::SIGNAL_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct ComparatorWidget : CommModuleWidget {

	ComparatorModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	ComparatorWidget(ComparatorModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addLabeledKnob("OFFSET", ComparatorModule::THRESHOLD_PARAM, {0, 0});
		addLabeledKnob("CV", ComparatorModule::CV_ATT_PARAM, {0, 1});

		addLabeledOutput("OUT", ComparatorModule::SIGNAL_OUTPUT, {0, 0});

		addLabeledInput("IN", ComparatorModule::SIGNAL_INPUT, {0, 2});
		addLabeledInput("CV", ComparatorModule::CV_INPUT, {0, 1});
	}
};

Model *modelComparator = createModel<ComparatorModule, ComparatorWidget>("comparator");
