#pragma once

#include "util/math.hh"
#include "util/math_tables.hh"

class TwoOpFM {
private:
	static constexpr uint32_t max_ = 0xFFFFFFFF;

	uint32_t phaccu[2];
	const float ratioTable[8] = {0.0625f, 0.125f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f, 8.0f};
	int sampleRate = 48000;
	float sinOut[2];
	uint32_t increment[2];

	float currentFreq = 1;
	float lastFreq = 1;

	float currentRatio = 1;
	float lastRatio = 1;

	void updateIncrement()
	{
		increment[0] = currentFreq * (currentRatio) * (max_ / sampleRate);
	}

public:
	int ratioCoarse = 4;
	float ratioFine = 1;
	float modAmount = 0;
	float shape = 0;

	TwoOpFM() {}

	void set_frequency(float _freq)
	{
		lastFreq = currentFreq;
		currentFreq = _freq;
		if (currentFreq != lastFreq) {
			updateIncrement();
		}
	}

	void updateRatio()
	{
		lastRatio = currentRatio;
		currentRatio = ratioTable[ratioCoarse] * ratioFine;
		if (currentRatio != lastRatio) {
			updateIncrement();
		}
	}

	float update(void)
	{
		updateRatio();
		phaccu[0] += increment[0];
		sinOut[0] = sinTable[phaccu[0] >> 21];
		auto freqCalc = (currentFreq + (sinOut[0] * modAmount * 4000.0f));
		increment[1] = freqCalc * (max_ / sampleRate);
		phaccu[1] += increment[1];

        
		sinOut[1] = sinTable[((phaccu[1]+max_/2)&max_) >> 21];
        auto sqrOut = (phaccu[1]>(max_/2))*2.0f-1.0f;
		return (MathTools::interpolate(sinOut[1],sqrOut,shape));
	}

	void set_samplerate(float sr)
	{
		sampleRate = sr;
	}
};
