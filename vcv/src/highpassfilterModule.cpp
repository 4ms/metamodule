#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct HighpassfilterModule : CommModule {

	enum ParamIds { CUTOFF_PARAM, Q_PARAM, NUM_PARAMS };
	enum InputIds { SIGNAL_INPUT, CV_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	HighpassfilterModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("HIGHPASSFILTER");
		selfID.typeID = "HIGHPASSFILTER";
	}
};

struct HighpassfilterWidget : CommModuleWidget {

	HighpassfilterModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	HighpassfilterWidget(HighpassfilterModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addModuleTitle("HPF");
		addLabeledKnob("CUTOFF", HighpassfilterModule::CUTOFF_PARAM, {0, 0});
		addLabeledKnob("Q", HighpassfilterModule::Q_PARAM, {0, 1});

		addLabeledInput("CV", HighpassfilterModule::CV_INPUT, {0, 2});
		addLabeledInput("INPUT", HighpassfilterModule::SIGNAL_INPUT, {0, 1});
		addLabeledOutput("OUTPUT", HighpassfilterModule::SIGNAL_OUTPUT, {0, 0});
	}
};

Model *modelHighpassfilter = createModel<HighpassfilterModule, HighpassfilterWidget>("HIGHPASSFILTER");
