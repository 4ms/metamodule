#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/moduleTypes.h"
#include "math.hh"

struct LogicModule : CommModule {

	enum ParamIds {
		NUM_PARAMS
	};
	enum InputIds {
		INPUT1_INPUT,
		INPUT2_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		AND_OUTPUT,
		OR_OUTPUT,
		XOR_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	LogicModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("LOGIC");
		selfID.typeID = "LOGIC";
	}

	~LogicModule()
	{
	}
};

struct LogicWidget : CommModuleWidget {

	LogicModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	LogicWidget(LogicModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/4hpTemplate.svg")));

		addLabeledInput("IN1", LogicModule::INPUT1_INPUT, {0, 4});
		addLabeledInput("IN2", LogicModule::INPUT2_INPUT, {0, 3});
		addLabeledOutput("AND", LogicModule::AND_OUTPUT, {0, 2});
		addLabeledOutput("OR", LogicModule::OR_OUTPUT, {0, 1});
		addLabeledOutput("XOR", LogicModule::XOR_OUTPUT, {0, 0});
	}
};

Model *modelLogic = createModel<LogicModule, LogicWidget>("logic");
