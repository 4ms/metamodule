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
	float priFreq=1;
	float secFreq=1;

	TwoOpFM() {}

	void set_frequency(int channel, float inputFreq)
	{
		if(channel == 0)
		priFreq = inputFreq;
		else if (channel ==1)
		{
			secFreq=inputFreq;
		}
		
	}

	float update(void)
	{
		phaccu[1] += secFreq * (max_/sampleRate);
		sinOut[1] = sinTable[((phaccu[1] + max_ / 2) & max_) >> 21];


		sinOut[0] = sinTable[phaccu[0] >> 21];
		auto freqCalc = (priFreq + (sinOut[1] * modAmount * 4000.0f));
		phaccu[0] += freqCalc*(max_/sampleRate);

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
