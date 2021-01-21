#pragma once

#include "sys/alloc_buffer.hh"
#include "util/interp_array.hh"
#include "util/math.hh"

template<int maxSamples>
class DelayLine {
public:
	float output = 0;

	DelayLine()
	{
		delayBuffer = new BigAlloc<InterpArray<float, maxSamples>>;
		for (int i = 0; i < maxSamples; i++) {
			(*delayBuffer)[i] = 0;
		}
	}

	void set_delay_samples(float delay)
	{
		delaySamples = delay;
	}

	virtual void set_samplerate(float sr) {}

	// calling 6 updates in a loop is 6.7us using float readIndex and interpolating
	// with int readIndex (just checking it's not negative), it's 5.6us
	float update(float input)
	{
		// ~13%
		(*delayBuffer)[writeIndex] = input;

		// ~2%
		readIndex = writeIndex - delaySamples;
		if (readIndex < 0)
			readIndex += maxSamples;

		// ~2.7%
		output = delayBuffer->interp_by_index(readIndex);

		// ~2%
		writeIndex++;
		if (writeIndex == maxSamples)
			writeIndex = 0;

		return output;
	}

private:
	BigAlloc<InterpArray<float, maxSamples>> *delayBuffer;
	unsigned int writeIndex = 0;
	float readIndex = 0;
	float delaySamples = 1.0f;
};
