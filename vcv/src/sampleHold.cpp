#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "math.hh"

struct SampleHoldModule : CommModule {

	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		INPUT1_INPUT,
		SAMPLE1_INPUT,
		INPUT2_INPUT,
		SAMPLE2_INPUT,
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

	SampleHoldModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("SAMPHOLD");
		selfID.typeID = "SAMPHOLD";

		outputJacks[SampleHoldModule::OUT1_OUTPUT]->scale = [](float f) { return f * 5.0f; };
		outputJacks[SampleHoldModule::OUT2_OUTPUT]->scale = [](float f) { return f * 5.0f; };

		inputJacks[SampleHoldModule::INPUT1_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[SampleHoldModule::INPUT2_INPUT]->scale = [](float f) { return f / 5.0f; };
	}
};

struct SampleHoldWidget : CommModuleWidget {

	SampleHoldModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	SampleHoldWidget(SampleHoldModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hpTemplate.svg")));

		addLabeledInput("IN 1", SampleHoldModule::INPUT1_INPUT, {0, 5});
		addLabeledInput("SAMP", SampleHoldModule::SAMPLE1_INPUT, {0, 4});
		addLabeledInput("IN 2", SampleHoldModule::INPUT2_INPUT, {0, 3});
		addLabeledInput("SAMP", SampleHoldModule::SAMPLE2_INPUT, {0, 2});
		addLabeledOutput("OUT 1", SampleHoldModule::OUT1_OUTPUT, {0, 1});
		addLabeledOutput("OUT 2", SampleHoldModule::OUT2_OUTPUT, {0, 0});
	}
};

Model *modelSampleHold = createModel<SampleHoldModule, SampleHoldWidget>("samplehold");
