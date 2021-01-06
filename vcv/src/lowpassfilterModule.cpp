#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct LowpassfilterModule : CommModule {

	enum ParamIds {
		CUTOFF_PARAM,
		RES_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		SIGNAL_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		SIGNAL_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	LowpassfilterModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        core = ModuleFactory::create("LOWPASSFILTER");
		selfID.typeID = "LOWPASSFILTER";

		inputJacks[LowpassfilterModule::SIGNAL_INPUT]->scale = [](float f) { return f / 5.0f; };
		outputJacks[LowpassfilterModule::SIGNAL_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct LowpassfilterWidget : CommModuleWidget {

	LowpassfilterModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	LowpassfilterWidget(LowpassfilterModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addLabeledKnob("CUT",LowpassfilterModule::CUTOFF_PARAM,{0,0});
		addLabeledKnob("RES",LowpassfilterModule::RES_PARAM,{0,1});

		addLabeledOutput("OUT",LowpassfilterModule::SIGNAL_OUTPUT,{0,0});
		addLabeledInput("IN",LowpassfilterModule::SIGNAL_INPUT,{0,1});
	}
};

Model *modelLowpassfilter = createModel<LowpassfilterModule, LowpassfilterWidget>("LOWPASSFILTER");
