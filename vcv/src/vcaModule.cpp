#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "math.hh"

struct VCAModule : CommModule {

	enum ParamIds {
		PREGAIN_PARAM,
		POSTGAIN_PARAM,
		OFFSET_PARAM,
		CVAMT_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL_INPUT,
		CV_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		VCA_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	VCAModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("VCA");
		selfID.typeID = "VCA";

		inputJacks[VCAModule::CV_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[VCAModule::SIGNAL_INPUT]->scale = [](float f) { return f / 5.0f; };
		outputJacks[VCAModule::VCA_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct VCAWidget : CommModuleWidget {

	VCAModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	VCAWidget(VCAModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hptemplate.svg")));

		addLabeledKnob("PRE", VCAModule::PREGAIN_PARAM, {0, 0});
		addLabeledKnob("POST", VCAModule::POSTGAIN_PARAM, {1, 0});
		addLabeledKnob("OFFSET", VCAModule::OFFSET_PARAM, {0, 1});
		addLabeledKnob("CV", VCAModule::CVAMT_PARAM, {1, 1});

		addLabeledInput("IN", VCAModule::SIGNAL_INPUT, {0, 0});
		addLabeledInput("CV", VCAModule::CV_INPUT, {1, 0});
		addLabeledOutput("OUT", VCAModule::VCA_OUTPUT, {0, 1});

		addModuleTitle("VCA");
	}
};

Model *modelVCA = createModel<VCAModule, VCAWidget>("vca");
