#pragma once
#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/EnOsc_info.hh"
#include "CoreModules/moduleFactory.hh"
#include "util/math.hh"
#include "util/math_tables.hh"

class EnOscCore : public CoreProcessor {
	using Info = EnOscInfo;

public:
	EnOscCore() = default;

	void update() override {
	}

	void set_param(int param_id, float val) override {
	}

	void set_input(int input_id, float val) override {
	}

	float get_output(int output_id) const override {
		return 0.f;
	}

	void set_samplerate(float sr) override {
	}

	float get_led_brightness(int led_id) const override {
		switch (led_id) {
			case Info::SwitchLearn * 3 + 0:
				return 0.75f;
				break;
			case Info::SwitchLearn * 3 + 1:
				return 0.40f;
				break;
			case Info::SwitchLearn * 3 + 2:
				return 0.f;
				break;
			case Info::SwitchFreeze * 3 + 0:
				return 0.00f;
				break;
			case Info::SwitchFreeze * 3 + 1:
				return 0.20f;
				break;
			case Info::SwitchFreeze * 3 + 2:
				return 0.9f;
				break;

			default:
				return 0.f;
		}
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<EnOscCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, description, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	// local vars here
};
