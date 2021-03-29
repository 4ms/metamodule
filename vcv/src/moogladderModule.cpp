#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct MoogladderModule : CommModule {

	enum ParamIds { CUTOFF_PARAM, Q_PARAM, NUM_PARAMS };
	enum InputIds { SIGNAL_INPUT, CV_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	MoogladderModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("MOOGLADDER");
		selfID.typeID = "MOOGLADDER";
	}
};

struct MoogladderWidget : CommModuleWidget {

	MoogladderModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	MoogladderWidget(MoogladderModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addModuleTitle("MOOG");
		addLabeledInput("CV", MoogladderModule::CV_INPUT,{0,2});
		addLabeledInput("IN", MoogladderModule::SIGNAL_INPUT,{0,1});
		addLabeledOutput("OUT",MoogladderModule::SIGNAL_OUTPUT,{0,0});
	}
};

Model *modelMoogladder = createModel<MoogladderModule, MoogladderWidget>("MOOGLADDER");
