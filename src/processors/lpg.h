#pragma once
#include "audio_processor.hh"
#include "lpf.h"
#include "tools/expDecay.h"
#include "vca.h"

class LPG : public AudioProcessor {
public:
	virtual float update(float input)
	{
		float slewedControl = expDecay.update(levelControl);
		lpf.set_param(0, slewedControl);
		return (lpf.update(input) * slewedControl);
	}

	LPG()
	{
		levelControl = 1;
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {
			levelControl = val;
		}
		if (param_id == 1) {
			expDecay.decayTime = map_value(val, 0.F, 1.F, 10.F, 1000.0F);
		}
	}
	virtual void set_samplerate(float sr)
	{
		lpf.set_samplerate(sr);
		expDecay.set_samplerate(sr);
	}

private:
	LowPassFilter lpf;
	ExpDecay expDecay;
	float levelControl;
};
