#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/BuffMult_info.hh"
#include <algorithm>

namespace MetaModule
{

class BuffMultCore : public CoreProcessor {
	using Info = BuffMultInfo;
	using ThisCore = BuffMultCore;

public:
	BuffMultCore() = default;

	void update() override {
	}

	void set_param(int param_id, float val) override {
	}

	void set_input(int input_id, float val) override {
		if (input_id < 0 || input_id > 1)
			return;
		in[input_id] = val;
	}

	void mark_all_inputs_unpatched() override {
		is_second_input_patched = false;
		in[0] = 0.f;
		in[1] = 0.f;
	}
	void mark_input_unpatched(int input_id) override {
		if (input_id == 0)
			in[0] = 0.f;
		if (input_id == 1) {
			in[1] = 0.f;
			is_second_input_patched = false;
		}
	}
	void mark_input_patched(int input_id) override {
		if (input_id == 1)
			is_second_input_patched = true;
	}

	float get_output(int output_id) const override {
		if (output_id < 0)
			return 0.f;
		if (output_id < 3 || !is_second_input_patched)
			return in[0];
		if (output_id < 6)
			return in[1];
		return 0.f;
	}

	void set_samplerate(float sr) override {
	}

	float get_led_brightness(int led_id) const override {
		switch (led_id) {
			case Info::LedInput_1_Led:
				return std::clamp(in[0], 0.f, 1.f);
			case Info::LedInput_2_Led:
				return std::clamp(is_second_input_patched ? in[1] : in[0], 0.f, 1.f);
			default:
				return 0.f;
		}
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>(), Info::png_filename);
	// clang-format on

private:
	float in[2];
	bool is_second_input_patched = false;
};

} // namespace MetaModule
