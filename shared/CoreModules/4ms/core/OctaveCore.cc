#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/Octave_info.hh"
#include "util/math.hh"

namespace MetaModule
{

class OctaveCore : public CoreProcessor {
	using Info = OctaveInfo;
	using ThisCore = OctaveCore;

public:
	OctaveCore() = default;

	void update() override {
		auto cvSum = MathTools::constrain<float>(octaveOffset + cvInput, 0.0f, 1.0f);
		int octave = MathTools::map_value(cvSum, 0.0f, 1.0f, 0, 5);
		voltOutput = voltInput + octave / 5.0f;
	}

	void set_param(int param_id, float val) override {
		if (param_id == Info::KnobOctave)
			octaveOffset = val;
	}

	void set_input(int input_id, float val) override {
		if (input_id == Info::InputInput)
			voltInput = val;
		if (input_id == Info::InputCv)
			cvInput = val;
	}

	float get_output(int output_id) const override {
		return output_id == Info::OutputOut ? voltOutput : 0.f;
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
	float octaveOffset = 0;
	float cvInput = 0;
	float voltInput = 0;
	float voltOutput = 0;
};

} // namespace MetaModule
