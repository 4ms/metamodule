#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "math.hh"

//Todo: separate out the "core" from this and put it in CoreModules/
struct adModule : public CommModule {

	enum ParamIds {
		ATTACK_KNOB,
		DECAY_KNOB,
		NUM_PARAMS
	};
	enum InputIds {
		GATE_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		ENV_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		REC_LIGHT,
		NUM_LIGHTS
	};

	adModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("ADENV");
		selfID.typeID = "ADENV";

		outputJacks[adModule::ENV_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct adWidget : CommModuleWidget {

	adModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	adWidget(adModule *module)
	{
		setModule(module);
		mainModule = module;

		if (mainModule != nullptr) {
			mainModule->updateDisplay = [&]() {
				this->recLabel->text = this->mainModule->DEBUGSTR;
			};
		}

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hpTemplate.svg")));

		addLabeledInput("GATE", adModule::GATE_INPUT, {0, 1});
		addLabeledOutput("OUT", adModule::ENV_OUTPUT, {0, 0});

		addLabeledKnob("A", adModule::ATTACK_KNOB, {0, 0});
		addLabeledKnob("D", adModule::DECAY_KNOB, {0, 1});
	}
};

Model *modelAD = createModel<adModule, adWidget>("ad_envelope");
