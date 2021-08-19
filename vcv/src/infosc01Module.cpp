#include "CommModule.h"
#include "CommWidget.h"
#include "util/math.hh"

struct Infosc01Module : public CommModule {

	enum ParamIds { NUM_PARAMS };
	enum InputIds { NUM_INPUTS };
	enum OutputIds { NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	Infosc01Module()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("INFOSC01");
		selfID.typeID = "INFOSC01";
	}
};

struct Infosc01Widget : CommModuleWidget {

	Infosc01Module *mainModule;

	Label *valueLabel;
	Label *recLabel;

	Infosc01Widget(Infosc01Module *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hpinfosc01.svg")));
	}
};

Model *modelInfosc01 = createModel<Infosc01Module, Infosc01Widget>("INFOSC01");
