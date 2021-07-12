#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct BipolarsourceModule : CommModule {

	enum ParamIds { VALUE1_PARAM, VALUE2_PARAM, NUM_PARAMS };
	enum InputIds { NUM_INPUTS };
	enum OutputIds { OUTPUT1_OUTPUT, OUTPUT2_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	BipolarsourceModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("BIPOLARSOURCE");
		selfID.typeID = "BIPOLARSOURCE";

		outputJacks[BipolarsourceModule::OUTPUT1_OUTPUT]->scale = [](float f) { return f * 5.0f; };
		outputJacks[BipolarsourceModule::OUTPUT2_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct BipolarsourceWidget : CommModuleWidget {

	BipolarsourceModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	BipolarsourceWidget(BipolarsourceModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
		addModuleTitle("Bipolar");

		addLabeledKnob("1", BipolarsourceModule::VALUE1_PARAM, {0, 0}, 0);
		addLabeledKnob("2", BipolarsourceModule::VALUE2_PARAM, {0, 1}, 0);

		addLabeledOutput("1", BipolarsourceModule::OUTPUT1_OUTPUT, {0, 1});
		addLabeledOutput("2", BipolarsourceModule::OUTPUT2_OUTPUT, {0, 0});
	}
};

Model *modelBipolarsource = createModel<BipolarsourceModule, BipolarsourceWidget>("BIPOLARSOURCE");
