#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct BitcrushModule : CommModule {

	enum ParamIds { SAMPLERATE_PARAM, BITCRUSH_PARAM, NUM_PARAMS };
	enum InputIds { SIGNAL_INPUT, SR_CV, B_CV, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	BitcrushModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("BITCRUSH");
		selfID.typeID = "BITCRUSH";

		inputJacks[BitcrushModule::SIGNAL_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[BitcrushModule::SR_CV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[BitcrushModule::B_CV]->scale = [](float f) { return f / 5.0f; };

		outputJacks[BitcrushModule::SIGNAL_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct BitcrushWidget : CommModuleWidget {

	BitcrushModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	BitcrushWidget(BitcrushModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addLabeledKnob("SR", BitcrushModule::SAMPLERATE_PARAM, {0, 0});
		addLabeledKnob("BIT", BitcrushModule::BITCRUSH_PARAM, {0, 1});

		addLabeledInput("SR CV", BitcrushModule::SR_CV, {0, 3});
		addLabeledInput("B CV", BitcrushModule::B_CV, {0, 2});

		addLabeledInput("IN", BitcrushModule::SIGNAL_INPUT, {0, 1});
		addLabeledOutput("OUT", BitcrushModule::SIGNAL_OUTPUT, {0, 0});
		addModuleTitle("CRUSH");
	}
};

Model *modelBitcrush = createModel<BitcrushModule, BitcrushWidget>("BITCRUSH");
