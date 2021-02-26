#include "CommModule.h"
#include "CommWidget.h"
#include "CoreModules/reverbCore.h"
#include "math.hh"

// #define DEBUG_SHOW_ALL_KNOBS
#define DEBUG_DISPLAY_RATIO_TEXT

struct ReverbModule : CommModule {

	enum ParamIds {
		SIZE_PARAM,
		DAMP_PARAM,
		MIX_PARAM,
		TIME_PARAM,
		APRATIO,
		CRATIO,
#ifdef DEBUG_SHOW_ALL_KNOBS
		AP1,
		AP2,
		AP3,
		AP4,
		C1,
		C2,
		C3,
		C4,
		C5,
		C6,
		C7,
		C8,
#endif
		NUM_PARAMS
	};
	enum InputIds { SIGNAL_INPUT, NUM_INPUTS };
	enum OutputIds { SIGNAL_OUTPUT, NUM_OUTPUTS };
	enum LightIds { NUM_LIGHTS };

	ReverbModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("REVERB");
		selfID.typeID = "REVERB";

		inputJacks[ReverbModule::SIGNAL_INPUT]->scale = [](float f) { return f / 5.0f; };
		outputJacks[ReverbModule::SIGNAL_OUTPUT]->scale = [](float f) { return f * 5.0f; };
	}

#ifdef DEBUG_DISPLAY_RATIO_TEXT
	virtual void process(const ProcessArgs &args)
	{
		CommModule::process(args);
		DEBUGSTR = "AllPass: ";
		for (int i = 0; i < 4; i++) {
			DEBUGSTR += std::to_string((int)static_cast<ReverbCore *>(core.get())->getAllpassTuning(i)) + " ";
		}
		DEBUGSTR += "\nCombs:  ";
		for (int i = 0; i < 8; i++) {
			DEBUGSTR += std::to_string((int)static_cast<ReverbCore *>(core.get())->getCombTuning(i)) + " ";
		}
		updateDisplay();
	}
#endif
};

struct ReverbWidget : CommModuleWidget {

	ReverbModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	ReverbWidget(ReverbModule *module)
	{
		setModule(module);
		mainModule = module;

		if (mainModule != nullptr) {
			mainModule->updateDisplay = [&]() { this->valueLabel->text = this->mainModule->DEBUGSTR; };
		}

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hpTemplate.svg")));

		valueLabel = createWidget<Label>(mm2px(Vec(0, 90)));
		valueLabel->color = rack::color::BLACK;
		valueLabel->text = "";
		valueLabel->fontSize = 10;
		addChild(valueLabel);

		addModuleTitle("VERB");
		addLabeledKnob("SIZE", ReverbModule::SIZE_PARAM, {0, 0});
		addLabeledKnob("TIME", ReverbModule::TIME_PARAM, {1, 0});
		addLabeledKnob("DAMP", ReverbModule::DAMP_PARAM, {2, 0});
		addLabeledKnob("MIX", ReverbModule::MIX_PARAM, {3, 0});

		addLabeledKnob("AP Ratio", ReverbModule::APRATIO, {0, 1});
		addLabeledKnob("Comb Ratio", ReverbModule::CRATIO, {1, 1});

#ifdef DEBUG_SHOW_ALL_KNOBS
		addLabeledKnob("AP1", ReverbModule::AP1, {0, 2}, 1.f);
		addLabeledKnob("AP2", ReverbModule::AP2, {1, 2}, 1.f);
		addLabeledKnob("AP3", ReverbModule::AP3, {2, 2}, 1.f);
		addLabeledKnob("AP4", ReverbModule::AP4, {3, 2}, 1.f);

		addLabeledKnob("C1", ReverbModule::C1, {0, 3}, 1.f);
		addLabeledKnob("C2", ReverbModule::C2, {1, 3}, 1.f);
		addLabeledKnob("C3", ReverbModule::C3, {2, 3}, 1.f);
		addLabeledKnob("C4", ReverbModule::C4, {3, 3}, 1.f);
		addLabeledKnob("C5", ReverbModule::C5, {0, 4}, 1.f);
		addLabeledKnob("C6", ReverbModule::C6, {1, 4}, 1.f);
		addLabeledKnob("C7", ReverbModule::C7, {2, 4}, 1.f);
		addLabeledKnob("C8", ReverbModule::C8, {3, 4}, 1.f);
#endif
		addLabeledInput("IN", ReverbModule::SIGNAL_INPUT, {0, 0});
		addLabeledOutput("OUT", ReverbModule::SIGNAL_OUTPUT, {1, 0});
	}
};

Model *modelReverb = createModel<ReverbModule, ReverbWidget>("REVERB");
