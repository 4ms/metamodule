#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/LPF_info.hh"
#include "processors/lpf.h"
#include "processors/moogLadder.h"
#include "util/math.hh"
#include "util/math_tables.hh"

namespace MetaModule
{

class LPFCore : public SmartCoreProcessor<LPFInfo> {
	using Info = LPFInfo;
	using ThisCore = LPFCore;
	using enum Info::Elem;

public:
	LPFCore() = default;

	void update() override {
		auto input = std::clamp(getInput<InputIn>().value_or(std::rand() / (RAND_MAX * 10)), -10.f, 10.f) / 10.f;

		moog.cutoff.setValue(getState<CutoffKnob>());
		moog.q.setValue(getState<QKnob>() * 25.f);

		lpf.cutoff.setValue(getState<CutoffKnob>() * 12000.f + 1.f);
		lpf.q.setValue(getState<QKnob>() * 25.f + 0.1f);

		auto moogOut = moog.update(input) * 10.f;
		auto lpfOut = lpf.update(input) * 10.f;

		setOutput<Out>(getState<ModeButton>() == LatchingButton::State_t::DOWN ? lpfOut : moogOut);
		setLED<ModeButton>(getState<ModeButton>() == LatchingButton::State_t::DOWN ? 1.f : 0.f);
	}

	void set_samplerate(float sr) {
		moog.sampleRate.setValue(sr);
		lpf.sampleRate.setValue(sr);
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>(), Info::png_filename);
	// clang-format on

private:
	int mode = 1;
	MoogLadder moog;
	LowPassFilter lpf;
	float signalIn = 0;
	float signalOut = 0;
	float baseFrequency = 1.0;
	float cvInput = 0;
	float filterQ = 0;
	// float cvAmount = 0;
};

} // namespace MetaModule
