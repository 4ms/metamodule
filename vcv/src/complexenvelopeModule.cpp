#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct ComplexenvelopeModule : CommModule {

	enum ParamIds {
		ATTACK_PARAM,
		HOLD_PARAM,
		DECAY_PARAM,
		SUSTAIN_PARAM,
		RELEASE_PARAM,
		ATTACK_CURVE_PARAM,
		DECAY_CURVE_PARAM,
		RELEASE_CURVE_PARAM,
		NUM_PARAMS
	};
	enum InputIds { GATE_INPUT, ATTACK_CV, HOLD_CV, DECAY_CV, SUSTAIN_CV, RELEASE_CV, NUM_INPUTS };
	enum OutputIds {
		SIGNAL_OUTPUT,
		ATTACK_OUTPUT,
		HOLD_OUTPUT,
		DECAY_OUTPUT,
		SUSTAIN_OUTPUT,
		RELEASE_OUTPUT,
		NUM_OUTPUTS
	};
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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hptemplate.svg")));

		addLabeledKnob("ATTACK", ComplexenvelopeModule::ATTACK_PARAM, {0, 0});
		addLabeledKnob("DECAY", ComplexenvelopeModule::DECAY_PARAM, {0, 1});
		addLabeledKnob("RELEASE", ComplexenvelopeModule::RELEASE_PARAM, {0, 2});

		addLabeledKnob("CURVE", ComplexenvelopeModule::ATTACK_CURVE_PARAM, {1, 0});
		addLabeledKnob("CURVE", ComplexenvelopeModule::DECAY_CURVE_PARAM, {1, 1});
		addLabeledKnob("CURVE", ComplexenvelopeModule::RELEASE_CURVE_PARAM, {1, 2});

		addLabeledKnob("HOLD", ComplexenvelopeModule::HOLD_PARAM, {0, 3});
		addLabeledKnob("SUSTAIN", ComplexenvelopeModule::SUSTAIN_PARAM, {0, 4});

		addLabeledOutput("OUT", ComplexenvelopeModule::SIGNAL_OUTPUT, {0, 0});
		addLabeledInput("IN", ComplexenvelopeModule::GATE_INPUT, {0, 1});

		addLabeledInput("ATTACK CV", ComplexenvelopeModule::ATTACK_CV, {2, 6});
		addLabeledInput("DECAY CV", ComplexenvelopeModule::DECAY_CV, {2, 5});
		addLabeledInput("HOLD CV", ComplexenvelopeModule::HOLD_CV, {2, 3});
		addLabeledInput("SUSTAIN CV", ComplexenvelopeModule::SUSTAIN_CV, {2, 2});
		addLabeledInput("RELEASE CV", ComplexenvelopeModule::RELEASE_CV, {2, 4});

		addLabeledOutput("ATTACK OUT", ComplexenvelopeModule::ATTACK_OUTPUT, {3, 6});
		addLabeledOutput("DECAY OUT", ComplexenvelopeModule::DECAY_OUTPUT, {3, 5});
		addLabeledOutput("HOLD OUT", ComplexenvelopeModule::HOLD_OUTPUT, {3, 3});
		addLabeledOutput("SUSTAIN OUT", ComplexenvelopeModule::SUSTAIN_OUTPUT, {3, 2});
		addLabeledOutput("RELEASE OUT", ComplexenvelopeModule::RELEASE_OUTPUT, {3, 4});

		addModuleTitle("COMPLEX EG");
	}
};

Model *modelComplexenvelope = createModel<ComplexenvelopeModule, ComplexenvelopeWidget>("COMPLEXENVELOPE");
