#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct BandpassfilterModule : CommModule {

	enum ParamIds { CUTOFF_PARAM, Q_PARAM, MODE_PARAM, NUM_PARAMS };
	enum InputIds { SIGNAL_INPUT, CV_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { MODE_LIGHT, NUM_LIGHTS };

	BandpassfilterModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("BANDPASSFILTER");
		selfID.typeID = "BANDPASSFILTER";

		inputJacks[BandpassfilterModule::SIGNAL_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[BandpassfilterModule::CV_INPUT]->scale = [](float f) { return f / 5.0f; };
		outputJacks[BandpassfilterModule::SIGNAL_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct BandpassfilterWidget : CommModuleWidget {

	BandpassfilterModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	BandpassfilterWidget(BandpassfilterModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hpTemplate.svg")));

		addModuleTitle("BPF");

		addLabeledKnob("CUTOFF", BandpassfilterModule::CUTOFF_PARAM, {0, 0});
		addLabeledKnob("Q", BandpassfilterModule::Q_PARAM, {0, 1});
		addLabeledInput("CV", BandpassfilterModule::CV_INPUT, {0, 2});
		addLabeledToggle("MODE", BandpassfilterModule::MODE_LIGHT, BandpassfilterModule::MODE_PARAM, {0, 3});
		addLabeledInput("INPUT", BandpassfilterModule::SIGNAL_INPUT, {0, 1});
		addLabeledOutput("OUTPUT", BandpassfilterModule::SIGNAL_OUTPUT, {0, 0});
	}
};

Model *modelBandpassfilter = createModel<BandpassfilterModule, BandpassfilterWidget>("BANDPASSFILTER");
