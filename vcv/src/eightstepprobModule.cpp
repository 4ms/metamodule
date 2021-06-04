#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct EightstepprobModule : CommModule {

	enum ParamIds {
		ENUMS(PROB_PARAMS, 8),
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK_INPUT,
		RESET_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		GATE_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	EightstepprobModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("EIGHTSTEPPROB");
		selfID.typeID = "EIGHTSTEPPROB";
	}
};

struct EightstepprobWidget : CommModuleWidget {

	EightstepprobModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	EightstepprobWidget(EightstepprobModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hptemplate.svg")));

		for (int x = 0; x < 2; x++) {
			for (int y = 0; y < 4; y++) {
				auto currentModule = x + y * 2;
				addLabeledKnob(std::to_string(currentModule + 1), EightstepprobModule::PROB_PARAMS + currentModule, {(float)x, (float)y});
			}
		}

		addLabeledInput("CLOCK", EightstepprobModule::CLOCK_INPUT, {0, 1});
		addLabeledInput("RESET", EightstepprobModule::RESET_INPUT, {0, 0});
		addLabeledOutput("OUT", EightstepprobModule::GATE_OUTPUT, {1, 0});

		addModuleTitle("PROB 8");
	}
};

Model *modelEightstepprob = createModel<EightstepprobModule, EightstepprobWidget>("EIGHTSTEPPROB");
