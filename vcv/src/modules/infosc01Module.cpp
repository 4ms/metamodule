#include "CommModule.h"
#include "CommWidget.h"
#include "infosc01Core.h"
#include "util/math.hh"

struct Infosc01Module : public CommModule {

	enum { NUM_PARAMS = Infosc01Core::NumKnobs };
	enum { NUM_INPUTS = Infosc01Core::NumInJacks };
	enum { NUM_OUTPUTS = Infosc01Core::NumOutJacks };
	enum LightIds { NUM_LIGHTS };

	Infosc01Module()
	{
		configComm(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		core = ModuleFactory::create("INFOSC01");
		selfID.typeID = "INFOSC01";

		constexpr float AxolotiPitchCorrection = 240.f / 256.f;
		inputJacks[Infosc01Core::PitchInJack]->scale = [](float f) {
			return MathTools::constrain(f / (5.f / AxolotiPitchCorrection), -1.f, 1.f);
		};
		inputJacks[Infosc01Core::RangeInJack]->scale = [](float f) { return MathTools::constrain(f / 5.f, -1.f, 1.f); };
		inputJacks[Infosc01Core::FMInJack]->scale = [](float f) { return MathTools::constrain(f / 5.f, -1.f, 1.f); };
		inputJacks[Infosc01Core::ModInJack]->scale = [](float f) { return MathTools::constrain(f / 5.f, -1.f, 1.f); };
		inputJacks[Infosc01Core::AbsInJack]->scale = [](float f) { return MathTools::constrain(f / 5.f, -1.f, 1.f); };
		inputJacks[Infosc01Core::LinInJack]->scale = [](float f) { return MathTools::constrain(f / 5.f, -1.f, 1.f); };
		inputJacks[Infosc01Core::PhaseInJack]->scale = [](float f) { return MathTools::constrain(f / 5.f, -1.f, 1.f); };
		inputJacks[Infosc01Core::PMInJack]->scale = [](float f) { return MathTools::constrain(f / 5.f, -1.f, 1.f); };
		inputJacks[Infosc01Core::ScanInJack]->scale = [](float f) { return MathTools::constrain(f, 0.f, 1.f); };
		inputJacks[Infosc01Core::AddInJack]->scale = [](float f) { return MathTools::constrain(f, 0.f, 1.f); };
		inputJacks[Infosc01Core::ResetInJack]->scale = [](float f) { return MathTools::constrain(f, 0.f, 1.f); };

		outputJacks[Infosc01Core::WaveOutJack]->scale = [](float f) { return f * 5.0f; };
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

		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/16hptemplate.svg")));

		for (int i = 0; i < Infosc01Core::NumKnobs; i++) {
			float x = i % 4;
			float y = i >> 2;
			addLabeledKnob(Infosc01Core::KnobNames[i].cstr(), i, {x, y});
		}

		for (int i = 0; i < Infosc01Core::NumInJacks; i++) {
			float x = (i + 1) % 4;
			float y = (i + 1) >> 2;
			addLabeledInput(Infosc01Core::InJackNames[i].cstr(), i, {x, y});
		}

		addLabeledOutput("Out", Infosc01Core::WaveOutJack, {0, 0});

		addModuleTitle("Infinite Osc");
	}
};

Model *modelInfosc01 = createModel<Infosc01Module, Infosc01Widget>("INFOSC01");
