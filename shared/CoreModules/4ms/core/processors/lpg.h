#pragma once
#include "lpf.h"
#include "processors/tools/expDecay.h"
#include "util/parameter.h"
#include "util/math.hh"

using namespace MathTools;

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
			float controlSignal = map_value(slewedControl, 0.0f, 1.0f, -1.0f,1.0f);
			lpf.cutoff.setValue(523.25f*setPitchMultiple(controlSignal));
		}

		return (lpf.update(input) * slewedControl);
		;
	}

	LowPassGate()
	{
		level.setValue(1.0f);
		lpf.q.setValue(1);
		lpf.cutoff.setValue(20000);
		sampleRate.setValue(48000);
		expDecay.decayTime = 100.0f;
	}

private:
	LowPassFilter lpf;
	ExpDecay expDecay;

	float slewedControl = 0;
};
