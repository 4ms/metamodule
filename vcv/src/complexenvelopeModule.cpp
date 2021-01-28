#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct ComplexenvelopeModule : CommModule {

	enum ParamIds { ATTACK_PARAM, HOLD_PARAM, DECAY_PARAM, SUSTAIN_PARAM, RELEASE_PARAM, NUM_PARAMS };
	enum InputIds { GATE_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	ComplexenvelopeModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("COMPLEXENVELOPE");
		selfID.typeID = "COMPLEXENVELOPE";

		outputJacks[ComplexenvelopeModule::SIGNAL_OUTPUT]->scale = [](float f) { return f * 10.0f; };
	}
};

struct ComplexenvelopeWidget : CommModuleWidget {

	ComplexenvelopeModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	ComplexenvelopeWidget(ComplexenvelopeModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hpTemplate.svg")));

		addLabeledKnob("ATTACK", ComplexenvelopeModule::ATTACK_PARAM, {0, 0});
		addLabeledKnob("HOLD", ComplexenvelopeModule::HOLD_PARAM, {1, 0});
		addLabeledKnob("DECAY", ComplexenvelopeModule::DECAY_PARAM, {0, 1});
		addLabeledKnob("SUSTAIN", ComplexenvelopeModule::SUSTAIN_PARAM, {1, 1});
		addLabeledKnob("RELEASE", ComplexenvelopeModule::RELEASE_PARAM, {0, 2});

		addLabeledOutput("OUT", ComplexenvelopeModule::SIGNAL_OUTPUT, {0, 0});
		addLabeledInput("IN", ComplexenvelopeModule::GATE_INPUT, {0, 1});
	}
};

Model *modelComplexenvelope = createModel<ComplexenvelopeModule, ComplexenvelopeWidget>("COMPLEXENVELOPE");
