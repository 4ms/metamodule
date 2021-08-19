#include "CommModule.h"
#include "CommWidget.h"
// #include "infosc01Core.h"
#include "util/math.hh"

struct Infosc01Module : public CommModule {

	enum ParamIds { PitchKnob, TrackKnob, RangeKnob, FMKnob, AbsKnob, PhaseKnob, ModshapeKnob, WaveKnob, NUM_PARAMS };
	enum InputIds {
		PitchInJack,
		RangeInJack,
		FMInJack,
		ModInJack,
		AbsInJack,
		LinInJack,
		PhaseInJack,
		PMInJack,
		ScanInJack,
		AddInJack,
		ResetInJack,
		NUM_INPUTS
	};
	enum OutputIds { WaveOutJack, NUM_OUTPUTS };
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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/12hptemplate.svg")));

		for (int i = 0; i < Infosc01Module::NUM_PARAMS /*Infosc01Core::NumKnobs*/; i++) {
			float x = i % 4;
			float y = i >> 2;
			addLabeledKnob("A" /*Infosc01Core::KnobNames[i].cstr()*/, i, {x, y});
		}

		for (int i = 0; i < Infosc01Module::NUM_INPUTS; i++) {
			float x = i % 4;
			float y = i >> 2;
			addLabeledInput("IN", i, {x, y});
		}

		addLabeledOutput("Out", Infosc01Module::WaveOutJack, {0, 0});

		addModuleTitle("Infinite Osc");
	}
};

Model *modelInfosc01 = createModel<Infosc01Module, Infosc01Widget>("INFOSC01");
