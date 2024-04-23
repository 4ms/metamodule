#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/MPEG_info.hh"

#include "mpeg/PingGenerator.h"
#include "mpeg/ClockDivMult.h"
#include "mpeg/PingableEnvelope.h"

#include "helpers/EdgeDetector.h"
#include "helpers/FlipFlop.h"
#include "helpers/Gestures.h"

namespace MetaModule
{

class MPEGCore : public SmartCoreProcessor<MPEGInfo> {
	using Info = MPEGInfo;
	using ThisCore = MPEGCore;
	using enum Info::Elem;

public:
	MPEGCore() 
		: mode(SYNC), ticks(0), triggerPing(1.0f, 2.0f), tapLongPress(2.f), isCycling(false), phaseOffset(0.f), startedWhileCycling(false), startedByTrigger(false), armQuantizedTrigger(false), triggerIn(lowerThresholdTrigInInV, risingEdgeThresholdInV)
	{

	};

	void update() override {
		ticks++;

		if (cycleButtonRisingEdge(getState<CycleButton>() == LatchingButton::State_t::DOWN))
		{
			isCycling = true;
		}
		else if (cycleButtonFallingEdge(getState<CycleButton>() == LatchingButton::State_t::DOWN))
		{
			isCycling = false;
		}

		auto cycleInput = getInput<CycleTrigIn>();
		if (cycleInput.has_value())
		{
			if (cycleJackRisingEdge(*cycleInput > risingEdgeThresholdInV))
			{
				isCycling = !isCycling;

				if (getState<CycleJackModeAltParam>() == 1)
				{
					mode = SYNC;
				}
			}
			else if (cycleJackFallingEdge(*cycleInput > risingEdgeThresholdInV))
			{
				if (getState<CycleJackModeAltParam>() != 2)
				{
					isCycling = !isCycling;
				}
			}
		}

		if (auto triggerSignal = getInput<TriggerIn>(); triggerSignal.has_value())
		{
			auto triggerJackMode = getState<TrigJackModeAltParam>();
			auto triggerFlipFlop = triggerIn(*triggerSignal);

			if (triggerInRisingEdge(triggerFlipFlop))
			{
				if (triggerJackMode != 2)
				{
					//async gate and trigger
					env.start();
					startedByTrigger = true;

					mode = ASYNC;
				}
				else
				{
					//re-phasing trigger
					if (clockDivMult.isDividing())
					{
						clockDivMult.rePhase();
					}
				}
			}

			if (triggerJackMode == 1)
			{
				env.setHold(triggerFlipFlop);
			}

			if (triggerJackMode == 2 && triggerFlipFlop == true)
			{
				//arm quantized trigger
				armQuantizedTrigger = true;
				mode = SYNC;
			}
		}

		if (cycleEdge(isCycling) && mode == ASYNC)
		{
			env.start();
			startedWhileCycling = isCycling;
		}

		if (isCycling && mode == ASYNC && !env.isRunning())
		{
			env.start();
			startedWhileCycling = isCycling;
		}


		if (tapEdge(getState<PingButton>() == MomentaryButton::State_t::PRESSED))
		{
			ping.tap(ticks);
		}

		if(tapLongPress(getState<PingButton>() == MomentaryButton::State_t::PRESSED))
		{
			ping.reset();
		}

		if (auto pingIn = getInput<PingTrigIn>(); pingIn.has_value())
		{
			if (pingEdge(triggerPing(*pingIn)))
			{
				ping.ping(ticks);
			}
		}

		ping.setFreeRunning(getState<FreeNRunningPingAltParam>() == 0);

		ping.update(ticks);

		clockDivMult.setFactor(getState<Div_MultKnob>(), getInput<DivIn>());

		clockDivMult.update((ping.getPhase() > 0.f && ping.getPhase() < 0.5f), ticks);

		auto period = clockDivMult.getOutPeriod();
		if(period.has_value())
		{
			env.setPeriod(*period);
		}

		if(clockEdge(clockDivMult.getPhase() < 0.1f))
		{
			if (mode == SYNC)
			{
				env.start();

				startedWhileCycling = isCycling;

				if (armQuantizedTrigger)
				{
					startedByTrigger = true;
				}
			}
		}

		env.update(ticks);
		if (env.stoppedAfterLastUpdate())
		{
			startedWhileCycling = false;
			startedByTrigger = false;
			armQuantizedTrigger = false;
		}

		if (clockDivMult.getPhase() < 0.5f && clockDivMult.getPhase() > 0.f)
		{
			if (mode == SYNC)
			{
				setLED<PingButton>(cyan);
			}
			else
			{
				setLED<PingButton>(white);
			}
		}
		else
		{
			setLED<PingButton>(off);
		}
		
		setLED<CycleButton>(isCycling);

		float envOutput = 0.f;
		if (isCycling || startedWhileCycling || startedByTrigger)
		{
			envOutput = env.getPhase();
		}
		setOutput<EnvOut>(envOutput);

		setOutput<EofOut>(ping.getPhaseTap() < 0.5f);
		setOutput<_5VEnvOut>(clockDivMult.getPhase() < 0.5f);
	}

	void set_samplerate(float sr) override {
		tapLongPress.set_samplerate(sr);
		clockDivMult.set_samplerate(sr);
	}

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	enum mode_t {ASYNC, SYNC};

	mode_t mode;

	uint32_t ticks;

	bool isCycling;
	float phaseOffset;
	bool startedWhileCycling;
	bool startedByTrigger;
	bool armQuantizedTrigger;

private:
	PingGenerator ping;
	EdgeDetector tapEdge;
	FlipFlop triggerPing;
	EdgeDetector pingEdge;
	LongPressDetector tapLongPress;
	ClockDivMult clockDivMult;
	EdgeDetector clockEdge;
	PingableEnvelope env;
	EdgeDetector cycleJackRisingEdge;
	FallingEdgeDetector cycleJackFallingEdge;
	EdgeDetector cycleButtonRisingEdge;
	FallingEdgeDetector cycleButtonFallingEdge;
	EdgeDetector cycleEdge;
	FlipFlop triggerIn;
	EdgeDetector triggerInRisingEdge;


private:
	static constexpr float lowerThresholdTrigInInV = 1.f;
	static constexpr float risingEdgeThresholdInV = 2.5f;

	static constexpr std::array<float,3> cyan = {0.f, 0.87f, 0.87f};
	static constexpr std::array<float,3> white = {1.0f, 1.0f, 1.0f};
	static constexpr std::array<float,3> off = {0.0f, 0.0f, 0.0f};
};

} // namespace MetaModule
