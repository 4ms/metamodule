#include "CoreModules/coreProcessor.h"
#include "CoreModules/moduleFactory.hh"
#include "info/Source_info.hh"
#include "util/math.hh"

namespace MetaModule
{

class SourceCore : public CoreProcessor {
	using Info = SourceInfo;
	using ThisCore = SourceCore;

public:
	SourceCore() = default;

	void update(void) override {
	}

	void set_param(int const param_id, const float val) override {
		switch (param_id) {
			case Info::Knob_1:
				output1 = MathTools::map_value(val, 0.0f, 1.0f, -1.0f, 1.0f);
				break;
			case Info::Knob_2:
				output2 = MathTools::map_value(val, 0.0f, 1.0f, -1.0f, 1.0f);
				break;
		}
	}

	void set_samplerate(const float sr) override {
	}

	void set_input(const int input_id, const float val) override {
	}

	float get_output(const int output_id) const override {
		switch (output_id) {
			case Info::Output_1:
				return output1;
				break;
			case Info::Output_2:
				return output2;
				break;
		}
		return 0;
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
	float output1;
	float output2;
};

} // namespace MetaModule
