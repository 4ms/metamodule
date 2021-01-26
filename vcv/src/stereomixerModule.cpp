#include "CommModule.h"
#include "CommWidget.h"
#include "math.hh"

struct StereomixerModule : CommModule {

	enum ParamIds { ENUMS(VOLUME_PARAM, 4), ENUMS(PAN_PARAM, 4), NUM_PARAMS };
	enum InputIds { ENUMS(SIGNAL_INPUTS, 8), NUM_INPUTS };
	enum OutputIds { LEFT_OUTPUT, RIGHT_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	StereomixerModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("STEREOMIXER");
		selfID.typeID = "STEREOMIXER";
	}
};

struct StereomixerWidget : CommModuleWidget {

	StereomixerModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	StereomixerWidget(StereomixerModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hpTemplate.svg")));

		for (int i = 0; i < 4; i++) {
			int channelNum = i + 1;
			addLabeledKnob(
				"LEVEL" + std::to_string(channelNum), StereomixerModule::VOLUME_PARAM + i, {static_cast<float>(i), 0});
			addLabeledKnob(
				"PAN" + std::to_string(channelNum), StereomixerModule::PAN_PARAM + i, {static_cast<float>(i), 1});
			addLabeledInput("IN " + std::to_string(channelNum) + " L",
							StereomixerModule::SIGNAL_INPUTS + i,
							{static_cast<float>(i), 3});
			addLabeledInput("IN " + std::to_string(channelNum) + " R",
							StereomixerModule::SIGNAL_INPUTS + i + 4,
							{static_cast<float>(i), 2});
		}

		addLabeledOutput("L OUT", StereomixerModule::LEFT_OUTPUT, {3, 1});
		addLabeledOutput("R OUT", StereomixerModule::RIGHT_OUTPUT, {3, 0});
		addModuleTitle("STEREO MIXER");
	}
};

Model *modelStereomixer = createModel<StereomixerModule, StereomixerWidget>("STEREOMIXER");
