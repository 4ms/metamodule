#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct QuantizerModule : CommModule {
	enum ParamIds { ENUMS(KEYPARAMS, 12), NUM_PARAMS };
	enum InputIds { SIGNAL_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { ENUMS(LIGHTPARAMS, 12), NUM_LIGHTS };

	QuantizerModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("QUANTIZER");
		selfID.typeID = "QUANTIZER";

		inputJacks[QuantizerModule::SIGNAL_INPUT]->scale = [](float f) { return f / 5.0f; };
		outputJacks[QuantizerModule::SIGNAL_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct QuantizerWidget : CommModuleWidget {

	const std::string noteNames[12] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};

	QuantizerModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	QuantizerWidget(QuantizerModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hptemplate.svg")));

		for (int i = 0; i < 12; i++) {
			addLabeledToggle(
				noteNames[i], QuantizerModule::LIGHTPARAMS + i, QuantizerModule::KEYPARAMS + i, {0, i * 0.49f + 0.57f});
		}

		addLabeledInput("IN", QuantizerModule::SIGNAL_INPUT, {0, 0});
		addLabeledOutput("OUT", QuantizerModule::SIGNAL_OUTPUT, {1, 0});

		addModuleTitle("QUANTIZER");
	}
};

Model *modelQuantizer = createModel<QuantizerModule, QuantizerWidget>("QUANTIZER");
