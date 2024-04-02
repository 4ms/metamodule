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

private:
	void packUnpackBlockBuffers()
	{
		auto clamp = [](auto val, auto max_amplitude)
		{
			return std::min(std::max(val, -max_amplitude), max_amplitude);
		};

		// TODO: this is mono to stereo
		auto monoInput = int16_t(clamp(getInput<Mapping::AudioInput>().value_or(0) / AudioInputFullScaleInVolt, 1.0f) * 32767.0 );
		inBlock[audioBufferFillCount] = {monoInput, monoInput};

		// TODO: this is stereo to mono
		setOutput<Mapping::AudioOutput>((float(outBlock[audioBufferFillCount].chan[0]) + float(outBlock[audioBufferFillCount].chan[1])) / 2 / 32768.0 * AudioOutputFullScaleInVolt);		
	}

private:
	static constexpr float AudioInputFullScaleInVolt  = 22.0f;
	static constexpr float AudioOutputFullScaleInVolt = 17.0f;

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