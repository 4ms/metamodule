#include "CommModule.h"
#include "CommWidget.h"
#include "util/math.hh"

struct TemplateModule : CommModule {

	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	TemplateModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
        core = ModuleFactory::create(SLUG);
		selfID.typeID = SLUG;
	}
};

struct TemplateWidget : CommModuleWidget {

	TemplateModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	TemplateWidget(TemplateModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hp.svg")));
	}
};

Model MODULENAME = createModel<TemplateModule, TemplateWidget>(SLUG);
