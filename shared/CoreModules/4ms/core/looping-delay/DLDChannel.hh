#include "src/flags.hh"
#include "src/controls.hh"
#include "src/params.hh"
#include "src/looping_delay.hh"

namespace MetaModule
{

template <class Parent, class Mapping>
class DLDChannel
{
private:
	template<Parent::Info::Elem EL>
	void setOutput(auto val)
	{
		return parent->template setOutput<EL>(val);
	}

	template<Parent::Info::Elem EL>
	auto getInput()
	{
		return parent->template getInput<EL>();
	}

	template<Parent::Info::Elem EL, typename VAL>
	void setLED(const VAL &value)
	{
		return parent->template setLED<EL>(value);
	}

	template<Parent::Info::Elem EL>
	auto getState()
	{
		return parent->template getState<EL>();
	}

private:
	Parent* parent;

public:
	DLDChannel(Parent* parent_)
		: parent(parent_)
		, params(controls, flags)
		, looping_delay(params, flags)
		, audioBufferFillCount(0)
		{
			for (auto& sample : outBlock)
			{
				for (auto& channel : sample.chan)
				{
					channel = 0;
				}
			}
		}

    void update()
    {
		params.timer.inc();

		sideloadDrivers();

		if (audioBufferFillCount == inBlock.size())
		{
			audioBufferFillCount = 0;

			params.update();
			looping_delay.update(inBlock, outBlock);		
		}

		packUnpackBlockBuffers();
		audioBufferFillCount++;
    }

    void set_samplerate(float sr) {
		// TODO: implement
    }

public:
	struct ModuleIO_t
	{
		bool pingButtonIn;
		bool pingJackIn;
		bool pingOut;
		bool clockOut;
	};
	ModuleIO_t io;

private:
	void sideloadDrivers()
	{
		auto ConvertKnobFunc = [](float val) -> int16_t
		{
			return int16_t(std::clamp(val, 0.0f, 1.0f) * 32767.0f);
		};

		auto Convert3WaySwitchStateFunc = [](auto inState) -> LDKit::Mocks::SwitchPos
		{
			switch (inState)
			{
				case Toggle3pos::State_t::DOWN: return LDKit::Mocks::SwitchPos::Down;
				case Toggle3pos::State_t::UP: return LDKit::Mocks::SwitchPos::Up;
				case Toggle3pos::State_t::CENTER: return LDKit::Mocks::SwitchPos::Center;
				default: return LDKit::Mocks::SwitchPos::Invalid;
			}
		};

		// Knobs
		controls.sideload_pot(LDKit::TimePot,      ConvertKnobFunc(getState<Mapping::TimeKnob>()));
		controls.sideload_pot(LDKit::FeedbackPot,  ConvertKnobFunc(getState<Mapping::FeedbackKnob>()));
		controls.sideload_pot(LDKit::DelayFeedPot, ConvertKnobFunc(getState<Mapping::DelayFeedKnob>()));
		controls.sideload_pot(LDKit::MixPot,       ConvertKnobFunc(getState<Mapping::MixKnob>()));

		// CVs
		controls.sideload_cv(LDKit::TimeCV,      ConvertKnobFunc(getInput<Mapping::TimeInput>().value_or(0)));
		controls.sideload_cv(LDKit::FeedbackCV,  ConvertKnobFunc(getInput<Mapping::FeedbackInput>().value_or(0)));
		controls.sideload_cv(LDKit::DelayFeedCV, ConvertKnobFunc(getInput<Mapping::DelayFeedInput>().value_or(0)));
		// controls.sideload_cv(LDKit::MixCV,       ConvertKnobFunc(getInput<Mapping::MixInput>().value_or(0)));

		// LEDs
		setLED<Mapping::ReverseButton>(controls.rev_led.sideload_get());
		setLED<Mapping::HoldButton>(controls.inf_led.sideload_get());

		 // TODO: this should be a mono color light
		setLED<Mapping::TimeLight>(std::array<float,3>{params.timer.loop_led.sideload_get() ? 1.0f: 0.0f, 0.0f, 0.0f});

		// Buttons
		controls.rev_button.sideload_set(getState<Mapping::ReverseButton>() == MomentaryButton::State_t::PRESSED);
		controls.inf_button.sideload_set(getState<Mapping::HoldButton>() == MomentaryButton::State_t::PRESSED);

		// Trigger Inputs
		controls.rev_jack.sideload_set(getInput<Mapping::ReverseInput>().value_or(0) > TriggerThresholdInVolt);
		controls.inf_jack.sideload_set(getInput<Mapping::HoldInput>().value_or(0) > TriggerThresholdInVolt);

		// Switch
		controls.time_switch.sideload_set(Convert3WaySwitchStateFunc(getState<Mapping::TimeModSwitch>()));

		// Clock outputs
		setOutput<Mapping::LoopOutput>(params.timer.loop_out.sideload_get() * TriggerOutputFullScaleInVolt);

		// Forward to/from module level
		io.pingOut = controls.ping_led.sideload_get();
		io.clockOut = params.timer.clk_out.sideload_get();
		params.timer.ping_jack.sideload_set(io.pingJackIn);
		controls.ping_button.sideload_set(io.pingButtonIn);

	}

private:
	void packUnpackBlockBuffers()
	{
		constexpr float AudioFullScale = ((1<<(AudioStreamConf::SampleBits-1)) -1);

		auto clamp = [](auto val, auto max_amplitude)
		{
			return std::min(std::max(val, -max_amplitude), max_amplitude);
		};

		auto InputConversionFunc = [clamp](auto inputInV) -> int32_t
		{
			float normalized = clamp(inputInV / AudioInputFullScaleInVolt, 1.0f);
			return int32_t(normalized * AudioFullScale);
		};

		auto OutputConversionFunc = [](auto output) -> float
		{
			return float(output) / AudioFullScale * AudioOutputFullScaleInVolt;
		};
		
		inBlock[audioBufferFillCount] = {InputConversionFunc(getInput<Mapping::AudioInput>().value_or(0)), InputConversionFunc(getInput<Mapping::ReturnInput>().value_or(0))};

		setOutput<Mapping::AudioOutput>(OutputConversionFunc(outBlock[audioBufferFillCount].chan[0]));
		setOutput<Mapping::SendOutput>(OutputConversionFunc(outBlock[audioBufferFillCount].chan[1]));
	}

private:
	static constexpr float AudioInputFullScaleInVolt    = 22.0f;
	static constexpr float AudioOutputFullScaleInVolt   = 17.0f;
	static constexpr float TriggerThresholdInVolt       = 0.1f;
	static constexpr float TriggerOutputFullScaleInVolt = 5.0f;

private:
	LDKit::Controls controls;
	LDKit::Flags flags;
	LDKit::Params params;
	LDKit::LoopingDelay looping_delay;

private:
	AudioStreamConf::AudioInBlock inBlock;
	AudioStreamConf::AudioOutBlock outBlock;
	std::size_t audioBufferFillCount;

}; 

}