#pragma once

#include "util/big_buffer.hh"
#include "util/interp_array.hh"
#include "util/math.hh"

template<int maxSamples>
class DelayLine {
public:
	float output = 0;

	DelayLine()
	{
		for (int i = 0; i < maxSamples; i++) {
			delayBuffer[i] = 0;
		}
	}

	void set_delay_samples(float delay)
	{
		delaySamples = delay;
	}

	virtual void set_samplerate(float sr) {}

	float update(float input)
	{
		delayBuffer[writeIndex] = input;

		readIndex = writeIndex - delaySamples;
		if (readIndex < 0)
			readIndex += maxSamples;

		output = delayBuffer.get().interp_by_index(readIndex);

		writeIndex++;
		if (writeIndex == maxSamples)
			writeIndex = 0;

		return output;
	}

private:
	BigBuffer<InterpArray<float, maxSamples>> delayBuffer;
	unsigned int writeIndex = 0;
	float readIndex = 0;
	float delaySamples = 1.0f;
};
