#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct QuantizerModule : CommModule {
	enum ParamIds {
		ENUMS(KEYPARAMS, 12),
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		ENUMS(LIGHTPARAMS, 12),
		NUM_LIGHTS
	};

	QuantizerModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("QUANTIZER");
		selfID.typeID = "QUANTIZER";
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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hpTemplate.svg")));

		for (int i = 0; i < 12; i++) {
			addLabeledToggle(noteNames[i], QuantizerModule::LIGHTPARAMS + i, QuantizerModule::KEYPARAMS + i, {0, i * 0.42f});
		}
	}
};

Model *modelQuantizer = createModel<QuantizerModule, QuantizerWidget>("QUANTIZER");
