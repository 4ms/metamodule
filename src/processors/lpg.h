#pragma once
#include "audio_processor.hh"
#include "lpf.h"
#include "vca.h"

class LPG : public AudioProcessor {
public:
	virtual float update(float input)
	{
		float slewedControl = expDecay.update(levelControl);
		lpf.set_param(0, slewedControl);
		vca.set_param(0, slewedControl);
		return (lpf.update(input));
	}

	LPG()
	{
		expDecay.decayTime = 50;
		lpf.set_param(0, 1);
		lpf.set_param(1, 0);
		vca.set_param(0, 1);
		vca.set_param(1, 0);
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			levelControl = val;
		}
		if (param_id == 1)
			expDecay.decayTime = map_value(val, 0.F, 1.F, 10.F, 300.F);
	}
	virtual void set_samplerate(float sr)
	{
		lpf.set_samplerate(sr);
		expDecay.set_samplerate(sr);
	}

private:
	VCA vca;
	LowPassFilter lpf;
	ExpDecay expDecay;
	float levelControl;
};

