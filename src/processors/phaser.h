#pragma once

#include "audio_processor.hh"
#include <cmath>

using namespace MathTools;

class Phaser : public AudioProcessor {
public:
	virtual float update(float input)
	{
		float output = 0;
		return output;
	}

	Phaser()
	{
	}

	virtual void set_param(int param_id, float val)
	{
		if (param_id == 0)
			//
			if (param_id == 1)
		//
	}
	virtual void set_samplerate(float sr)
	{
	}

	//~LowPassFilter() {}

private:
};
