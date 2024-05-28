#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/PI_info.hh"

#include "l4/DCBlock.h"
#include "l4/PeakDetector.h"

namespace MetaModule
{

class PICore : public SmartCoreProcessor<PIInfo> {
	using Info = PIInfo;
	using ThisCore = PICore;
	using enum Info::Elem;

private:
	enum GainRange_t { LOW = 0, MEDIUM = 1, HIGH = 2 };
	enum GateState_t { IDLE, TRIGGERED };

public:
	PICore()
		: ticks(0)
		, sampleRate(48000.f)
		, mode(FOLLOW)
		, dcBlocker(DCBlockerFactor)
		, gateState(IDLE){

		  };

	void update() override {
		ticks++;

		auto scaledInput = 0.f;

		if (auto input = getInput<In>(); input) {
			auto filteredInput = dcBlocker(*input);
			auto maximumGain = readMaximumGain();
			scaledInput = filteredInput * (getState<SensitivityKnob>() * maximumGain);

			checkGateTrigger(scaledInput);
		}

		updateGate(ticks);

		setLED<GateLight>(gateState == TRIGGERED ? 1.f : 0.f);
		setOutput<GateOut>(gateState == TRIGGERED ? gateOutHighVoltage : gateOutLowVoltage);
		setOutput<AudioOut>(scaledInput);
	}

	float readMaximumGain() {
		auto gainMode = Toggle3posHoriz::State_t::LEFT;

		if (gainMode == Toggle3posHoriz::State_t::LEFT) {
			return maximumGains[LOW];
		} else if (gainMode == Toggle3posHoriz::State_t::CENTER) {
			return maximumGains[MEDIUM];
		} else {
			return maximumGains[HIGH];
		}
	}

	void checkGateTrigger(float input) {
		if (gateState == IDLE) {
			if (input >= gateThresholdInV) {
				gateState = TRIGGERED;
				lastGateTriggerInTicks = ticks;
			}
		}
	}

	void updateGate(uint32_t now)
	{
		if (gateState == TRIGGERED) {
			auto gateLengthInTicks = getState<SustainKnob>() * (maximumGateLengthInTicks - minimumGateLengthInTicks) +
									 minimumGateLengthInTicks;

			if (now > lastGateTriggerInTicks + gateLengthInTicks) {
				gateState = IDLE;
			}
		}
	}

	void set_samplerate(float sr) override {
		sampleRate = sr;
		minimumGateLengthInTicks = minimumGateLengthInS * sampleRate;
		maximumGateLengthInTicks = maximumGateLengthInS * sampleRate;
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>(), Info::png_filename);
	// clang-format on

private:
	static constexpr float minimumGateLengthInS = 0.005f;
	static constexpr float maximumGateLengthInS = 0.5f;

	static constexpr float gateOutLowVoltage = 0.f;
	static constexpr float gateOutHighVoltage = 8.f;

	static constexpr float gateThresholdInV = 8.f;

	static constexpr std::array<float, 3> maximumGains{2.f, 20.f, 500.f};

	enum Mode_t { FOLLOW, GEN };

private:
	uint32_t ticks;
	float sampleRate;
	Mode_t mode;
	GateState_t gateState;

	uint32_t minimumGateLengthInTicks;
	uint32_t maximumGateLengthInTicks;
	uint32_t lastGateTriggerInTicks;

private:
	static constexpr float DCBlockerFactor = 0.9995f;
	DCBlock dcBlocker;
};

} // namespace MetaModule
