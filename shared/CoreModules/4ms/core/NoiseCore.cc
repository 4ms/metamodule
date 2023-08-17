#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/Noise_info.hh"
#include "util/math.hh"

namespace MetaModule
{

class NoiseCore : public CoreProcessor {
	using Info = NoiseInfo;
	using ThisCore = NoiseCore;

public:
	NoiseCore() = default;

	void update() override {
		whiteNoise = MathTools::randomNumber(-1.0f, 1.0f);
		//FIXME: make pink noise
		pinkNoise = whiteNoise;
	}

	void set_param(int param_id, float val) override {
	}

	void set_input(int input_id, float val) override {
	}

	float get_output(int output_id) const override {
		if (output_id == Info::OutputWhite)
			return whiteNoise;
		if (output_id == Info::OutputPink)
			return pinkNoise;
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
	float whiteNoise = 0;
	float pinkNoise = 0;
};

} // namespace MetaModule
