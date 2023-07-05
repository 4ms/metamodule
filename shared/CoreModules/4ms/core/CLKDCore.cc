#include "CoreModules/coreProcessor.h"
#include "info/CLKD_info.hh"
#include "CoreModules/moduleFactory.hh"
#include "processors/tools/clockPhase.h"
#include "util/math.hh"

using namespace MathTools;

class CLKDCore : public CoreProcessor {
	using Info = CLKDInfo;
	using ThisCore = CLKDCore;

public:
	CLKDCore() = default;

	void update() override {
		float finalDivide = constrain(clockDivideOffset + clockDivideCV, 0.0f, 1.0f);
		cp.setDivide(map_value(finalDivide, 0.0f, 1.0f, 1.0f, 16.99f));
		cp.update();
		if ((cp.getWrappedPhase() < pulseWidth) && clockInit) {
			clockOutput = 1;
		} else {
			clockOutput = 0;
		}
	}

	void set_param(int param_id, float val) override {
		switch (param_id) {
			case Info::KnobDivide:
				clockDivideOffset = val;
				break;
		}
	}

	void set_input(int input_id, float val) override {
		switch (input_id) {
			case Info::InputClk_In:
				cp.updateClock(val);
				clockInit = true;
				break;
			case Info::InputCv:
				clockDivideCV = val;
				break;
		}
	}

	float get_output(int output_id) const override {
		return clockOutput;
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
	float pulseWidth = 0.5f;
	int clockOutput = 0;
	bool clockInit = false;
	float clockDivideOffset = 0;
	float clockDivideCV = 0;

	ClockPhase cp;
};
