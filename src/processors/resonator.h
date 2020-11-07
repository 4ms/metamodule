#pragma once

#include "processors/audio_processor.hh"
#include "util/math.hh"
#include "util/math_tables.hh"
#include "processors/resonator_caltable.h"

using namespace MathTools;

class Resonator : public AudioProcessor {

	struct Coefs {
		float c0;
		float c1;
		float c2;
	};
	using Buffer = float[3];

	Coefs coefs[2];
	Buffer buff[2] = {{0,0,0},{0,0,0}};
	float tap_volume[2];

	float run_filter(float input, Coefs &c, Buffer &b)
	{
		b[2] = (c.c0 * b[1] + c.c1 * b[0]) - c.c2 * input;
		b[0] = b[0] - (c.c1 * b[2]);
		b[1] = b[2];
		return  b[1];
	}

public:
	virtual float update(float input)
	{
		float out_a = run_filter(input, coefs[0], buff[0]);
		float out_b = run_filter(out_a, coefs[1], buff[1]);

		float output = (tap_volume[0] * out_a) - out_b; // output of filter two needs to be inverted to avoid phase cancellation
		return output;
	}

	Resonator()
	{
		freq = 50.f;
		res = 0.05f;
		calc_coefs();
	}

	virtual void set_param(int param_id, float val)
	{
		const float minFreq = 20.0f;
		const float maxFreq = 15000.f;
		if (param_id == 0) {
			freq = expTable.interp(val);
			freq = map_value(freq, 1.f, 32.f, minFreq, maxFreq);
		}
		else if (param_id == 1) {
			res = val;
		}
		calc_coefs();
	}
	virtual void set_samplerate(float sr)
	{
		samplerate = sr;
		calc_coefs();
	}

	void calc_coefs() {
		// Q/RESONANCE: c0 = 1 - 2/(decay * samplerate), where decay is around 0.01 to 4.0
		// Todo: samplerate should be in this calculation
		float res0 = MathTools::constrain(res * 2.f, 0.f, 1.f);
		//coefs[0].c0 = 1.003225f - expTable.interp(1.0f - res0) / 310.f; // * 96000/samplerate ??
		coefs[0].c0 = 1.0f - 2.f/(samplerate * ((expTable.closest(res0)-0.9f)/32.f));

		float res1 = res < 0.952f ? 0.244f : (0.244f + (res - 0.952f) * 15.f);
		//coefs[1].c0 = 1.003225f - expTable.closest(1.0f - res1) / 310.f;
		coefs[1].c0 = 1.0f - 2.f/(samplerate * ((expTable.closest(res1)-0.9f)/32.f));

		// FREQ: c1 = 2 * pi * freq / samplerate
		coefs[0].c1 = 2.f * M_PI * freq / samplerate;
		coefs[1].c1 = coefs[0].c1;

		// Volume between 1st and 2nd pass filter taps
		const float balance_min = 0.44f;
		const float balance_max = 0.88f;
		if 	(res < balance_min)
			tap_volume[0] = 1.0f;
		else if (res > balance_max)
			tap_volume[0] = 0.0f;
		else {
			tap_volume[0] = 1.0f - (res - balance_min) / (balance_max - balance_min);
		}
		tap_volume[1] = 1.0f - tap_volume[0];
		tap_volume[1] *= boost_table.closest(res1 - 0.220f);

		const float highfreqboost = 0.4f;
		const float high_res_cut = 0.1f;
		coefs[0].c2 = (highfreqboost * coefs[0].c1) - (high_res_cut * coefs[0].c0) + 0.102f;
		//coefs[0].c2 *= 6.0f;

		coefs[1].c2 = (highfreqboost * coefs[1].c1) - (high_res_cut * coefs[1].c0) + 0.102f;
		coefs[1].c2 *= tap_volume[1];
		//coefs[1].c2 *= 6.0f;
	}

private:
	float samplerate =48000.f;
	float freq;
	float res;

};


