#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct Gateseq16Module : CommModule {

	enum ParamIds { ENUMS(STEP_PARAMS, 16), NUM_PARAMS };
	enum InputIds { CLOCK_INPUT, RESET_INPUT, NUM_INPUTS };
	enum OutputIds { GATE_OUTPUT, NUM_OUTPUTS };
	enum LightIds { ENUMS(STEP_LIGHTS, 16), NUM_LIGHTS };

	Gateseq16Module()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("GATESEQ16");
		selfID.typeID = "GATESEQ16";
	}
};

struct Gateseq16Widget : CommModuleWidget {

	Gateseq16Module *mainModule;

	Label *valueLabel;
	Label *recLabel;

	Gateseq16Widget(Gateseq16Module *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hptemplate.svg")));

		addModuleTitle("GATE 16");

		for (int y = 0; y < 8; y++) {
			for (int x = 0; x < 2; x++) {
				addLabeledToggle(std::to_string(x * 8 + y + 1),
								 Gateseq16Module::STEP_LIGHTS + (x * 8 + y),
								 Gateseq16Module::STEP_PARAMS + (x * 8 + y),
								 {static_cast<float>(x * 2), 1 + static_cast<float>((7 - y) * 0.7f)});
			}
		}

		addLabeledInput("CLOCK", Gateseq16Module::CLOCK_INPUT, {0, 0});
		addLabeledInput("RESET", Gateseq16Module::RESET_INPUT, {1, 0});
		addLabeledOutput("OUTPUT", Gateseq16Module::GATE_OUTPUT, {3, 0});
	}
};

Model *modelGateseq16 = createModel<Gateseq16Module, Gateseq16Widget>("GATESEQ16");
