#pragma once

#include "util/math.hh"
#include "util/math_tables.hh"

class FMOsc {
private:
	float phaccu = 0;
	float sampleRate = 48000;

public:
	float frequency;
	float waveOut = 0;
	float sinOut = 0;

	float modInput = 0;
	float modAmount = 0;

	void update()
	{

		phaccu += frequency / sampleRate;
		if (phaccu >= 1.0f) {
			phaccu -= 1.0f;
		}

		float tempPhase = phaccu + modInput * modAmount;
		if (tempPhase >= 1) {
			tempPhase = tempPhase - (long)tempPhase;
		}
		if (tempPhase < 0) {
			tempPhase = tempPhase + (1 - (long)tempPhase);
		}
		sinOut = sinTable.interp(tempPhase);
	}

	void set_samplerate(float sr)
	{
		sampleRate = sr;
	}
};

class TwoOpFM {
private:
	FMOsc osc[2];
	const float ratioTable[8] = {0.0625f, 0.125f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f, 8.0f};

public:
	float freq = 40;
	int ratioCoarse = 1;
	float ratioFine = 1;
	float modAmount = 0;
	TwoOpFM() {}

	float update(void)
	{
		osc[1].frequency = freq * (ratioTable[ratioCoarse] * ratioFine);
		osc[1].update();

		osc[0].modInput = osc[1].sinOut;
		osc[0].modAmount = modAmount;
		osc[0].frequency = freq;
		osc[0].update();

		return osc[0].waveOut;
	}

	void set_samplerate(float sr)
	{
		for (int i = 0; i < 2; i++) {
			osc[i].set_samplerate(sr);
		}
	}
};
