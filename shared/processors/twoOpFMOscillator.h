#pragma once

#include "util/math.hh"
#include "util/math_tables.hh"

class TwoOpFM {
private:
	static constexpr uint32_t max_ = 0xFFFFFFFF;

	uint32_t phaccu[2];
	int sampleRate = 48000;
	float sinOut[2];

public:
	float modAmount = 0;
	float shape = 0;
	float mix = 0;
	float priFreq = 1;
	float secFreq = 1;

	TwoOpFM() {}

	void set_frequency(int channel, float inputFreq)
	{
		if (channel == 0)
			priFreq = inputFreq;
		else if (channel == 1) {
			secFreq = inputFreq;
		}
	}

	// Todo: store inv_samplerate, not sampleRate
	float update(void)
	{
		auto inv_samplerate = max_ / sampleRate;

		uint32_t increment = secFreq * static_cast<float>(inv_samplerate);
		phaccu[1] += increment;
		sinOut[1] = sinTable[((phaccu[1] + max_ / 2) & max_) >> 21];

		sinOut[0] = sinTable[phaccu[0] >> 21];
		auto freqCalc = (priFreq + (sinOut[1] * modAmount * 4000.0f));
		uint32_t increment2 = freqCalc * static_cast<float>(inv_samplerate);
		phaccu[0] += increment2;

		auto sqrOut1 = (phaccu[0] > (max_ / 2)) * 2.0f - 1.0f;
		auto sqrOut2 = (phaccu[1] > (max_ / 2)) * 2.0f - 1.0f;

		auto finalWav1 = MathTools::interpolate(sinOut[0], sqrOut1, shape);
		auto finalWav2 = MathTools::interpolate(sinOut[1], sqrOut2, shape);
		return (MathTools::interpolate(finalWav1, finalWav2, mix));
	}

	void set_samplerate(float sr)
	{
		sampleRate = sr;
	}
};
