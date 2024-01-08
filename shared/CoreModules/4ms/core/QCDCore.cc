#include "CoreModules/4ms/info/QCD_info.hh"
#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"

#include "CoreModules/4ms/core/helpers/EdgeDetector.h"
#include "CoreModules/4ms/core/helpers/FlipFlop.h"

namespace MetaModule
{

class QCDCore : public SmartCoreProcessor<QCDInfo> {
	using Info = QCDInfo;
	using ThisCore = QCDCore;
	using enum Info::Elem;

private: 	
	enum operation_t {MULT, DIV};
	
	struct factorType_t
	{
		operation_t operation;
		uint32_t factor;
	};

	enum invMode_t {DELAY, INVERTED, SHUFFLE};
	enum edge_t {FALLING, RISING};
	enum outputState_t {LOW, HIGH};

public:
	QCDCore()
		: triggerDetector(1.0f, 2.0f), ticks(0), clockInCounter(0), invMode(DELAY), clockOutState(LOW) {
			set_samplerate(48000.f);
	}

	void update() override {
		auto now = ++ticks;

		factor = readFactorCV();
		pulsewidth = readPulsewidthCV();
		triggerLengthInTicks = calculateTriggerlength(pulsewidth);
		invMode = readInvMode();

		if (auto clockInputValue = getInput<ClkIn1In>(); clockInputValue) {
			if (triggerEdgeDetector(triggerDetector(*clockInputValue))) {
				calculateClockInPeriod(now);
				calculateClockOutPeriod(now);

				if(factor.operation == DIV) {
					clockInCounter++;

					if(clockInCounter == factor.factor)
					{
						setClockOut(now);
						clockInCounter = 0;
					}
				} else {
					setClockOut(now);
				}
			}
		}

		updateClockOut(now);
		updateInvOut(now);
	}

	void set_samplerate(float sr) override {
		timeStepInS = 1.f /sr;

		triggerLengthMinimumInTicks = uint32_t(std::round(triggerLengthMinimumInS / timeStepInS));
	}

private:
	factorType_t readFactorCV() {
		auto selector = getState<DivMult1Knob>();

		if(auto selectorCV = getInput<DivMultCv1JackIn>(); selectorCV) {
			selector += (getState<DivMultCv1Knob>() * 2.0f - 1.0f) * *selectorCV / 10.0f;
			selector = std::clamp(selector, 0.0f, 1.0f);
		}

		return clockFactor[uint32_t(std::round(selector * (clockFactor.size() - 1)))];
	}

	float readPulsewidthCV() {
		auto pulsewidth = getState<GatePw1Knob>();

		if(auto pulsewidthCV = getInput<GatePwCv1In>(); pulsewidthCV) {
			pulsewidth += (getState<GatePwAtt1Knob>() * 2.0f - 1.0f) * *pulsewidthCV / 10.0f;
			pulsewidth = std::clamp(pulsewidth, 0.0f, 1.0f);
		}

		return pulsewidth;
	}

	invMode_t readInvMode() {
		return SHUFFLE;
	}

	uint32_t calculateTriggerlength(float pulsewidth) {
		if(clockOut.periodInTicks) {
			return triggerLengthMinimumInTicks + uint32_t(std::round(pulsewidth * (*clockOut.periodInTicks - 2 * triggerLengthMinimumInTicks)));
		} else {
			return triggerLengthMinimumInTicks;
		}
	}

	void calculateClockInPeriod(uint32_t timestampInTicks) {
		if(clockIn.lastEventInTicks) {
			//clockIn.periodInTicks = *clockIn.lastEventInTicks - timestampInTicks;
			if(clockIn.lastEventInTicks < timestampInTicks) {
				clockIn.periodInTicks = timestampInTicks - *clockIn.lastEventInTicks;
			} else { //overflow
				clockIn.periodInTicks = std::numeric_limits<decltype(ticks)>::max() - *clockIn.lastEventInTicks;
				clockIn.periodInTicks = *clockIn.periodInTicks + timestampInTicks;
			}
		}

		clockIn.lastEventInTicks = timestampInTicks;
	}

	void calculateClockOutPeriod(uint32_t timestampInTicks) {
		if(clockIn.periodInTicks) {
			if(factor.operation == MULT) {
				clockOut.periodInTicks = *clockIn.periodInTicks / factor.factor;
			} else if (factor.operation == DIV){
				clockOut.periodInTicks = *clockIn.periodInTicks * factor.factor;
			} else {
				clockOut.periodInTicks.reset();
			}
		}
	}

	void setClockOut(uint32_t timestampInTicks) {
		if (clockOutState == LOW) {
			setOutput<Out1Out>(5.f);
			setLED<Out1Light>(1.0f);
			updateInvOut(timestampInTicks, RISING);

			clockOut.lastEventInTicks = timestampInTicks;
			clockOutState = HIGH;
		}
	}

	void updateClockOut(uint32_t timestampInTicks) {
		if(clockOut.periodInTicks) {
			if (!clockOut.lastEventInTicks) {
				clockOut.lastEventInTicks = 0;
			}

			if (timestampInTicks >= (*clockOut.lastEventInTicks + *clockOut.periodInTicks)) {
				if(clockOutState == LOW) {
					setOutput<Out1Out>(outputHighVoltageLevel);
					setLED<Out1Light>(1.f);
					updateInvOut(timestampInTicks, RISING);

					clockOut.lastEventInTicks = timestampInTicks;

					clockOutState = HIGH;
				}
			}

			if (timestampInTicks >= (*clockOut.lastEventInTicks + triggerLengthInTicks)) {
				if(clockOutState == HIGH) {
					setOutput<Out1Out>(0.f);
					setLED<Out1Light>(0.f);
					updateInvOut(timestampInTicks, FALLING);

					clockOutState = LOW;
				}
			}
		}
	}

	void updateInvOut(uint32_t timestamp) {
		if ((invMode == DELAY) || (invMode == SHUFFLE)) {
			if(clockInvOut.lastEventInTicks) {
				if(timestamp >= (*clockInvOut.lastEventInTicks + triggerLengthMinimumInTicks)) {
					setOutput<InvOut1Out>(0.f);
					setLED<Inv1Light>(0.f);
					clockInvOut.lastEventInTicks.reset();
				}
			}
		}
	}

	void updateInvOut(uint32_t timestamp, edge_t edgeType) {
		if(invMode == INVERTED) {
			if(edgeType == RISING) {
				setOutput<InvOut1Out>(0.f);
				setLED<Inv1Light>(0.f);
				clockInvOut.lastEventInTicks.reset();
			} else {
				setOutput<InvOut1Out>(outputHighVoltageLevel);
				setLED<Inv1Light>(1.f);
				clockInvOut.lastEventInTicks = timestamp;
			}
		} else if(invMode == DELAY) {
			if(edgeType == FALLING) {
				setOutput<InvOut1Out>(outputHighVoltageLevel);
				setLED<Inv1Light>(1.f);
				clockInvOut.lastEventInTicks = timestamp;
			}
		} else if(invMode == SHUFFLE) {
			setOutput<InvOut1Out>(outputHighVoltageLevel);
			setLED<Inv1Light>(1.f);
			clockInvOut.lastEventInTicks = timestamp;
		}
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	static constexpr float outputHighVoltageLevel = 5.0f;
	static constexpr float triggerLengthMinimumInS = 0.005f;
	
	static constexpr std::array<factorType_t,21> clockFactor = {{
		{DIV, 32},
		{DIV, 32},
		{DIV, 16},
		{DIV, 8},
		{DIV, 7},
		{DIV, 6},
		{DIV, 5},
		{DIV, 4},
		{DIV, 3},
		{DIV, 2},
		{MULT, 1},
		{MULT, 2},
		{MULT, 3},
		{MULT, 4},
		{MULT, 5},
		{MULT, 6},
		{MULT, 7},
		{MULT, 8},
		{MULT, 12},
		{MULT, 16},
		{MULT, 16}
	}};

private:
	float timeStepInS;
	uint32_t triggerLengthMinimumInTicks;
	uint32_t triggerLengthInTicks;
	uint32_t ticks;
	uint32_t clockInCounter;
	factorType_t factor;
	float pulsewidth;
	invMode_t invMode;
	outputState_t clockOutState;

	struct clockMeasures
	{
		std::optional<uint32_t> lastEventInTicks;
		std::optional<uint32_t> periodInTicks;
	};

	clockMeasures clockIn;
	clockMeasures clockOut;
	clockMeasures clockInvOut;

private:
	FlipFlop triggerDetector;
	EdgeDetector triggerEdgeDetector;
};

} // namespace MetaModule
