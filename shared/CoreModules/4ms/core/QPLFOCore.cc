#include "CoreModules/SmartCoreProcessor.hh"
#include "CoreModules/moduleFactory.hh"
#include "info/QPLFO_info.hh"
#include "qplfo/LFO.h"
#include "helpers/EdgeDetector.h"

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
			, lfo(PulseWidthInS * get_timestamp_frequency())
		{
		}

		void update()
		{
			auto now = get_timestamp();

			if (tapEdge(getState<Mapping::PingButton>() == MomentaryButton::State_t::PRESSED))
			{
				if (lastTapTime)
				{
					lfo.setPeriodLength(now - *lastTapTime);
				}
				lastTapTime = now;
			}

			lfo.setSkew(getState<Mapping::SkewKnob>());
			lfo.update(now);

			setLED<Mapping::PingButton>(lfo.getPhase() > 0.5f);

			if (getState<Mapping::OnButton>() == LatchingButton::State_t::DOWN)
			{
				setLED<Mapping::OnButton>(true);

				auto outValue = lfo.getValue();

				setOutput<Mapping::Out>(outValue * 10.0f);
			}
			else
			{
				setLED<Mapping::OnButton>(false);
				setOutput<Mapping::Out>(0.0f);
			}
		}

		void set_samplerate(float sr) {
		}


	private:
		QPLFOCore* parent;
		QPLFO::LFO lfo;
		EdgeDetector tapEdge;

		std::optional<uint32_t> lastTapTime;

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
	static constexpr float PulseWidthInS = 10e-3f;

	// Boilerplate to auto-register in ModuleFactory
	// clang-format off
	static std::unique_ptr<CoreProcessor> create() { return std::make_unique<ThisCore>(); }
	static inline bool s_registered = ModuleFactory::registerModuleType(Info::slug, create, ModuleInfoView::makeView<Info>());
	// clang-format on

private:
};

} // namespace MetaModule
