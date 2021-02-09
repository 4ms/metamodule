#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct Gateseq8Module : CommModule {

	enum ParamIds { ENUMS(STEP_PARAMS, 8), NUM_PARAMS };
	enum InputIds { CLK_INPUT, RESET_INPUT, NUM_INPUTS };
	enum OutputIds { GATE_OUTPUT, ENUMS(STEP_OUTS, 8), NUM_OUTPUTS };
	enum LightIds { ENUMS(STEP_LIGHTS, 8), NUM_LIGHTS };

	Gateseq8Module()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("GATESEQ8");
		selfID.typeID = "GATESEQ8";

		outputJacks[Gateseq8Module::GATE_OUTPUT]->scale = [](float f) { return f * 5.0f; };
		for (int i = 0; i < 8; i++) {
			outputJacks[Gateseq8Module::STEP_OUTS+i]->scale = [](float f) { return f * 5.0f; };
		}
	}
};

struct Gateseq8Widget : CommModuleWidget {

	Gateseq8Module *mainModule;

	Label *valueLabel;
	Label *recLabel;

	Gateseq8Widget(Gateseq8Module *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/12hpTemplate.svg")));

		for (int i = 0; i < 8; i++) {
			addLabeledToggle(std::to_string(i + 1),
							 Gateseq8Module::STEP_LIGHTS + i,
							 Gateseq8Module::STEP_PARAMS + i,
							 {0, 1 + static_cast<float>((7 - i) * 0.7f)});

			addLabeledOutput("", Gateseq8Module::STEP_OUTS + i, {2, static_cast<float>(7 - i) * 0.88f});
		}

		addModuleTitle("GATE 8");

		addLabeledInput("CLK", Gateseq8Module::CLK_INPUT, {0, 0});
		addLabeledInput("RESET", Gateseq8Module::RESET_INPUT, {1, 0});
		addLabeledOutput("OUT", Gateseq8Module::GATE_OUTPUT, {2, 0});
	}
};

Model *modelGateseq8 = createModel<Gateseq8Module, Gateseq8Widget>("GATESEQ8");
