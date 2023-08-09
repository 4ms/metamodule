#pragma once
#include "util/interp_array.hh"
#include "util/math.hh"

template<int maxSamples>
class DelayLine {
public:
	float output = 0;

	DelayLine() {
		for (int i = 0; i < maxSamples; i++) {
			delayBuffer.set(i, 0);
		}
	}

	void set_delay_samples(float delay) {
		delaySamples = delay;
	}

	virtual void set_samplerate(float sr) {
	}

	float update(float input) {
		delayBuffer.set(writeIndex, input);

		readIndex = writeIndex - delaySamples;
		if (readIndex < 0)
			readIndex += maxSamples;

		output = delayBuffer.interp_by_index(readIndex);

		writeIndex++;
		if (writeIndex == maxSamples)
			writeIndex = 0;

		return output;
	}

private:
	InterpArray<float, maxSamples> delayBuffer;
	unsigned int writeIndex = 0;
	float readIndex = 0;
	float delaySamples = 1.0f;
};
