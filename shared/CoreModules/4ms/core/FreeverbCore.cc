#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/Freeverb_info.hh"
#include "processors/allpass.h"
#include "processors/comb.h"
#include "processors/tools/dcBlock.h"
#include "util/math.hh"

namespace MetaModule
{

class FreeverbCore : public SmartCoreProcessor<FreeverbInfo> {
	using Info = FreeverbInfo;
	using ThisCore = FreeverbCore;
	using enum Info::Elem;

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
		float dry = getInput<InputIn>().value_or(0.f);

		auto add_cv_and_pot = [](std::optional<float> cv, float pot) {
			const float cv_val = cv.value_or(0.f) / 5.f; // range: -1 .. 1 for CV -5V .. +5V
			return std::clamp(pot + cv_val, 0.f, 1.f);
		};

		if (auto size = add_cv_and_pot(getInput<SizeCvIn>(), getState<SizeKnob>()); prev_size != size) {
			prev_size = size;
			setSize(size);
		}

		if (auto damp = add_cv_and_pot(getInput<DampCvIn>(), getState<DampKnob>()); prev_damp != damp) {
			prev_damp = damp;
			setDamp(damp);
		}

		if (auto fb = add_cv_and_pot(getInput<FeedbackCvIn>(), getState<FeedbackKnob>()); prev_fb != fb) {
			prev_fb = fb;
			setFeedback(fb);
		}

		float wet = 0;
		for (auto &comb : combFilter) {
			wet += comb.process(dry);
		}

		wet /= static_cast<float>(numComb);

		for (auto &allpass : apFilter) {
			wet = allpass.process(wet);
		}

		const auto mix = add_cv_and_pot(getInput<MixCvIn>(), getState<MixKnob>());

		setOutput<Out>(dcblock.update(MathTools::interpolate3(dry, wet, mix)));
	}

	void setSize(float val) {
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
	}

	void setDamp(float val) {
		for (auto &comb : combFilter) {
			comb.setDamp(val);
		}
	}

	void setFeedback(float val) {
		for (auto &comb : combFilter) {
			comb.setFeedback(MathTools::map_value(val, 0.0f, 1.0f, 0.8f, 0.99f));
		}
	}

	void set_samplerate(float sr) override {
		//TODO
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>(), Info::png_filename);
	// clang-format on

private:
	static const int numComb = 8;
	static const int numAll = 4;

	static constexpr int allTuning[numAll] = {1248, 812, 358, 125};
	static constexpr int combTuning[numComb] = {3000, 4003, 4528, 5217, 1206, 2108, 3337, 5003};

	int currentAllTunning[numAll];
	int currentCombTuning[numComb];

	std::array<Comb<6000>, numComb> combFilter;
	std::array<AllPass<6000>, numAll> apFilter;

	float prev_size{0};
	float prev_damp{0};
	float prev_fb{0};

	DCBlock dcblock;
};

} // namespace MetaModule
