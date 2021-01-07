#pragma once
#include "audio_processor.hh"
#include "lpf.h"
#include "tools/expDecay.h"
#include "tools/parameter.h"

class LowPassGate {
public:
	Parameter<float> level;
	Parameter<float> decayTime;

	Parameter<float> sampleRate;
	float update(float input)
	{
		if (sampleRate.isChanged()) {
			lpf.sampleRate.setValue(sampleRate.getValue());
			expDecay.set_samplerate(sampleRate.getValue());
		}

		slewedControl = expDecay.update(level.getValue());

		if (decayTime.isChanged() || level.isChanged()) {
			expDecay.decayTime = decayTime.getValue();
			lpf.cutoff.setValue(map_value(slewedControl, 0.0f, 1.0f, 20.0f, 20000.0f));
		}

		return (lpf.update(input) * slewedControl);
		;
	}

	LowPassGate()
	{
		level.setValue(1.0f);
		lpf.q.setValue(1);
		lpf.cutoff.setValue(20000);
		expDecay.decayTime = 100.0f;
	}

private:
	LowPassFilter lpf;
	ExpDecay expDecay;

	float slewedControl = 0;
};
