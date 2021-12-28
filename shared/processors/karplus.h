#pragma once

#include "tools/dcBlock.h"
#include "tools/delayLine.h"
#include "tools/kneeCompress.h"
#include <cmath>

class Karplus {
	static constexpr int taps = 6;

public:
	float update(float input) {
		float output = input * taps;

		//NEON note: cannot vectorize because "data ref analysis failed"
		output += delayLine[0].update(input + delayLine[taps - 1].output * feedback);
		for (int i = 1; i < taps; i++) {
			output += delayLine[i].update(input + delayLine[i].output * feedback);
		}

		output = dcBlock.update(output / (taps * 2.f));
		return output;
	}

	Karplus() {
		set_samplerate(48000.0f);
	}
	void set_samplerate(float sr) {
		sampleRate = sr;
	}

	void set_frequency(float inFreq) {
		apPeriods[0] = 1.0f / inFreq;
		delayLine[0].set_delay_samples(periodToSamples(apPeriods[0]));
		update_delay_samples();
	}

	void set_spread(float _spread) {
		spread = MathTools::map_value(_spread, 0.0f, 1.0f, 1.001f, 1.01f);
		update_delay_samples();
	}

	void set_decay(float val) {
		feedback = MathTools::map_value(val, 0.0f, 1.0f, 0.98f, 1.0f);
	}

private:
	alignas(16) float apPeriods[taps];

	alignas(16) DelayLine<2400> delayLine[taps];

	float sampleRate = 48000;
	float spread = 1.0f;
	float feedback = 0.995f;

	float periodToSamples(float period) {
		return (period * sampleRate);
	}
	void update_delay_samples() {
		//NEON note: cannot vectorize this because of dependence between apPeriods[x] and [x-1]
		for (int i = 1; i < taps; i++) {
			apPeriods[i] = apPeriods[i - 1] / spread;
			delayLine[i].set_delay_samples(periodToSamples(apPeriods[i]));
		}
	}

	DCBlock dcBlock;
};
