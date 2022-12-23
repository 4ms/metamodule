#include "CoreModules/coreProcessor.h"
#include "CoreModules/info/EnOsc_info.hh"
#include "CoreModules/moduleFactory.hh"

#include "CoreModules/enosc/polyptic_oscillator.hh"
#include "enosc/ui.hh"

class EnOscCore : public CoreProcessor {
	using Info = EnOscInfo;
	using ThisCore = EnOscCore;

	enum { kBlockSize = 1 };
	enum { kUiUpdateRate = 120 };

public:
	EnOscCore() = default;
	// : enosc{params} {
	// }

	void update() override {
		// Low-priority thread:
		enosc.Process();

		// High-priority at SR/BR:
		enosc.Poll();

		Buffer<Frame, kBlockSize> block;
		enosc.osc().Process(block);
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
		return 0.f;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	Ui<kUiUpdateRate, kBlockSize> enosc;
	// Parameters params;
	// PolypticOscillator<1> enosc;
};
