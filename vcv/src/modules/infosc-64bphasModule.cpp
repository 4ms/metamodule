#include "CommModule.h"
#include "CommWidget.h"
#include "infosc-64bphasCore.hpp"
#include "util/math.hh"

struct Infosc64bphaseModule : public CommModule {

	enum { NUM_PARAMS = Infosc64bphaseCore::NumKnobs };
	enum { NUM_INPUTS = Infosc64bphaseCore::NumInJacks };
	enum { NUM_OUTPUTS = Infosc64bphaseCore::NumOutJacks };
	enum LightIds { OctaveLight, DampedLight, GenLight, IndexrelatedLight, NUM_LIGHTS };

	Infosc64bphaseModule()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("INFOSC64");
		selfID.typeID = "INFOSC64";

		constexpr float AxolotiPitchCorrection = 240.f / 256.f;
		inputJacks[Infosc64bphaseCore::PitchInJack]->scale = [](float f) {
			return MathTools::constrain(f / (5.f / AxolotiPitchCorrection), -1.f, 1.f);
		};
		outputJacks[Infosc64bphaseCore::WaveOutJack]->scale = [](float f) { return f * 5.0f; };

		configParam(Infosc64bphaseCore::PitchKnob, 0.f, 1.0f, 0.5f, "Pitch");
		configParam(Infosc64bphaseCore::TrackKnob, 0.f, 1.0f, 0.5f, "Track");
		configParam(Infosc64bphaseCore::RangeKnob, 0.f, 1.0f, 0.5f, "Range");
		configParam(Infosc64bphaseCore::StackNumber, 0.f, 1.0f, 0.125f, "Stack#", "", 0.f, 16.f, 0.f);
		configParam(Infosc64bphaseCore::ShiftKnob, 0.f, 1.0f, 0.5f, "Shift");
		configParam(Infosc64bphaseCore::RateKnob, 0.f, 1.0f, 0.5f, "Rate");
		configParam(Infosc64bphaseCore::ModKnob, 0.f, 1.0f, 0.5f, "Mod");
	}

	void process(const CommModule::ProcessArgs &args) override
	{
		CommModule::process(args);
		lights[OctaveLight].setBrightness(params[Infosc64bphaseCore::OctaveToggle].getValue());
		lights[DampedLight].setBrightness(params[Infosc64bphaseCore::DampedToggle].getValue());
		lights[GenLight].setBrightness(params[Infosc64bphaseCore::GenMomentary].getValue());
		lights[IndexrelatedLight].setBrightness(params[Infosc64bphaseCore::IndexrelatedToggle].getValue());
	}
};

struct Infosc64bphaseWidget : CommModuleWidget {

	Infosc64bphaseModule *mainModule;

	Label *valueLabel;
	Label *recLabel;

	Infosc64bphaseWidget(Infosc64bphaseModule *module)
	{
		setModule(module);
		mainModule = module;

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hptemplate.svg")));

		for (int i = 0; i < Infosc64bphaseCore::NumKnobs; i++) {
			float x = i % 4;
			float y = i >> 2;
			if (i == Infosc64bphaseCore::OctaveToggle)
				addLabeledToggle(Infosc64bphaseCore::KnobNames[i].cstr(), Infosc64bphaseModule::OctaveLight, i, {x, y});
			else if (i == Infosc64bphaseCore::DampedToggle)
				addLabeledToggle(Infosc64bphaseCore::KnobNames[i].cstr(), Infosc64bphaseModule::DampedLight, i, {x, y});
			else if (i == Infosc64bphaseCore::GenMomentary)
				addLabeledMomentary(Infosc64bphaseCore::KnobNames[i].cstr(), Infosc64bphaseModule::GenLight, i, {x, y});
			else if (i == Infosc64bphaseCore::IndexrelatedToggle)
				addLabeledToggle(
					Infosc64bphaseCore::KnobNames[i].cstr(), Infosc64bphaseModule::IndexrelatedLight, i, {x, y});
			else
				addLabeledKnob(Infosc64bphaseCore::KnobNames[i].cstr(), i, {x, y});
		}

		for (int i = 0; i < Infosc64bphaseCore::NumInJacks; i++) {
			float x = (i + 1) % 4;
			float y = (i + 1) >> 2;
			addLabeledInput(Infosc64bphaseCore::InJackNames[i].cstr(), i, {x, y});
		}

		addLabeledOutput("Out", Infosc64bphaseCore::WaveOutJack, {0, 0});

		addModuleTitle("Infinite Osc 64");
	}
};

Model *modelInfosc64bphas = createModel<Infosc64bphaseModule, Infosc64bphaseWidget>("INFOSC64");
