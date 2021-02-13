#include "CommModule.h"
#include "CommWidget.h"
#include "util/math.hh"

struct KarplusModule : CommModule {

	enum ParamIds { NUM_PARAMS };
	enum InputIds { NUM_INPUTS };
	enum OutputIds { NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	KarplusModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("KARPLUS");
		selfID.typeID = "KARPLUS";
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
/*
		addModuleTitle("KPLS");
		addLabeledKnob("PITCH",KarplusModule::PITCH_PARAM,{0,0});
		addLabeledKnob("DECAY",KarplusModule::DECAY_PARAM,{0,1});

		addLabeledInput("V/OCT",KarplusModule::PITCH_INPUT,{0,2});
		addLabeledInput("TRIG",KarplusModule::TRIGGER_INPUT,{0,1});
		addLabeledOutput("OUT",KarplusModule::SIGNAL_OUTPUT,{0,0});
		*/
	}
};

Model *modelKarplus = createModel<KarplusModule, KarplusWidget>("KARPLUS");
