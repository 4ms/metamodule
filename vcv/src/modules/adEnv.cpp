#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleFactory.hh"
#include "math.hh"

// Todo: separate out the "core" from this and put it in CoreModules/
struct adModule : public CommModule {

	enum ParamIds { ATTACK_KNOB, DECAY_KNOB, A_SHAPE, D_SHAPE, NUM_PARAMS };
	enum InputIds { GATE_INPUT, ATTACK_CV, DECAY_CV, ASHAPE_CV, DSHAPE_CV, NUM_INPUTS };
	enum OutputIds { ENV_OUTPUT, EOA_OUTPUT, EOD_OUTPUT, NUM_OUTPUTS };
	enum LightIds { REC_LIGHT, NUM_LIGHTS };

	adModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("ADENV");
		selfID.typeID = "ADENV";

		inputJacks[adModule::ATTACK_CV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[adModule::DECAY_CV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[adModule::ASHAPE_CV]->scale = [](float f) { return f / 5.0f; };
		inputJacks[adModule::DSHAPE_CV]->scale = [](float f) { return f / 5.0f; };

		outputJacks[adModule::ENV_OUTPUT]->scale = [](float f) { return f * 5.0f; };
		outputJacks[adModule::EOA_OUTPUT]->scale = [](float f) { return f * 5.0f; };
		outputJacks[adModule::EOD_OUTPUT]->scale = [](float f) { return f * 5.0f; };
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
			mainModule->updateDisplay = [&]() { this->recLabel->text = this->mainModule->DEBUGSTR; };
		}

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hptemplate.svg")));

		addLabeledInput("GATE", adModule::GATE_INPUT, {0, 1});
		addLabeledOutput("OUT", adModule::ENV_OUTPUT, {1, 1});
		addLabeledOutput("EOA", adModule::EOA_OUTPUT, {0, 0});
		addLabeledOutput("EOD", adModule::EOD_OUTPUT, {1, 0});

		addLabeledInput("A CV", adModule::ATTACK_CV, {1, 6});
		addLabeledInput("D CV", adModule::DECAY_CV, {1, 5});
		addLabeledInput("A_S CV", adModule::ASHAPE_CV, {1, 4});
		addLabeledInput("D_S CV", adModule::DSHAPE_CV, {1, 3});

		addLabeledKnob("A", adModule::ATTACK_KNOB, {0, 0});
		addLabeledKnob("D", adModule::DECAY_KNOB, {0, 1});
		addLabeledKnob("A SHAPE", adModule::A_SHAPE, {0, 2});
		addLabeledKnob("D SHAPE", adModule::D_SHAPE, {0, 3});
		addModuleTitle("A/D");
	}
};

Model *modelAD = createModel<adModule, adWidget>("ad_envelope");
