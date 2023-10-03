#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/Seq4_info.hh"
#include "processors/stepsequencer.h"
#include "util/math.hh"

namespace MetaModule
{

class Seq4Core : public CoreProcessor {
	using Info = Seq4Info;
	using ThisCore = Seq4Core;

public:
	Seq4Core() = default;

	void update() override {
		seq.update();
	}

	void set_param(int param_id, float val) override {
		if (param_id < Info::NumKnobs)
			seq.setStep(param_id, val);
	}

	void set_input(int input_id, float val) override {
		if (input_id == Info::InputClock)
			seq.updateClock(val);
	}

	float get_output(int output_id) const override {
		if (output_id == Info::OutputOut)
			return seq.output * CVOutVolts;
		return 0.f;
	}

	void set_samplerate(float sr) override {
	}

	float get_led_brightness(int led_id) const override {
		return 0.f;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	StepSequencer seq{4};
	static constexpr float CVOutVolts = 10.f;
};

} // namespace MetaModule
