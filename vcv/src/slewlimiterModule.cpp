#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct SlewlimiterModule : CommModule {

	enum ParamIds { RISE_TIME_PARAM, FALL_TIME_PARAM, NUM_PARAMS };
	enum InputIds { SIGNAL_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	SlewlimiterModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("SLEWLIMITER");
		selfID.typeID = "SLEWLIMITER";
	}
};

struct SlewlimiterWidget : CommModuleWidget {

	SlewlimiterModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	SlewlimiterWidget(SlewlimiterModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addModuleTitle("SLEW LIMITER");

		addLabeledKnob("RISE", SlewlimiterModule::RISE_TIME_PARAM, {0, 0});
		addLabeledKnob("FALL", SlewlimiterModule::FALL_TIME_PARAM, {0, 1});

		addLabeledInput("IN", SlewlimiterModule::SIGNAL_INPUT, {0, 1});
		addLabeledOutput("OUT", SlewlimiterModule::SIGNAL_OUTPUT, {0, 0});
	}
};

Model *modelSlewlimiter = createModel<SlewlimiterModule, SlewlimiterWidget>("SLEWLIMITER");
