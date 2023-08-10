#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/Freeverb_info.hh"
#include "processors/allpass.h"
#include "processors/comb.h"
#include "processors/tools/dcBlock.h"
#include "util/math.hh"

namespace MetaModule
{

class FreeverbCore : public CoreProcessor {
	using Info = FreeverbInfo;
	using ThisCore = FreeverbCore;

public:
	FreeverbCore() {
		for (int i = 0; i < numAll; i++) {
			apFilter[i].setLength(allTuning[i]);
			apFilter[i].setFeedback(0.6f);
			apFilter[i].setFadeSpeed(0.001f);
			currentAllTunning[i] = allTuning[i];
		}

		for (int i = 0; i < numComb; i++) {
			combFilter[i].setFeedback(0);
			combFilter[i].setLength(combTuning[i]);
			currentCombTuning[i] = combTuning[i];
		}
	}

	void update() override {
		float wetSignal = 0;

		for (int i = 0; i < numComb; i++) {
			wetSignal += combFilter[i].process(signalIn);
		}

		wetSignal /= static_cast<float>(numComb);

		for (int i = 0; i < numAll; i++) {
			wetSignal = apFilter[i].process(wetSignal);
		}

		signalOut = dcblock.update(MathTools::interpolate3(signalIn, wetSignal, mix));
	}

	void set_param(int param_id, float val) override {
		switch (param_id) {
			case 0: // size
				for (int i = 0; i < numComb; i++) {
					currentCombTuning[i] = combTuning[i] * val;
					if (currentCombTuning[i] < 1)
						currentCombTuning[i] = 1;
					combFilter[i].setLength(currentCombTuning[i]);
				}
				for (int i = 0; i < numAll; i++) {
					currentAllTunning[i] = allTuning[i] * val;
					if (currentAllTunning[i] < 1)
						currentAllTunning[i] = 1;
					apFilter[i].setLength(currentAllTunning[i]);
				}
				break;
			case 1: // damp
				for (int i = 0; i < numComb; i++) {
					combFilter[i].setDamp(val);
				}
				break;
			case 2:
				mix = val;
				break;
			case 3: // time
				for (int i = 0; i < numComb; i++) {
					combFilter[i].setFeedback(MathTools::map_value(val, 0.0f, 1.0f, 0.8f, 0.99f));
				}
				break;
		}
	}

	void set_input(int input_id, float val) override {
		switch (input_id) {
			case Info::InputInput:
				signalIn = val;
				break;
			//TODO handle other CV inputs
			default:
				break;
		}
	}

	float get_output(int output_id) const override {
		return signalOut;
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
	float signalIn = 0;
	float signalOut = 0;

	static const int numComb = 8;
	static const int numAll = 4;

	static constexpr int allTuning[numAll] = {1248, 812, 358, 125};
	static constexpr int combTuning[numComb] = {3000, 4003, 4528, 5217, 1206, 2108, 3337, 5003};

	int currentAllTunning[numAll];
	int currentCombTuning[numComb];

	Comb<6000> combFilter[numComb];
	AllPass<6000> apFilter[numAll];

	DCBlock dcblock;

	float mix = 0;
};

} // namespace MetaModule
