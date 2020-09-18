#pragma once

#include "audio_processor.hh"
#include "math.hh"
#include <cmath>

using namespace MathTools;

class Phaser : public AudioProcessor {
public:
	virtual float update(float input)
	{
		//output = interpolate(input, delay->update(input), 0.5f);
		float output = input;
		return output;
	}

	Phaser()
	{
		//delay = new DelayLine(1000);
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0) {}
		if (param_id == 1) {}
	}
	virtual void set_samplerate(float sr)
	{
		//delay->set_samplerate(sr);
	}

private:
	//DelayLine *delay;
};
