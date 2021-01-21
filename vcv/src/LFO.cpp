#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "math.hh"

struct LfoModule : CommModule {

	enum ParamIds { FREQ_KNOB, SHAPE_KNOB, LEVEL_KNOB, NUM_PARAMS };
	enum InputIds { FM_INPUT, RESET_INPUT, NUM_INPUTS };
	enum OutputIds { LFO_OUTPUT, NUM_OUTPUTS };
	enum LightIds { REC_LIGHT, NUM_LIGHTS };

	LfoModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("LFOSINE");
		selfID.typeID = "LFOSINE";

		outputJacks[LfoModule::LFO_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct LfoWidget : CommModuleWidget {

	LfoModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	LfoWidget(LfoModule *module)
	{
		setModule(static_cast<Module *>(module));
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/adjTest.svg")));

		addLabeledKnob("SPEED", LfoModule::FREQ_KNOB, {0, 0});
		addLabeledKnob("PHASE", LfoModule::SHAPE_KNOB, {0, 1});
		addLabeledKnob("LEVEL", LfoModule::LEVEL_KNOB, {0, 2});

		addLabeledInput("FM", LfoModule::FM_INPUT, {0, 2});
		addLabeledInput("RESET", LfoModule::RESET_INPUT, {0, 1});

		addLabeledOutput("OUT", LfoModule::LFO_OUTPUT, {0, 0});
	}
};

Model *modelLFO = createModel<LfoModule, LfoWidget>("lfo");
