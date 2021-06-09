#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct MultilfoModule : CommModule {

	enum ParamIds {
		RATE_PARAM,
		PHASE_PARAM,
		PW_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		FM_INPUT,
		PHASE_INPUT,
		PW_INPUT,
		RESET_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		SIN_OUTPUT,
		SAW_OUTPUT,
		ISAW_OUTPUT,
		PULSE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	MultilfoModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        core = ModuleFactory::create("MULTILFO");
		selfID.typeID = "MULTILFO";

		inputJacks[MultilfoModule::PHASE_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[MultilfoModule::PW_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[MultilfoModule::FM_INPUT]->scale = [](float f) { return f / 5.0f; };

		outputJacks[MultilfoModule::SIN_OUTPUT]->scale = [](float f) { return f * 5.0f; };
		outputJacks[MultilfoModule::SAW_OUTPUT]->scale = [](float f) { return f * 5.0f; };
		outputJacks[MultilfoModule::ISAW_OUTPUT]->scale = [](float f) { return f * 5.0f; };
		outputJacks[MultilfoModule::PULSE_OUTPUT]->scale = [](float f) { return f * 5.0f; };

	}
};

struct MultilfoWidget : CommModuleWidget {

	MultilfoModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	MultilfoWidget(MultilfoModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hptemplate.svg")));

		addModuleTitle("Multi LFO");
		addLabeledKnob("RATE",MultilfoModule::RATE_PARAM,{0,0},0.5f);
		addLabeledKnob("PHASE",MultilfoModule::PHASE_PARAM,{1,0},0.0f);
		addLabeledKnob("PW", MultilfoModule::PW_PARAM, {0,1});

		addLabeledInput("RATE",MultilfoModule::FM_INPUT,{0,2});
		addLabeledInput("PHASE",MultilfoModule::PHASE_INPUT,{1,2});
		addLabeledInput("PW",MultilfoModule::PW_INPUT,{1,3});
		addLabeledInput("RESET",MultilfoModule::RESET_INPUT,{0,3});

		addLabeledOutput("SINE",MultilfoModule::SIN_OUTPUT,{0,1});
		addLabeledOutput("PULSE",MultilfoModule::PULSE_OUTPUT,{1,1});
		addLabeledOutput("SAW",MultilfoModule::SAW_OUTPUT,{0,0});
		addLabeledOutput("ISAW",MultilfoModule::ISAW_OUTPUT,{1,0});
	}
};

Model *modelMultilfo = createModel<MultilfoModule, MultilfoWidget>("MULTILFO");
