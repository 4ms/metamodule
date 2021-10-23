#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct NoiseModule : CommModule {

	enum ParamIds { NUM_PARAMS };
	enum InputIds { NUM_INPUTS };
	enum OutputIds { WHITE_NOISE_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	NoiseModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("NOISE");
		selfID.typeID = "NOISE";

		outputJacks[NoiseModule::WHITE_NOISE_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}
};

struct NoiseWidget : CommModuleWidget {

	NoiseModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	NoiseWidget(NoiseModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
		addModuleTitle("NOISE");

		addLabeledOutput("WHITE", NoiseModule::WHITE_NOISE_OUTPUT, {0, 0});
	}
};

Model *modelNoise = createModel<NoiseModule, NoiseWidget>("NOISE");
