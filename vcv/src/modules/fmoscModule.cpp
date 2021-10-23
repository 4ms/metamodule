#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct FmoscModule : CommModule {

	enum ParamIds {
		COARSE_TUNE_PARAM,
		INDEX_PARAM,
		RATIO_COARSE_PARAM,
		RATIO_FINE_PARAM,
		SHAPE_PARAM,
		SHAPE_CV_PARAM,
		INDEX_CV_PARAM,
		MIX_PARAM,
		NUM_PARAMS
	};
	enum InputIds { INDEX_INPUT, VOCT_INPUT, SHAPE_CV_INPUT, MIX_CV_INPUT, SEC_VOCT_INPUT, NUM_INPUTS };
	enum OutputIds { MAIN_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	FmoscModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("FMOSC");
		selfID.typeID = "FMOSC";

		inputJacks[FmoscModule::INDEX_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[FmoscModule::VOCT_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[FmoscModule::SEC_VOCT_INPUT]->scale = [](float f) { return f / 5.0f; };
		inputJacks[FmoscModule::SHAPE_CV_INPUT]->scale = [](float f) { return f / 5.0f; };
		outputJacks[FmoscModule::MAIN_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct FmoscWidget : CommModuleWidget {

	FmoscModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	FmoscWidget(FmoscModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/8hptemplate.svg")));

		addLabeledKnob("PITCH", FmoscModule::COARSE_TUNE_PARAM, {0, 0});
		addLabeledKnob("MIX", FmoscModule::MIX_PARAM, {1, 0});
		addLabeledKnob("INDEX", FmoscModule::INDEX_PARAM, {0, 1});
		addLabeledKnob("INDEX CV", FmoscModule::INDEX_CV_PARAM, {1, 1});
		addLabeledKnob("RATIO C", FmoscModule::RATIO_COARSE_PARAM, {0, 2});
		addLabeledKnob("RATIO F", FmoscModule::RATIO_FINE_PARAM, {1, 2});
		addLabeledKnob("SHAPE", FmoscModule::SHAPE_PARAM, {0, 3});
		addLabeledKnob("SHAPE CV", FmoscModule::SHAPE_CV_PARAM, {1, 3});

		addLabeledInput("V/OCT SEC", FmoscModule::SEC_VOCT_INPUT, {1, 2});
		addLabeledInput("MIX", FmoscModule::MIX_CV_INPUT, {0, 1});

		addLabeledInput("V/OCT PRI", FmoscModule::VOCT_INPUT, {0, 2});
		addLabeledInput("INDEX", FmoscModule::INDEX_INPUT, {1, 1});
		addLabeledInput("SHAPE CV", FmoscModule::SHAPE_CV_INPUT, {0, 0});

		addLabeledOutput("OUT", FmoscModule::MAIN_OUTPUT, {1, 0});

		addModuleTitle("FM");
	}
};

Model *modelFmosc = createModel<FmoscModule, FmoscWidget>("FMOSC");
