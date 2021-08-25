#include "CommModule.h"
#include "CommWidget.h"
#include "util/math.hh"

struct TemplateModule : CommModule {

	enum ParamIds { NUM_PARAMS };
	enum InputIds { NUM_INPUTS };
	enum OutputIds { NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hptemplate.svg")));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	}
};

Model MODULENAME = createModel<TemplateModule, TemplateWidget>(SLUG);
