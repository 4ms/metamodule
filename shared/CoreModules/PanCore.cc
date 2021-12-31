#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/Pan_info.hh"
#include "CoreModules/moduleFactory.hh"

#include "util/math.hh"

class PanCore : public CoreProcessor {
	using Info = PanInfo;
	using ThisCore = PanCore;

public:
	PanCore() = default;

	void update() override {
		float finalPan = MathTools::constrain(panPosition + panCV, 0.0f, 1.0f);
		leftOut = signalInput * (1.0f - finalPan);
		rightOut = signalInput * finalPan;
	}

	void set_param(int param_id, float val) override {
		if (param_id == Info::KnobPan)
			panPosition = val;
	}

	void set_input(int input_id, float val) override {
		switch (input_id) {
			case Info::InputIn:
				signalInput = val;
				break;
			case Info::InputCv:
				panCV = val;
		}
	}

	float get_output(int output_id) const override {
		switch (output_id) {
			case Info::OutputOut_1:
				return leftOut;

			case Info::OutputOut_2:
				return leftOut;
		}
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
	float panPosition = 0;
	float signalInput = 0;
	float leftOut = 0;
	float rightOut = 0;
	float panCV = 0;
};
