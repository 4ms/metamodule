#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/QPLFO_info.hh"
#include "qplfo/LFO.h"
#include "qplfo/TapPing.h"
#include "helpers/EdgeDetector.h"
#include "helpers/Gestures.h"

#include <chrono>

namespace MetaModule
{

class QPLFOCore : public SmartCoreProcessor<QPLFOInfo> {
	using Info = QPLFOInfo;
	using ThisCore = QPLFOCore;
	using enum Info::Elem;

public:
	template<Info::Elem EL>
	void setOutput(auto val)
	{
		return SmartCoreProcessor<Info>::setOutput<EL>(val);
	}

	template<Info::Elem EL>
	auto getInput()
	{
		return SmartCoreProcessor<Info>::getInput<EL>();
	}

	template<Info::Elem EL, typename VAL>
	void setLED(const VAL &value)
	{
		return SmartCoreProcessor<Info>::setLED<EL>(value);
	}

	template<Info::Elem EL>
	auto getState()
	{
		return SmartCoreProcessor<Info>::getState<EL>();
	}

private:
	template <class Mapping>
	class Channel
	{
	private:
		template<Info::Elem EL>
		void setOutput(auto val)
		{
			return parent->setOutput<EL>(val);
		}

		template<Info::Elem EL>
		auto getInput()
		{
			return parent->getInput<EL>();
		}

		template<Info::Elem EL, typename VAL>
		void setLED(const VAL &value)
		{
			return parent->setLED<EL>(value);
		}

		template<Info::Elem EL>
		auto getState()
		{
			return parent->getState<EL>();
		}

	public:
		Channel(QPLFOCore* parent_)
			: parent(parent_)
			, lfo(PulseWidthInS)
			, tapLongPress(2.0f)
		{
		}

		void update()
		{
			ticks++;

			auto resetIn = getInput<Mapping::ResetIn>().value_or(0);

			if (auto pingInput = getInput<Mapping::PingJackIn>(); pingInput)
			{
				//ping input based triggering
				auto isPingHigh = *pingInput > TriggerThresholdInV;

				if (extClockEdge(isPingHigh))
				{
					if (lastExtClockTime)
					{
						lfo.setPeriodLength((ticks - *lastExtClockTime) * timeStepInS);
						//don't start in "floating reset mode"
						if(resetIn < TriggerThresholdInV)
						{
							lfo.start();
						}
					}
					lastExtClockTime = ticks;
				}

				setLED<Mapping::PingButton>(isPingHigh);				
			}
			else
			{
				//tap based triggering
				if (tapLongPress(getState<Mapping::PingButton>() == MomentaryButton::State_t::PRESSED))
				{
					tapPing.deactivateOuput();
				}

				tapPing.inputButton(ticks, getState<Mapping::PingButton>() == MomentaryButton::State_t::PRESSED);

				if(auto tapPeriod = tapPing.getPeriod()) 
				{
					lfo.setPeriodLength(*tapPeriod * timeStepInS);
				}

				//don't start in "floating reset mode"
				if(tapEdge(tapPing.updateTapOut(ticks)) && (resetIn < TriggerThresholdInV))
				{
					lfo.start();
				} 

				if (getState<Mapping::PingButton>() == MomentaryButton::State_t::PRESSED) 
				{
					setLED<Mapping::PingButton>(1.f);
				} 
				else 
				{
					if (lfo.hasPeriodLength())
					{
						setLED<Mapping::PingButton>(lfo.getPhase() < 0.5f);					
					}
					else
					{
						setLED<Mapping::PingButton>(0.f);
					}
				}
				
			}

			//reset based triggering
			if (resetEdge(resetIn > TriggerThresholdInV))
			{
				if(lfo.isRunning() == true)
				{
					lfo.reset();
				}
				else
				{
					lfo.start();
				}
			}

			//cycle in "floating reset mode"
			if(resetIn > TriggerThresholdInV)
			{
				if(lfo.isRunning() != true)
				{
					lfo.start();
				}
			}

			auto onButtonState = getState<Mapping::OnButton>();

			if(getState<Mapping::FireOnUnmute>() == 1)
			{
				if(onButtonState == LatchingButton::State_t::DOWN && previousOnButtonState == LatchingButton::State_t::UP)
				{
					lfo.start();
				}
			}

			previousOnButtonState = onButtonState;

			auto skewCV = getInput<Mapping::SkewCVIn>().value_or(0) / CVInputRangeInV;
			auto skew = std::clamp(getState<Mapping::SkewKnob>() + skewCV, 0.0f, 1.0f);
			lfo.setSkew(skew);

			lfo.update(timeStepInS);

			if (getState<Mapping::OnButton>() == LatchingButton::State_t::DOWN)
			{
				setLED<Mapping::OnButton>(1.f);

				auto outValue = lfo.getValue();

				if(getState<OutputRangeAltParam>() == 0)
				{
					setOutput<Mapping::Out>(outValue * 10.0f);
				}
				else
				{
					setOutput<Mapping::Out>(outValue * 10.0f - 5.f);
				}

				// TODO: does this need to be changed for bipolar output
				setLED<Mapping::LED>(outValue);
			}
			else
			{
				setLED<Mapping::OnButton>(0.f);
				setOutput<Mapping::Out>(0.0f);

				// TODO: does this need to be changed for bipolar output
				setLED<Mapping::LED>(0.f);
			}

		}

		void set_samplerate(float sr) {
			timeStepInS = 1.f / sr;

			tapLongPress.set_samplerate(sr);
		}


	private:
		QPLFOCore* parent;
		QPLFO::LFO lfo;
		LongPressDetector tapLongPress;
		EdgeDetector extClockEdge;
		EdgeDetector resetEdge;
		EdgeDetector tapEdge;
		TapPing tapPing;

		std::optional<uint32_t> lastTapTime;
		std::optional<uint32_t> lastExtClockTime;

		LatchingButton::State_t previousOnButtonState = LatchingButton::State_t::DOWN;

		float timeStepInS = 1.f / 48000.f;
		uint32_t ticks = 0;
	};

private:
	struct MappingA
	{
		const static auto SkewKnob   = Skew1Knob;
		const static auto PingButton = Ping1Button;
		const static auto OnButton   = On1Button;
		const static auto PingJackIn = Ping1JackIn;
		const static auto SkewCVIn   = Skew1CvIn;
		const static auto ResetIn    = Reset1In;
		const static auto Out        = Out1Out;
		const static auto LED        = Led1Light;
		const static auto FireOnUnmute = FireOnUnmuteCh1AltParam;
	};

	struct MappingB
	{
		const static auto SkewKnob   = Skew2Knob;
		const static auto PingButton = Ping2Button;
		const static auto OnButton   = On2Button;
		const static auto PingJackIn = Ping2JackIn;
		const static auto SkewCVIn   = Skew2JackIn;
		const static auto ResetIn    = Reset2In;
		const static auto Out        = Out2Out;
		const static auto LED        = Led2Light;
		const static auto FireOnUnmute = FireOnUnmuteCh2AltParam;
	};

	struct MappingC
	{
		const static auto SkewKnob   = Skew3Knob;
		const static auto PingButton = Ping3Button;
		const static auto OnButton   = On3Button;
		const static auto PingJackIn = Ping3JackIn;
		const static auto SkewCVIn   = Skew3JackIn;
		const static auto ResetIn    = Reset3In;
		const static auto Out        = Out3Out;
		const static auto LED        = Led3Light;
		const static auto FireOnUnmute = FireOnUnmuteCh3AltParam;
	};

	struct MappingD
	{
		const static auto SkewKnob   = Skew4Knob;
		const static auto PingButton = Ping4Button;
		const static auto OnButton   = On4Button;
		const static auto PingJackIn = Ping4JackIn;
		const static auto SkewCVIn   = Skew4JackIn;
		const static auto ResetIn    = Reset4In;
		const static auto Out        = Out4Out;
		const static auto LED        = Led4Light;
		const static auto FireOnUnmute = FireOnUnmuteCh4AltParam;
	};	

	Channel<MappingA> channelA;
	Channel<MappingB> channelB;
	Channel<MappingC> channelC;
	Channel<MappingD> channelD;

	friend Channel<MappingA>;
	friend Channel<MappingB>;
	friend Channel<MappingC>;
	friend Channel<MappingD>;

public:
	QPLFOCore()
		: channelA(this), channelB(this), channelC(this), channelD(this)
	{
	}

	void update() override {
		channelA.update();
		channelB.update();
		channelC.update();
		channelD.update();
	}

	void set_samplerate(float sr) override {
		channelA.set_samplerate(sr);
		channelB.set_samplerate(sr);
		channelC.set_samplerate(sr);
		channelD.set_samplerate(sr);
	}

	static uint32_t get_timestamp()
	{
		return uint32_t(std::chrono::steady_clock::now().time_since_epoch().count());
	}

	static float get_timestamp_frequency()
	{
		return float(std::chrono::steady_clock::period::den) / float(std::chrono::steady_clock::period::num);
	}

private:
	static constexpr float PulseWidthInS       = 10e-3f;
	static constexpr float TriggerThresholdInV = 2.5f;
	static constexpr float CVInputRangeInV     = 10.0f;

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
	float timeStepInS = 1.f / 48000.f;
};

} // namespace MetaModule
