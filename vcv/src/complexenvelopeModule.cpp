#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct ComplexenvelopeModule : CommModule {

	enum ParamIds { NUM_PARAMS };
	enum InputIds { GATE_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	ComplexenvelopeModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("COMPLEXENVELOPE");
		selfID.typeID = "COMPLEXENVELOPE";
	}
};

struct ComplexenvelopeWidget : CommModuleWidget {

	ComplexenvelopeModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	ComplexenvelopeWidget(ComplexenvelopeModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));

		addLabeledOutput("OUT", ComplexenvelopeModule::SIGNAL_OUTPUT, {0, 0});
		addLabeledInput("IN", ComplexenvelopeModule::GATE_INPUT, {0, 1});
	}
};

Model *modelComplexenvelope = createModel<ComplexenvelopeModule, ComplexenvelopeWidget>("COMPLEXENVELOPE");
