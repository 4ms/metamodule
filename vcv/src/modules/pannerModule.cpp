#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct PannerModule : CommModule {

	enum ParamIds { PAN_PARAM, NUM_PARAMS };
	enum InputIds { SIGNAL_INPUT, CV_INPUT, NUM_INPUTS };
	enum OutputIds { LEFT_OUTPUT, RIGHT_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	PannerModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("PANNER");
		selfID.typeID = "PANNER";

		inputJacks[PannerModule::CV_INPUT]->scale = [](float f) { return f / 5.0f; };
	}
};

struct PannerWidget : CommModuleWidget {

	PannerModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	PannerWidget(PannerModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addLabeledKnob("PAN", PannerModule::PAN_PARAM, {0, 0});
		addLabeledInput("CV", PannerModule::CV_INPUT, {0, 3});
		addLabeledInput("IN", PannerModule::SIGNAL_INPUT, {0, 2});
		addLabeledOutput("LEFT", PannerModule::LEFT_OUTPUT, {0, 1});
		addLabeledOutput("RIGHT", PannerModule::RIGHT_OUTPUT, {0, 0});

		addModuleTitle("PAN");
	}
};

Model *modelPanner = createModel<PannerModule, PannerWidget>("PANNER");
