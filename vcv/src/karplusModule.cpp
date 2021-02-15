#include "CommModule.h"
#include "CommWidget.h"
#include "util/math.hh"

struct KarplusModule : CommModule {

	enum ParamIds { PITCH_PARAM, DECAY_PARAM, SPREAD_PARAM, NUM_PARAMS };
	enum InputIds { TRIGGER_INPUT, PITCH_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	KarplusModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("KARPLUS");
		selfID.typeID = "KARPLUS";

		inputJacks[KarplusModule::PITCH_INPUT]->scale = [](float f) { return f / 5.0f; };

		outputJacks[KarplusModule::SIGNAL_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct KarplusWidget : CommModuleWidget {

	KarplusModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	KarplusWidget(KarplusModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addModuleTitle("KPLS");
		addLabeledKnob("PITCH", KarplusModule::PITCH_PARAM, {0, 0});
		addLabeledKnob("DECAY", KarplusModule::DECAY_PARAM, {0, 1});
		addLabeledKnob("SPREAD", KarplusModule::SPREAD_PARAM, {0, 2});

		addLabeledInput("V/OCT", KarplusModule::PITCH_INPUT, {0, 2});
		addLabeledInput("TRIG", KarplusModule::TRIGGER_INPUT, {0, 1});
		addLabeledOutput("OUT", KarplusModule::SIGNAL_OUTPUT, {0, 0});
	}
};

Model *modelKarplus = createModel<KarplusModule, KarplusWidget>("KARPLUS");
