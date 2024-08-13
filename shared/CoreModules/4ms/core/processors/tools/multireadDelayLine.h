#pragma once
#include "util/interp_array.hh"
#include "util/math.hh"

template<long maxSamples>
class MultireadDelayLine {
public:
	MultireadDelayLine() {
		for (int i = 0; i < maxSamples; i++) {
			delayBuffer[i] = 0;
		}
	}

	virtual void set_samplerate(float sr) {
	}

	// calling 6 updates in a loop is 6.7us using float readIndex and interpolating
	// with int readIndex (just checking it's not negative), it's 5.6us
	void updateSample(float input) {
		delayBuffer[writeIndex] = input;
	}

	void incrementWriteHead() {
		writeIndex++;
		if (writeIndex >= maxSamples)
			writeIndex = 0;
	}

	float readSample(float delaySamples) {
		float readIndex = writeIndex - delaySamples;
		if (readIndex < 0)
			readIndex += maxSamples;

		return delayBuffer.interp_by_index(readIndex);
	}

private:
	InterpArray<float, maxSamples> delayBuffer;
	unsigned long writeIndex = 0;
};
